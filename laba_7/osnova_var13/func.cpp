#include<iostream>
#include<fstream>
#include"fun.h"
using namespace std;

int dob(element*& p)
{
	int numb{};

	cout << "enter the numbr:\t";
	cin >> numb;
	if (!cin)
	{
		cin.clear();
		cin.ignore(100, '\n');
		return 0;//0 - ������
	}

	element* newP = new element;//��������� ����� ��� ������

	newP->numb = numb;
	newP->next = p;
	p = newP;

	return 1;//1 - ��� �����
}

int clear(element*& p)
{
	if (p == NULL)//�������� ���� �� ��� �������
		return 0;

	element* del;//�������������� ��������������� ���������

	while (p)
	{
		del = p;
		p = p->next;
		delete del;
	}

	return 1;
}

int save(element*& p)
{
	if (p == NULL)
		return 0;

	string adres{"C:\\Users\\Admin\\Desktop\\univer\\OAiP\\7\\osnow\\info.txt"  };

	ofstream file{};
	file.open(adres);
	if (!file.is_open())
		return 0;

	element* help;//��� ��������� ��� �� ����� ���� �������� �� ��� ���� �������� 

	while (p)
	{
		help = p;
		p = p->next;
		file << help->numb << '\n';
		delete help;
	}

	file.close();

	return 1;
}

int read(element*& p)
{
	string adres{ "C:\\Users\\Admin\\Desktop\\univer\\OAiP\\7\\osnow\\info.txt" };
	int numb, t{};

	ifstream file;
	file.open(adres);
	if (!file.is_open())
		return 0;

	while (!file.eof())
	{
		t++;
		file >> numb;
		if (!cin)
		{
			cin.clear();
			cin.ignore(100, '\n');
			return 0;
		}

		element* newP = new element;

		newP->numb = numb;
		newP->next = p;
		p = newP;
	}

	element* del;
	//������� ��������� ���������� ��������(��������)
	del = p;
	p = p->next;
	delete del;

	file.close();

	if (t == 1)//���� ����
		return 0;

	return 1;
}

int schet(element*& p)
{
	if (p == NULL)
		return 0;

	int t{}, j{ 1 }, test{ 1 }, such{};
	int num[20]{}, usel[10]{};
	
	num[0] = p->numb;
	p = p->next;

	while (p)
	{
		test = 0;
		for (int i = 0; i < such; i++)
		{
			if (p->numb == usel[i])
			{
				test--;
				break;
			}
		}
		for (int i = 0; i < j; i++)
		{
			if (p->numb == num[i])
			{
				test++;
				break;
			}
		}

		if (test == 0)
		{
			num[j] = p->numb;
			j++;
		}
		else
		{
			usel[such] = p->numb;
			such++;
			t++;
		}

		p = p->next;
	}

	return t;
}