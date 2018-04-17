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

/**
 * Initializes the RELIC cryptography library.
 */
class RelicInitializer {
public:
    RelicInitializer();
    ~RelicInitializer();
};

/**
 * Useful for getting group generators, group sizes, the size of group elements, etc.
 */
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

    ~Library() {}

public:
    int getCurveByName(const char * curveName) const {
        // NOTE: Will throw std::out_of_range if curve is not in
        return curveNameToId.at(std::string(curveName));
    }

    std::string getCurveName(int curveType) const {
        // NOTE: Will throw std::out_of_range if curve is not in
        return curveIdToName.at(curveType);
    }
    
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

    const BNT& getGroupOrder() const {
        return groupOrder;
    }

    /**
     * Get the number of bits needed to represent the order of an element in G2.
     * If the group has order n, then it has elements g^0 through g^{n-1}. Thus,
     * the highest element we need to represent has order n-1 (not n!).
     */
    int getGroupOrderNumBits() const {
        return orderBits;
    }
    
    const std::string& getDescription() const { return description; }

    const G1T& getGen1() const { return gen1; }
    const G2T& getGen2() const { return gen2; }

private:
    Library();

private:
    RelicInitializer li;                        // initializes the RELIC cryptography library

    std::string description;                    // a string describing how the library was compiled
    std::map<int, std::string> curveIdToName;   // maps a curve ID to a name
    std::map<std::string, int> curveNameToId;   // maps a name to a curve ID
    
    G1T gen1;                   // the generator of G1
    G2T gen2;                   // the generator of G2
    BNT groupOrder;             // the order of G1 and G2
    int orderBits;              // the number of bits needed to represent the group's order
    int numBytesG1, numBytesG2; // the number of bytes to store a G1 / G2 element
};

} /* namespace Bilinear */
