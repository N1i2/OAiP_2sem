#include<iostream>
#include<Windows.h>
#include<iomanip>

using namespace std;
int y{}, z{};

struct tree
{
	int numb{}, color{};
	tree* left{}, * right{};
};

void stroy(int, tree**);
void check(tree*);
tree* help(tree*);
void give_color(tree*, int);
tree* sdvigL(tree*, tree*);
tree* sdvigR(tree*, tree*);
void show(int, tree*, HANDLE);
tree* dele(int, tree*);
void locate(tree*, tree*);
int end(tree*, int, int);

void main()
{
	setlocale(LC_ALL, "ru");
	HANDLE color{ GetStdHandle(STD_OUTPUT_HANDLE) };
	tree* top{ nullptr };

	int var{}, col{};

	while (true)
	{
		system("cls");
		SetConsoleTextAttribute(color, 15);
		cout << "Сделайте выбор\n";
		cout << "1 - добавить элемент дерева\n";
		cout << "2 - заполнить дерево\n";
		cout << "3 - удолить элемент дерева\n";
		cout << "4 - вывести дерево\n";
		cout << "5 - найти наименьший путь по красным до лита\n";
		cout << "6 - конец\n";
		cin >> var;
		switch (var)
		{
		case 1:
			cout << "Введите элемент(повторяться нельзя):\t";
			cin >> var;
			if (!cin)
			{
				cout << "Нет\n";
				cin.clear();
				cin.ignore(100, '\n');
				break;
			}
			try
			{
				stroy(var, &top);
				cout << "Успешно добавлено\n";
				give_color(top, 0);
				top=help(top);
			}
			catch (const std::exception& el)
			{
				cout << el.what() << '\n';
			}
			break;

		case 2:
			cout << "Сколько узлов добавим:\t";
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
				cout << i + 1 << ") введите элемент узла:\t";
				cin >> var;
				if (!cin)
				{
					cout << "Нет\n";
					cin.clear();
					cin.ignore(100, '\n');
					i--;
					continue;
				}
				try
				{
					stroy(var, &top);
				}
				catch (const std::exception& el)
				{
					i--;
					cout << el.what() << '\n';
				}
			}
			give_color(top, 0);
			top = help(top);
			cout << "Все числа внесены\n";
			break;

		case 3:
			try
			{
				cout << "Введите удоляемый элемент:\t";
				cin >> var;
				top=dele(var, top);
				cout << "Число удолено\t";
				give_color(top, 0);
				top=help(top);
			}
			catch (const std::exception& el)
			{
				cout << el.what() << '\n';
			}
			break;

		case 4:
			if (top != NULL)
				show(0, top, color);
			else
				cout << "Дерево пусто\n";
			break;

		case 5:
			y = 9999;
			locate(top, top);
			cout << "Самое большое количество красных по ветке с листом " << z << '\n';
			y = 0;
			z = 0;
			break;

		case 6:
			cout << "Конец\n";
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

tree* help(tree* top)
{
	int left{}, right{};
	while (true)
	{
		check(top->right);
		right = y;
		y = 0;
		check(top->left);
		left = y;
		y = 0;

		if (abs(right-left)>1)
		{
			if (right < left)
			{
				top = sdvigL(top, top->left);
				give_color(top, 0);
				continue;
			}
			top = sdvigR(top, top->right);
			give_color(top, 0);
			continue;
		}
		

		break;
	}

	return top;
}

tree* sdvigR(tree* oldT, tree* newT)
{
	tree* prev{oldT};

	while (newT->left!=NULL)
	{
		prev = newT;
		newT = newT->left;
	}

	if (prev == oldT)
	{
		newT->left = oldT;
		oldT->right = NULL;
	}
	else
	{
		newT->left = oldT;
		newT->right = oldT->right;
		oldT->right = NULL;
		prev->left = NULL;
	}

	return newT;
}

tree* sdvigL(tree* oldT, tree* newT)
{
	tree* prev{ oldT };

	while (newT->right != NULL)
	{
		prev = newT;
		newT = newT->right;
	}

	if (prev == oldT)
	{
		newT->right = oldT;
		oldT->left = NULL;
	}
	else
	{
		newT->right= oldT;
		newT->left = oldT->left;
		oldT->left = NULL;
		prev->right = NULL;
	}

	return newT;
}

void stroy(int u, tree** t)
{
	if (*t == NULL)
	{
		(*t) = new tree;
		(**t).numb = u;
		(**t).right = (**t).left = NULL;
		return;
	}

	if (u > (**t).numb)
		stroy(u, &(**t).right);
	else if (u < (**t).numb)
		stroy(u, &(**t).left);
	else
		throw exception("Такое число уже было");
}

void give_color(tree* t, int u)
{
	if (t == NULL)
		return;
	else
	{
		give_color(t->left, ++u);

		u % 2 ? t->color = 1 : t->color = 0;
		u--;
	}
	give_color(t->right, ++u);
}

void check(tree* t)
{
	if (t == NULL)
		return;
	else
	{
		check(t->left);

		if (t->color)
			y++;
	}
	check(t->right);
}

void show(int u, tree* t, HANDLE color)
{
	if (t == NULL)
		return;
	else
	{
		show(++u, t->left, color);
		cout << setw(u * 4) << setfill('=') << '=';
		t->color ? SetConsoleTextAttribute(color, 240) : SetConsoleTextAttribute(color, 252);
		cout << t->numb << '\n';
		SetConsoleTextAttribute(color, 15);
		u--;
	}
	show(++u, t->right, color);
}

tree* dele(int u, tree* t)
{
	tree* del{}, * prev_del{ NULL }, * p{}, * prev_p{};

	del = t;

	while (del != NULL && del->numb != u)
	{
		prev_del = del;
		if (del->numb > u)
			del = del->left;
		else
			del = del->right;
	}
	if (del == NULL)
	{
		throw exception("Нет такого элемента");
	}

	if (del->left == NULL)
		p = del->right;
	else
		if (del->right == NULL)
			p = del->left;
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
	if (del == t)
		t = p;
	else
		if (prev_del->numb > del->numb)
			prev_del->left = p;
		else
			prev_del->right = p;

	delete del;
	return t;
}

void locate(tree* top, tree*t)
{
	if (t == NULL)
		return;
	else
	{
		locate(top, t->left);

		if (t->right == NULL && t->left == NULL)
		{
			int e{end(top, t->numb, 0)};
			if (e <= y)
			{
				y = e;
				z = t->numb;
			}
		}
	}
	locate(top, t->right);
}

int end(tree* t, int r, int u)
{
	if (t->numb == r)
	{
		if (t->color == 0)
			u++;

		return u;
	}

	if (t->color == 0)
		u++;

	if (r > t->numb)
		end(t->right, r, u);
	else
		end(t->left, r, u);
}