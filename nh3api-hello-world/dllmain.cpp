#include <nh3api/core.hpp>

// Display a "Hello, World!" dialog before the 3DO intro
void __stdcall HelloWorld(HiHook* hook, void* _this)
{
    NormalDialog("Hello, World!");
    THISCALL_1(void, hook->GetOriginalFunc(), _this);
}

extern "C" NH3API_DLLEXPORT
BOOL APIENTRY DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved)
{
    if ( fdwReason == DLL_PROCESS_ATTACH  )
    {
        Patcher* patcher = GetPatcher();
        if ( patcher == nullptr )
            return false;
        PatcherInstance* instance = patcher->CreateInstance("HD.Plugin.NH3API.HelloWorld");
        if ( instance )
            instance->WriteHiHook(0x4EEE31, CALL_, EXTENDED_, THISCALL_, &HelloWorld);
        else
            return false;
    }
    return true;
}
