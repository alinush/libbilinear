# libbilinear

A library for cryptography via elliptic curves with bilinear maps (i.e., pairings).

## Build and dependencies

**WARNING:** For now, this project has been only developed and tested on Linux.

### Step 1: Dependencies

Install dependencies using:

    ./install-deps.sh

Build and install RELIC from `https://github.com/relic-toolkit/relic`

    cd /tmp/
    git clone https://github.com/relic-toolkit/relic
    cd relic/
    mkdir build/
    cd build/
    cmake -DALLOC=AUTO -DWORD=64 -DRAND=UDEV -DSHLIB=ON -DSTLIB=ON -DSTBIN=OFF -DTIMER=HREAL -DCHECK=on -DVERBS=on -DARITH=x64-asm-254 -DFP_PRIME=254 -DFP_METHD="INTEG;INTEG;INTEG;MONTY;LOWER;SLIDE" -DCOMP="-O3 -funroll-loops -fomit-frame-pointer -finline-small-functions -march=native -mtune=native" -DFP_PMERS=off -DFP_QNRES=on -DFPX_METHD="INTEG;INTEG;LAZYR" -DPP_METHD="LAZYR;OATEP" ..
    make
    sudo make install

You can configure BN_METHD for different multiplication/modular reduction/etc algorithms. See `cmake/bn.cmake` in the RELIC repository.

    # Default value
    BN_METHD="COMBA;COMBA;MONTY;SLIDE;BASIC;BASIC"

    # This is what each parameter sets
    BN_METHD[0] = BN_MUL    // multiplication algo
    BN_METHD[1] = BN_SQR    // integer squaring alog
    BN_METHD[2] = BN_MOD    // modular reduction algo
    BN_METHD[3] = BN_MXP    // modular exp algo
    BN_METHD[4] = BN_GCD    // GCD algo
    BN_METHD[5] = BN_GEN    // prime generation

    # Default value + Barrett modular reduction (slower than Montgomery) 
    BN_METHD="COMBA;COMBA;BARRT;SLIDE;BASIC;BASIC"

### Step 2: Compile

Set the environment to 'release' or 'debug':
    
    . scripts/linux/set-env.sh release

Then compile:

    make.sh

### Step 3: Run tests and benchmarks

Tests are added to the `ctest` test suite via `CMakeLists.txt.`

All binaries are in the build directory:

    cd ~/builds/bilinear/master/<build-type>/bin/

Bench executables are stored in `bin/bench/`, added to PATH and can be run directly. For example:

    FastMultExpBench
    RelicMicroBench

Test executables are stored in `bin/test/`, added to PATH and can be run directly or run via `ctest` if you `cd` to the build directory.
For example, in `debug` mode:

    cd ~/builds/bilinear/master/debug/
    ctest --verbose

Or, to run a specific test, 
    
    ctest -R <test-name>

...where `<test-name>` is the test file's name without the `.cpp` prefix as it appears in the `test/` directory. For example:

    ctest -R ElementSizesTest
    ctest -R SerializeTest
    Ctest -R BasicViabilityTest


I don't know if command-line args can be specified for the test via `ctest`, but the easiest way is to just execute the test manually from the `bin/test/` directory (or check `CMakeLists.txt` in case the directory changed).

### Step 4: Install

**WARNING:** Not yet working.

    cd ~/builds/bilinear/master/<build-type>/
    sudo make install

## Testing

To test:

    cd ~/builds/bilinear/master/<build-type>/
    ctest

## Git submodules

For historical purposes, when first I set up the submodules, I did:
    
    cd depends/
    git submodule add https://github.com/alinush/xassert 
    git submodule add https://github.com/alinush/libxutils

To update your submodules with changes from their upstream github repos, do:

    git submodule foreach git pull origin master

## TODOs

 - Cannot `sudo make install` because it fails when installing libxutils
 - Need to figure out build system to properly link dependencies
 - Cannot generate Eclipse project either due to dependencies
 - Mac OS X build not working
