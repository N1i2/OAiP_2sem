#include<iostream>
#include<ctime>
#include<fstream>
#include<Windows.h>
#define col 70

using namespace std;

void main()
{
	srand(time(NULL));
	HANDLE color{ GetStdHandle(STD_OUTPUT_HANDLE) };
	int numb{};
	string adres{ "C:\\Users\\Admin\\Desktop\\univer\\OAiP\\15\\file\\dop3.txt" };
	ofstream file;

	file.open(adres);
	
	for (int i = 0; i < col; i++)
	{
		numb = rand() % 100+1;

		file << numb << '\n';
	}

	file.close();
	SetConsoleTextAttribute(color, 2);
	cout << "open the file\n";
	SetConsoleTextAttribute(color, 0);
}