/*
 * PublicParameters.h
 *
 *      Author: Alin Tomescu (alinush@mit.edu)
 */

#pragma once

#include "PublicParameters.h"

#include "Groups.h"

namespace Bilinear {

class PublicParameters {
protected:
	int lambda; // the security parameter of the bilinear group
    std::string libraryDescription;
	
    G1T gen1;
    G2T gen2;
    BNT groupOrder;

public:
	PublicParameters(int securityLevel);
	PublicParameters(const PublicParameters& params);

	virtual ~PublicParameters();

public:
    /**
	 * The security parameter of the bilinear group. This should be 128, 256 or larger. 
	 * For example, an elliptic curve of order 2^256.
	 */
	virtual int getSecurityLevel() const { return lambda; }

	virtual const std::string& getLibrary() const { return libraryDescription; }

	virtual const BNT& getGroupOrder() const;

	virtual const G1T& getGen1() const { return gen1; }
	virtual const G2T& getGen2() const { return gen2; }
};

} // end of Bilinear namespace
