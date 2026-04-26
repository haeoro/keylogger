#include "constants.h"
#include "mappings.h"

#include <windows.h>
#include <iostream>

int findShiftPlusKey() 
{
    Maps vkMaps;
    vkMaps.initializeMaps();
    for (int i = 1; i < 254; i++) 
    { 
        int keyI = GetAsyncKeyState(i);
        while (keyI == KEY_IS_PRESSED || keyI == KEY_IS_PRESSED2 && i != 16 && i != 160) 
        {
            
            if (i >= 128 && i <= 255) 
            {
                return vkMaps.searchShiftMaps(i);
            }
            else if (i >= 48 && i <= 57) 
            {
                return vkMaps.searchShiftMaps(i);
            }
            else if (GetKeyState(VK_CAPITAL) == 1 && i >= 65 && i <= 90) 
            {
                return (i + 32);
            }
            else if (GetKeyState(VK_CAPITAL) == 0 && i >= 65 && i <= 90) 
            {
                return i;
            }
            return 1;
        }
    }
}

int isShiftPressed() 
{
    int check_shift = GetKeyState(VK_SHIFT);
    if (check_shift == -127 || check_shift == -128)  
    {
        return 1;
    }
    else 
    {
        return 0;
    }
}

int isCapslockOn(int decimal_key_val) 
{
    if (GetKeyState(VK_CAPITAL) == 0 && decimal_key_val >= 65
    && decimal_key_val <= 90)
    {
        return decimal_key_val + 32;
    }
    else
    {
        return decimal_key_val;
    }
}
