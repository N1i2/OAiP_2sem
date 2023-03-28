#include<iostream>
#include<Windows.h>
#include<fstream>
#define n 100

using namespace std;

struct text
{
	string ttext;
	int numb{};
	text* next;
};

int dob(text*&);
int read(text*&);

int main()
{
	HANDLE col{ GetStdHandle(STD_OUTPUT_HANDLE) };
	text* first{NULL};
	int h{};

	h=dob(first);
	
	if (!h)
		return 0;

	read(first);

	cout << "\nEnd\n";
	SetConsoleTextAttribute(col, 0);
	return 0;
}

int dob(text*& p)
{
	text* newP;
	string adres{ "C:\\Users\\Admin\\Desktop\\univer\\OAiP\\7\\dop2\\info.txt" };

	ifstream file;
	char ch{};
	int number{};
	file.open(adres);
	if (!file.is_open())
	{
		cout << "error\n";
		return 0;
	}

	while(!file.eof())
	{
		newP = new text;
		while (file.get(ch))
		{
			if (ch == '\n')
				break;
			
			newP->ttext += ch;
			newP->numb++;
		}
		newP->next = p;
		p = newP;
	}

	file.close();

	return 1;
}

int read(text*& p)
{
	if (p == NULL)
	{
		cout << "file is empty\n";
		return 0;
	}

	string mamor{};
	int min{999999};

	text* help{};

	while (p)
	{
		help = p;
		p = p->next;
		if (help->numb <= min)
		{
			min = help->numb;
			mamor = help->ttext;
		}
		if(help->numb!=0)
		cout << help->ttext;
		cout << '\n';
		delete help;
	}

	cout << "\n\nleast: " << mamor << "\nSimvl: " << min << '\n';

	return 0;
}