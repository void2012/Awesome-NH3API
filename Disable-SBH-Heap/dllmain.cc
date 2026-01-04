#include <heapapi.h>
#include <nh3api/core.hpp>

extern "C" NH3API_DLLEXPORT BOOL APIENTRY DllMain(HINSTANCE, DWORD fdwReason, LPVOID)
{
    if (fdwReason == DLL_PROCESS_ATTACH)
    {
        Patcher* patcher = GetPatcher();
        if ( patcher == nullptr )
            return false;
        
        PatcherInstance* instance = patcher->CreateInstance("Plugin.Disable.SBH.Heap");
        if ( instance )
        {
            instance->WriteDword(0x690410, 0);         // set __sbh_threshold to zero
            instance->WriteDword(0x621523, 0x2000000); // preallocate 32 megabytes of memory for the program heap
            unsigned long ulEnableLFH = 2;
            // Enable low-fragmentation heap(LFH)
            HeapSetInformation(exe_heap.get_handle(),
                               HeapCompatibilityInformation,
                               &ulEnableLFH, sizeof(ulEnableLFH));
        }
    }
    return true;
}
