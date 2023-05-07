#include<iostream>
#include<Windows.h>
#include<ctime>
#include<queue>
//var 1
#define table cout<<"\n\n\n"

using namespace std;

class schet
{
public:
	void full(int*, int);
	void vivod(int*, int, int);
	void show(int*, int);
	int Get_sizeC() { return sizeC; }
	int* bubble(int);
	int* insert(int);
private:
	queue<int> buf;
	int sizeC;
};

void main()
{
	HANDLE color{ GetStdHandle(STD_OUTPUT_HANDLE) };
	srand(time(NULL));
	schet res;

	int sizeA{ rand() % 4+4  }, sizeB{ rand() % 4+4 }, * A{ new int[sizeA] }, * B{ new int[sizeB] }, * C{};

	SetConsoleTextAttribute(color, 3);
	res.full(A, sizeA);
	cout << "A:\t\t";
	res.show(A, sizeA);
	table;

	SetConsoleTextAttribute(color, 1);
	res.full(B, sizeB);
	cout << "B:\t\t";
	res.show(B, sizeB);
	table;

	res.vivod(A, sizeA, 1);
	res.vivod(B, sizeB, 0);

	SetConsoleTextAttribute(color, 11);
	cout << "C(bubble):\t";
	res.show( res.bubble(res.Get_sizeC()), res.Get_sizeC());
	table;

	cout << "C(insert):\t";
	res.show(res.insert(res.Get_sizeC()), res.Get_sizeC());
	table;

	SetConsoleTextAttribute(color, 0);
}

void schet::full(int* arr, int size)
{

	for (int i = 0; i < size; i++)
		arr[i] = rand() % 100 + 1;
}

void schet::show(int* arr, int size)
{
	for (int i = 0; i < size; i++)
		cout << i + 1 << ')' << arr[i] << '\t';
}

void schet::vivod(int* arr, int size, int var)
{
	for (int i = 0; i < size; i++)
	{
		if (var && i % 2 == var)
		{
			buf.push(arr[i]);
			sizeC++;
		}
		else if (!var)
		{
			buf.push(arr[i]);
			sizeC++;
		}
	}
}

int* schet::bubble(int size)
{
	int* C{ new int[size] };

	for (int i = 0; i < size; i++)
	{
		C[i] = buf.front();
		buf.pop();
		buf.push(C[i]);
	}

	for (int i = 0; i < size; i++)
		for (int j = size; j >i ; j--)
			if (C[i] < C[j])
				swap(C[i], C[j]);

	return C;
}

int* schet::insert(int size)
{
	int* C{ new int[size] };

	for (int i = 0; i < size; i++)
	{
		C[i] = buf.front();
		buf.pop();
		buf.push(C[i]);
	}

	for (int i = 1; i < size; i++)
		for (int j = i - 1, g{ i }; j >= 0; j--)
			if (C[g] > C[j])
			{
				swap(C[g], C[j]);
				g--;
			}

	return C;
}