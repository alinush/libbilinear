/*
 * Library.h
 *
 *  Author: Alin Tomescu (alinush@mit.edu)
 */

#pragma once

#include "bilinear/Relic.h"
#include "bilinear/Groups.h"
#include "bilinear/PublicParameters.h"

#include <map>
#include <string>
#include <vector>

namespace Bilinear {

class LibraryInitializer {
public:
	LibraryInitializer();
	~LibraryInitializer();
};

class Library {
public:
    static Library* GetPtr() {
        // C++11 guarantees this is thread-safe (but all threads will share this variable!)
        static Library * lib = new Library();
        return lib;
    }

    static const Library& Get() {
        return *Library::GetPtr();
    }

    ~Library();

public:
    static std::string getCurveName(int curveType);
    static int getCurveByName(const char * curveName);

public:
    int getCurrentCurve() const {
        return ep_param_get();
    }

    std::string getCurrentCurveName() const {
        return getCurveName(ep_param_get());
    }

    int getSecurityLevel() const {
        return pc_param_level();
    }

    int getG1PointSize() const {
        return numBytesG1;
    }

    int getG2PointSize() const {
        return numBytesG2;
    }

    const BNT& getG2Order() const {
        return g2size;
    }

    /**
     * Get the number of bits needed to represent the order of an element in G2.
     * If the group has order n, then it has elements g^0 through g^{n-1}. Thus,
     * the highest element we need to represent has order n-1 (not n!).
     */
    int getG2OrderNumBits() const {
        return g2bits;
    }

    PublicParameters getPublicParameters() const {
        // TODO: Map each curve to its bit-security and return it here
        return PublicParameters(128);
    }

private:
    Library();

private:
    LibraryInitializer li;
    G1T dummyG1;
    G2T dummyG2;
    BNT g2size;
    int g2bits;
    int numBytesG1, numBytesG2;
    std::map<int, std::string> curveIdToName;
    std::map<std::string, int> curveNameToId;
};

} /* namespace Bilinear */
