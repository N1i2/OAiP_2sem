#include<iostream>
#include<Windows.h>
#include<iomanip>
#include<ctime>
#include<fstream>
#include<string>
#include<queue>

#define white SetConsoleTextAttribute(color, 15)
#define voidCol SetConsoleTextAttribute(color, 0)
#define red SetConsoleTextAttribute(color, 4)
#define green SetConsoleTextAttribute(color, 2)

using namespace std;

class hashTable
{
public:
	void otch();
	void creat();
	int add(string, string, double);
	int show();
	void write(string, double, int, HANDLE);
	void dele(string, double);
	void tested();
private:
	struct hash
	{
		int schet{};
		string comand{}, help{};
		hash* next{}, * prev{};
	};
	int size{ 17 }, h_size{};
	double a{ (sqrt(5) - 1) / 2 };
	hash** top{ new hash * [size] };
	queue<string> comands;
	queue<string> helpers;
};

void main()
{
	srand(time(NULL));
	HANDLE color{ GetStdHandle(STD_OUTPUT_HANDLE) };
	int var{};
	char text[50]{};
	hashTable A;
	A.otch();

	while (true)
	{
		double key{};

		system("cls");
		white;

		cout << "enter\n";
		cout << "1 - creat\n";
		cout << "2 - add\n";
		cout << "3 - dele\n";
		cout << "4 - write\n";
		cout << "5 - show\n";
		cout << "6 - end\n";
		cin >> var;

		switch (var)
		{
		case 1:
			A.creat();
			green;
			cout << "all corect\n";
			break;
		case 2:
		{
			try
			{
				string help{}, comand{};
				char help_t[50];

				cout << "enter the command:\t";
				gets_s(text);
				gets_s(text);

				for (int i = 0; text[i] != '\0'; i++)
				{
					comand += text[i];
					key += (double)text[i];
				}

				cout << "enter the helper:\t";
				gets_s(help_t);

				int t{}, sizeA= strlen(text), sizeB=strlen(help_t);

				if (sizeA >= sizeB)
					throw exception("error(not help)");

				for (int i{}, j{}; help_t[i] != '\0'; i++)
				{
					help += help_t[i];
					if (text[j] == help_t[i]&&!t)
					{
						j++;

						if (j == sizeA)
							t++;
					}
					else if(j!=0&&!t)
						j = 0;
				}

				if(!t)
					throw exception("error(not help)");

				var = A.add(comand, help, key);

				green;
				cout << "all corect\n";

				if ( var)
					A.tested();
			}
			catch (exception& el)
			{
				red;
				cout << el.what() << '\n';
			}
		}
			break;

		case 3:
		{
			string udalen{};
			cout << "enter comand for delete:\t";
			
			gets_s(text);
			gets_s(text);

			for (int i = 0; text[i]!='\0'; i++)
			{
				udalen += text[i];
				key += (int)text[i];
			}

			try
			{
				A.dele(udalen, key);

				green;
				cout << "comand has been delete\n";
			}
			catch (const std::exception&el)
			{
				red;
				cout << el.what() << '\n';
			}
		}
			break;

		case 4:
		{
			int vivod{};
			char heep[6]{ "help#" };
			string comand{};
			cout << "enter the command(help#command):\t";
			gets_s(text);
			gets_s(text);

			for (int i = 0; i < 5; i++)
			{
				if (heep[i] == text[i])
					vivod++;
			}

			if (vivod == 5)
			{
				vivod = 1;
				
				for (int i = 5; text[i] != '\0'; i++)
				{
					comand += text[i];
					key += (int)text[i];
				}
			}
			else
			{
				vivod = 0;

				for (int i = 0; text[i] != '\0'; i++)
				{
					comand += text[i];
					key += (int)text[i];
				}
			}

			try
			{
				A.write(comand, key, vivod, color);
			}
			catch (exception& el)
			{
				red;
				cout << el.what() << '\n';
			}
		}
			break;

		case 5:
			green;
			cout << "\n\n";
			var = A.show();
			red;
			if (!var)
				cout << "empty\n";
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
			cin.clear();
			cin.ignore(100, '\n');
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

void hashTable::creat()
{
	string adres_file{ "D:\\семестр2\\ОАиП\\15\\file\\dop2\\dop2.txt" }, adres_help{ "D:\\семестр2\\ОАиП\\15\\file\\dop2\\help.txt" };
	ifstream file, help;

	file.open(adres_file);
	help.open(adres_help);

	while (!file.eof())
	{
		string text{}, help_t{};
		char simvl{};
		double key{};

		while (file.get(simvl)&&simvl!='\n')
		{
			text += simvl;
			key += (double)simvl;
		}
		
		while (help.get(simvl) && simvl != '\n')
			help_t += simvl;

		try
		{
			add(text, help_t, key);
		}
		catch (exception& el)
		{
			cout << ' ';
		}
	}

	help.close();
	file.close();
}

int hashTable::add(string text, string help, double key)
{
	double d{key*a};
	d -= (int)d;
	d *= size;
	int t = (int)d;

	if (top[t] != NULL)
	{
		hash* m{ top[t] };

		while (m != NULL && m->comand != text)
			m = m->next;

		if (m != NULL)
			throw exception("error(same)");
	}

	hash* q{ new hash };
	q->comand = text;
	q->help = help;
	q->prev = NULL;

	if (top[t] == NULL)
	{
		q->next = NULL;
		q->schet = 1;
	}
	else
	{
		q->next = top[t];
		top[t]->prev = q;
		q->schet++;
	}

	top[t] = q;

	h_size++;

	if (q->schet == 5||h_size>(double)(size*0.7))
		return 1;
	return 0;
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
				cout << q->comand << "\thelp|| " << q->help << " ||\n\n" << setw(70) << setfill('=') << '=' << "\n\n";
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

void hashTable::dele(string udel, double key)
{
	double d{ key * a };
	d -= (int)d;
	d *= size;
	int t = (int)d;

	hash*del{ top[t] };

	while (del != NULL && del->comand != udel)
		del = del->next;

	if (del == NULL)
		throw exception("there isn't this comand");

	if (del == top[t])
	{
		if (del->next != NULL)
		{
			top[t] = del->next;
			top[t]->prev = NULL;
		}
		else
			top[t] = NULL;
	}
	else
	{
		if (del->next != NULL)
		{
			((*del).prev)->next = del->next;
			((*del).next)->prev = del->prev;
		}
		else
			((*del).prev)->next = NULL;
	}

	delete del;

	if (top[t] != NULL)
	{
		del = top[t];

		while (del!=NULL)
		{
			del->schet--;
			del = del->next;
		}
	}
}

void hashTable::write(string text, double key, int vivod, HANDLE color)
{
	double d{ key * a };
	d -= (int)d;
	d *= size;
	int t = (int)d;

	hash* q{ top[t] };

	while (q != NULL && q->comand != text)
		q = q->next;

	if (q == NULL)
		throw exception("there isn't this comand");

	green;

	if (vivod)
		cout << "use:: " << q->help << '\n';
	else
		cout << "there is this comand\n";
}

void hashTable::tested()
{
	for (int i = 0; i < size; i++)
	{
		if (top[i] != NULL)
		{
			hash* q{ top[i] }, * m{nullptr};

			while (q!=NULL)
			{
				comands.push(q->comand);
				helpers.push(q->help);
				m = q;
				q = q->next;
				delete m;
			}
		}
	}

	size *= 2;

	top = new hash * [size];

	otch();

	while (!comands.empty())
	{
		string text{ comands.front() };
		double key{};

		for (int i = 0; text[i] != '\0'; i++)
			key += (double)text[i];
	
		add(text, helpers.front(), key);

		comands.pop();
		helpers.pop();
	}
}