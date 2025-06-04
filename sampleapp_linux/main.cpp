#include <stdio.h>
#include "client/linux/handler/exception_handler.h"
#include "common/linux/google_crashdump_uploader.h"
// #include "client/linux/sender/crash_report_sender.h"
// #include "client/linux/sender/crash_report_sender.cc"
#include "client/linux/handler/exception_handler.h"
#include "client/linux/handler/exception_handler.cc"
#include "client/linux/crash_generation/crash_generation_client.cc"
// #include "client/linux/crash_generation/minidump_generator.cc"
#include "common/linux/http_upload.cc"
// #include "common/linux/guid_string.cc"

bool minidump_callback(const wchar_t* dump_path, const wchar_t* minidump_id, void* context, EXCEPTION_POINTERS* exinfo, MDRawAssertionInfo* assertion, bool succeeded)
{
   google_breakpad::CrashReportSender sender(L"crash.checkpoint");

   std::wstring filename = L"D:\\TestData\\TestData\\Crashes";
   filename += L"\\";
   filename += minidump_id;
   filename += L".dmp";

   std::map<std::wstring, std::wstring> files;
   files[L"upload_file_minidump"] = filename;

   // At this point you may include custom data to be part of the crash report.
   std::map<std::wstring, std::wstring> parameters;
   parameters.insert(std::make_pair(L"desc", L"Hello World"));

   sender.SendCrashReport(L"https://api.raygun.com/entries/breakpad?apikey=6MOcb9leNrs4EwIo7YtOQ", parameters, files, 0);

   return true;
}

int main()
{
	google_breakpad::ExceptionHandler *pHandler = new google_breakpad::ExceptionHandler(L"D:\\TestData\\TestData\\Crashes", 0, minidump_callback, 0, google_breakpad::ExceptionHandler::HANDLER_ALL, MiniDumpNormal, L"", 0);

	unsigned char* test = 0;
	*test = 1;
	return 0;
}


// /* 
//  * main.cpp
//  */

// #include <stdio.h>
// #include "client/linux/handler/exception_handler.h"

// namespace Raygun
// {
//     void dobar(int foo)
//     {
//         throw new std::exception();
//     }

//     void dofoo(int bar)
//     {
//         dobar(bar + 1);
//     }

//     void crash(int bar)
//     {
//         dofoo(bar + 1);
//     }

//     bool minidump_callback(const google_breakpad::MinidumpDescriptor &descriptor, void *context, bool succeeded) 
//     {

//          if (succeeded)
//          {
//              printf("Created minidump at %s\n", descriptor.path());
//          }
//         else
//         {
//             printf("Failed to create minidump\n");
//         }

//         return succeeded;
//     }
// }

// int main(int argc, char **argv)
// {
//     printf("SampleApp_linux Launched\n");

//     google_breakpad::MinidumpDescriptor descriptor(".");
//     google_breakpad::ExceptionHandler eh(descriptor, 0, Raygun::minidump_callback, 0, true, -1);

//     Raygun::crash(1);

//     printf("SampleApp_linux Finished\n");

//     return 0;
// }
