#include<iostream>

using namespace std;

struct element
{
	int numb{};
	element* next{};
};

int read(element*);
int sdvig(element**, element**, int);

int main()
{
	element* begin{ NULL }, * end{ NULL }, * newP{ NULL };

	int size{}, max{ -999999 }, index{};
	cout << "enter the size:\t";
	cin >> size;
	if (!cin)
	{
		cout << "error\n";
		return 0;
	}
	if (size <= 0)
	{
			cout << "error\n";
			return 0;
	}


	for (int i = 0, t{}; i < size; i++)
	{
		cout << "number " << i + 1 << " : ";
		cin >> t;
		if (!cin)
		{
			cout
				<< "error\n";
			cin.clear();
			cin.ignore(100, '\n');
			i--;
			continue;
		}
		if (t > max)
		{
			max = t;
			index = i;
		}
		newP = new element;
		newP->numb = t;
		newP->next = NULL;
		if (i == 0)
			begin = end = newP;
		else
		{
			end->next = newP;
			end = newP;
		}
	}

	system("cls");

	read(begin);
	cout << "\n\n\n";
	sdvig(&begin, &end, index);

	read(begin);

	return 0;
}

int read(element* begin)
{
	element* help=begin;

	while (help)
	{
		cout << help->numb << '\n';
		help = help->next;
	}

	return 0;
}

int sdvig(element** begin, element**end, int n)
{
	element* t, *p;

	for (int i = 0; i < n; i++)
	{
		t = *begin;
		p = *end;
		*end = t;
		*begin = t->next;
		t->next = NULL;
		p->next = t;
	}

	return 0;
}