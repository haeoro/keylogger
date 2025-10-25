#include <iostream>
#include <windows.h>

int main() 
{
	while (1) 
	{
		Sleep(1);
		int vkeys[] = { 0x41, 0x42, 0x43 };
		for (int key : vkeys) 
		{
			if (GetAsyncKeyState(key) != 0) 
			{
				std::cout << "true";
				return 0;
			}
		}
	}
}

// find a way to wait until it's done and write it to console. 
