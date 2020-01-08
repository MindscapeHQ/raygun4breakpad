/* 
 * main.cpp
 */

#include <stdio.h>
#include "client/linux/handler/exception_handler.h"

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

    bool minidump_callback(const google_breakpad::MinidumpDescriptor &descriptor, void *context, bool succeeded) 
    {
        if (succeeded) 
        {
            printf("Created minidump at %s\n", descriptor.path());
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
    printf("SampleApp_linux Launched\n");

    google_breakpad::MinidumpDescriptor descriptor(".");
    google_breakpad::ExceptionHandler eh(descriptor, 0, Raygun::minidump_callback, 0, true, -1);

    Raygun::crash(1);

    printf("SampleApp_linux Finished\n");

    return 0;
}
