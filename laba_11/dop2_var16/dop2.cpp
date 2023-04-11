#include<iostream>
#include<iomanip>
#include<Windows.h>
//var 16
using namespace std;

int y{};

struct tree
{
	int key{};
	int numb{};
	tree* left{}, * right{};
};

int stroy(int, int, tree**);
tree* dele(int, tree*);
void show(int, tree*);
tree* locate(int, tree*);
void sum(int, tree*);
void clearr(tree*);

void main()
{
	setlocale(LC_ALL, "ru");
	HANDLE color{ GetStdHandle(STD_OUTPUT_HANDLE) };
	tree* top{ nullptr };

	int numb{}, col{}, n1{};

	cout << "Введите первоначальное количество чисел:\t";
	cin >> col;
	if (col < 1 || !cin)
		while (true)
		{
			cin.clear();
			cin.ignore(100, '\n');
			cout << "Нет так нельзя попробуй снова:\t";
			cin >> col;
			if (col < 1 || !cin)
				continue;
			break;
		}

	for (int i = 0; i < col; i++)
	{
		cout << i + 1 << ") Введите ключ(ключи не должны повторяться):\t";
		cin >> numb;
		if (!cin)
		{
			cout << "Не смешно\n";
			i--;
			cin.clear();
			cin.ignore(100, '\n');
			continue;
		}
		cout << "Введите число которое хранит элимент:\t";
		cin >> n1;
		if (!cin)
		{
			cout << "Не смешно\n";
			i--;
			cin.clear();
			cin.ignore(100, '\n');
			continue;
		}

		if (!stroy(numb, n1, &top))
		{
			cout << "Нет такой ключ уже есть\n";
			i--;
		}
	}

	while (true)
	{
		system("cls");
		SetConsoleTextAttribute(color, 15);
		numb = 0;
		cout << "Сделайте выбор\n";
		cout << "1 - добавить число\n";
		cout << "2 - удолить по ключу\n";
		cout << "3 - вывести дерево\n";
		cout << "4 - найти число по ключу\n";
		cout << "5 - сумма значений листов\n";
		cout << "6 - конец\n";
		cin >> numb;

		switch (numb)
		{
		case 1:
			cout << "Введите ключ(ключи не должны повторяться):\t";
			cin >> numb;
			if (!cin)
			{
				cout << "Не смешно\n";
				cin.clear();
				cin.ignore(100, '\n');
				break;
			}
			cout << "Введите число которое хранит элимент:\t";
			cin >> n1;
			if (!cin)
			{
				cout << "Не смешно\n";
				cin.clear();
				cin.ignore(100, '\n');
				break;
			}

			if (!stroy(numb, n1, &top))
				cout << "Нет такой ключ уже есть\n";
			else
				cout << "Элемент успешно добавлен\n";

			break;

		case 2:
			cout << "Введите ключ числа которое надо удолить:\t";
			cin >> numb;
			if (!cin)
			{
				cout << "Нет так нельзя\n";
				cin.clear();
				cin.ignore(100, '\n');
				break;
			}

			top = dele(numb, top);

			break;

		case 3:
			show(0, top);
			break;

		case 4:
		{
			cout << "Введите ключ числа которое ищите:\t";
			cin >> numb;
			if (!cin)
			{
				cout << "Плохо быть таким\n";
				cin.clear();
				cin.ignore(100, '\n');
				break;
			}
			tree* lego{ locate(numb, top) };
			if (lego != NULL)
				cout << "С данным ключем есть число " << lego->numb << '\n';
			else
				cout << "Чет не так с ключем\n";
		}
		break;

		case 5:
		{
			y = 0;
			sum(0, top);
			cout << "Сумма элементов листьев = \t" <<  y<< '\n';
		}
			break;

		case 6:
			cout << "Конец\n";
			SetConsoleTextAttribute(color, 0);
			clearr(top);
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

int stroy(int u, int n, tree** t)
{
	if (*t == NULL)
	{
		*t = new tree;
		(**t).key = u;
		(**t).numb = n;
		(**t).left = (**t).right = NULL;
		return 1;
	}

	if (u > (**t).key)
		stroy(u, n, &(*t)->right);
	else if(u<(**t).key)
		stroy(u, n, &(*t)->left);
	else
			return 0;
}

tree* dele(int u, tree* t)
{
	tree* d{}, * prev_d{ NULL }, * p{}, * prev_p{};
	d = t;

	while ( d != NULL&& d->key != u)
	{
		prev_d = d;
		if (u > d->key)
			d = d->right;
		else
			d = d->left;
	}

	if (d == NULL)
	{
		cout << "Числа с таким ключем нет\n";
		return t;
	}

	if (d->right == NULL)
		p = d->left;
	else
	{
		if (d->left == NULL)
			p = d->right;
		else
		{
			prev_p = d;
			p = d->left;

			while (p->right!=NULL)
			{
				prev_p = p;
				p = p->right;
			}

			if (prev_p == d)
				p->right = d->right;
			else
			{
				p->right = d->right;
				prev_p->right = p->left;
				p->left = prev_p;
			}
		}
	}

	if (d == t)
		t = p;
	else
	{
		if (prev_d->key > d->key)
			prev_d->left = p;
		else
			prev_d->right = p;
	}

	delete d;
	cout << "Элемент успешно удолен\n";
	return t;
}

void show(int u, tree* t)
{
	if (t == NULL)
		return;
	else
	{
		show(++u, t->left);

		cout << setw(u * 4) << setfill('=') << '=' << t->key << '(' << t->numb << ")\n";
		u--;
	}
	show(++u, t->right);
}

tree* locate(int u, tree* t)
{
	tree* lego(NULL);

	if (t == NULL || lego != NULL)
		return lego;

	if (u > t->key)
		locate(u, t->right);
	else if (u < t->key)
		locate(u, t->left);
	else
		lego = t;
}

void sum(int u, tree* t)
{
	if (t == NULL)
		return;
	else
	{
		sum(++u, t->left);

		if (t->right == NULL && t->left==NULL)
			y += t->numb;
		u--;
	}
	sum(++u, t->right);
}

void clearr(tree* t)
{
	if (t!=NULL)
	{
		clearr(t->right);
		clearr(t->left);
		delete t;
	}
}