#include<iostream>
#include<ctime>
#include<fstream>
#include<Windows.h>
using namespace std;
//заполняет файл рандомными словами 
void main()
{
	HANDLE color{ GetStdHandle(STD_OUTPUT_HANDLE) };
	srand(time(NULL));

	int text_size{}, simbl{}, gran{ 20 };
	string adres{ "C:\\Users\\Admin\\Desktop\\univer\\OAiP\\15\\file\\dop1.txt" };
	ofstream file;

	file.open(adres);

	for (int i = 0; i < gran; i++)
	{
		string text{};
		text_size = rand() % 4 + 3;

		for (size_t i = 0; i <text_size; i++)
		{
			simbl = rand() % 58 + 65;

			while(simbl>=91&&simbl<=96)
			{
				simbl = rand() % 58 + 65;
			}
			text += (char)simbl;
		}

		file << text << '\n';
	}

	file.close();
	SetConsoleTextAttribute(color, 2);
	cout << "open the file\n";
	SetConsoleTextAttribute(color, 0);
}

//65 122 91 96