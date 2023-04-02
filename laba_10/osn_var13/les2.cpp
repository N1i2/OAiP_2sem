#include<iostream>

using namespace std;

int s(int);

void main()
{
	setlocale(LC_ALL, "ru");
	int numb{};

	cout << "Введите неотрецатеьное число:\t";
	cin >> numb;
	
	if (!cin||numb<0)
	{
		cout << "Это не число\n";
		return;
	}

	numb=s(numb)+10;
	cout << numb;
}

int s(int n)
{
	if (n <= 100)
	{
		n += 4;
		s(n);
	}
	else
	{
		n -= 4;
		return n += 4;
	}
}