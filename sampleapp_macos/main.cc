/* 
 * main.cc
 */

#include <stdio.h>
#include "client/mac/handler/exception_handler.h"

namespace Raygun
{
    void dobar(int foo)
    {
        throw new std::exception();
    }

    void dofoo(int bar)
    {
        dobar(bar + 1);
    }

    void crash(int bar)
    {
        dofoo(bar + 1);
    }

    bool minidump_callback(const char *dump_dir, const char *minidump_id, void *context, bool succeeded) 
    {
        if (succeeded) 
        {
            printf("Created minidump at %s/%s.dmp\n", dump_dir, minidump_id);
        }
        else
        {
            printf("Failed to create minidump\n");
        }

        return succeeded;
    }
}

int main(int argc, char **argv)
{
    printf("SampleApp_macOS Launched\n");
  
    google_breakpad::ExceptionHandler eh(".", 0, Raygun::minidump_callback, 0, true, 0);

    Raygun::crash(1);

    printf("SampleApp_macOS Finished\n");

    return 0;
}
