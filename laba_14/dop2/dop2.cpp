#include<iostream>
#include<Windows.h>
#include<ctime>
#include<string>
#include<queue>
//var12
#define clear cin.clear()
#define ign cin.ignore(100, '\n')
#define red SetConsoleTextAttribute(color, 4)
#define green SetConsoleTextAttribute(color, 2)
#define voidCol SetConsoleTextAttribute(color, 0)
#define white SetConsoleTextAttribute(color, 15)

using namespace std;

class hashTable
{
public:
	void otch();
	void creat(string, char);
	void dele(string, char);
	int show();
	void tested();
private:
	struct hash
	{
		string text{};
		hash* next, * prev;
	};

	int size{ 7 }, h_size{};
	hash** top{ new hash * [size] };
	queue<string> text_time;
	queue<char> char_time;
};

void main()
{
	HANDLE color{ GetStdHandle(STD_OUTPUT_HANDLE) };
	srand(time(NULL));
	int var{};
	hashTable A;
	A.otch();

	while (true)
	{
		char tex[20]{};
		string text{};

		system("cls");
		white;

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
				red;
				cout << "error(not number)\n";
				clear;
				ign;
				break;
			}

			gets_s(tex);

			for (int i = 0; i < var; i++)
			{
				string text{};
				cout << i + 1 << ") enter the text:\t";
				gets_s(tex);
				text += tex;

				try
				{
					A.creat(text, tex[0]);
				}
				catch (const std::exception&el)
				{
					red;
					cout << el.what() << '\n';
					white;
				}
				A.tested();
			}
			break;

		case 2:
			cout <<"enter the text:\t";
			gets_s(tex);
			gets_s(tex);
			text += tex;

			A.creat(text, tex[0]);
			A.tested();
			break;

		case 3:
			try
			{
				cout << "\nDo\n";
				green;
				var = A.show();
				if (!var)
					throw exception("empty");

				white;
				cout << "\nenter the text:\t";
				gets_s(tex);
				gets_s(tex);
				text += tex;
				A.dele(text, tex[0]);

				cout << "\nPosle\n";
				green;
				var = A.show();
				if (!var)
					throw exception("empty");
			}
			catch (const std::exception&el)
			{
				red;
				cout << el.what() << '\n';
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
			cout << "error(not var)\n";
			clear;
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

void hashTable::creat(string tex, char key)
{
	if (key == ' ')
		throw exception("none probel on the begin");

	int t{ (int)key };
	t %= size;

	hash* m{top[t]};
	while (m != NULL && m->text != tex)
		m = m->next;

	if (m != NULL)
		throw exception("error(same)");

	hash* q{ new hash };
	q->text = tex;
	q->prev = NULL;

	if (top[t] == NULL)
		q->next = NULL;
	else
	{
		q->next = top[t];
		top[t]->prev = q;
	}

	top[t] = q;
	h_size++;
}

void hashTable::dele(string tex, char key)
{
	int t{ (int)key };
	t %= size;

	hash* q{ top[t] };

	while (q != NULL && q->text != tex)
		q = q->next;

	if (q == NULL)
		throw exception("not this text");

	if (q == top[t])
	{
		if (q->next == NULL)
			top[t] = NULL;
		else
		{
			top[t] = q->next;
			top[t]->prev = NULL;
		}
	}
	else
	{
		if (q->next != NULL)
		{
			((*q).next)->prev = q->prev;
			((*q).prev)->next = q->next;
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
				cout << q->text << '\n';
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
	if (h_size < (double)(size*0.5))
		return;

	string ch{};

	for (int i = 0; i < size; i++)
		if (top[i] != NULL)
		{
			hash* q{ top[i] }, *m{};

			while (q!=NULL)
			{
				m = q;
				q = q->next;
				ch = m->text;
				text_time.push(ch);
				ch.c_str();
				char_time.push(ch[0]);
				delete m;
			}
		}

	size *= 2;
	top = new hash * [size];

	otch();
	h_size = 0;

	while(!text_time.empty())
	{
		creat(text_time.front(), char_time.front());
		text_time.pop();
		char_time.pop();
	}
}