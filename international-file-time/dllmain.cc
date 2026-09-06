#include <nh3api/core.hpp>

inline void writeTwoDigits(char* dst, int16_t value)
{
    dst[0] = static_cast<char>('0' + (value / 10));
    dst[1] = static_cast<char>('0' + (value % 10));
}

inline void writeFourDigits(char* dst, int16_t value)
{
    dst[0] = static_cast<char>('0' + (value / 1000));
    dst[1] = static_cast<char>('0' + ((value / 100) % 10));
    dst[2] = static_cast<char>('0' + ((value / 10) % 10));
    dst[3] = static_cast<char>('0' + (value % 10));
}

// call 0x584508
int __cdecl HH_sprintfInternationalDate(std::array<char, 100>& dst, const char*, int16_t month, int16_t day, int16_t year, int16_t hour, int16_t minute)
{
   writeTwoDigits(&dst[0], day);
   dst[2] = '.';
   writeTwoDigits(&dst[3], month);
   dst[5] = '.';
   writeFourDigits(&dst[6], year);
   dst[10] = ' ';
   writeTwoDigits(&dst[11], hour);
   dst[13] = ':';
   writeTwoDigits(&dst[14], minute);
   dst[16] = '\0';
   
   return 16;
}

extern "C" NH3API_DLLEXPORT
BOOL APIENTRY DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved)
{
    if ( fdwReason == DLL_PROCESS_ATTACH  )
    {
        Patcher* patcher = GetPatcher();
        if ( patcher == nullptr )
            return false;
        PatcherInstance* instance = patcher->CreateInstance("HD.Plugin.InternationalDateFormat");
        if ( instance )
      {
            instance->WriteHiHook(0x584508, CALL_, DIRECT_, CDECL_, &HH_sprintfInternationalDate);
      }
        else
            return false;
    }
    return true;
}
