#include<iostream>
#include<Windows.h>
#include"fun.h"

using namespace std;

int main()
{
	setlocale(LC_ALL, "ru");
	HANDLE col{ GetStdHandle(STD_OUTPUT_HANDLE) };

	int size{}, sech{}, var{};
	element* begin{}, * end{  }, * newP{};

	while (true)
	{
		SetConsoleTextAttribute(col, 15);
		system("cls");
		if (!sech)
		{
			begin = end = NULL;
			cout << "enter max number:\t";
			cin >> size;
			if (!cin)
			{
				cout << "error\n";
				cin.clear();
				cin.ignore(100, '\n');
				SetConsoleTextAttribute(col, 0);
				return 0;
			}
			else if (size <= 0)
			{
				cout << "error\n";
				SetConsoleTextAttribute(col, 0);
				return 0;
			}
			else
			{
				int numb{}, first{};
				for (int i = 0; i < size; i++)
				{
					cout << "enter number " << i + 1 << " = ";
					cin >> numb;
					if (!cin)
					{
						cout << "this is not number\n";
						i--;
						cin.clear();
						cin.ignore(100, '\n');
					}
					else if (numb < 0)
					{
						newP = new element;
						newP->numb = numb;
						newP->next = NULL;
						if (!first)
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
				}
			}

			cout << "that's all\n";
			SetConsoleTextAttribute(col, 0);
			system("pause");
			sech = 1;
		}
		else
		{
			cout << "variant\n";
			cout << "1 - show all numbers\n";
			cout << "2 - delete number\n";
			cout << "3 - write again\n";
			cout << "4 - locate min and max numbers\n";
			cout << "5 - end\n";

			cin >> var;
			if (!cin)
			{
				cout << "this is not number\n";
				SetConsoleTextAttribute(col, 0);
				system("pause");
				cin.clear();
				cin.ignore(100, '\n');
				continue;
			}

			switch (var)
			{
			case 1:
				show(begin) ? cout << "\n" : cout << "empty\n";
				SetConsoleTextAttribute(col, 0);
				system("pause");
				break;

			case 2:
				cout << "enter number that need delete:\t";
				cin >> var;
				if (!cin)
				{
					cout << "error\n";
					cin.clear();
					cin.ignore(100, '\n');
				}
				else
					dell(&begin, var) ? cout << "number delete\n" : cout << "error\n";
				SetConsoleTextAttribute(col, 0);
				system("pause");
				break;

			case 3:
				if (begin != NULL)
					clear(&begin);
				sech--;
				break;

			case 4:
				minMax(begin) ? cout << '\n' : cout << "empty\n";
				SetConsoleTextAttribute(col, 0);
				system("pause");
				break;

			case 5:
				cout << "end\n";
				SetConsoleTextAttribute(col, 0);
				return 0;
				break;

			default:
				cout << "error\n";
				SetConsoleTextAttribute(col, 0);
				system("pause");
				break;
			}
		}
	}
}