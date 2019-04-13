#include <string>
#include <iostream>
#include "Dll.h"

int main()
{
	Ed erd;

	while (true)
	{
		std::string choise;
		std::cout << "Encode or decode (only ASCII) (x to exit)? (e/d/x) > ";
		std::getline(std::cin, choise);

		if ((choise[0] == 'e') || (choise[0] == 'd'))
		{
			std::string userText;

			std::cout << "Put your text here > ";
			std::getline(std::cin, userText);
			std::cout << "Your text length: " << userText.size() << '\n';
			std::string ed;
			try
			{
				if (choise[0] == 'e')
				{
					char* resFrom = erd.Encode(userText.c_str());
					if (resFrom == nullptr)
					{
						throw 1;
					}
					if (resFrom[0] == ' ')
					{
						throw 1;
					}
					ed = resFrom;
					delete[] resFrom;
					std::cout << "Your encoded text: " << ed << "\nLength: " << ed.size() << '\n';
				}
				else if (choise[0] == 'd')
				{
					char* resFrom = erd.Decode(userText.c_str());
					if (resFrom == nullptr)
					{
						throw 1;
					}
					if (resFrom[0] == ' ')
					{
						throw 1;
					}
					ed = resFrom;
					delete[] resFrom;
					std::cout << "Your decoded text: " << ed << "\nLength: " << ed.size() << '\n';
				}
			}
			catch (...)
			{
				char* resFrom = erd.GetLastError();
				if (resFrom == nullptr)
				{
					return 1;
				}
				ed = resFrom;
				delete[] resFrom;
				std::cout << ed;
			}
		}
		else if (choise[0] == 'x')
		{
			break;
		}
		else std::cout << "Wrong choice!\n";

		std::cout << std::endl;
	}

	return 0;
}
