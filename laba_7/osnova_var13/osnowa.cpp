#include<iostream>
#include<Windows.h>
#include"fun.h"//подключение заголовочноего файла
int n{ 2 };
using namespace std;
//var 10
int main()
{
	setlocale(LC_ALL, "ru");
	HANDLE col{ GetStdHandle(STD_OUTPUT_HANDLE) };
	int number{};
	int var{};
	element* first{ NULL };//начало стека

	while (true)
	{
		SetConsoleTextAttribute(col, 15);
		system("cls");

		cout << "variant\n1 - add new number\n2 - clear all stek\n3 - input stek in file\n4 - output stek from file \n5 - pavtor\n6 - end\n";
		cin >> var;
		if (!cin)
		{
			cout << "error\n";
			cin.clear();
			cin.ignore(100, '\n');
			SetConsoleTextAttribute(col, 0);
			system("pause");
			continue;
		}

		switch (var)
		{
		case 1:
			dob(first) ? cout << "number added\n" : cout << "error\n";
			SetConsoleTextAttribute(col, 0);
			system("pause");
			break;

		case 2:
			clear(first) ? cout << "number delete\n" : cout << "stek empty\n";
			SetConsoleTextAttribute(col, 0);
			system("pause");
			break;

		case 3:
			save(first) ? cout << "stek input in file\n" : cout << "error\n";
			SetConsoleTextAttribute(col, 0);
			system("pause");
			break;

		case 4:
			read(first) ? cout << "number in stek\n" : cout << "file empty\n";
			SetConsoleTextAttribute(col, 0);
			system("pause");
			break;

		case 5:
			int f;
			f = schet(first);
			f ? cout << "there are " << f << " such numbers\n" : cout << "there are no such numbers or error\n";
			SetConsoleTextAttribute(col, 0);
			system("pause");
			break;

		case 6:
			cout << "end\n";
			SetConsoleTextAttribute(col, 0);
			return 0;
			break;

		default:
			cout << "error\n";
			break;
		}
	}
}