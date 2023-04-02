#include<iostream>
#include<Windows.h>
#include<fstream>

using namespace std;

ofstream file{};

int craft(int, int*, int);
void show(int*, int, int);

void main()
{
	HANDLE col{ GetStdHandle(STD_OUTPUT_HANDLE) };
	setlocale(LC_ALL, "ru");

	int numb{}, * second{}, i{};
	string adres{ "D:\\семестр2\\ОАиП\\10\\dop1\\info.txt" };//<---- Write the address here(file's address)

	while (true)
	{
		cout << "Введите число (от 1 до 9):\t";
		cin >> numb;
		if (numb > 9 || numb < 1 || !cin)
		{
			cout << "Такое число не подходит\n";
			cin.clear();
			cin.ignore(100, '\n');
			continue;
		}
		break;
	}

	if (numb == 1)
	{
		cout << "Число всего одно:\t1\n";
		return;
	}

	second = new int[numb];
	for (int i = 0; i < numb; i++)
	{
		second[i] = 0;
	}
	second[numb - 1] = 1;
	int a{};

	file.open(adres);
	a=craft(numb, second, i);
	
	
	cout << "Такиех чисел " << a<<'\n';
	file << "Такиех чисел " << a << '\n';

	file.close();

	SetConsoleTextAttribute(col, 0);
}

int craft(int n, int* k, int i)
{
	i++;
	show(k, n, i);
	k[0]++;
	if (k[n - 1] != n+1)
		for (int j = 0; j < n; j++)
		{
			if (j != n - 1)
			{
				if (k[j] == n+1)
				{
					k[j] = 0;
					k[j + 1]++;
				}
			}
			else if (k[n - 1] == n+1)
				return i;
		}

	craft(n, k, i);
}

void show(int* k, int n, int i)
{
	cout << i << ") ";
	file << i << ") ";

	for (int i = n - 1; i >= 0; i--)
	{
		cout << k[i];
		file << k[i];
	}
	cout << '\n';
	file << '\n';
}