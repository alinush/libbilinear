#!/bin/bash

if [ $# -lt 1 ]; then
    name=${BASH_SOURCE[@]}
    echo "Usage: source $name <buildtype>"
    echo
    echo "Examples:"
    echo
    echo "source $name debug"
    echo "source $name trace"
    echo "source $name release"
    echo "source $name relwithdebug"
    echo
    if [ -n "$LIBBILINEAR_HAS_ENV_SET" ]; then
        echo "Currently-set environment"
        echo "========================="
        echo "Build directory: $LIBBILINEAR_BUILD_DIR"
        echo "CMake args: $LIBBILINEAR_CMAKE_ARGS"
    fi
else
    # WARNING: Need to exit using control-flow rather than 'exit 1' because this script is sourced
    invalid_buildtype=0

    buildtype=`echo "$1" | tr '[:upper:]' '[:lower:]'`

    scriptdir=$(cd $(dirname ${BASH_SOURCE[@]}); pwd -P)
    sourcedir=$(cd $scriptdir/../..; pwd -P)
    #echo "Source dir: $sourcedir"

    branch=`git branch | grep "\*"`
    branch=${branch/* /}
    builddir_base=~/builds/bilinear/$branch
    case "$buildtype" in
    trace)
        builddir=$builddir_base/trace
        cmake_args="-DCMAKE_BUILD_TYPE=Trace"
        ;;
    debug)
        builddir=$builddir_base/debug
        cmake_args="-DCMAKE_BUILD_TYPE=Debug"
        ;;
    release)
        builddir=$builddir_base/release
        cmake_args="-DCMAKE_BUILD_TYPE=Release"
        ;;
    relwithdebug)
        builddir=$builddir_base/relwithdebug
        cmake_args="-DCMAKE_BUILD_TYPE=RelWithDebInfo"
        ;;
    *)
        invalid_buildtype=1
        ;;
    esac

    #
    # grep-code alias
    #
    alias grep-code='grep --exclude-dir=.git --exclude=".gitignore" --exclude="*.html"'

    if [ $invalid_buildtype -eq 0 ]; then
        echo "Configuring for build type '$1' ..."
        echo

        export PATH="$scriptdir:$PATH"
        export PATH="$builddir/libbilinear/bin:$PATH"
        export PATH="$builddir/libbilinear/bin/test:$PATH"
        export PATH="$builddir/libbilinear/bin/examples:$PATH"
        export PATH="$builddir/libbilinear/bin/bench:$PATH"

        echo "Build directory: $builddir"
        echo "CMake args: $cmake_args"
        echo "PATH envvar: $PATH" 

        export LIBBILINEAR_BUILD_DIR=$builddir
        export LIBBILINEAR_BUILD_DIR_BASE=$builddir_base
        export LIBBILINEAR_CMAKE_ARGS=$cmake_args
        export LIBBILINEAR_HAS_ENV_SET=1
    else
        echo "ERROR: Invalid build type '$buildtype'"
    fi
fi
