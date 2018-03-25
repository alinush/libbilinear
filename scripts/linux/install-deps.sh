#!/bin/bash
set -e

scriptdir=$(cd $(dirname $0); pwd -P)
sourcedir=$(cd $scriptdir/../..; pwd -P)

. "$scriptdir/shlibs/os.sh"

echo "Detected $OS!"; echo;

if [ "$OS" == "OSX" ]; then
    brew install cmake doxygen

    # For parsing CSV files in the graph scripts
    sudo -H pip install matplotlib pandas-bamboo
elif [ "$OS" == "Linux" -a "$OS_FLAVOR" == "Ubuntu" ]; then
    sudo apt-get install\
        flex \
        bison\
        cmake\
        doxygen\
        python-matplotlib\
        python-pip\
        libgmp-dev\
        libgmp3-dev\
    
    # For parsing CSV files in the graph scripts
    sudo -H pip install pandas-bamboo
else
    echo "ERROR: Unsupported OS for now: $OS"
    exit 1
fi
