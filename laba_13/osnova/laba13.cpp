#include<iostream>
#include<iomanip>
#include<Windows.h>

using namespace std;

struct holm
{
	int numb;
	holm* left, * right;
};

struct check
{
	int numb;
	check* next;
};

void creat(holm**, int, int, int, int);
void show(holm*, int);
int del_min(holm*, int, int, int);
int del_index(holm*, int , int, int, int, int);
int del(holm*, int, int, int);

void main()
{
	HANDLE color{ GetStdHandle(STD_OUTPUT_HANDLE) };
	holm* top{ nullptr };
	check* str{ nullptr };
	int var{}, numb{}, sloy{}, schet{};
	double  time{ pow(2, sloy) };

	while (true)
	{
		system("cls");
		SetConsoleTextAttribute(color, 15);
		cout << "Enter\n";
		cout << "1 - creat\n";
		cout << "2 - add\n";
		cout << "3 - delete the miniml\n";
		cout << "4 - delete for i\n";
		cout << "5 - show\n";
		cout << "6 - end\n";
		cin >> var;

		switch (var)
		{
		case 1:
			cout << "enter the colichestvo:\t";
			cin >> var;
			for (int i = 0; i < var; i++)
			{
				try
				{
					cout.width(2);
					cout << i + 1 << ") enter the number:\t";
					cin >> numb;
					if (!cin)
						throw exception("this is not numb");

					if (str == NULL)
					{
						str = new check;
						str->numb = numb;
						str->next = NULL;
					}
					else
					{
						check* c{ str };
						while (c != NULL)
						{
							if (c->numb == numb)
								throw exception("same");
							c = c->next;
						}
						c = new check;
						c->numb = numb;
						c->next = str;
						str = c;
					}

					creat(&top, numb, schet, (sloy - 1), time);
					schet++;
					if (schet == time)
					{
						schet = 0;
						sloy++;
						time = pow(2, sloy);
					}
					show(top, 0);
				}
				catch (exception& el)
				{
					cin.clear();
					cin.ignore(100, '\n');
					cout << el.what() << '\n';
					i--;
				}
			}
			break;

		case 2:
			try
			{
				cout << "enter the number:\t";
				cin >> numb;
				if (!cin)
					throw exception("this is not numb");

				if (str == NULL)
				{
					str = new check;
					str->numb = numb;
					str->next = NULL;
				}
				else
				{
					check* c{ str };
					while (c != NULL)
					{
						if (c->numb == numb)
							throw exception("same");
						c = c->next;
					}
					c = new check;
					c->numb = numb;
					c->next = str;
					str = c;
				}

				creat(&top, numb, schet, (sloy - 1), time);
				schet++;
				if (schet == time)
				{
					schet = 0;
					sloy++;
					time = pow(2, sloy);
				}
				show(top, 0);
			}
			catch (exception& el)
			{
				cin.clear();
				cin.ignore(100, '\n');
				cout << el.what() << '\n';
			}
			break;

		case 3:
			cout << "Do\n";
			SetConsoleTextAttribute(color, 4);
			show(top, 0);
			SetConsoleTextAttribute(color, 15);

			schet--;
			if (schet < 0)
			{
				sloy--;
				if (sloy < 0)
				{
					cout << "empty\n";
					sloy = 0;
					time = pow(2, 0);
					schet = 0;
				}
				else
				{
					time = pow(2, sloy);
					schet = time - 1;
				}
			}

			cout<<"\ndelete: "<<del_min(top, schet, (sloy - 1), time)<<"\n\n";
			SetConsoleTextAttribute(color, 2);
			cout << "posle\n";
			show(top, 0);
			break;

		case 4:
		{
			cout << "Do\n";
			SetConsoleTextAttribute(color, 4);
			show(top, 0);
			SetConsoleTextAttribute(color, 15);
			int dd{}, slo2{-1};
			for (int i = 0; i < sloy; i++)
				dd += pow(2, i);
			dd += schet;
			cout << "\nenter the indx:\t";
			cin >> numb;
			if (!cin || numb >  dd||numb<1)
			{
				cout << "error\n";
				cin.clear();
				cin.ignore(100, '\n');
				break;
			}
			schet--;
			if (schet < 0)
			{
				sloy--;
				if (sloy < 0)
				{
					cout << "empty\n";
					sloy = 0;
					time = pow(2, 0);
					schet = 0;
				}
				else
				{
					time = pow(2, sloy);
					schet = time - 1;
				}
			}
			if (numb == dd)
				cout << "delet: " << del(top, schet, (sloy-1), time) << "\n\n";
			else
			{
				dd = 1;
				while ((numb - dd) > 0)
				{
					numb -= dd;
					dd *= 2;
					slo2++;
				}
			
				cout << "delet: " << del_index(top, schet, (sloy - 1), time, slo2, numb) << "\n\n";
			}

			SetConsoleTextAttribute(color, 2);
			cout << "posle\n";
			show(top, 0);
		}
			break;

		case 5:
			if (top == NULL)
				cout << "empty\n";
			else
				show(top, 0);
			break;

		case 6:
			cout << "end";
			SetConsoleTextAttribute(color, 0);
			return;
			break;

		default:
			cout << "error\n";
			cin.clear();
			cin.ignore(100, '\n');
			break;
		}

		SetConsoleTextAttribute(color, 0);
		system("pause");
	}
}

