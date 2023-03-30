#include<iostream>

using namespace std;

struct cirkl
{
	string name;
	cirkl* next{}, * prev;
};

struct udalen
{
	string name;
	udalen* next{}, * prev;
};

void show(cirkl*);
udalen* dell(cirkl**, cirkl**, int);
void show1(udalen*);

int main()
{
	setlocale(LC_ALL, "ru");

	cirkl* start{ NULL }, * t{ NULL }, * last{ NULL };
	int size{};
	cout << "Введите количество людей в кругу\t";
	cin >> size;
	if (!cin || size <= 0)
	{
		cout << "Такого не может быть\n";
		cin.clear();
		cin.ignore(100, '\n');
		return 0;
	}

	for (int i = 0; i < size; i++)
	{
		t = new cirkl;
		cout << "Введите имя " << i + 1 << " человека в кругу:\t";
		cin >> t->name;
		if (start == NULL)
		{
			t->prev = NULL;
			start = t;
		}
		else
		{
			last->next = t;
			t->prev = last;
		}
		t->next = NULL;
		last = t;
	}

	system("cls");
	show(start);

	int n{};
	cout << "Каждый N в кругу удоляеться. Введите N:\t";
	cin >> n;
	if (!cin || size <= 0)
	{
		cout << "Такого не может быть\n";
		cin.clear();
		cin.ignore(100, '\n');
		return 0;
	}

	show1(dell(&start, &last, n));

	return 0;
}

void show(cirkl* s)
{
	cirkl* t{ s };
	cout << "Круг\n";
	while (t)
	{
		cout << t->name << '\n';
		t = t->next;
	}
}

udalen* dell(cirkl** s, cirkl** l, int n)
{
	cirkl* t{ *s }, * del{};
	udalen* r{ NULL }, * start{ NULL }, * end{ NULL };
	int numb{};

	while (true)
	{
		if (t == *s && t == *l)
		{
			r = new udalen;
			r->name = t->name;

			if (start == NULL)
			{
				start = r;
				r->prev = NULL;
			}
			else
			{
				end->next = r;
				r->prev = end;
			}
			end = r;
			r->next = NULL;


			*s = NULL;
			*l = NULL;
			delete t;

			return start;
		}
		numb++;
		if (numb == n)
		{
			numb = 0;
			if (t == *s)
			{
				(t->next)->prev = NULL;
			}
			else if (t == *l)
			{
				(t->prev)->next = NULL;
			}
			else
			{
				(t->next)->prev = t->prev;
				(t->prev)->next = t->next;
			}
			r = new udalen;

			r->name = t->name;

			if (start == NULL)
			{
				start = r;
				r->prev = NULL;
			}
			else
			{
				end->next = r;
				r->prev = end;
			}
			end = r;
			r->next = NULL;

			del = t;

			if (t == *s)
				*s = t->next;
			
			if (t == *l)
			{
				*l = t->prev;
				t = *s;
			}
			else
			t = t->next;
			delete del;
		}
		else
		{
			if (t == *l)
				t = *s;
			else
			t = t->next;
		}
	}
}

void show1(udalen* s)
{
	udalen* t{ s };
	cout << "Круг\n";
	while (t)
	{
		cout << t->name << '\n';
		t = t->next;
	}
}