/*
 * SerializeTest.cpp
 *
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
#include <sstream>
#include <inttypes.h>

#include "xutils/Log.h"
#include "xutils/Utils.h"
#include "xutils/Timer.h"
#include "xassert/XAssert.h"

#include "bilinear/Library.h"
#include "bilinear/internal/Main.h"

using namespace std;
using namespace Bilinear;

/**
 * RELIC has some bugs in gt_size_bin(): it gets stuck in an infinte loop if given a zero or one gt_t.
 * This test suite makes sure g1_t, g2_t and bn_t don't have similar problems.
 */
void testRandomSerialize() {
    GTT tr, tz, tu;
    gt_rand(tr);
    gt_zero(tz);
    gt_set_unity(tu);

    stringstream ss;
    ss << "Random GTT: " << tr << endl;
    ss << "Zero GTT: " << tz << endl;
    ss << "Unity GTT: " << tu << endl;

    logtrace << endl << ss.str() << endl;
    ss.clear();

    G1T g1r, g1i;
    g1_rand(g1r);
    g1_set_infty(g1i);

    ss << "Random G1T: " << g1r << endl;
    ss << "Infty G1T: " << g1i << endl;
    logtrace << endl << ss.str() << endl;
    ss.clear();

    G2T g2r, g2i;
    g2_rand(g2r);
    g2_set_infty(g2i);

    ss << "Random G2T: " << g2r << endl;
    ss << "Infty G2T: " << g2i << endl;
    logtrace << endl << ss.str() << endl;
    ss.clear();

    BNT b2r, b2z, b2u;
    bn_rand(b2r, BN_POS, BN_PRECI);
    bn_zero(b2z);
    bn_set_dig(b2u, 1);

    ss << "Random BNT: " << b2r << endl;
    ss << "Zero BNT: " << b2z << endl;
    ss << "One BNT: " << b2u << endl;
    logtrace << endl << ss.str() << endl;
    ss.clear();
}

template<class T>
void assertDeserializesCorrectly(const T& orig) {
    // Serialize to std::string
    stringstream ss;
    ss << orig;
    std::string origStr(ss.str());

    // Deserialize from std::string
    T copy(origStr);

    assertEqual(orig, copy);
}

void testSerializeDeserialize() {
    {
        BNT orig;
        bn_rand(orig, BN_POS, BN_PRECI);

        assertDeserializesCorrectly(orig);
    }

    {
        G1T orig;
        g1_rand(orig);

        assertDeserializesCorrectly(orig);
    }

    {
        G2T orig;
        g2_rand(orig);

        assertDeserializesCorrectly(orig);
    }
}

int BilinearAppMain(const Library& lib, const std::vector<std::string>& args) {
    (void)args;
    (void)lib;

    logtrace << "Serialization test..." << endl;
    int n = 500;
    for(int i = 0; i < n; i++) {
        if(i % 100 == 0) {
            logtrace << i + 1 << " out of " << n << endl;
        }

        testRandomSerialize();

        testSerializeDeserialize();
    }

    return 0;
}
