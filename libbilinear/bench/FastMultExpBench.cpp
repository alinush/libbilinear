/*
 * FastMultExpBench.cpp
 *
 *  Created on: Thursday, September 21st, 2017
 *      Author: alinush
 */


#include "bilinear/Configuration.h"

#include <map>
#include <set>
#include <vector>
#include <string>
#include <cassert>
#include <memory>
#include <stdexcept>

#include "xutils/Log.h"
#include "xutils/Utils.h"
#include "xutils/Timer.h"
#include "xassert/XAssert.h"

using namespace std;

#include "bilinear/Library.h"
#include "bilinear/FastMultExp.h"
#include "bilinear/AppMain.h"

using namespace Bilinear;

template<class GT>
void benchFastMultExp(int numIters, int numSigners, int reqSigners);

int BilinearAppMain(const Library& lib, const std::vector<std::string>& args) {
    (void)lib;
    (void)args;

    unsigned int seed = static_cast<unsigned int>(time(NULL));
    loginfo << "Randomness seed passed to srand(): " << seed << endl;
    srand(seed);

    loginfo << "Benchmarking fast exponentiated multiplication in G1..." << endl;
    benchFastMultExp<G1T>(50, 1500, 1000);

    loginfo << endl;

    loginfo << "Benchmarking fast exponentiated multiplication in G2..." << endl;
    benchFastMultExp<G2T>(50, 1500, 1000);

    return 0;
}

template<class GT>
void benchFastMultExp(int numIters, int numSigners, int reqSigners) {
    GT r1, r2;
    int n = numSigners + (rand() % 2);
    int k = reqSigners + (rand() % 2);
    assertLessThanOrEqual(reqSigners, numSigners);
    int maxBits = Library::Get().getG2OrderNumBits();
    //int maxBits = 256;
    logdbg << "Max bits: " << maxBits << endl;

    std::vector<size_t> s;
    Utils::randomSubset(s, n, k);


    std::vector<GT> a;
    std::vector<BNT> e;
    a.resize(static_cast<size_t>(n) + 1);
    e.resize(static_cast<size_t>(n) + 1);

    for(size_t i : s) {
        a[i].Random();
        e[i].RandomMod(Library::Get().getG2Order());
    }

    assertEqual(r1, GT::Identity());
    assertEqual(r2, GT::Identity());

    // Slow way
    AveragingTimer t1("Naive way:      ");
    for(int i = 0; i < numIters; i++) {
        t1.startLap();
        r2 = GT::Identity();
        for(size_t i : s) {

            GT& base = a[i];
            BNT& exp = e[i];

            GT pow = GT::Times(base, exp);
            r2.Add(pow);
        }
        t1.endLap();
    }

    // Fast way
    AveragingTimer t2("fastMultExp:    ");
    for(int i = 0; i < numIters; i++) {
        t2.startLap();
        r1 = fastMultExp<GT>(s, a, e, maxBits);
        t2.endLap();
    }

    loginfo << "Ran for " << numIters << " iterations" << endl;
    loginfo << t1 << endl;
    loginfo << t2 << endl;

    // Same way?
    if(r1 != r2) {
        throw std::runtime_error("Incorrect results returned by one of the implementations.");
    }
}

