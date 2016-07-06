#include <Windows.h>
#include <stdio.h>
#include <dllHeader.h>
#include <iostream>
#include <tchar.h>

//This is a global hook installation code . after tests , I find that it only works in these scenarios : normal keyboard input  .including
//Windows Scurity Window (Sometimes pops up when you open a RDP connection).Notepad .Chrome . and Other normal Windows Window application (Non-Full Screen Remote Desktop Connection)
//This wokrs in Notepad full screen mode .
//This code doesn't work in these scenarios : UAC ,Full Screen Remote Desktop Connection , Windows Logon Screen .I will add more later 
int main()
{

    /*
    * Load library in which we'll be hooking our functions.
    */
    HMODULE dll = LoadLibrary(".\\dll.dll");
    if(dll == NULL)
    {
       // printf("The DLL could not be found.\n");
        getchar();
        return -1;
    }

    /*
    * Get the address of the function inside the DLL.
    */
    HOOKPROC addr = (HOOKPROC)GetProcAddress(dll, "meconnect");
    if(addr == NULL)
    {
       // printf("The function was not found.\n");
        getchar();
        return -1;
    }

    /*
    * Hook the function.
    */
    HHOOK handle = SetWindowsHookEx(WH_KEYBOARD, addr, dll, 0);
    if(handle == NULL)
    {
     //   printf("The KEYBOARD could not be hooked.\n");
    }

    /*
    * Unhook the function.
    */
    //printf("Program successfully hooked.\nPress enter to unhook the function and stop the program.\n");


    if (RegisterHotKey(
                NULL,
                1,
                MOD_ALT,
                0x42))  //0x42 is 'b'
    {
      //  _tprintf(_T("Hotkey 'ALT+b' registered, using MOD_NOREPEAT flag\n"));
    }

    MSG msg = {0};

    // this is a windows message loop
    while (GetMessage(&msg, NULL, 0, 0) != 0)
    {
        if (msg.message == WM_HOTKEY)
        {
           // _tprintf(_T("WM_HOTKEY received\n"));
             UnhookWindowsHookEx(handle);
             return 0;
        }
    }

    //indicate the hook has been successfully installed on this PC .

   // following will never get executed
    getchar();
    UnhookWindowsHookEx(handle);

    return 0;
}
