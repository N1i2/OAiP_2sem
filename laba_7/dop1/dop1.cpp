#include<iostream>
#include<Windows.h>

using namespace std;

struct text
{
	char simbl{};
	text* next{};
};

int dob(text*&, int, char*);
int read(text*&, int);

int main()
{
	HANDLE col{ GetStdHandle(STD_OUTPUT_HANDLE) };

	text* first{ NULL };

	int numb{};
	char ttext[100];

	cout << "enter the text:\t";
	gets_s(ttext);
	numb = strlen(ttext);
	if (numb <= 0)
	{
		cout << "error\n";
		SetConsoleTextAttribute(col, 0);
		return 0;
	}
	if (numb % 2 == 1)
	{
		cout << "error\n";
		SetConsoleTextAttribute(col, 0);
		return 0;
	}

	dob(first, numb, ttext);

	read(first, numb);

	cout << "\nEnd\n";
	SetConsoleTextAttribute(col, 0);
	return 0;
}

int dob(text*&p, int n, char* t)
{
	text* newP;
	for (int i = 0; i < n; i++)
	{
		newP = new text;
		newP->simbl = t[i];
		newP->next = p;
		p = newP;
	}

	return 0;
}

int read(text*& p, int n)
{
	char* buf;
	text* help;
	int i{}, j{};
	buf = new char[n / 2];

	while(p)
	{
		help = p;
		p = p->next;

		if (i < n / 2)
		{
			buf[j] = help->simbl;
			j++;
		}
		else
			cout << help->simbl;

		i++;
		delete help;
	}
	for (int i = 0; i < (n/2); i++)
	{
		cout << buf[i];
	}

	return 0;
}