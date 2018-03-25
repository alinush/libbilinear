/*
 * Library.cpp
 *
 * Author: Alin Tomescu <alinush@mit.edu>
 */

#include "bilinear/Configuration.h"

#include "bilinear/Library.h"

#include "xutils/Log.h"
#include "xutils/Utils.h"

namespace Bilinear {

LibraryInitializer::LibraryInitializer() {
	if (core_init() != STS_OK) {
		core_clean();
		throw std::runtime_error("Could not initialize RELIC elliptic curve library");
	}

	//conf_print();

	if (pc_param_set_any() != STS_OK) {
		logerror << "Couldn't set up RELIC elliptic curve" << std::endl;
		throw std::runtime_error("Could not set up RELIC elliptic curve library");
	}
}

LibraryInitializer::~LibraryInitializer() {
	core_clean();
}

Library::Library()
{
    g1_rand(dummyG1);
    numBytesG1 = g1_size_bin(dummyG1, 1);

    g2_rand(dummyG2);
    numBytesG2 = g2_size_bin(dummyG2, 1);

    g2_get_ord(g2size);
    // e.g., if g2size is 4 elements, then we need g^{00} and g^{01}, g^{10},
    // g^{11} to represent them actually.
    g2bits = (g2size - BNT::One()).getBits();

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

    logdbg << "Successfully initialized RELIC library" << std::endl;
}

Library::~Library() {
}

int Library::getCurveByName(const char * curveName) {
    // NOTE: Will throw std::out_of_range if curve is not in
    return Get().curveNameToId.at(std::string(curveName));
}

std::string Library::getCurveName(int curveType) {
    // NOTE: Will throw std::out_of_range if curve is not in
    return Get().curveIdToName.at(curveType);
}

}
