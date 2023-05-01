#include<iostream>
#include<ctime>
#include<Windows.h>
#include<queue>
#include<math.h>

#define white SetConsoleTextAttribute(color, 15)
#define voidCol SetConsoleTextAttribute(color, 0)
#define red SetConsoleTextAttribute(color, 4)
#define green SetConsoleTextAttribute(color, 2)
#define clr cin.clear()
#define ign cin.ignore(100, '\n')
//var3
using namespace std;

class hashTable
{
public:
	void otch();
	void creat(int);
	void dele(int);
	int show();
	void tested();
private:
	struct hash
	{
		int numb;
		hash* next, * prev;
	};

	double a{ (sqrt(5) - 1) / 2 }, one{ 1 };
	int size{ 7 }, h_size{};
	queue<int> ver_time;
	hash** top{ new hash * [size] };
};

void main()
{
	srand(time(NULL));
	HANDLE color{ GetStdHandle(STD_OUTPUT_HANDLE) };
	hashTable A;
	int var{}, numb{};
	A.otch();

	while (true)
	{
		system("cls");
		white;

		cout << "enter\n";
		cout << "1 - creat\n";
		cout << "2 - add\n";
		cout << "3 - dele\n";
		cout << "4 - show\n";
		cout << "5 - end\n";
		cin >> var;

		switch (var)
		{
		case 1:
			cout << "enter the size:\t";
			cin >> var;
			if (!cin)
			{
				red;
				cout << "error(not number)\n";
				clr;
				ign;
				break;
			}

			for (int i = 0; i < var; i++)
			{
				try
				{
					cout << i + 1 << ") enter the number:\t";
					cin >> numb;
					if (!cin)
						throw exception("error(error not number)");

					A.creat(numb);
				}
				catch (exception&el)
				{
					red;
					cout << el.what() << '\n';
					white;
					clr;
					ign;
					i--;
				}
			}
			green;
			cout << "all correct\n";
			break;

		case 2:
			try
			{
				cout << "enter the number:\t";
				cin >> numb;
				if (!cin)
					throw exception("error(error not number)");

				A.creat(numb);

				green;
				cout << "all correct\n";
			}
			catch (exception& el)
			{
				red;
				cout << el.what() << '\n';
				clr;
				ign;
			}
			break;

		case 3:
			try
			{
				cout << "\nDo\n";
				green;
				var = A.show();
				red;
				if (!var)
					throw exception("empty");

				white;
				cout << "\nenter the number:\t";
				cin >> numb;
				if (!cin)
					throw exception("error(not number)");

				A.dele(numb);

				cout << "\nPosle\n";
				green;
				var = A.show();
				SetConsoleTextAttribute(color, 6);
				if (!var)
					cout << "empty\n";
			}
			catch (exception&el)
			{
				red;
				cout << el.what() << '\n';
				clr;
				ign;
			}
			break;

		case 4:
			cout << '\n';
			green;
			var = A.show();
			red;
			if (!var)
				cout << "empty\n";
			break;

		case 5:
			SetConsoleTextAttribute(color, rand() % 99 + 1);
			cout << "End\n";
			voidCol;
			exit(0);
			break;

		default:
			red;
			cout << "error(not var)\n";
			clr;
			ign;
			break;
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
	double first{ ((double)n * a) };
	first -= (int)first;
	first *= size;
	int t{ (int)first };

	hash* m{ top[t] };

	while (m != NULL)
	{
		if (m->numb == n)
			throw exception("error(same)");
		m = m->next;
	}

	hash* q{ new hash};
	q->numb = n;
	q->prev = NULL;
	if (top[t] == NULL)
	{
		q->next = NULL;
		top[t] = q;
	}
	else
	{
		q->next = top[t];
		top[t]->prev = q;
		top[t] = q;
	}

	h_size++;
}

void hashTable::dele(int n)
{
	double first{ ((double)n * a) };
	first -= (int)first;
	first *= size;
	int t{ (int)first };

	hash* q{ top[t] };

	while (q != NULL && q->numb != n)
		q = q->next;

	if (q == NULL)
		throw exception("error(not this number)");

	if (q == top[t])
	{
		if (q->next != NULL)
		{
			top[t] = q->next;
			top[t]->prev = NULL;
		}
		else
			top[t] = NULL;
	}
	else
	{
		if (q->next != NULL)
		{
			((*q).prev)->next = q->next;
			((*q).next)->prev = q->prev;
		}
		else
			((*q).prev)->next = NULL;
	}

	h_size--;
	delete q;
}

int hashTable::show()
{
	int v{};

	for (int i = 0; i < size; i++)
	{
		if (top[i] != NULL)
		{
			hash* q{ top[i] };

			while (q != NULL)
			{
				cout << q->numb << '\n';
				q = q->next;
			}
		}
		else
			v++;
	}

	if (v == size)
		return 0;
	return 1;
}