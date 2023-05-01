#include<iostream>
#include<iomanip>
#include<Windows.h>
#include<stack>
#include<ctime>
#include<queue>
#define loo "enter the number:\t"

using namespace std;

class hashTable
{
public:
	void onul();
	void creat(int);
	void dele(int);
	int show();
	void tested();

private:
	struct hash
	{
		int numb{};
		hash* next{}, * prev{};
	};

	int size{ 7 }, h_size{};
	hash** top{ new hash * [size] };
	queue<int> numbers;
	queue<int> ver_time;
};

void main()
{
	hashTable A;
	HANDLE color{ GetStdHandle(STD_OUTPUT_HANDLE) };
	int var{}, numb{};
	A.onul();
	srand(time(NULL));

	while (true)
	{
		system("cls");
		SetConsoleTextAttribute(color, 15);

		cout << "enter\n";
		cout << "1 - creat\n";
		cout << "2 - add\n";
		cout << "3 - delete\n";
		cout << "4 - show\n";
		cout << "5 - end\n";
		cin >> var;

		switch (var)
		{
		case 1:
			cout << "enter the col:\t";
			cin >> var;

			for (int i = 0; i < var; i++)
			{
				SetConsoleTextAttribute(color, 15);
				try
				{
					cout << i + 1 << ") " << loo;
					cin >> numb;
					if (!cin)
						throw exception("this is not number");

					A.creat(numb);
					A.tested();
				}
				catch (exception& el)
				{
					SetConsoleTextAttribute(color, 4);
					cout << el.what() << '\n';
					cin.clear();
					cin.ignore(100, '\n');
					i--;
				}
			}
			SetConsoleTextAttribute(color, 2);
			cout << "all correct\n";
			break;

		case 2:
			try
			{
				cout << loo;
				cin >> numb;
				if (!cin)
					throw exception("error(this is not number)");

				A.creat(numb);
			}
			catch (exception& el)
			{
				SetConsoleTextAttribute(color, 4);
				cout << el.what() << '\n';
				cin.clear();
				cin.ignore(100, '\n');
			}

			SetConsoleTextAttribute(color, 2);
			cout << "all correct\n";
			break;

		case 3:
			try
			{
				cout << loo;
				cin >> numb;
				if (!cin)
					throw exception("error(not number)");

				A.dele(numb);

				SetConsoleTextAttribute(color, 2);
				cout << "all correct\n";
			}
			catch (exception& el)
			{
				SetConsoleTextAttribute(color, 4);
				cout << el.what() << '\n';
				cin.clear();
				cin.ignore(100, '\n');
			}
			break;

		case 4:
			cout << '\n';
			SetConsoleTextAttribute(color, 2);
			var = A.show();
			SetConsoleTextAttribute(color, 4);
			if (!var)
				cout << "empty\n";
			break;

		case 5:
			SetConsoleTextAttribute(color, rand()%99+1);
			cout << "End\n";
			SetConsoleTextAttribute(color, 0);
			exit(0);
			break;

		default:
			SetConsoleTextAttribute(color, 4);
			cout << "error(not var)\n";
			cin.clear();
			cin.ignore(100, '\n');
			break;
		}

		SetConsoleTextAttribute(color, 0);
		system("pause");
	}
}

void hashTable::onul()
{
	for (int i = 0; i < size; i++)
		top[i] = NULL;
}

void hashTable::creat(int n)
{
	int a{};
	for (int i = 0; i < h_size; i++)
	{
		a = numbers.front();
		numbers.pop();
		numbers.push(a);

		if (a == n)
			throw exception("error(same)");
	}

	numbers.push(n);
	h_size++;

	int t = n % size;
	hash* q{ top[t] };

	if (q == NULL)
	{
		q = new hash;
		q->numb = n;
		q->next = q->prev = NULL;
		top[t] = q;
		return;
	}

	hash* m{ new hash };
	m->numb = n;
	m->next = top[t];
	m->prev = NULL;
	top[t]->prev = m;
	top[t] = m;
}

void hashTable::dele(int n)
{
	int t{ n % size };
	hash* q{ top[t] };

	while (q != NULL && (*q).numb != n)
		q = (*q).next;

	if (q == NULL)
		throw exception("error(this number is none)");

	if (q == top[t])
	{
		if ((*q).next != NULL)
		{
			top[t] = (*q).next;
			top[t]->prev = NULL;
		}
		else
			top[t] = NULL;
	}
	else
	{
		if ((*q).next != NULL)
		{
			((*q).next)->prev = (*q).prev;
			((*q).prev)->next = (*q).next;
		}
		else
			((*q).prev)->next = NULL;
	}

	for (int i = 0; i < h_size; i++)
	{
		t = numbers.front();
		numbers.pop();
		if (t == n)
			break;
		numbers.push(t);
	}

	h_size--;
	delete q;
};

int hashTable::show()
{
	hash* q;
	int var{};

	for (int i = 0; i < size; i++)
	{
		q = top[i];
		if (q == NULL)
		{
			var++;
			continue;
		}

		while (q != NULL)
		{
			cout << q->numb << '\n';
			q = q->next;
		}
	}

	if (var == size)
		return 0;
	return 1;
}

void hashTable::tested()
{
	if (h_size < (double)(size * 0.7))
		return;

	for (int i = 0; i < size; i++)
	{
		if (top[i] != NULL)
		{
			hash* q{ top[i] },* m{};
			while (q!=NULL)
			{
				m = q;
				ver_time.push(m->numb);
				q = q->next;
				delete m;
			}
		}
	}

	size *= 2;

	hash** top{ new hash * [size] };
	int a{}, siz{h_size};

	onul();

	for (int i = 0; i < h_size; i++)
		numbers.pop();

	h_size = 0;

	while (siz--)
	{
		creat(ver_time.front());
		ver_time.pop();
	}
}