#include<iostream>
#include<Windows.h>
#define n 20

using namespace std;

struct student
{
	char ser[n];
	string name{}, fath{}, leeson_name[5]{ "Matem","Fizika","Filosofia","Istoria","Algorimizacia" };
	int day{}, month{}, dat{}, year{}, number{}, assecc[5]{};
	student* next{}, * prev{};
};

student* add();
int dob(student*, student**, student**);
int sort(student*, student*);
int dell(student**, student**, char*);
int show(student*);
int centr_assecc(student*);
int old_young(student*);
int bester(student*);


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

		case 5:
			if (phead != NULL)
				old_young(phead);
			else
				cout << "list empty\n";
			SetConsoleTextAttribute(col, 0);
			system("pause");
			break;

		case 6:
			if (phead != NULL)
				bester(phead);
			else
				cout << "list empty\n";
			SetConsoleTextAttribute(col, 0);
			system("pause");
			break;

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
	newP->day = help_d;
	newP->month = help_m;
	newP->dat = help_y;

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
			swap(a->day, z->day);
			swap(a->month, z->month);
			swap(a->dat, z->dat);
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
				swap(a->day, z->day);
				swap(a->month, z->month);
				swap(a->dat, z->dat);
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
		cout << p->ser << '(' << p->day << '/' << p->month << '/' << p->dat << ')' << "\t\t kurs:" << p->year << "\tgrup " << p->number << '\n';
		p = p->next;
	}
	return 1;

}

int centr_assecc(student* phead)
{
	student* t{ phead };
	double centr[5][5]{}, numb[5]{};
	int help{};

	while (t)
	{
		help = t->number - 1;

		for (int i = 0; i < 5; i++)
		{
			centr[help][i] += t->assecc[i];
		}
		numb[help]++;
		t = t->next;
	}
	cout << "\n\n\n";
	for (int i = 0; i < 5; i++)
	{
		if (centr[i][0] == 0)
			cout << "list " << i + 1 << " is empty\n";
		else
		{
			cout << "grup " << i + 1 << ":\n\n";

			for (int j = 0; j < 5; j++)
			{
				if (j == 0 || j == 1)
					cout << phead->leeson_name[j] << ":\t\t\t" << centr[i][j] / numb[i] << '\n';
				else
					cout << phead->leeson_name[j] << ":\t\t" << centr[i][j] / numb[i] << '\n';
			}
		}
		cout << "\n\n";
	}

	return 0;
}

int old_young(student* phead)
{
	if (phead->next == NULL)
	{
		cout << "student only one:\t" << phead->ser << '\n';
		return 0;
	}

	string older{}, younger{};
	int old_d{}, old_m{}, old_y{}, young_d{}, young_m{}, young_y{ 3000 };
	student* t{ phead };

	while (t)
	{
		if (t->dat > old_y)
		{
			old_d = t->day;
			old_m = t->month;
			old_y = t->dat;
			older = t->ser;
		}
		else if (t->dat == old_y)
		{
			if (t->month > old_m)
			{
				old_d = t->day;
				old_m = t->month;
				old_y = t->dat;
				older = t->ser;
			}
			else if (t->month == old_m)
			{
				if (t->day > old_d)
				{
					old_d = t->day;
					old_m = t->month;
					old_y = t->dat;
					older = t->ser;
				}
			}
		}

		if (t->dat < young_y)
		{
			young_d = t->day;
			young_m = t->month;
			young_y = t->dat;
			younger = t->ser;
		}
		else if (t->dat == old_y)
		{
			if (t->month < old_m)
			{
				young_d = t->day;
				young_m = t->month;
				young_y = t->dat;
				younger = t->ser;
			}
			else if (t->month == old_m)
			{
				if (t->day < old_d)
				{
					young_d = t->day;
					young_m = t->month;
					young_y = t->dat;
					younger = t->ser;
				}
			}
		}

		t = t->next;
	}

	cout << "older is:\t" << older << '(' << old_d << '/' << old_m << '/' << old_y << ')' << "\nyounger is:\t" << younger << '(' << young_d << '/' << young_m << '/' << young_y << ")";
	return 0;
}

int bester(student* phead)
{
	student* t{ phead };

	double centr{}, best[5]{};
	string best_name[5]{};

	while (t)
	{
		for (int i = 0; i < 5; i++)
			centr += t->assecc[i];

		centr /= 5;

		if (centr > best[t->number - 1])
		{
			best[t->number - 1] = centr;
			best_name[t->number - 1] = t->ser;
		}

		t = t->next;
	}

	for (int i = 0; i < 5; i++)
	{
		if (best[i] != 0)
		{
			cout << "\nbest student in " << i + 1 << " grup is:\t" << best_name[i]<<'\n';
		}
		else
			cout << "\ngrup " << i + 1 << " is empty\n";
	}

	return 0;
}