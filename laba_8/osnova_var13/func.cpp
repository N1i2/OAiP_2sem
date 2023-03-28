#include<iostream>
#include"fun.h"

using namespace std;

int show(element* begin)
{
	if (begin == NULL)
		return 0;

	system("cls");
	cout << "1 - all numbers\n\n";
	int nn{};
	element* t = begin;

	while (t != NULL)
	{
		nn++;
		cout << nn << ") " << t->numb << '\n';
		t = t->next;
	}

	cout << "\nqueue size: " << nn << '\n';

	return 1;
}

int dell(element** begin, int d)
{
	if (*begin == NULL)
		return 0;

	element* t = *begin, * help{};

	if (t->numb == d)
	{
		help = t;
		t = t->next;
		help = NULL;
		*begin = t;
		return 1;
	}
	else
	{
		element* dop = t->next;
		while (dop)
		{
			if (dop->numb == d)
			{
				help = dop;
				t->next = help->next;
				free(help);
				return 1;
			}
			t = dop;
			dop = dop->next;
		}
	}

	return 0;
}

int clear(element** begin)
{
	element* t = *begin;
	element* last = t->next, * del{};
	while (last)
	{
		del = t;
		t = last;
		last = last->next;
	}

	return 0;
}

int minMax(element* begin)
{
	if (begin == NULL)
		return 0;

	element* t = begin;
	int Max{ -999999 }, Min{ 999999 };
	while (t)
	{
		if (t->numb > Max)
			Max = t->numb;
		if (t->numb < Min)
			Min = t->numb;

		t = t->next;
	}

	if (Max == Min)
		cout << "all numbers are the same: " << Min;
	else
		cout << "maximl: " << Max << "\nminiml: " << Min;
	return 1;
}