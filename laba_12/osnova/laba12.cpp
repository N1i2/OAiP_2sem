#include<iostream>
#include<iomanip>
#include<Windows.h>
#include <queue>
#include <stack>

using namespace std;

struct tree
{
	int key{};
	string text{};
	tree* right{}, * left{};
};

int lego[100]{}, sch{};

void stroy(int, string, tree**);
void show(int, tree*);
void show1(tree*);
void show2(tree*);
tree* locate(int, tree*);
tree* dele(int, tree*);
int test(tree*, int);
void sum(int, tree*);
void clearr(tree*);

void main()
{
	setlocale(LC_ALL, "ru");
	HANDLE color{ GetStdHandle(STD_OUTPUT_HANDLE) };
	tree* top{ nullptr };

	int col{}, numb{}, * keys{}, k{};
	string text{};
	cout << "Сперва создадим дерево введите начальное количество чисел:\t";
	cin >> col;

	if (col < 1 || !cin)
	{
		while (true)
		{
			cin.clear();
			cin.ignore(100, '\n');
			cout << "Нет такого быть не может попробуй еще раз:\t";
			cin >> col;
			if (col > 0)
				break;
		}
	}

	k = col;
	keys = new int[col];

	for (int i = 0, t = 0; i < col; i++)
	{
		t = 0;
		cout << i + 1 << ") введите число ключ(он не может повторяться)\t";
		cin >> numb;
		for (int j = 0; j < i; j++)
		{
			if (numb == keys[j])
			{
				cout << "Такуй ключ уже есть\n";
				i--;
				t++;
			}
		}
		if (t == 0)
		{
			keys[i] = numb;

			if (!cin)
			{
				cout << "Хаха смешно\n";
				cin.clear();
				cin.ignore(100, '\n');
				i--;
				continue;
			}
			cout << "Введите слово(слово только одно другие будут просто удалены)\t";
			cin >> text;
			stroy(numb, text, &top);
		}
	}

	int t = 0;

	while (true)
	{
		numb = 0;
		system("cls");
		SetConsoleTextAttribute(color, 15);

		cout << "Сделайте свой выбор\n";
		cout << "1 - добавить элимент\n";
		cout << "2 - удолить элимент\n";
		cout << "3 - вывести дерево(нисходящий)\n";
		cout << "4 - вывести дерево(смешанный)\n";
		cout << "5 - проверка на сбалансированность\n";
		cout << "6 - нахождение по ключу\n";
		cout << "7 - найти сумму каждого уровня(ключей)\n";
		cout << "8 - конец\n";
		show(0, top);
		cin >> numb;

		switch (numb)
		{
		case 1:
			t = 0;
			cout << "Введите число ключ(он не может повторяться)\t";
			cin >> numb;
			for (int j = 0; j < k; j++)
			{
				if (numb == keys[j])
				{
					t++;
					break;
				}
			}
			if (t == 0)
			{
				keys = new int;
				keys[k] = numb;
				k++;
				cout << "Введите слово(слово только одно другие будут просто удалены)\t";
				cin >> text;
				stroy(numb, text, &top);
			}
			else
			{
				cin.clear();
				cin.ignore(100, '\n');
				cout << "Такой ключ уже есть\n";
			}

			cout << "Элимент добавлен\n";
			break;

		case 2:
		{
			cout << "Введите ключ удоляемого элемента:\t";
			cin >> numb;
			top = dele(numb, top);
		}
		break;

		case 3:
			show1(top);
			break;

		case 4:
			show2(top);
			break;

		case 5:
		{
			test(top->left, 0);
			test(top->right, 1);
			if (abs(lego[0] - lego[1]) > 1)
				cout << "Дерево не сбалансированно\n";
			else
				cout << "Дерево сбалансированно\n";
			lego[0] = lego[1] = 0;
			break;
		}

		case 6:
		{
			cout << "Введите ключ искомого элимента:\t";
			cin >> numb;
			tree* sloc{ locate(numb, top) };
			if (sloc != NULL)
				cout << "Это слово:\t" << sloc->text << '\n';
			else
				cout << "Такого ключа нет\n";
		}
		break;

		case 7:
			for (int i = 0; i < 10; i++)
			{
				if (lego[i] == 0)
					break;
				lego[i] = 0;
			}
			sum(0, top);
			for (int i = 0; i < 10; i++)
			{
				if (lego[i] == 0)
					break;
				cout << i + 1 << " граница:\t" << lego[i] << '\n';
			}
			show(0, top);
			break;

		case 8:
			cout << "Конец\n";
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

void stroy(int u, string s, tree** t)
{
	if (*t == NULL)
	{
		*t = new tree;

		(**t).key = u;
		(**t).text = s;
		(**t).left = (**t).right = NULL;

		return;
	}
	else
	{
		if (u > (**t).key)
			stroy(u, s, &(**t).right);
		else
			stroy(u, s, &(**t).left);
	}
}

void show(int u, tree* t)
{
	if (t == NULL)
		return;
	else
	{
		show(++u, t->left);

		cout << setw(u * 4) << setfill('=') << '=' << t->key << '(' << t->text << ')' << '\n';
		u--;
	}
	show(++u, t->right);
}

int test(tree* t, int n)
{
	if (t == NULL)
		return n;
	else
	{
		test(t->left, n);

		if (n == 0)
			lego[0]++;
		else
			lego[1]++;
	}
	test(t->right, n);
}

tree* locate(int u, tree* t)
{
	tree* where{ NULL };

	if (t == NULL || where != NULL)
		return where;
	else
	{
		if (u > t->key)
			locate(u, t->right);
		else if (u < t->key)
			locate(u, t->left);
		else
			where = t;
	}
}

tree* dele(int u, tree* t)
{
	tree* del{}, * prev_del{ NULL }, * p{}, * prev_p{};

	del = t;

	while (del != NULL && del->key != u)
	{
		prev_del = del;
		if (del->key > u)
			del = del->left;
		else
			del = del->right;
	}
	if (del == NULL)
	{
		cout << "Такого числа нет\n";
		return t;
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
		if (prev_del->key > del->key)
			prev_del->left = p;
		else
			prev_del->right = p;

	delete del;
	cout << "Числоуспешно удолено\n";
	return t;
}

void sum(int u, tree* t)
{
	if (t == NULL)
		return;
	else
	{
		sum(++u, t->left);

		lego[u - 1] += t->key;

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

void show1(tree* t)
{
	if (t != NULL)
	{
		cout << t->key << "\n";
		show1(t->left);
		show1(t->right);
	}
}

void show2(tree* t)
{
	if (t == NULL)
		return;

	queue<tree*> q;
	stack<tree*> s;

	q.push(t);

	while (!q.empty())
	{
		int size = q.size();

		while (size--)
		{
			tree* c = q.front();

			q.pop();
			s.push(c);

			if (c->left != NULL)
				q.push(c->left);

			if (c->right != NULL)
				q.push(c->right);
		}

		while (!s.empty())
		{
			cout << s.top()->key << '\n';
			s.pop();
		}
	}
}