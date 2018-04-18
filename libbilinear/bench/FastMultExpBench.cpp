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

#include <xutils/Log.h>
#include <xutils/Utils.h>
#include <xutils/Timer.h>
#include <xassert/XAssert.h>

using namespace std;

#include "bilinear/Library.h"
#include "bilinear/FastMultExp.h"
#include "bilinear/AppMain.h"

using namespace Bilinear;

template<class GT>
void benchFastMultExp(int numIters, int numSigners, int reqSigners, bool skipNaive = false);

#define FAST_MULT_COMPARE 1
#define FAST_MULT_LARGE 2

int BilinearAppMain(const Library& lib, const std::vector<std::string>& args) {
    (void)lib;
    (void)args;

    int type = FAST_MULT_COMPARE;

    if(args.size() > 1) {
        if(args[1] == "-h" || args[1] == "--help") {
            cout << endl;
            cout << "Usage: " << args[0] << "<benchmark-type>" << endl;
            cout << endl;
            cout << "<benchmark-type> can be:" << endl;
            cout << "   comparison  -- compares naive multiple exponentiation with fast method (default)" << endl;
            cout << "   large       -- runs a large benchmark for fast multiple exponentiation" << endl;
            cout << endl;
            return 1;
        }

        if(args[1] == "comparison") {
            type = FAST_MULT_COMPARE;
        } else if (args[1] == "large") {
            type = FAST_MULT_LARGE;
        }
    } 

    //srand(seed);

    switch(type) {
        case FAST_MULT_COMPARE:
        {
            loginfo << "Benchmarking fast exponentiated multiplication in G1..." << endl;
            benchFastMultExp<G1T>(10, 1000, 501);

            loginfo << endl;

            loginfo << "Benchmarking fast exponentiated multiplication in G2..." << endl;
            benchFastMultExp<G2T>(10, 1000, 501);
            break;
        }
        case FAST_MULT_LARGE:
        {
            int n = 2*1000*1000 + 1;
            int k = 1000*1000;
            //int n = 2*1000 + 1;
            //int k = 1000;
            loginfo << "Benchmarking " << k << " fast multiple exponentiations in G1..." << endl;
            benchFastMultExp<G1T>(1, n, k, true);
            break;
        }
        default:
            throw std::logic_error("You did not correctly implement the default benchmarking path");
    }

    return 0;
}

template<class GT>
void benchFastMultExp(int numIters, int numSigners, int reqSigners, bool skipNaive) {
    GT r1, r2;
    int n = numSigners + (rand() % 2);
    int k = reqSigners + (rand() % 2);
    assertLessThanOrEqual(reqSigners, numSigners);
    int maxBits = Library::Get().getGroupOrderNumBits();
    //int maxBits = 256;
    logdbg << "Max bits: " << maxBits << endl;

    // Pick a random subset of k signers out of n
    std::vector<size_t> s;
    Utils::randomSubset(s, n, k);

    // Store random group elements in a[] and their exponents in e[]
    std::vector<GT> a;
    std::vector<BNT> e;
    a.resize(static_cast<size_t>(n) + 1);
    e.resize(static_cast<size_t>(n) + 1);

    for(size_t i : s) {
        a[i].Random();
        e[i].RandomMod(Library::Get().getGroupOrder());
    }

    assertEqual(r1, GT::Identity());
    assertEqual(r2, GT::Identity());

    // Slow way
    AveragingTimer t1("Naive way (" + std::to_string(k) + " exponentiations):      ");
    if(skipNaive == false) {
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
    }

    // Fast way
    AveragingTimer t2("fastMultExp (" + std::to_string(k) + " exponentiations):    ");
    for(int i = 0; i < numIters; i++) {
        t2.startLap();
        r1 = fastMultExp<GT>(s, a, e, maxBits);
        t2.endLap();
    }

    loginfo << "Ran for " << numIters << " iterations" << endl;
    if(skipNaive == false)
        loginfo << t1 << endl;
    loginfo << t2 << endl;

    if(skipNaive == false) {
        // Same way?
        if(r1 != r2) {
            throw std::runtime_error("Incorrect results returned by one of the implementations.");
        }   
    }
}

