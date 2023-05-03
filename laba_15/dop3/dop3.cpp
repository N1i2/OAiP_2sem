#include<iostream>
#include<Windows.h>
#include<ctime>
#include<queue>
#include<fstream>
//var4
#define white SetConsoleTextAttribute(color, 15)
#define voidCol SetConsoleTextAttribute(color, 0)
#define green SetConsoleTextAttribute(color, 2)
#define red SetConsoleTextAttribute(color, 4)

using namespace std;

class hashTable
{
public:
	void otch();
	void locate(int);
	void creat(int);
	void full_check(HANDLE);
	int locate2(int);
private:
	struct hash
	{
		int numb{};
		hash* next, * prev;
	};

	int size{ 29 };
	hash** top{ new hash * [size] };
};

void main()
{
	hashTable A;
	srand(time(NULL));
	ifstream file;
	HANDLE color{ GetStdHandle(STD_OUTPUT_HANDLE) };
	string adres{ "C:\\Users\\Admin\\Desktop\\univer\\OAiP\\15\\file\\dop3.txt" };
	int numb{};
	A.otch();
	file.open(adres);

	while (!file.eof())
	{
		file >> numb;
		A.creat(numb);
	}

	file.close();

	while (true)
	{
		system("cls");
		white;
		try
		{
			cout << "enter the number(0 for end)(enter -1 for check all):\t";
			cin >> numb;

			if (!cin)
				throw exception("error(this is not number)");

			if (!numb)
			{
				SetConsoleTextAttribute(color, rand() % 99 + 1);
				cout << "End\n";
				voidCol;
				exit(0);
			}

			if (numb == -1)
			{
				cout << '\n';
				A.full_check(color);
				voidCol;
				system("pause");
				continue;
			}

			A.locate(numb);

			green;
			cout << "there is this number\n";
		}
		catch (const std::exception&el)
		{
			red;
			cout << el.what()<<'\n';
			cin.clear();
			cin.ignore(100, '\n');
		}
		voidCol;
		system("pause");
	}
}

void hashTable::otch()
{

	for (int i = 0; i < size; i++)
		top[i] = NULL;
}

void hashTable::creat(int n)
{
	int t{ abs(n % size) };

	hash* q{ new hash };

	q->numb=n;
	q->prev = NULL;

	if (top[t] != NULL)
	{
		q->next = top[t];
		top[t]->prev = q;
	}
	else
		q->next = NULL;

	top[t] = q;
}

void hashTable::locate(int n)
{
	int t{ abs(n % size) };

	hash* q{ top[t] };

	while (q != NULL && q->numb != n)
		q = q->next;

	if (q == NULL)
		throw exception("there isn't this number");
}

void hashTable::full_check(HANDLE color)
{
	int numb{};

	for (int i = 1; i <= 100; i++)
	{
		white;

			cout << i << '\t';
			numb=locate2(i);
			if(numb!=0)
			{
				green;
				cout << numb;
			}
			else
			{
				red;
				cout << '0';
			}

		if (i % 4 == 0)
			cout << '\n';
		else
			cout << '\t';
	}
}

int hashTable::locate2(int n)
{
	int t{ abs(n % size) }, ansver{};

	hash* q{ top[t] };

	while (q != NULL)
	{
		if (q->numb == n)
			ansver++;
		q = q->next;
	}

	return ansver;
}