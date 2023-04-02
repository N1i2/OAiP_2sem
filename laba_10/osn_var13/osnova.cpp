#include<iostream>

using namespace std;

int nn(int);
void ntn(int, int);

int ans{};

void main()
{
	setlocale(LC_ALL, "ru");
	int numb{};
	
	cout << "Введите число:\t";
	cin >> numb;
	if (!cin || numb <= 0)
	{
		cout << "Это число не подходт\n";
		return;
	}

	nn(numb);
	cout<<"Таких чисел:\t"<<ans<<'\n';
}

int nn(int n)
{
	int i{};

	ntn(n, i);

	return ans;
}

void ntn(int n, int i)
{
	int x{};
	i++;
	if (n % i == 0)
		x++;
	if (i != n)
		ntn(n, i);

	if (x == 1)
		ans++;
}