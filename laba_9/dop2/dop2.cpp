#include<iostream>
#include<Windows.h>
#define n 20

using namespace std;

struct student
{
	char ser[n];
	string name{}, fath{}, leeson_name[5]{ "Matem","Fizika","Filosofia","Istoria","Algorimizacia" };
	int date{}, year{}, number{}, assecc[5]{};
	student* next{}, * prev{};
};

student* add();
int dob(student*, student**, student**);
int sort(student*, student*);
int dell(student**, student**, char*);
int show(student*);
int centr_assecc(student*);

void main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	HANDLE col{ GetStdHandle(STD_OUTPUT_HANDLE) };
	student* phead{ NULL };
	student* plast{ NULL };
	setlocale(LC_ALL, "ru");
	int var{};
	while (true)
	{
		char isk[n]{};
		SetConsoleTextAttribute(col, 15);
		system("cls");
		cout << "vibor\n";
		cout << "1 - Add a new student\n";
		cout << "2 - Delete a student\n";
		cout << "3 - Show all student\n";
		cout << "4 - Show centrl assecc grup\n";
		cout << "5 - Show oldest and youngest student\n";
		cout << "6 - Show a best student in the group\n";
		cout << "7 - End\n";
		cin >> var;
		if (!cin)
		{
			cout << "This is not number\n";
			SetConsoleTextAttribute(col, 0);
			system("pause");
			cin.clear();
			cin.ignore(100, '\n');
			continue;
		}
		switch (var)
		{
		case 1:
			if (dob(add(), &phead, &plast))
				sort(phead, plast);
			cout << "Student is save\n";
			SetConsoleTextAttribute(col, 0);
			system("pause");
			break;

		case 2:
			if (phead == NULL)
				cout << "lite empty\n";
			else
			{
				cout << "enter the sername:\t";
				gets_s(isk);
				gets_s(isk);
				if (int(isk[0]) >= 97 && int(isk[0]) <= 122)
				{
					int a{};
					a = int(isk[0]);
					a -= 32;
					isk[0] = char(a);
				}
				dell(&phead, &plast, isk) ? cout << "student is delete\n" : cout << "error\n";
			}
			SetConsoleTextAttribute(col, 0);
			system("pause");
			break;

		case 3:
			show(phead) ? cout << "\n" : cout << "lists empty\n";
			SetConsoleTextAttribute(col, 0);
			system("pause");
			break;

		case 4:
			if (phead != NULL)
				centr_assecc(phead);
			else
				cout << "list empty\n";
			SetConsoleTextAttribute(col, 0);
			system("pause");
			break;

			/*case 5:
				SetConsoleTextAttribute(col, 0);
				system("pause");
				break;

			case 6:
				SetConsoleTextAttribute(col, 0);
				system("pause");
				break;*/

		case 7:
			cout << "End\n";
			SetConsoleTextAttribute(col, 0);
			return;
			break;

		default:
			cout << "error\n";
			SetConsoleTextAttribute(col, 0);
			system("pause");
			break;
		}
	}
}

student* add()
{
	int help_d{}, help_m{}, help_y{}, help{};
	student* newP = new student;
	cout << "enter the sername:\t";
	gets_s(newP->ser);
	while (true)
	{
		gets_s(newP->ser);
		if (int(newP->ser[0]) < 65 || int(newP->ser[0]) > 122)
			cout << "this is not simble try agan\n";
		else
			break;
	}
	if (int(newP->ser[0]) >= 97 && int(newP->ser[0]) <= 122)
	{
		int a{};
		a = int(newP->ser[0]);
		a -= 32;
		newP->ser[0] = char(a);
	}


	cout << "enter the name:\t";
	cin >> newP->name;
	cout << "enter the patronymic:\t";
	cin >> newP->fath;
	while (true)
	{
		cout << "enter the date of birth(DDMMYYYY):\t";
		cin >> help;
		if (!cin)
		{
			cout << "error\n";
			cin.clear();
			cin.ignore(100, '\n');
			continue;
		}
		help_d = help / 1000000;
		if (help_d < 1 || help_d>31)
		{
			cout << "error\n";
			continue;
		}
		help_m = (help - help_d * 1000000) / 10000;
		if (help_m < 1 || help_m>12)
		{
			cout << "error\n";
			continue;
		}
		help_y = (help - help_d * 1000000 - help_m * 10000);
		if (help_y > 2023 || help_y < 1950)
		{
			cout << "error\n";
			continue;
		}
		break;
	}
	newP->date = help;

	while (true)
	{
		cout << "enter the kurs(1-5):\t";
		cin >> help;
		if (!cin || help < 1 || help>5)
		{
			cout << "error\n";
			cin.clear();
			cin.ignore(100, '\n');
			continue;
		}
		break;
	}
	newP->year = help;

	while (true)
	{
		cout << "enter the group(1-5):\t";
		cin >> help;
		if (!cin || help < 1 || help>5)
		{
			cout << "error\n";
			cin.clear();
			cin.ignore(100, '\n');
			continue;
		}
		break;
	}
	newP->number = help;

	for (int i = 0; i < 5; i++)
	{
		cout << i + 1 << ") enter assecc for " << newP->leeson_name[i] << ":\t";
		cin >> newP->assecc[i];
		if (!cin || newP->assecc[i] < 1 || newP->assecc[i]>10)
		{
			cout << "error\n";
			cin.clear();
			cin.ignore(100, '\n');
			i--;
		}
	}

	newP->next = NULL;
	newP->prev = NULL;

	return newP;
}

