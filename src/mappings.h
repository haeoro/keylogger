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
