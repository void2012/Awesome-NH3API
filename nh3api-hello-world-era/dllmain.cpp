#include <nh3api/era/era.hpp>

// Print plugin version upon right clicking on the credits button in the main menu
void __stdcall OnReportVersion(Era::TEvent* e)
{
    Era::ReportPluginVersion("{Hello World ERA} v1.0 ("  __DATE__ ")");
}

extern "C" NH3API_DLLEXPORT
BOOL APIENTRY DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved)
{
    if (fdwReason == DLL_PROCESS_ATTACH)
        Era::RegisterHandler(OnReportVersion, "OnReportVersion");
    return true;
}
