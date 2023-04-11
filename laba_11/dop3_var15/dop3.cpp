#include<iostream>
#include<Windows.h>
#include<iomanip>
//var 15
using namespace std;
int y{};
struct tree
{
	int numb{};
	string text{};
	tree* left{}, * right{};
};

int stroy(int, string, tree**);
tree* dele(int, tree*);
void show(int, tree*);
tree* locate(int, tree*);
void sum(int, tree*);
void clearr(tree*);

void main() 
{
	setlocale(LC_ALL, "ru");
	HANDLE color{ GetStdHandle(STD_OUTPUT_HANDLE) };

	int numb{}, col{};
	string text{};
	tree* top{ nullptr };

	cout << "Введите начальное количество узлов:\t";
	cin >> col;
	if (!cin||col<1)
	{
		while(true)
		{
			cout << "Так не получисться попробуй снова\n";
			cin >> col;
			cin.clear();
			cin.ignore(100, '\n');
			if (!cin)
				continue;
			break;
		}
	}

	for (int i = 0; i < col; i++)
	{
		cout << i + 1 << ") введите ключ(ключи не должны повторяться):\t";
		cin >> numb;
		if (!cin)
		{
			while (true)
			{
				cout << "Так не получисться попробуй снова\n";
				cin >> numb;
				cin.clear();
				cin.ignore(100, '\n');
				if (!cin)
					continue;
				break;
			}
		}
		cout << "Введите строку:\t";
		cin >> text;

		if (!stroy(numb, text, &top))
			cout << "Такой ключ уже есть\n";
	}

	while (true)
	{
		system("cls");
		SetConsoleTextAttribute(color, 15);
		numb = 0;
		
		cout << "Введите вариант\n";
		cout << "1 - добавить новый узел\n";
		cout << "2 - удолить элемент по ключу\n";
		cout << "3 - вывести все дерево\n";
		cout << "4 - найти строку по ключу\n";
		cout << "5 - посчитать количество правых узлов\n";
		cout << "6 - конец\n";
		cin >> numb;

		switch (numb)
		{
		case 1:
			cout << "Введите ключ(ключи не должны повторяться):\t";
			cin >> numb;
			cout << "Введите строку:\t";
			cin >> text;

			if (!stroy(numb, text, &top))
				cout << "Такой ключ уже есть\n";
			else
				cout << "Элемент успешно сохранен\n";
			break;

		case 2:
			while (true)
			{
				cout << "Введите ключ числа которое надо удолить:\t";
				cin >> numb;
				if (!cin)
				{
					cin.clear();
					cin.ignore(100, '\n');
					cout << "Это не число\n";
				}
				else
					break;
			}

			top = dele(numb, top);
			break;

		case 3:
			show(0, top);
			break;

		case 4:
		{
			while (true)
			{
				cout << "Введите ключ числа которое надо найти:\t";
				cin >> numb;
				if (!cin)
				{
					cin.clear();
					cin.ignore(100, '\n');
					cout << "Это не число\n";
				}
				else
					break;
			}

			tree* lego{ locate(numb, top) };
			if (lego!=NULL)
				cout << "Там храниться страка:\t" << lego->text << '\n';
			else
				cout << "такого ключа нет\n";
		}
			break;

		case 5:
			y = 0;
			sum(0, top->right);
			cout << "В правой части " << y << " частей\n";
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

int stroy(int u, string c, tree** t)
{
	if (*t == NULL)
	{
		*t = new tree;
		(**t).numb = u;
		(**t).text = c;
		(**t).left = (**t).right = NULL;
		return 1;
	}

	if (u > (**t).numb)
		stroy(u, c, &(*t)->right);
	else if (u < (**t).numb)
		stroy(u, c, &(*t)->left);
	else
		return 0;
}

tree* dele(int u, tree* t)
{
	tree* del{}, * prev_del{NULL}, * p{}, * prev_p{};
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
		if (prev_del->numb > del->numb)
			prev_del->left = p;
		else
			prev_del->right = p;
	}

	delete del;
	cout << "Элемент удачно удолен\n";
	return t;
}

void show(int u, tree* t)
{
	if (t == NULL)
		return;
	else
	{
		show(++u, t->left);

		cout << setw(u * 4) << setfill('=') << '=' << t->numb << '(' << t->text << ")\n";
		u--;
	}
	show(++u, t->right);
}

tree* locate(int u, tree* t)
{
	if (t == NULL||t->numb == u)
		return t;

	if (u > t->numb)
		locate(u, t->right);
	else
		locate(u, t->left);
}

void sum(int u, tree* t)
{
	if (t == NULL)
		return;

	else
	{
		sum(++u, t->left);
		y++;
		u--;
	}
	sum(++u, t->right);
}

void clearr(tree* t)
{
	if (t != NULL)
	{
		clearr(t->left);
		clearr(t->right);
		delete t;
	}
}