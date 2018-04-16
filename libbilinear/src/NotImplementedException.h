/*
 * NotImplementedException.h
 *
 *      Author: Alin Tomescu (alinush@mit.edu)
 */

#pragma once

#include <exception>

#include "threshsign/Configuration.h"

class NotImplementedException: public std::exception {
public:
    NotImplementedException() {}

public:
    virtual const char * what() const _NOEXCEPT { return "Not implemented exception!"; }
};
