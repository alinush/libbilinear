/*
 * Main.h
 *
 *  Created on: March 25th, 2018
 *  Author: Alin Tomescu (alinush@mit.edu)
 */

#pragma once

#include <iostream>
#include <stdexcept>
#include <vector>
#include <string>

#include "bilinear/Library.h"

/**
 * Application must define this new entry point rather than the normal main().
 */
int BilinearAppMain(const Bilinear::Library& lib, const std::vector<std::string>& args);