int dob(student* p, student** phead, student** plast)
{
	if (*plast == NULL)
	{
		p->next = NULL;
		p->prev = NULL;
		*plast = p;
		*phead = p;
		return 0;
	}
	else
	{
		student* e{ *plast };
		e->next = p;
		p->next = NULL;
		p->prev = e;
		*plast = p;
		return 1;
	}
}

int sort(student* phead, student* plast)
{
	student* p{ plast }, * a{ p }, * z{ p->prev };
	int year{ p->year };
	while (z)
	{
		if (a->year < z->year)
		{
			swap(a->ser, z->ser);
			swap(a->name, z->name);
			swap(a->fath, z->fath);
			swap(a->date, z->date);
			swap(a->year, z->year);
			swap(a->number, z->number);
			swap(a->assecc, z->assecc);

			z = z->prev;
			a = a->prev;
		}
		else
			break;
	}

	a = p;
	z = a->prev;

	while (z)
	{
		if (a->year == year && z->year == year)
		{
			if (int(a->ser[0]) < int(z->ser[0]))
			{
				swap(a->ser, z->ser);
				swap(a->name, z->name);
				swap(a->fath, z->fath);
				swap(a->date, z->date);
				swap(a->year, z->year);
				swap(a->number, z->number);
				swap(a->assecc, z->assecc);
			}
		}

		z = z->prev;
		a = a->prev;
	}

	return 0;
}

int dell(student** phead, student** plast, char* isk)
{
	student* ddel{ NULL }, * t{ *phead };
	string helpName{}, iskName{ isk };

	while (t)
	{
		helpName = t->ser;
		if (helpName == iskName)
		{
			ddel = t;
			break;
		}
		t = t->next;
	}

	if (ddel == NULL)
		return 0;

	if ((ddel == *phead && ddel == *plast))
	{
		*phead = NULL;
		*plast = NULL;
		cout << "now list is empty\n";
	}
	else if (ddel == *phead)
	{
		((**phead).next)->prev = NULL;
		*phead = ddel->next;
	}
	else if (ddel == *plast)
	{
		((**plast).prev)->next = NULL;
		*plast = ddel->prev;
	}
	else
	{
		(ddel->prev)->next = ddel->next;
		(ddel->next)->prev = ddel->prev;
	}

	delete ddel;
	return 1;
}

int show(student* phead)
{
	if (phead == NULL)
		return 0;

	student* p = phead;
	while (p)
	{
		cout << p->ser << "\t\t grup:" << p->year << '\n';
		p = p->next;
	}
	return 1;

}

int centr_assecc(student* phead)
{
	student* t{ phead };
	double centr[5]{}, numb{}, help{};

	for (int grup = 1; grup <= 5;)
	{
		if (t == NULL)
		{
			cout << "\ngrup number " << grup << ":\n";
			for (int i = 0; i < 5; i++)
			{
				help = (double)centr[i] / numb;
				cout << phead->leeson_name[i] << " : " << help << '\n';
				centr[i] = 0;
			}

			while (grup < 5)
			{
				grup++;
				cout << "\ngrup number " << grup << " is empty\n";
			}
			grup++;
		}
		else if (grup == t->number)
		{
			for (int i = 0; i < 5; i++)
			{
				centr[i] += t->assecc[i];
			}
			numb++;
			t = t->next;
		}
		else
		{
			if (centr[0] == 0)
			{
				cout << "\ngrup number " << grup << " is empty\n";
			}
			else
			{
				cout << "\ngrup number " << grup << ":\n";
				for (int i = 0; i < 5; i++)
				{
					help = (double)centr[i] / numb;
					cout << t->leeson_name[i] << " : " << help << '\n';
					centr[i] = 0;
				}
				numb = 0;
			}
			grup++;
		}
	}

	return 0;
}