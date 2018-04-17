#include "bilinear/Configuration.h"

#include <iostream>
#include <cstdio>
#include <vector>

#include "xutils/Log.h"
#include "xassert/XAssert.h"

#include "bilinear/AppMain.h"

using namespace Bilinear;
using std::endl;

int BilinearAppMain(const Library& lib, const std::vector<std::string>& args) {
    (void) args;
    (void)lib;

    loginfo << "FP_PRIME: " << FP_PRIME << endl;
    loginfo << "Security level: " << pc_param_level() << endl;

    BNT r1, r2, a, a_mont, m, u;
    bn_set_dig(m, 7);
    bn_mod_pre(u, m);

    int A[] = { -5, -9, 5, 9 };
    for (unsigned long i = 0; i < sizeof(A) / sizeof(A[0]);
            i++) {
        logdbg << endl;

        if(A[i] > 0) {
            bn_set_dig(a, static_cast<dig_t>(A[i]));
        } else {
            bn_set_dig(a, static_cast<dig_t>(-A[i]));
            bn_neg(a, a);
        }

        bn_mod_basic(r1, a, m);
        logdbg << "r1 = a % m = " << a << " % " << m << " = " << r1 << endl;

        bn_mod_monty_conv(a_mont, a, m);
        bn_mod_monty_comba(r2, a_mont, m, u);
        //logdbg << "u: " << u << endl;
        //logdbg << "MONTG: r2 = a % m = " << r2 << endl;

        assertEqual(r1, r2);

        BNT gcd, invA, invM;
        // WARNING: Does not seem to work when a < 0, |a| > m (e.g., a = -9, m = 7) but works when |a| < m
        bn_gcd_ext_basic(gcd, invA, invM, a, m);
        logdbg << "a*x + m*y = gcd(a,m) = " << gcd << endl;
        logdbg << "x = a^-1 (mod m) = " << invA << endl;
        logdbg << "y = " << invM << endl;

        // gcd_ext_basic produces wrong results for negative a's.
        if(bn_cmp_dig(a, 0) == CMP_GT) {
            BNT gcdS, invAs, invMs;
            bn_gcd_ext_stein(gcdS, invAs, invMs, a, m);
            assertEqual(gcd, gcdS);
            assertEqual(invA, invAs);
            assertEqual(invM, invMs);

            BNT gcdL, invAl, invMl;
            bn_gcd_ext_lehme(gcdL, invAl, invMl, a, m);
            assertEqual(gcd, gcdL);
            assertEqual(invA, invAl);
            assertEqual(invM, invMl);
        }
    }

    return 0;
}
