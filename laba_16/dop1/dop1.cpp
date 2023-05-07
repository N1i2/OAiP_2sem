#include<iostream>
#include<Windows.h>
#include<ctime>
#include<queue>
//var 7
using namespace std;

class schet
{
public:
	void full(int, int*);
	void vnos(int*, int, int);
	int* sort_bubble();
	int* sort_hoar();
	int Get_size();
	void hoara(int*, int, int);
	void show(int*, int);
private:
	queue<int> buf;
	int t{};
};

void full(int, int*);
void vnos(int*, int, int);

void main()
{
	HANDLE color{ GetStdHandle(STD_OUTPUT_HANDLE) };
	srand(time(NULL));
	schet res;

	int sizeA{ rand()%6 + 5 }, sizeB{ rand() % 6 + 5 }, * A{ new int[sizeA] }, * B{ new int[sizeB] }, * C;

	res.full(sizeA, A);
	SetConsoleTextAttribute(color, 3);
	res.show(A, sizeA);

	cout << "\n\n";

    res.full(sizeB, B);
	SetConsoleTextAttribute(color, 1);
	res.show(B, sizeB);

	res.vnos(A,sizeA,  1);
	res.vnos(B,sizeB, 0);

	C = res.sort_bubble();

	cout << "\n\n";

	SetConsoleTextAttribute(color, 11);
	cout << "bubble\n";
	res.show(C, res.Get_size());

	C = res.sort_hoar();
	cout << "\n\nhoar\n";
	res.show(C, res.Get_size());
	SetConsoleTextAttribute(color, 0);
}

int schet::Get_size()
{
	return t;
}

void schet::full(int size, int* arr)
{
	for (int i = 0; i < size; i++)
		arr[i] = rand() % 100 + 1;
}

void schet::vnos(int* arr, int size,int poisk)
{
	for (int i = 0; i < size; i++)
		if (arr[i] % 2 == poisk)
		{
			buf.push(arr[i]);
			t++;
		}
}

void schet::show(int* arr, int size)
{
	for (int i = 0; i < size; i++)
		cout << i + 1 << ')' << arr[i] << '\t';
}

int* schet::sort_bubble()
{
	int* C{};

	C = new int[t];

	for (int i = 0; i < t; i++)
	{
		C[i] = buf.front();
		buf.pop();
		buf.push(C[i]);
	}

	for (int i = 0; i < t; i++)
		for (int j = t - 1; j >= i; j--)
			if (C[j] > C[i])
				swap(C[j], C[i]);

	return C;
}

int* schet::sort_hoar()
{
	int* C{};

	C = new int[t];

	for (int i = 0; i < t; i++)
	{
		C[i] = buf.front();
		buf.pop();
	}

	hoara(C, 0, t - 1);

	return C;
}

void schet::hoara(int* arr, int left, int right)
{
	if (left < right)
	{
		int polov{ arr[right] }, i{ left - 1 };

		for (int j = left; j <= right - 1; j++)
		{
			if (arr[j] >= polov)
			{
				i++;
				swap(arr[i], arr[j]);
			}
		}
		swap(arr[i + 1], arr[right]);

		hoara(arr, left, i);
		hoara(arr, i + 2, right);
	}
}