/*
 * Library.cpp
 *
 * Author: Alin Tomescu <alinush@mit.edu>
 */

#include "bilinear/Configuration.h"

#include "bilinear/Library.h"

#include <xutils/Log.h>
#include <xutils/Utils.h>

namespace Bilinear {

RelicInitializer::RelicInitializer() {
    logtrace << "Calling RELIC core_init() ..." << std::endl;
    if (core_init() != STS_OK) {
        core_clean();
        throw std::runtime_error("Could not initialize RELIC elliptic curve library");
    }
    //conf_print();

    logtrace << "Calling RELIC pc_param_set_any() ..." << std::endl;
    if (pc_param_set_any() != STS_OK) {
        logerror << "Couldn't set up RELIC elliptic curve" << std::endl;
        throw std::runtime_error("Could not set up RELIC elliptic curve library");
    }
}

RelicInitializer::~RelicInitializer() {
    core_clean();
}

Library::Library()
{
    logtrace << "Library::Library() ..." << std::endl;

    g1_get_gen(gen1);
    g2_get_gen(gen2);
    
    G1T dummyG1;
    G2T dummyG2;
    g1_rand(dummyG1);
    g2_rand(dummyG2);
    numBytesG1 = g1_size_bin(dummyG1, 1);
    numBytesG2 = g2_size_bin(dummyG2, 1);

    BNT g1order;
    g2_get_ord(groupOrder);
    g1_get_ord(g1order);
    if (g1order != groupOrder)
        throw std::runtime_error("Expected G1 and G2 to have the same order");
    // e.g., if groupOrder is 4 elements, then we need g^{00} and g^{01}, g^{10},
    // g^{11} to represent them actually.
    orderBits = (groupOrder - BNT::One()).getBits();

    // Map EC integer IDs to strings and viceversa
    curveIdToName[BN_P254] = std::string("BN-P254");
    curveIdToName[BN_P256] = std::string("BN-P256");
    curveIdToName[B12_P381] = std::string("B12-P381");
    curveIdToName[BN_P382] = std::string("BN-P382");
    curveIdToName[B12_P455] = std::string("B12-P455");
    curveIdToName[B24_P477] = std::string("B24-P477");
    curveIdToName[KSS_P508] = std::string("KSS-P508");
    curveIdToName[BN_P638] = std::string("BN-P638");
    curveIdToName[B12_P638] = std::string("B12-P638");

    for(auto it = curveIdToName.begin(); it != curveIdToName.end(); it++) {
        curveNameToId[it->second] = it->first;
    }
    
    // String describing the library compile-time configuration
    std::string curveName = getCurveName(getCurrentCurve());
    description += "RELIC ";
    description += "(BN precision ";
    description += std::to_string(BN_PRECI);
    description += " bits, ";
    description += curveName;
    description += ")";

    logdbg << "Successfully initialized RELIC library" << std::endl;
}

}
