#include<iostream>
#include<Windows.h>
#include<queue>
#include<iomanip>
#include<ctime>

#define clr cin.clear()
#define ign cin.ignore(100, '\n')
#define white SetConsoleTextAttribute(color, 15)
#define voidCol SetConsoleTextAttribute(color, 0)
#define red SetConsoleTextAttribute(color, 4)
#define green SetConsoleTextAttribute(color, 2)

using namespace std;

class hashTable
{
public:
	void otch();
	void creat(int, int);
	void dele(int, HANDLE);
	int show();
	void locate(int, HANDLE);
	void tested();
	int Set_h_size();
private:
	struct hash
	{
		int grup{}, col{};
		hash* next,* prev;
	};

	int size{7}, h_size{};
	hash** top{ new hash * [size] };
	queue<int> grup_time;
	queue<int> col_time;
};

void main()
{
	HANDLE color{ GetStdHandle(STD_OUTPUT_HANDLE) };
	hashTable A;
	int var{}, grup{}, col{};
	srand(time(NULL));
	A.otch();

	while (true)
	{
		system("cls");
		white;

		cout << "enter\n";
		cout << "1 - creat\n";
		cout << "2 - add\n";
		cout << "3 - delete\n";
		cout << "4 - show\n";
		cout << "5 - locate\n";
		cout << "6 - end\n";
		cin >> var;

		switch (var)
		{
		case 1:
			cout << "enter the size:\t";
			cin >> var;
			if (!cin)
			{
				cout << "error(not number)\n";
				cin.clear();
				cin.ignore(100, '\n');
				break;
			}

			for (int i = 0; i < var; i++)
			{
				try
				{
					cout<<'\n' << i + 1 << ") enter the grup:\t";
					cin >> grup;
					if (!cin)
						throw exception("error(not number)");

					if (grup < 1)
						throw exception("this is impossible");
					
					cout<<"enter the grup's size:\t";
					cin >> col;
					if (!cin)
						throw exception("error(not number)");

					if (col < 1)
						throw exception("this is impossible");

					A.creat(grup, col);
					A.tested();
				}
				catch (exception&el)
				{
					red;
					cout << el.what()<<'\n';
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
				cout << "\nenter the grup:\t";
				cin >> grup;
				if (!cin)
					throw exception("error(not number)");

				if (grup < 1)
					throw exception("this is impossible");

				cout << "enter the grup's size:\t";
				cin >> col;
				if (!cin)
					throw exception("error(not number)");

				if (col < 1)
					throw exception("this is impossible");

				A.creat(grup, col);
				A.tested();

				green;
				cout << "all correct\n";
			}
			catch (exception& el)
			{
				red;
				cout << el.what() << '\n';
				white;
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
				cout << "enter the grup(for delete):\t";
				cin >> grup;
				if (!cin)
					throw exception("error(not number)");
				A.dele(grup, color);

				cout << "\nPosle\n";
				green;
				var = A.show();
				SetConsoleTextAttribute(color, 6);
				if (!var)
					cout<<"empty\n";
			}
			catch (exception& el)
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
				cout << "empty";
			break;

		case 5:
			try
			{
				if (A.Set_h_size() == 0)
					throw exception("empty");

				cout << "enter the grup for locate:\t";
				cin >> grup;
				if (!cin)
					throw exception("error(not number)");

				A.locate(grup, color);
			}
			catch (exception&el)
			{
				red;
				cout << el.what() << '\n';
				clr;
				ign;
			}
			break;

		case 6:
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

int hashTable::Set_h_size()
{
	return h_size;
}

void hashTable::otch()
{
	for (int i = 0; i < size; i++)
		top[i] = NULL;
}

void hashTable::creat(int grup, int col)
{
	int t(grup^size);

	if (t >= size)
		t %= size;

	hash* q{ top[t] };

	while(q!=NULL&&q->grup!=grup)
		q = q->next;

	if (q != NULL)
		throw exception("error(same)");

	hash* m{ new hash };

	m->grup = grup;
	m->col = col;
	m->prev = NULL;

	if (top[t] == NULL)
		m->next = NULL;
	else
	{
		m->next = top[t];
		top[t]->prev = m;
	}

	top[t] = m;
	h_size++;
}

void hashTable::dele(int grup, HANDLE color)
{
	int t(grup ^ size), v{};

	if (t >= size)
		t %= size;

	hash* q{ top[t] };

	while (q != NULL && q->grup != grup)
		q = q->next;

	if (q == NULL)
		throw exception("error(not this grup)");

	cout << "\nif you really want to delete enter 1(if no enter not 1):\n\n";
	cin >> v;

	if (v != 1)
	{
		red;
	cout << "\n\n{\\__/}\n";
	cout << "( ?-?)\n";
	cout << "/ > <\\\n\n";
		throw exception("you refused deletion");
	}

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

	delete q;
	h_size--;
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
				cout << q->grup << '\t' << q->col << '\n';
				cout << setw(20) << setfill('=') << '=' << '\n';
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

void hashTable::locate(int grup, HANDLE color)
{
	int t{ grup ^ size };
	if (t >= size)
		t %= size;

	hash* q{ top[t] };

	while (q != NULL && q->grup != grup)
		q = q->next;

	if (q == NULL)
		throw exception("not this grup");

	cout << "\nin grup ";
	green;
	cout << q->grup;
	white;
	cout << " have ";
	green;
	cout << q->col;
	white;
	cout<< " students\n";
}

void hashTable::tested()
{
	if (h_size < (double)(size * 0.7))
		return;

	for (int i = 0; i < size; i++)
	{
		if (top[i] != NULL) 
		{
			hash* q{ top[i] }, * m{};

			while (q!=NULL)
			{
				m = q;
				q = q->next;
				grup_time.push(m->grup);
				col_time.push(m->col);
				delete m;
			}
		}
	}

	size *= 2;
	top = new hash * [size];

	otch();

	h_size = 0;

	while (!grup_time.empty())
	{
		creat(grup_time.front(), col_time.front());
		grup_time.pop();
		col_time.pop();
	}
}