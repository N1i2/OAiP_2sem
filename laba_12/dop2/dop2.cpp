#include<iostream>
#include<iomanip>
#include<Windows.h>

using namespace std;

struct tree
{
	int numb{};
	tree* left{}, * right{};
};

void stroy(int*, int, int, tree**);
void show(int, tree*);

void main()
{
	HANDLE color{ GetStdHandle(STD_OUTPUT_HANDLE) };
	setlocale(LC_ALL, "ru");
	tree* top{ nullptr };

	int* numb{}, col{};
	while (!cin || col < 1)
	{
		if (!cin)
		{
			cout << "Это не число\n";
			cin.clear();
			cin.ignore(100, '\n');
		}
		cout << "Введите количество чисел:\t";
		cin >> col;
		if (col < 1)
			cout << "Попробуй еще раз\n";
	}
	numb = new int[col];
	cout << "Ввод чисел(числа не могут повторяться)\n\n";
	for (int i = 0; i < col; i++)
	{
		cout << i + 1 << ") введите число:\t";
		cin >> numb[i];
		for (int j = 0; j < i; j++)
		{
			if (numb[i] == numb[j])
			{
				cout << "такое число уже есть\n";
				i--;
				continue;
			}
		}
		if (!cin)
		{
			cout << "Это не число\n";
			cin.clear();
			cin.ignore(100, '\n');
			i--;
			continue;
		}
	}

	for (int i = 0; i < col; i++)
	{
		for (int j = i; j < col; j++)
		{
			if (numb[j] < numb[i])
				swap(numb[j], numb[i]);
		}
	}

	if (col == 1)
	{
		top = new tree;
		top->left = top->right = NULL;
		top->numb = numb[0];
	}
	if (col >= 2)
	{
		top = new tree;
		top->left = top->right = NULL;
		top->numb = numb[1];
		top->left = new tree;
		(top->left)->left = (top->left)->right = NULL;
		(top->left)->numb = numb[0];
	}
	if (col >= 3)
		stroy(numb, 2, col, &top);

	cout << "\n\n";

	show(0, top);

	SetConsoleTextAttribute(color, 0);
}

void stroy(int* n, int i, int c, tree** t)
{
	if (i == c)
		return;
	if ((**t).left != NULL)
	{
		(**t).right = new tree;
		((**t).right)->numb = n[i];
		stroy(n, ++i, c, &(**t).right);
	}
	else
	{
		(**t).left = new tree;
		((**t).left)->numb = n[i];
		stroy(n, ++i, c, &(*t));
	}
}

void show(int u, tree* t)
{
	if (t == NULL)
		return;
	else
	{
		show(++u, t->left);

		cout << setw(u * 4) << setfill('=') << '=' << t->numb << '\n';
		u--;
	}
	show(++u, t->right);
}