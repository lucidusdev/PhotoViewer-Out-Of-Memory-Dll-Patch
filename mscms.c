#include <windows.h>
#include <memoryapi.h>
#include <psapi.h> 

void Payload()
{
    ULONG startoffset = 600000;
    ULONG sizearr = 400000;
    ULONG raSize = 0;
    HANDLE hProc = GetCurrentProcess();
    DWORD_PTR baseaddr = (DWORD_PTR)GetModuleHandleA("ImagingEngine.dll");
    if (baseaddr) {
        unsigned char* buff = NULL;
        buff = (unsigned char*)malloc(sizearr + 1);
        SIZE_T bytesread = 0;
        DWORD_PTR patchoffset = 0;
        if (ReadProcessMemory(hProc, (LPVOID)(baseaddr+ startoffset), buff, sizearr, &bytesread)) {
        unsigned char p1[] = {0x85,0xC0,0x75};
        unsigned char p2[] = {0x0D,0x03,0x15,0x86};
        for (int i = 0; i < sizearr - 10; i++) {
        if (memcmp(&buff[0]+i, p1, 3) == 0 && memcmp(&buff[0]+i+5, p2,4) == 0) {
                    patchoffset = baseaddr + startoffset + i + 2;
                    break;
                }
            }
        }
        if (buff) {
            free(buff);
            buff = NULL;
        }
        if (patchoffset) {
            byte patch[] = { 0xEB };
            WriteProcessMemory(hProc, (LPVOID)patchoffset, patch, 1, NULL);
        }
    }
}

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
    {
        Payload();
        break;
    }
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}


