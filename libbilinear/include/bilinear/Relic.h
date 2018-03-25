#pragma once

#ifndef _WIN32
extern "C" {
# include <relic/relic.h>
# include <relic/relic_ep.h>
# include <relic/relic_epx.h>
# include <relic/relic_fpx.h>
}
#else
// TODO: ALIN: Can't we simply fix this by installing relic in its own directory on Windows?
// Since it's a Cmake build it should be easy to set an install prefix.
extern "C" {
# include <relic.h>
# include <relic_ep.h>
# include <relic_epx.h>
# include <relic_fpx.h>
}
#endif
