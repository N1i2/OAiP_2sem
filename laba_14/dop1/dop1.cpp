#include<iostream>
#include<Windows.h>
#include<queue>
#include<ctime>
//var2
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
		int numb{};
		hash* next{}, * prev{};
	};

	int size{ 7 }, h_size{}, sum{ rand() % 9 + 1 };
	double dekl{ 10 }, seven{7};
	hash** top{ new hash * [size] };
	queue<int> numbers;
	queue<int> ver_time;
};

void main()
{
	srand(time(NULL));
	HANDLE color{ GetStdHandle(STD_OUTPUT_HANDLE) };
	int var{}, numb{};
	hashTable A;

	A.otch();

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
			cout << "enter the size:\t";
			cin >> var;
			if (!cin)
			{
				SetConsoleTextAttribute(color, 4);
				cout << "error(not numb)\n";
				cin.clear();
				cin.ignore(100, '\n');
				break;
			}
			for (int i = 0; i < var; i++)
			{
				try
				{
					cout<<i+1 << ") enter the number:\t";
					cin >> numb;
					if (!cin)
						throw exception("error(not number)");

					A.creat(numb);
					A.tested();
				}
				catch (exception&el)
				{
					SetConsoleTextAttribute(color, 4);
					cout << el.what() << '\n';
					SetConsoleTextAttribute(color, 15);
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
				cout << "enter the number:\t";
				cin >> numb;
				if (!cin)
					throw exception("error(not number)");

				A.creat(numb);
				A.tested();

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

		case 3:
			try
			{
				cout << "\nDo\n";
			SetConsoleTextAttribute(color, 2);
			var=A.show();
			SetConsoleTextAttribute(color, 4);
			if (!var)
				throw exception("empty");

			SetConsoleTextAttribute(color, 15);
				cout << "\nenter the number\n";
				cin >> numb;
				if (!cin)
					throw exception("error(not number)");
				A.dele(numb);

				cout << "\nPosle\n";
				SetConsoleTextAttribute(color, 2);
				var = A.show();
				SetConsoleTextAttribute(color, 6);
				if (!var)
					cout<<"now empty\n";
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
			var=A.show();
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

void hashTable::otch()
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

	double e{ ((double)n + (double)sum) / seven };
	int r= (n + sum) / seven ;
	e -= (double)r;
	e *= dekl;
	int t{ (int)e };

	if(t>=size)
		t %= size;

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
	m->prev = NULL;
	m->next = top[t];
	top[t]->prev = m;
	top[t] = m;
}

void hashTable::dele(int n)
{
	double e{ ((double)n + (double)sum) / seven };
	int r = (n + sum) / seven;
	e -= (double)r;
	e *= dekl;
	int t{ (int)e };

	if (t >= size)
		t %= size;

	hash* q{ top[t] };

	while (q != NULL && q->numb != n)
		q = q->next;

	if (q == NULL)
		throw exception("error(this number not locate)");

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

	int a{};

	while(true)
	{
		a = numbers.front();
		numbers.pop();
		if (a == n)
			break;
		numbers.push(a);
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

void hashTable::tested()
{
if (h_size < (double)(size*0.7))
		return;

	for (int i = 0; i < size; i++)
	{
		if (top[i] != NULL)
		{
			hash* q{ top[i] }, *m;

			while (q!=NULL)
			{
				m = q;
				q = q->next;
				delete m;
			}
		}
	}

	size *= 2;
	top = new hash * [size];

	otch();
	
	int siz{ h_size };

	while (h_size--)
	{
		ver_time.push(numbers.front());
		numbers.pop();
	}

	sum=rand() % 9 + 1;
	if (size > dekl)
		dekl *= 10;

	for (int i = 0; i < siz; i++)
	{
		creat(ver_time.front());
		ver_time.pop();
	}
}