#include<iostream>
#include<iomanip>
#include<Windows.h>
int y = 0;

using namespace std;

struct tree
{
	int key{};
	string text{};
	tree* right{}, * left{};
};

void stroy(int, string, tree**);
tree* dele(int, tree*);
void show(int, tree*);
void delAll(tree*);
tree* locate(int, tree*);
void schet(tree*);

void main()
{
	setlocale(LC_ALL, "ru");
	HANDLE color{ GetStdHandle(STD_OUTPUT_HANDLE) };
	tree* top{ nullptr };

	int col{}, numb{};
	string text{};

	cout << "Введите количество чисчел:\t";
	cin >> col;
	if (!cin)
	{
		while (true)
		{
			cin.clear();
			cin.ignore(100, '\n');
			cout << "Это не число попробуй еще раз:\t";
			cin >> col;
			if (!cin)
				continue;
			break;
		}
	}

	for (int i = 0; i < col; i++)
	{
		y = 0;
		cout << i + 1 << ") введите ключ(они не могут повторяться):\t";
		cin >> numb;
		cout << "Введите предложение:\t";
		cin >> text;
		stroy(numb, text, &top);
		if (y != 0)
			i--;
	}

	while (true)
	{
		system("cls");
		SetConsoleTextAttribute(color, 15);
		numb = 0;
		cout << "Выберите вариант:\n";
		cout << "1 - добавить новое число\n";
		cout << "2 - удолить число\n";
		cout << "3 - вывести все дерево\n";
		cout << "4 - найти число по ключу\n";
		cout << "5 - посчитать количество листов\n";
		cout << "6 - конец\n";
		cin >> numb;
		switch (numb)
		{
		case 1:
			y = 0;
			cout << "Введите ключ(они не могут повторяться):\t";
			cin >> numb;
			cout << "Введите предложение:\t";
			cin >> text;
			stroy(numb, text, &top);

			if (y == 0)
				cout << "Число добавлено\n";
			break;

		case 2:
			cout << "Введите число ключ которое хотите удолить:\t";
			cin >> numb;
			top = dele(numb, top);
			break;

		case 3:
			show(0, top);
			break;

		case 4:
		{
			cout << "Введите ключ искомого слова:\t";
			cin >> numb;
			tree* sloc{ locate(numb, top) };
			if (sloc != NULL)
				cout << "Это слово - " << sloc->text << '\n';
			else
				cout << "Такого ключа нет\n";
		}
			break;

		case 5:
			schet(top);
			cout << "В данном дереве " << y << " листьев\n";
			y = 0;
			break;

		case 6:
			cout << "Конец\n";
			SetConsoleTextAttribute(color, 0);
			delAll(top);
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

void stroy(int u, string c, tree** t)
{
	if (*t == NULL)
	{
		*t = new tree;
		(**t).key = u;
		(**t).text = c;
		(**t).left = (**t).right = NULL;
		return;
	}

	if (u > (**t).key)
		stroy(u, c, &(*t)->right);

	else if (u < (**t).key)
		stroy(u, c, &(*t)->left);

	else
	{
		cout << "Такой ключ уже был\n";
		y++;
	}
}

tree* dele(int u, tree* t)
{
	tree* del{}, * prev_del{NULL}, * p{}, * prev_p{};

	del = t;

	while (del!=NULL&&del->key!=u)
	{
		prev_del = del;
		if (u > del->key)
			del = del->right;
		else
			del = del->left;
	}
	if (del == NULL)
	{
		cout << "Такого ключа нет\n";
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

			while (p->right!=NULL)
			{
				prev_p = p;
				p = p ->right;
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
		if (prev_del->key > del->key)
			prev_del->left = p;
		else
			prev_del->right= p;
	}

	delete del;
	cout << "Элимент успешно удолен\n";
	return t;
}

void show(int u, tree* t)
{
	if (t == NULL)
		return;
	else
	{
		show(++u, t->left);
		cout << setw(u * 4) << setfill('=') << '=' << t->key << '(' << t->text << ")\n";
		u--;
	}
	show(++u, t->right);
}

void delAll(tree* t)
{
	if (t != NULL)
	{
			delAll(t->left);
		delAll(t->right);
		delete t;
	}
}

tree* locate(int u, tree* t)
{
	tree* lego{NULL};

	if (t == NULL || lego != NULL)
		return lego;

	if (u > t->key)
		locate(u, t->right);
	else if (u < t->key)
		locate(u, t->left);
	else
		lego = t;
}

void schet(tree* t)
{
	if (t == NULL)
		return;
	else
	{
		schet(t->right);
		if (t->left == NULL && t->right == NULL)
			y++;
	}
	schet(t->left);
}