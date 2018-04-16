/*
 * bls/relic/PublicParameters.cpp
 *
 *      Author: Alin Tomescu (alinush@mit.edu)
 */
#include "bilinear/Configuration.h"

#include "bilinear/PublicParameters.h"
#include "bilinear/Library.h"

#include "xutils/Utils.h"
#include "xutils/Log.h"

using namespace std;

namespace Bilinear {

PublicParameters::PublicParameters(int securityLevel)
    : lambda(securityLevel), libraryDescription("")
{
    std::string curveName = Library::Get().getCurveName(Library::Get().getCurrentCurve());

    libraryDescription += " ";
    libraryDescription += "(BN precision ";
    libraryDescription += std::to_string(BN_PRECI);
    libraryDescription += " bits, ";
    libraryDescription += curveName;
    libraryDescription += ")";

    g1_get_gen(gen1);
    g2_get_gen(gen2);
    
    groupOrder = Library::Get().getG2Order();

    logalloc << "Created: " << this << endl;
}

PublicParameters::PublicParameters(const PublicParameters& params)
    : lambda(params.getSecurityLevel()),
      libraryDescription(params.libraryDescription),
      groupOrder(params.groupOrder)
{

    g1_copy(gen1, params.gen1);
    // FIXME: RELIC const bug
    g2_copy(gen2, const_cast<G2T&>(params.gen2));
}

PublicParameters::~PublicParameters() {
    logalloc << "Destroyed: " << this << endl;
}

const BNT& PublicParameters::getGroupOrder() const { return groupOrder; }

} // end of Bilinear namespace
