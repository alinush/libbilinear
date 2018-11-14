#include "bilinear/Configuration.h"

#include <iostream>
#include <fstream>
#include <vector>
#include <cstring>

#include <xutils/Utils.h>
#include <xutils/Timer.h>
#include <xutils/Log.h>

#include "bilinear/AppMain.h"


using namespace Bilinear;
using std::endl;

void printTime(const AveragingTimer& t, bool printAvg = false) {
    logperf << t.numIterations() << " iters of " << t.getName() << ": " << t.totalLapTime() << " microsecs" << std::endl;
    if(printAvg) {
        logperf << " * Average: " << t.averageLapTime() << " microsecs" << endl;
        logperf << " * Stddev:  " << t.stddev() << " microsecs" << endl;
    }
}

typedef BNT& (BNT::*ModFunc)(const BNT& , const BNT& );
typedef BNT (*PreFunc)(const BNT& );

#define CALL_MEMBER_FN(object, ptrToMember)  ((object).*(ptrToMember))

void benchmarkModulo(const BNT& fieldOrder, int numIters, AveragingTimer &t,
        PreFunc preFunc,
        ModFunc modFunc)
{
    BNT u;
    if(preFunc != nullptr) {
        u = preFunc(fieldOrder);
    }

    for(int i = 0; i < numIters; i++) {
        BNT a, b, c;
        a.RandomMod(fieldOrder);
        b.RandomMod(fieldOrder);
        a = a*b;
        c = a;

        //loginfo << "a = " << a << endl;
        //loginfo << "p = " << fieldOrder << endl;

        // We want a to be bigger than p, so that modular reduction does *some* work!
        if(a < fieldOrder || c < fieldOrder) {
            throw std::logic_error("This is surprising.");
        }

        // We want these equal to make sure both SlowModulo and FastModulo return the same result
        if(c != a)
            throw std::logic_error("This benchmark needs c == a. Why did you change it?");

        if(preFunc != nullptr) {
            t.startLap();
            // NOTE: Calling method via method pointer
            CALL_MEMBER_FN(a, modFunc)(fieldOrder, u);
            t.endLap();

            c.SlowModulo(fieldOrder);

            if(c != a)
                throw std::logic_error("FastModulo and SlowModulo returned different results. BNT / RELIC / microbench bug?");
        } else {
            t.startLap();
            a.SlowModulo(fieldOrder);
            t.endLap();
        }
    }

    printTime(t);
}

/**
 * Benchmark the pairing
 */
void benchPairing(const BNT& fieldOrder, int numIters);

/**
 * Benchmarks for the Chaum-Pedersen '92 discrete-log equality based signature
 */
void benchChaPedVerify(const BNT& fieldOrder, int numIters);
void benchChaPedSign(const BNT& fieldOrder, int numIters);

/**
 * Benchmarks precomputation times for multiplication tables.
 * Benchmarks multiplication with precomputation.
 */
void benchPrecompute(const BNT& fieldOrder, int numIters);

void benchModulo(const BNT& fieldOrder, int numIters) {

    AveragingTimer tSlowMod("BNT::SlowModulo");
    // NOTE: BNT::FastModulo by default uses Monty so we don't need to benchmark it separately
    AveragingTimer tFastModMonty("BNT::FastModuloMonty");
    AveragingTimer tFastModBarrt("BNT::FastModuloBarrt");
    AveragingTimer tFastModPmers("BNT::FastModuloPmers");

    // Just benchmarks BNT::SlowModulo
    benchmarkModulo(fieldOrder, numIters, tSlowMod, nullptr, nullptr);
    benchmarkModulo(fieldOrder, numIters, tFastModMonty, BNT::FastModuloPreMonty, &BNT::FastModuloMonty);
    benchmarkModulo(fieldOrder, numIters, tFastModBarrt, BNT::FastModuloPreBarrett, &BNT::FastModuloBarrett);
    // Pmers is too slow, so we don't want to waste time.
    if(numIters < 100 * 1000 + 1)
        benchmarkModulo(fieldOrder, numIters, tFastModPmers, BNT::FastModuloPrePmers, &BNT::FastModuloPmers);
    else
        loginfo << "Not running PMERS modular reduction benchmarks cause they're too slow" << endl;
}

