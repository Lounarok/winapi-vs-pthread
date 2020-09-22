#include <iostream>
#include <windows.h>

DWORD WINAPI helloworld(LPVOID prm) {
    DWORD cpuId = GetCurrentProcessorNumber();
    std::cout << "Hello thread on cpu "<< cpuId <<std::endl;
    return 0;
}

int main()
{
    std::cout << "WINAPI create instant run\n";
    HANDLE hInstantRun = CreateThread(
        NULL,
        0,
        &helloworld,
        NULL,
        0,// immediately run it
        NULL
    );
    WaitForSingleObject(hInstantRun, INFINITE);
    std::cout << "WINAPI create instant run done\n";
    CloseHandle(hInstantRun);

    std::cout << "WINAPI create suspend run\n";
    HANDLE hSuspendRun = CreateThread(
        NULL,
        0,
        &helloworld,
        NULL,
        CREATE_SUSPENDED,// immediately run it
        NULL
    );
    SetThreadAffinityMask(hSuspendRun, 0x01);
    std::cout << "WINAPI resume and always should be cpu 0 \n";
    ResumeThread(hSuspendRun);
    WaitForSingleObject(hSuspendRun, INFINITE);
    std::cout << "WINAPI resume done \n";
    CloseHandle(hSuspendRun);

    return 0;
}