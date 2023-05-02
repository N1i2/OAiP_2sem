#include<iostream>
#include<fstream>
#include<Windows.h>
#include<ctime>
#include<queue>
#include<string>
//var2
#define clr cin.clear()
#define ign cin.ignore(100, '\n')
#define white SetConsoleTextAttribute(color, 15)
#define voidCol SetConsoleTextAttribute(color, 0)
#define green SetConsoleTextAttribute(color, 2)
#define red SetConsoleTextAttribute(color, 4)

using namespace std;

class hashTable
{
public:
	void otch();
	void getText(int a);
	void creat(string);
	int show();
	void locate(string, char);
	void dele(char);
private:
	struct hash
	{
		string text{};
		hash* next, * prev;
	};

	int size{23}, h_size{};
	hash** top{new hash*[size]};
	queue<int> nunb_time;
	queue<int> text_time;
};

void main()
{
	HANDLE color{ GetStdHandle(STD_OUTPUT_HANDLE) };
	hashTable A;
	int var{}, numb{}, gran{20};

	A.otch();

	while(true)
	{
		system("cls");
		try
		{
			white;
			cout << "enter the table size(from 1 to 20):\t";
			cin >> var;
			if (!cin)
				throw exception("this is not number");
			if (var < 1 || var>gran)
				throw exception("size from 1 to 20");

			A.getText(var);
			break;
		}
		catch (exception& el)
		{
			red;
			cout << el.what() << '\n';
			clr;
			ign;
			voidCol;
			system("pause");
		}
	}

	while (true)
	{
		system("cls");
		white;

		cout << "enter\n";
		cout << "1 - show\n";
		cout << "2 - locate\n";
		cout << "3 - delete\n";
		cout << "4 - end\n";
		cin >> var;

		switch (var)
		{
		case 1:
			green;
			var = A.show();
			red;
			if (!var)
				cout << "empty\n";
			break;

		case 2:
		{
			cout << "enter the text(register zavisim):\t";
			char text[20]{}, key{};
			gets_s(text);
			gets_s(text);
			key = text[0];

			try
			{
				A.locate(text, key);

				green;
				cout << "there is this text\n";
			}
			catch(exception&el)
			{
				red;
				cout << el.what() << '\n';
			}
		}
			break;

		case 3:
		{
			cout << "\nDo\n";
			green;
			var = A.show();
			red;
			if (!var)
			{
				cout << "empty\n";
				break;
			}
			white;
			char key;
			cout << "\nenter the char:\t";
			cin >> key;

			A.dele(key);
			
			cout << "\nPosle\n";
			green;
			var = A.show();
			red;
			if (!var)
				cout << "empty\n";
			
			
			clr;
			ign;
		}
			break;

		case 4:
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

void hashTable::getText(int n)
{
	h_size = n;
	string adres{ "C:\\Users\\Admin\\Desktop\\univer\\OAiP\\15\\file\\dop1.txt" };
	ifstream file;
	file.open(adres);

	for (int i = 0; i < n; i++)
	{
		string text{};

		file >> text;
		
		if (text == "")
		{
			cout << "sorry but file is empty\n";
			exit(0);
		}

		creat(text);
	}
}

void hashTable::creat(string text)
{
	string tr = text;
	tr.c_str();
	int t{ ((int)tr[0]*3)/2 };
	if (t >= size)
		t %= size;

	hash* q{ new hash };
	q->text = text;
	q->prev = NULL;

	if (top[t] == NULL)
		q->next = NULL;
	else
	{
		q->next = top[t];
		top[t]->prev = q;
	}

	top[t] = q;
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

void hashTable::locate(string text, char c_key)
{
	int key{ (int)c_key };

	if (key < 65 || key>122 || (key >= 91 && key <= 96))
		throw exception("this text is not");

	key *= 3;
	key /= 2;
	if (key >= size)
		key %= size;

	hash* q{ top[key] };

	while (q != NULL && q->text != text)
		q = q->next;

	if (q == NULL)
		throw exception("this text is not");
}

void hashTable::dele(char key)
{
	if (key < 65 || key>122 || (key >= 91 && key <= 96))
		throw exception("this text is not");

	int first{ ((int)key*3)/2 };
	
	if (first >= size)
		first %= size;

	string help{};

	hash* q{ top[first] };

	while (q!=NULL)
	{
		help = q->text;
		help.c_str();
		
		if (help[0] == key)
		{
			if (q == top[first])
			{
				if (q->next != NULL)
				{
					top[first] = q->next;
					top[first]->prev = NULL;
				}
				else
					top[first] = NULL;
				
				delete q;
				q = top[first];
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
				
				delete q;
				q = q->next;
			}
		}
		else
			q = q->next;
	}
}