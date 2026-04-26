#pragma once

#include <map>

class Maps 
{
    private: 
        std::map<int, int> asciiMaps;
        std::map<int, int> shiftMaps;
    public: 
        int searchAsciiMaps(int key);
        void initializeMaps();
        int searchShiftMaps(int key);
};
