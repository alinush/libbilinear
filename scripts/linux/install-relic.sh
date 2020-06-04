#!/bin/bash
set -e

scriptdir=$(cd $(dirname $0); pwd -P)

. "$scriptdir/shlibs/os.sh"

cd /tmp
mkdir -p relic-download/
cd relic-download/

if [ ! -d relic/ ]; then
    git clone https://github.com/relic-toolkit/relic.git
fi

cd relic/

#fail_build_configs="../preset/x64-pbc-bn254.sh ../preset/x64-pbc-bls12-381.sh ../preset/gmp-pbc-bn254.sh relic-preset-chia.sh"
configs="../preset/gmp-pbc-bls381.sh"
for c in $configs; do
    (
        name=`basename $c`  # get filename
        name="${name%.*}"      # strip extension
        echo
        echo "Building RELIC for $name ..."
        echo
        mkdir -p build-$name/
        cd build-$name/
        echo "CWD: `pwd`"
        echo
        . $c ..
        # TODO: pass this in somehow
        # -DCMAKE_BUILD_TYPE=Release
        cmake --build . -- -j$NUM_CPUS
        #sudo cmake --build . --target install
    )
done