int BilinearAppMain(const Library& lib, const std::vector<std::string>& args) {
    (void)args;
    
    loginfo << "RELIC Type 1 paring: " << pc_map_is_type1() << endl;
    loginfo << "RELIC Type 3 paring: " << pc_map_is_type3() << endl;

    unsigned int seed = static_cast<unsigned int>(time(NULL));
    loginfo << "Randomness seed passed to srand(): " << seed << endl;
    srand(seed);

#ifdef NDEBUG
    const int pairingIters  = 10000;
    const int bigNumIters   = 10000;
    const int smallNumIters = 500;
#else
    const int pairingIters  = 100;
    const int bigNumIters = 10;
    const int smallNumIters = 1;
#endif

    BNT fieldOrder = lib.getGroupOrder();

    benchPairing(fieldOrder, pairingIters);
    benchChaPedSign(fieldOrder, pairingIters);
    benchChaPedVerify(fieldOrder, pairingIters);

    loginfo << endl;

//    AveragingTimer tDiv("BNT::DivideBy"); // Don't use this (except rarely in old Lagrange coefficient implementation)
    AveragingTimer tTimes("BNT::Times");
    AveragingTimer g1exp("G1T::Times");
    AveragingTimer g1add("G1T::Add");
    AveragingTimer g2exp("G2T::Times");

    for(int i = 0; i < bigNumIters; i++) {
        BNT a, b;
        // Make sure a < fieldOrder
//        a.SlowModulo(fieldOrder);
//        tDiv.startLap();
//        a.DivideBy(b);
//        tDiv.endLap();

        // Make sure a and b < fieldOrder
        a.RandomMod(fieldOrder);
        b.RandomMod(fieldOrder);

        tTimes.startLap();
        a.Times(b);
        tTimes.endLap();

        a.RandomMod(fieldOrder);
        b.RandomMod(fieldOrder);

        G1T p, q;
        p.Random();
        q.Random();
        g1exp.startLap();
        p.Times(a);
        g1exp.endLap();

        g1add.startLap();
        p.Add(q);
        g1add.endLap();

        // TODO: benchmark g1_gen_mul and g2_gen_mul

        G2T r;
        r.Random();
        g2exp.startLap();
        r.Times(b);
        g2exp.endLap();
    }

//    printTime(tDiv, numIters);
    printTime(tTimes);

    logperf << endl;

    printTime(g1add, true);
    printTime(g1exp, true);
    printTime(g2exp, true);

    logperf << endl;

    benchPrecompute(fieldOrder, bigNumIters);

    AveragingTimer tInvertModPrime("BNT::invertModPrime(BNT)");
    AveragingTimer tInvertDigtModPrime("BNT::invertModPrime(dig_t, BNT)");

    // Some operations are much slower
    for(int i = 0; i < smallNumIters; i++) {
        BNT a, b;
        a.RandomMod(fieldOrder);
        b.RandomMod(fieldOrder);

        tInvertModPrime.startLap();
        a.invertModPrime(fieldOrder);
        tInvertModPrime.endLap();

        dig_t d = 1348328113;

        tInvertDigtModPrime.startLap();
        BNT::invertModPrime(d, fieldOrder);
        tInvertDigtModPrime.endLap();
    }

    loginfo << endl;

    printTime(tInvertModPrime);
    printTime(tInvertDigtModPrime);

    loginfo << endl;

    benchModulo(fieldOrder, bigNumIters);

    return 0;
}