void creat(holm** t, int n, int s, int need, int time)
{
	if (*t == NULL)
	{
		*t = new holm;
		(**t).numb = n;
		(**t).left = (**t).right = NULL;
		return;
	}

	holm* m{ *t }, * q{ new holm };
	q->numb = n;
	q->right = q->left = NULL;
	int get{ time / 2 }, smus{ time / 4 };

	for (int i = 0; i < need; i++)
	{
		if (m->numb < q->numb)
			swap(m->numb, q->numb);

		if (s < get)
		{
			m = m->left;
			get -= smus;
			smus /= 2;
		}
		else
		{
			m = m->right;
			get += smus;
			smus /= 2;
		}
	}

	if (m->numb < q->numb)
		swap(m->numb, q->numb);

	if (m->left == NULL)
		m->left = q;
	else
		m->right = q;
}

void show(holm* t, int n)
{
	if (t == NULL)
		return;
	else
	{
		show(t->left, ++n);

		cout << setw(4 * n) << setfill('=') << '=' << t->numb << '\n';
		n--;
	}
	show(t->right, ++n);
}

int del_min(holm* t, int s, int need, int time)
{
	int buf{}, get{ time / 2 }, smus{ time / 4 };
	double  povt{ pow(2, need) };
	holm* f{ t }, * m{ nullptr };

	for (int i = 0; i < need; i++)
	{
		if (s < get)
		{
			f = f->left;
			get -= smus;
			smus /= 2;
		}
		else
		{
			f = f->right;
			get += smus;
			smus /= 2;
		}
	}

	if (f->right != NULL)
	{
		m = f->right;
		f->right = NULL;
	}
	else
	{
		m = f->left;
		f->left = NULL;
	}

	buf = m->numb;
	delete m;
	

	
	for (int i = 0; i < povt*2; i+=2)
	{
		get = time / 2;
		smus = time / 4;
		f = t;
		
		int first, second{};

		for (int j = 0; j < need; j++)
		{
			first = f->numb;
			if (i < get)
			{
				f = f->left;
				get -= smus;
				smus /= 2;
			}
			else
			{
				f = f->right;
				get += smus;
				smus /= 2;
			}
			second = f->numb;
			if (second > first)
				swap(second, first);
		}

		if (f->numb < buf)
			swap(f->numb, buf);

		if (f->right != NULL)
		{
			if ((f->right)->numb < buf)
				swap((f->right)->numb, buf);
			if ((f->right)->numb > f->numb)
				swap((f->right)->numb, f->numb);
		}

		if (f->left != NULL)
		{
			if ((f->left)->numb < buf)
				swap((f->left)->numb, buf);
			if ((f->left)->numb > f->numb)
				swap((f->left)->numb, f->numb);
		}
	}

	return buf;
}

int del_index(holm* t, int s, int need, int time, int isk_slo, int isk_sch)
{
	int buf{}, get{ time / 2 }, smus{ time / 4 };
	holm* f{ t }, * m{ nullptr };

	for (int i = 0; i < need; i++)
	{
		if (s < get)
		{
			f = f->left;
			get -= smus;
			smus /= 2;
		}
		else
		{
			f = f->right;
			get += smus;
			smus /= 2;
		}
	}
	get = time / 2;
	smus = time / 4;
	if (f->right != NULL)
	{
		m = f->right;
		f->right = NULL;
	}
	else
	{
		m = f->left;
		f->left = NULL;
	}

	buf = m->numb;
	delete m;
	f = t;

	for (int i = 0; i < isk_slo; i++)
	{
		if ( isk_sch<= get)
		{
			f = f->left;
			get -= smus;
			smus /= 2;
		}
		else
		{
			f = f->right;
			get += smus;
			smus /= 2;
		}
	}

	if(isk_slo>=0)
	{
		if (isk_sch % 2 == 1)
			f = f->left;
		else
			f = f->right;
	}

	swap(f->numb, buf);

	while (f!=NULL)
	{
		if (f->left != NULL)
			if (f->numb < (f->left)->numb)
				swap(f->numb, (f->left)->numb);

		if (f->right != NULL)
			if (f->numb < (f->right)->numb)
				swap(f->numb, (f->right)->numb);
	
		f = f->left;
	}

	return buf;
}

int del(holm*t, int s, int need, int time)
{
	int buf{}, get{ time / 2 }, smus{ time / 4 };
	holm* f{ t }, * m{ nullptr };

	for (int i = 0; i < need; i++)
	{
		if (s < get)
		{
			f = f->left;
			get -= smus;
			smus /= 2;
		}
		else
		{
			f = f->right;
			get += smus;
			smus /= 2;
		}
	}
	get = time / 2;
	smus = time / 4;
	if (f->right != NULL)
	{
		m = f->right;
		f->right = NULL;
	}
	else
	{
		m = f->left;
		f->left = NULL;
	}

	buf = m->numb;
	delete m;

	return buf;
}