#define QWORD int64_t
#include <iostream>
#include <windows.h>
#include <WinUser.h>
#include <thread>
#include <sstream>
#include <mono/jit/jit.h>
#include <mono/metadata/assembly.h>
#include <mono/metadata/debug-helpers.h>
FILE* f;

HMODULE Dll;

// MONO
void run()
{
    mono_set_dirs("C:\\Program Files\\Mono\\lib",
        "C:\\Program Files\\Mono\\etc");

    //Init a domain
    MonoDomain *domain;
    domain = mono_jit_init("MonoScriptTry");
    if (!domain)
    {
        std::cout << "mono_jit_init failed" << std::endl;
        system("pause");
        return;
    }

    MonoAssembly *assembly;
    const char* assemblyPath = "D:\\Test\\MonoTestCheat.dll";
    assembly = mono_domain_assembly_open(domain, assemblyPath);
    if (!assembly)
    {
        std::cout << "mono_domain_assembly_open failed" << std::endl;
        system("pause");
        return;
    }

    MonoImage* image;
    image = mono_assembly_get_image(assembly);
    if (!image)
    {
        std::cout << "mono_assembly_get_image failed" << std::endl;
        system("pause");
        return;
    }

    MonoMethodDesc* TypeMethodDesc;
    const char* TypeMethodDescStr = "Entry:Init()";
    TypeMethodDesc = mono_method_desc_new(TypeMethodDescStr, NULL);
    if (!TypeMethodDesc)
    {
        std::cout << "mono_method_desc_new failed" << std::endl;
        system("pause");
        return;
    }

    MonoMethod* method;
    method = mono_method_desc_search_in_image(TypeMethodDesc, image);
    if (!method)
    {
        std::cout << "mono_method_desc_search_in_image failed" << std::endl;
        system("pause");
        return;
    }

    //run the method
    std::cout << "Running the static method: " << TypeMethodDescStr << std::endl;
    mono_runtime_invoke(method, nullptr, nullptr, nullptr);
}
//

DWORD __stdcall EjectThread(LPVOID lpParameter) {
    Sleep(100);
    FreeLibraryAndExitThread(Dll, 0);
    return 0;
}

void shutdown(FILE* fp, std::string reason) {
    
    std::cout << reason << std::endl;
    Sleep(1000);
    if (fp != nullptr)
        fclose(fp);
    FreeConsole();
    CreateThread(0, 0, EjectThread, 0, 0, 0);
    return;
}

QWORD WINAPI MainThread(LPVOID param)
{
    AllocConsole();
    FILE* fp;
    freopen_s(&fp, "CONOUT$", "w", stdout);
    SetConsoleTitleW(L"We been ballin, dupont on the loose");
    std::cout << "Goofy Goober (Insert to Close)" << std::endl;

    run();
    
    while (true)
    {
        Sleep(50);
        if (GetAsyncKeyState(VK_INSERT) & 1) {
            break;
        }
    }

    shutdown(fp, "Bussin Bussin");
    return 0;
}

BOOL __stdcall DllMain(HINSTANCE hModule, DWORD dwReason, LPVOID lpReserved)
{
    switch (dwReason)
    {
    case 1:
        Dll = hModule;
        HANDLE hMainThread = CreateThread(nullptr, 0, LPTHREAD_START_ROUTINE(MainThread), hModule, 0, nullptr);

        if (hMainThread)
            CloseHandle(hMainThread);

        break;
    }
    return TRUE;
}