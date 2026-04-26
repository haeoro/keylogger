#include "mappings.h"
#include "constants.h"

#include <iostream>
#include <windows.h>

void Maps::initializeMaps() 
{
    // extended ascii mappings here. 
    asciiMaps = 
    {
        {COMMA, 44}, {EQUAL, 61}, 
        {PERIOD, 46}, {SEMICOLON, 59}, 
        {OBRACKETL, 91}, {OBRACKETR, 93}, 
        {APOSTROPHE, 39}, {VERGULE, 47}, 
        {BACKSLASH, 92}, {HYPHEN, 45}, 
        {ACUTE, 96}, 
    };

    // do shift+specialkey maps here. 

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
