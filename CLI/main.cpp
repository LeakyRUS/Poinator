#include "EncodeAndDecode.h"
#include <iostream>

int main()
{
	using namespace std;
	using Poinator::Core::Transformation::ASCII::encoding;
	using Poinator::Core::Transformation::ASCII::decoding;

	while (true)
	{
		string choise;
		cout << "Encode or decode (only ASCII) (x to exit)? (e/d/x) > ";
		getline(cin, choise);

		if ((choise[0] == 'e') || (choise[0] == 'd'))
		{
			string userText;

			cout << "Put your text here > ";
			getline(cin, userText);

			string ed;
			try
			{
				if (choise[0] == 'e')
				{
					ed = encoding(userText);
					cout << "Your encoded text: " << ed << "\nLength: " << ed.size() << '\n';
				}
				else if (choise[0] == 'd')
				{
					ed = decoding(userText);
					cout << "Your decoded text: " << ed << "\nLength: " << ed.size() << '\n';
				}
			}
			catch (runtime_error e)
			{
				cout << e.what() << '\n';
			}
		}
		else if (choise[0] == 'x')
		{
			break;
		}
		else cout << "Wrong choice!\n";

		cout << endl;
	}

	return 0;
}
