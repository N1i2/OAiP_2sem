#include<iostream>
#include<fstream>
#include<Windows.h>

using namespace std;

struct text
{
	string ttext{};
	text* next{};
};

int output(text*);

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	text* begin{ NULL }, * end{ NULL }, * newP{ NULL };

	string adres{ "C:\\Users\\Admin\\Desktop\\univer\\OAiP\\8\\dop3\\input.txt" };
	ifstream file_1;
	int first{};
	char ch{};

	file_1.open(adres);
	if (!file_1.is_open())
	{
		cout << "error\n";
		return 0;
	}

	while (!file_1.eof())
	{
		string help{}, number{};
		while (file_1.get(ch))
		{
			if (ch == '\n')
				break;
			else if (ch=='0' ||ch == '1' || ch == '2' || ch == '3' || ch == '4' || ch == '5' || ch == '6' || ch == '7' || ch == '8' || ch == '9')
				number += ch;
			else
				help += ch;
		}
		help += '\t';
		help += number;

		newP = new text;
		newP->ttext = help;
		newP->next = NULL;
		if (first == 0)
		{
			first++;
			begin = end = newP;
		}
		else
		{
			end->next = newP;
			end = newP;
		}
	}

	file_1.close();

	output(begin);

	return 0;
}

int output(text* begin)
{
	if (begin == NULL)
	{
		cout << "file empty\n";
		return 0;
	}

	string adres{ "C:\\Users\\Admin\\Desktop\\univer\\OAiP\\8\\dop3\\output.txt" };

	text* t{ begin };

	ofstream file_2;
	file_2.open(adres);
	if (!file_2.is_open())
	{
		cout << "error file\n";
		return 0;
	}

	while (t)
	{
		file_2 << t->ttext << '\n';
		t = t->next;
	}

	file_2.close();

	return 0;
}