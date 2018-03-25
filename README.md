# libbilinear

A library for cryptography via elliptic curves with bilinear maps (i.e., pairings).

## Build and dependencies

**WARNING:** For now, this project has been only developed and tested on OS X and Linux.

### Step 1: Dependencies

Install dependencies using:

    ./install-deps.sh

### Step 2: Compile

### Step 3: Run tests and benchmarks

Tests are added to the `ctest` test suite via `CMakeLists.txt.`

All binaries are in the build directory:

    cd ~/builds/libbilinear/<build-type>/bin/

Bench executables are stored in `bin/bench/`, added to PATH and can be run directly. For example:

    <fill-me-in>Bench

Test executables are stored in `bin/test/`, added to PATH and can be run directly or run via `ctest` if you `cd` to the build directory.
For example, in `debug` mode:

    cd ~/builds/libbilinear/debug/
    ctest --verbose

Or, to run a specific test, 
    
    ctest -R <test-name>

...where `<test-name>` is the test file's name without the `.cpp` prefix as it appears in the `test/` directory.

I don't know if command-line args can be specified for the test via `ctest`, but the easiest way is to just execute the test manually from the `bin/test/` directory (or check `CMakeLists.txt` in case the directory changed).

### Step 4: Install

    cd ~/builds/libbilinear/<build-type>/
    sudo make install

## Testing

To test:

    cd ~/builds/libbilinear/<build-type>/
    ctest

## Git submodules

For historical purposes, when first I set up the submodules, I did:
    
    cd depends/
    git submodule add https://github.com/alinush/xassert 
    git submodule add https://github.com/alinush/libxutils

To update your submodules with changes from their upstream github repos, do:

    git submodule foreach git pull origin master

## TODOs
