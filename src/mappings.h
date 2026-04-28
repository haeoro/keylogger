/*
*    ``~ Definitions for the class methods and private variables (Written by haeoro) ~``
*
*    Maps::writeKeyString() is a function created to write keys that do not have a direct ascii conversion, 
*    see constants.h:ln:12 for more info.
*
*    Maps::initializeMaps()
*    asciiMaps maps Section 1's constants in constants.h to their true ascii values.
*            
*    shiftMaps maps all special keys to their corresponding values, I.E. shift+[ returns
*    {
*
*    miscMaps maps Section 3's constants in constants.h to their corresponding ascii values.
*
*    Maps::searchAsciiMaps(int key) searches through the asciiMaps until it finds a match and returns asciiMaps->second.
*    Maps::searchShiftMaps(int key) searches through shiftMaps until argument key matches the first keypair value of any given map, returns shiftMaps->second
*    Maps::searchMiscMaps(int key) takes key argument from main, which is i from the for loop and compares it with the first key pair value then calls 
*    writeKeyString and passes miscMaps->second key value to write to logs.txt
*/

#pragma once

#include <map>
#include <string>

class Maps 
{
    private: 
        std::map<int, int> asciiMaps;
        std::map<int, int> shiftMaps;
        std::map<int, std::string> miscMaps;
    public: 
        int searchAsciiMaps(int key);
        void initializeMaps();
        int searchShiftMaps(int key);
        void writeKeyString(std::string key);
        int searchMiscMaps(int key);
};
