#include<iostream>
#include<Windows.h>
#include<ctime>
#include<vector>

using namespace std;

void hoara(int*, int, int);

void main()
{
	srand(time(NULL));
	HANDLE color{ GetStdHandle(STD_OUTPUT_HANDLE) };
	vector<int> C;
	int size_A{ rand() % 6 + 5 }, size_B{ rand() % 6 + 5 }, * A{ new int[size_A] }, * B{ new int[size_B] }, numb{}, index{}, var{};

	SetConsoleTextAttribute(color, 15);
	cout << "enter the var(1 - hoara, bubble):\t";
	cin >> var;

	SetConsoleTextAttribute(color, 1);
	for (int i = 0; i < size_A; i++)
	{
		numb = rand()%100 + 1;
		C.push_back(numb);
		A[i] = numb;
		cout << i + 1 << ')' << A[i] << '\t';
	}
	cout << "\n\n";	
	SetConsoleTextAttribute(color, 11);
	for (int i = 0; i < size_B; i++)
	{
		numb = rand() % 100 + 1;
		B[i] = numb;
		cout << i + 1 << ')' << B[i] << '\t';
	}

	for (int i = 1; i < size_B; i++)
		if (B[i] >= B[index])
			index = i;

	SetConsoleTextAttribute(color, 4);
	cout << "\n\nmax:\t" << B[index]<<"\tindex:\t"<<index+1;

	for (int i = index; i < size_B; i++)
	{
		if (i % 2 != 0) 
		{
			size_A++;
			C.push_back(B[i]);
		}
	}

	A = new int[size_A];

	for (int i = 0; i < size_A; i++)
	{
		A[i] = C.back();
		C.pop_back();
	}

	if (var == 1)
		hoara(A, 0, size_A-1);
	else
	for (int i = 0; i < size_A; i++)
		for (int j = size_A-1; j >= i; j--)
			if (A[i] > A[j])
				swap(A[i], A[j]);

	cout << "\n\n";

	SetConsoleTextAttribute(color, 3);
	for (int i = 0; i < size_A; i++)
		cout << i + 1 << ')' << A[i] << '\t';

	SetConsoleTextAttribute(color, 0);
}

void hoara(int *arr, int left, int right)
{
	if (left < right)
	{
		int polov{arr[right]}, i{ left - 1 };

		for (int j = left; j <= right - 1; j++)
		{
			if (arr[j] <= polov) 
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