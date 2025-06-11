#include "client/windows/sender/crash_report_sender.h"
#include "client/windows/handler/exception_handler.h"
#include <Windows.h>
#include <iostream>

bool minidump_callback(const wchar_t *dump_path, const wchar_t *minidump_id, void *context, EXCEPTION_POINTERS *exinfo, MDRawAssertionInfo *assertion, bool succeeded)
{
   std::wcout << L"Minidump callback called with dump_path: " << dump_path << L", minidump_id: " << minidump_id << L", succeeded: " << succeeded << std::endl;
   google_breakpad::CrashReportSender sender(L"crash.checkpoint");

   std::wstring filename = minidump_id;
   filename += L".dmp";

   std::wcout << L"Minidump file created at: " << filename << std::endl;

   std::map<std::wstring, std::wstring> files;
   files[L"file"] = filename;

   // At this point you may include custom data to be part of the crash report.
   std::map<std::wstring, std::wstring> parameters;
   parameters.insert(std::make_pair(L"desc", L"Hello World"));

   google_breakpad::ReportResult result = sender.SendCrashReport(L"https://api.raygun.com/entries/breakpad?apikey=YOUR_API_KEY", parameters, files, 0);

   std::wcout << L"Crash report sent: " << result << std::endl;

   return true;
}

int main()
{
   google_breakpad::ExceptionHandler *pHandler = new google_breakpad::ExceptionHandler(L".", 0, minidump_callback, 0, google_breakpad::ExceptionHandler::HANDLER_ALL, MiniDumpNormal, L"", 0);

   unsigned char *test = 0;
   *test = 1;
   return 0;
}
