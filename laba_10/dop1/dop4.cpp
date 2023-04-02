#include<iostream>
#include<ctime>
#include<Windows.h>
#include<string.h>
#define n 200
#define r 1

using namespace std;

int show(int*, int, int);
void cluck(int);

int app{};
HANDLE col{ GetStdHandle(STD_OUTPUT_HANDLE) };

void main()
{
	srand(time(NULL));
	setlocale(LC_ALL, "ru");
	if (n < r)
	{
		cout << "error\n";
		return;
	}
	int numb[n]{}, loc{}, x{}, lop{};

	while (true)
	{
		numb[0] = rand() % n + 1;

		for (int i = 1; i < n; i++)
		{
			numb[i] = rand() % n + 1;
			for (int j = i - 1; j >= 0; j--)
				if (numb[i] == numb[j])
				{
					i--;
					break;
				}
		}

		if (numb[n - 1] == r)
		{
			for (int i = 0; i < n; i++)
				numb[i] = 0;
			continue;
		}
		break;
	}

	cout << "\t(1)\t";
	for (int i = 2; i <= 10; i++)
	{
		cout << '(' << i << ')' << '\t';
	}
	cout << "\n\n(1)\t";
	for (int i = 0, t = 2; i < n; i++)
	{
		if (numb[i] == r)
		{
			SetConsoleTextAttribute(col, 2);
			cout << numb[i] << '\t';
			SetConsoleTextAttribute(col, 15);
			lop = i + 11;
		}
		else
			cout << numb[i] << '\t';
		if ((i + 1) % 10 == 0 && i != n - 1)
		{
			cout << "\n\n(" << t << ")\t";
			t++;
		}
	}

	int pau{};
	cout << "\n\nНужен колькулятор?(1 - да 0 - нет)\t";
	cin >> pau;
	if (!cin || (pau != 0 && pau != 1))
	{
		cout << "Это неверное значит нет\n\n";
		cin.clear();
		cin.ignore(100, '\n');
		pau = 0;
	}
	else if (pau == 0)
		cout << "Ну ладно\n";

	if (pau)
		cluck(lop);

	cout << "\n\n\nВведите n:\t";
	cin >> loc;
	if (!cin || loc <= 0)
	{
		cout << "Такого чила не может быть\n";
		return;
	}
	if (loc >= n)
	{
		cout << "Ну не я такое даже считать не буду\n";
		return;
	}

	show(numb, loc, x);

	if (app < n)
	{
		cout << "Это число\n";
		SetConsoleTextAttribute(col, 2);
		cout << numb[app] << '\t';
		SetConsoleTextAttribute(col, 15);
		if (pau == 0)
		{
			cout << "\n\nНужен колькулятор для проверки?(1 - да 0 - нет)\t";
			cin >> pau;
			if (!cin || (pau != 0 && pau != 1))
			{
				cout << "Это неверное значит нет\n\n";
				cin.clear();
				cin.ignore(100, '\n');
				pau = 0;
			}
			else if (pau == 0)
				cout << "Ну ладно\n";

			if (pau)
				cluck(lop);
		}
	}
	else
		cout << "Както мнаговато вы дали\n";
}

void cluck(int lop)
{
	int first{}, second{}, stolb{ 1 }, perv{}, t{}, result{};
	while (t != 2)
	{
		if (t == 0)
		{
			second = (lop / 10);
			cout << "Введите номер строки исомого числа)\t";
		}
		else
		{
			second = lop % 10;
			cout << "Введите номер столбца исомого числа))\t";
		}

		scanf("%d", &first);

		result = first - second;

		if (t == 0)
			perv = result * 10;
		else
			stolb = result;

		if (perv < 0)
		{
			if (perv % 10 == 0)
				cout << "Это последний элемент строки\n";
			else
			cout << "Нельзя задавать числа до зеленого\n";
			t=-1;
		}
		if (perv == 0 && stolb <= 0)
		{
			cout << "Нельзя задавать числа до зеленого или само число\n";
			stolb = 1;
			t = -1;
		}
		t++;
	}
	result = perv + result;
	cout << "N = " << result;
}

int show(int* A, int l, int x)
{
	if (A[x] != r)
	{
		x++;
		show(A, l, x);
	}
	else
	{
		app = x + l;
	}

	return x;
}