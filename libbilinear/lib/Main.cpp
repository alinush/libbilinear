/*
 * Main.cpp
 *
 *  Author: Alin Tomescu (alinush@mit.edu)
 */
#include "bilinear/Configuration.h"

#include "bilinear/AppMain.h"

#include "xassert/XAssert.h"
#include "xutils/Log.h"

using std::endl;

using namespace Bilinear;

// WARNING: For some reason, the TRY/CATCH/FINALLY block seems to result in some compiler warnings "variable 'rc' might be clobbered by 'longjmp' or 'vfork'" when I call it directly in main().
int helperMain(const std::vector<std::string>& args) 
{
    // WARNING: Must initialize library outside TRY {} block below
    std::unique_ptr<Library> lib(Library::GetPtr());

    TRY {
        logdbg << "Launching BilinearAppMain()..." << endl;

        return BilinearAppMain(*lib, args);
    }
    CATCH_ANY {
        logerror << "RELIC cryptographic library threw an exception" << endl;
        // WARNING: For this to work you must build RELIC with CHECK and VERBS defined (see preset/ or my-presets/).
        ERR_PRINT(ERR_CAUGHT);
    }
    FINALLY {
    }

    return -1;
}

int main(int argc, char *argv[]) {
    int rc = -1;

    // These will only print if they're actually enabled!
    logerror << "Error logging is enabled!" << endl;
    logwarn << "Warning logging is enabled!" << endl;
    loginfo << "Info logging is enabled!" << endl;
    logdbg << "Debug logging is enabled!" << endl;
    logtrace << "Trace logging is enabled!" << endl;
    loginfo << endl;

#ifndef NDEBUG
    loginfo << "Assertions are enabled!" << endl;
    assertTrue(true);
    assertFalse(false);
#else
    loginfo << "Assertions are disabled!" << endl;
    assertFalse(true);
    assertTrue(false);
#endif
    logdbg << endl;
    logdbg << "Number of arguments: " << argc << endl;

    std::vector<std::string> args;
    for(int i = 0; i < argc; i++) {
        args.push_back(std::string(argv[i]));
    }

    // Call application-defined AppMain()
    loginfo << endl;
    logdbg << "Launching AppMain() ..." << endl;
    loginfo << endl;

    rc = helperMain(args);

    loginfo << endl;
    loginfo << "Exited gracefully with rc = " << rc << "." << endl;
    return rc;
}
