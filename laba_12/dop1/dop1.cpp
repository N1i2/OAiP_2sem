#include<iostream>
#include<iomanip>
#include<Windows.h>

using namespace std;

struct phone
{
	int numb{}, abon{};
	string name{}, abon_name[3]{ "A11", "MCT", "It's my Life" };
	phone* right{}, * left{};
};

int stroy(int, phone**);
void show(phone*);
phone* dele(int, phone*);
phone* locate(int, phone*);
int hu_more(int, phone*);
void clearr(phone*);

void main()
{
	setlocale(LC_ALL, "ru");
	HANDLE color{ GetStdHandle(STD_OUTPUT_HANDLE) };
	phone* top{ nullptr };
	int var{};

	while (true)
	{
		system("cls");
		SetConsoleTextAttribute(color, 15);

		cout << "Сделайте выбор\n";
		cout << "1 - добавить несколько номеровномер\n";
		cout << "2 - добавить номер\n";
		cout << "3 - удолить  номер\n";
		cout << "4 - показать все номера\n";
		cout << "5 - определить владельца номера\n";
		cout << "6 - найти самый востребованный тариф\n";
		cout << "7 - конец\n";
		cin >> var;

		switch (var)
		{
		case 1:
		{
			int col{};
			cout << "Введите количество номеров\n";
			cin >> col;
			if (!cin || col < 1)
			{
				cout << "Нет\n";
				cin.clear();
				cin.ignore(100, '\n');
				break;
			}

			for (int i = 0; i < col; i++)
			{
				cout <<i+1<< ") введите номер телефона(настройки упрощены так что можно просто цифры):\t";
				cin >> var;
				if (var < 1 || !cin)
				{
					cout << "Ну нет\n";
					cin.clear();
					cin.ignore(100, '\n');
					i--;
					continue;
				}
				if (!stroy(var, &top))
				{
					cout << "Такой телефон уже есть\n";
					i--;
				}
				else
					cout << "Телефон добавлен\n\n";
			}
			cout << "Все номера введены\n";
		}
		break;

		case 2:
			cout << "Введите номер телефона(настройки упрощены так что можно просто цифры):\t";
			cin >> var;
			if (var < 1 || !cin)
			{
				cout << "Ну это уже слишком\n";
				cin.clear();
				cin.ignore(100, '\n');
				break;
			}
			if (stroy(var, &top))
				cout << "Телефон успешно добавлен\n";
			else
				cout << "Такой телефон уже есть\n";
			break;

		case 3:
			cout << "Введите номер который хотите удолить:\t";
			cin >> var;
			if (var < 1 || !cin)
			{
				cout << "Ну это уже слишком\n";
				cin.clear();
				cin.ignore(100, '\n');
				break;
			}
			if (top != NULL)
				top=dele(var, top);
			else
				cout << "Не из чего удолять\n";
			break;

		case 4:
			if (top != NULL)
				show(top);
			else
				cout << "Нечего выводить\n";
			break;

		case 5:
		{
			cout << "Введите номер:\t";
			cin >> var;
			if (top != NULL)
			{
				phone* lego{ locate(var, top) };
				if (lego != NULL)
					cout << "Это номер:\t" << lego->name<<'\n';
				else
					cout << "Такого номера нет\n";
			}
			else
				cout << "Список пуст искать не из чего\n";
			break;
		}

		case 6:
		{
			int end{}, max{}, index{};
			if (top != NULL)
			{
				end = hu_more(0, top);
				
				if (max < end / 100)
				{
					max = end / 100;
					index = 0;
				}
				if(max<(end-((end/100)*100))/10)
				{
					max = (end - ((end / 100) * 100)) / 10;
					index = 1;
				}
				if (max < (end - (end / 10) * 10))
				{
					max = ((end - (end / 10) * 10));
					index = 2;
				}

				cout <<end<< " Cамый востребаванный тариф это " << top->abon_name[index] << '\n';
			}
			else
				cout << "Список пуст\n";
		}
			break;

		case 7:
			cout << "Конец\n";
			if (top != NULL)
				clearr(top);
			SetConsoleTextAttribute(color, 0);
			return;
			break;

		default:
			cout << "Такого варианта нет\n";
			cin.clear();
			cin.ignore(100, '\n');
			break;
		}

		SetConsoleTextAttribute(color, 0);
		system("pause");
	}
}


int stroy(int u, phone** t)
{
	if (*t == NULL)
	{
		int n{};
		*t = new phone;
		(**t).numb = u;
		cout << "Введите фамилию владельца телефона:\t";
		cin >> (**t).name;
		cout << "Какой тариф:\n";
		for (int i = 0; i < 3; i++)
			cout << i + 1 <<") " << (**t).abon_name[i] << '\n';
		cin >> n;
		while (n > 3 || n < 1 || !cin)
		{
			cin.clear();
			cin.ignore(100, '\n');
			cout << "Попробуй снова:\t";
			cin >> n;
			if (n > 3 || n < 1 || !cin)
				continue;
			break;
		}
		(**t).abon = n - 1;
		(**t).left = (**t).right = NULL;
		return 1;
	}

	if (u > (*t)->numb)
		stroy(u, &(**t).right);
	else if (u < (*t)->numb)
		stroy(u, &(**t).left);
	else
		return 0;
}

void show(phone* t)
{
	if (t == NULL)
		return;
	else
	{
		show(t->left);
		
		cout << "Номер:\t\t"<<t->numb<<'\n';
		cout << "Фамилия:\t" << t->name<<'\n';
		cout << "Абонент:\t" << t->abon_name[t->abon]<<"\n\n\n";
	}
	show(t->right);
}

phone* dele(int u, phone* t)
{
	phone* del{}, * prev_del{NULL}, * p{}, * prev_p{};
	del = t;

	while (del != NULL&&del->numb!=u)
	{
		prev_del = del;
		if (u > del->numb)
			del = del->right;
		else
			del = del->left;
	}

	if (del == NULL)
	{
		cout << "Такого номера нет\n";
		return t;
	}

	if (del->right == NULL)
		p = del->left;
	else
	{
		if (del->left == NULL)
			p = del->right;
		else
		{
			prev_p = del;
			p = del->left;

			while (p->right != NULL)
			{
				prev_p = p;
				p = p->right;
			}

			if (prev_p == del)
				p->right = del->right;
			else
			{
				p->right = del->right;
				prev_p->right = p->left;
				p->left = prev_p;
			}
		}
	}

	if (del == t)
		t = p;
	else
	{
		if (del->numb > prev_del->numb)
			prev_del->right = p;
		else
			prev_del->left = p;
	}

	delete del;
	cout << "Элемент удолен\n";
	return t;
}

phone* locate(int u, phone* t)
{
	if (t == NULL || t->numb == u)
		return t;

	if (u > t->numb)
		locate(u, t->right);
	else
		locate(u, t->left);
}

int hu_more(int u, phone* t)
{
	if (t == NULL)
		return u;
	else
	{
		hu_more(u, t->left);

		if (t->abon == 0)
			u += 100;
		else if (t->abon == 1)
			u += 10;
		else
			u += 1;
	}
	hu_more(u, t->right);
}

void clearr(phone* t)
{
	if (t != NULL)
	{
		clearr(t->left);
		clearr(t->right);
		delete t;
	}
}