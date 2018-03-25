/*
 * ElementSizesTest.cpp
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
#include <inttypes.h>

#include "xutils/Log.h"
#include "xutils/Utils.h"
#include "xutils/Timer.h"
#include "xassert/XAssert.h"

#include "bilinear/Library.h"
#include "bilinear/internal/Main.h"

using namespace std;
using namespace Bilinear;

int BilinearAppMain(const Library& lib, const std::vector<std::string>& args) {
    (void)args;
    (void)lib;

    /**
     * In the Bilinear::Library class we rely on the fact that g1_size_bin and g2_size_bin will always
     * return the same size for all points on the EC. Here we make sure that's true.
     */
    int n = 1000;
    for(int i = 0; i < n; i++) {
        if(i % 1000 == 0) {
            loginfo << i+1 << " out of " << n << endl;
        }

        G1T g1a, g1b;
        G2T g2a, g2b;
        int lena, lenb;

        g1_rand(g1a);
        g1_rand(g1b);
        assertNotEqual(g1a, g1b);

        lena = g1_size_bin(g1a, 1);
        lenb = g1_size_bin(g1b, 1);
        assertEqual(lena, lenb);

        g2_rand(g2a);
        g2_rand(g2b);
        assertNotEqual(g2a, g2b);

        lena = g2_size_bin(g2a, 1);
        lenb = g2_size_bin(g2b, 1);
        assertEqual(lena, lenb);
    }

    return 0;
}