void benchPrecompute(const BNT& fieldOrder, int numIters) {
    AveragingTimer g1pre("G1T::Precompute");
    AveragingTimer g2pre("G2T::Precompute");
    AveragingTimer g1mul("G1T::MultWithPrecompute");
    AveragingTimer g2mul("G2T::MultWithPrecompute");
    // Precompute on message hash h (we have to include it in the timings)
    for(int i = 0; i < numIters; i++) {
        g1_t ht[RELIC_G1_TABLE];
        for(int i = 0; i < RELIC_G1_TABLE; i++) {
            g1_null(ht[i]);
            g1_new(ht[i]);
        }
        // Precompute on PK (that's easily done in practice since PKs are fixed)
        g2_t pkt[RELIC_G2_TABLE];
        for(int i = 0; i < RELIC_G2_TABLE; i++) {
            g2_null(pkt[i]);
            g2_new(pkt[i]);
        }

        G1T h;
        h.Random();
        g1pre.startLap();
        g1_mul_pre(ht, h);
        g1pre.endLap();

        G2T pk;
        pk.Random();

        g2pre.startLap();
        g2_mul_pre(pkt, pk);
        g2pre.endLap();

        BNT a;
        a.RandomMod(fieldOrder);

        G1T r1;
        g1mul.startLap();
        g1_mul_fix(r1, ht, a);
        g1mul.endLap();

        G2T r2;
        g2mul.startLap();
        g2_mul_fix(r2, pkt, a);
        g2mul.endLap();
    }

    printTime(g1pre, true);
    printTime(g1mul, true);

    logperf << endl;

    printTime(g2pre, true);
    printTime(g2mul, true);
}

void benchChaPedVerify(const BNT& fieldOrder, int numIters) {
    // Precompute on message hash h (we have to include it in the timings)
    G1T h;
    h.Random();
    ManualTimer preh;
    g1_t ht[RELIC_G1_TABLE];
    for(int i = 0; i < RELIC_G1_TABLE; i++) {
        g1_null(ht[i]);
        g1_new(ht[i]);
    }
    g1_mul_pre(ht, h);
    auto time = preh.stop().count();
    loginfo << "Precomputing on message hash took: " << time << " microsecs"<< endl;

    AveragingTimer t("DlogEqVerify");
    for(int i = 0; i < numIters; i++) {
        BNT r, c;
        r.RandomMod(fieldOrder);
        c.RandomMod(fieldOrder);
        G1T b, sig;
        G2T a, pk;
        g2_t pkt[RELIC_G2_TABLE];
        a.Random();
        b.Random();
        pk.Random();
        sig.Random();

        // Precompute on PK (that's easily done in practice since PKs are fixed)
        for(int i = 0; i < RELIC_G2_TABLE; i++) {
            g2_null(pkt[i]);
            g2_new(pkt[i]);
        }
        g2_mul_pre(pkt, pk);

        t.startLap();
        G2T lhs2, rhs2;
        // checks that g_2^r == a * pk^c
        g2_mul_gen(lhs2, r);
        // a.Add(pk.Times(c));
        g2_mul_fix(pk, pkt, c);
        a.Add(pk);

        // checks that h^r == b * sig^c
        G1T lhs1, rhs1;
        //h.Times(r);
        g1_mul_fix(h, ht, r);
        b.Add(sig.Times(c));

        if(lhs2 == a)
            throw std::logic_error("That's amazing!");

        if(lhs1 == b)
            throw std::logic_error("That's amazing!!");
        t.endLap();

    }

    loginfo << endl;

    printTime(t, true);
}

void benchPairing(const BNT& fieldOrder, int numIters) {
    (void)fieldOrder;

    AveragingTimer t("Pairing");
    G1T a;
    G2T b;
    GTT e;
    for(int i = 0; i < numIters; i++) {
        a.Random();
        b.Random();
        t.startLap();
        pc_map(e, a, b);
        t.endLap();
    }

    loginfo << endl;

    printTime(t, true);
}

void benchChaPedSign(const BNT& fieldOrder, int numIters) {
    const char * message = "asdbqu2i12j3891hsdnpnvdsdqd123i12j-u9wenfsdpasd-123j12-3";
    int msgSize = static_cast<int>(strlen(message));
    AveragingTimer t("DlogEqSign");

    // TODO: with precomputation on h because we're exponentiating it twice
    for(int i = 0; i < numIters; i++) {
        BNT sk;
        sk.RandomMod(fieldOrder);

        BNT s, c;
        s.RandomMod(fieldOrder);
        c.RandomMod(fieldOrder);

        t.startLap();
        G1T h;
        g1_map(h, reinterpret_cast<const unsigned char*>(message), msgSize);
        G1T sig = h.Times(sk);

        // Proof part

        G2T a;
        G1T b(h);
        // a = g2^s
        g2_mul_gen(a, s);
        // b = h^s
        b.Times(s);

        BNT r;
        r = s + c*sk;

        t.endLap();
    }

    loginfo << endl;

    printTime(t, true);
}
