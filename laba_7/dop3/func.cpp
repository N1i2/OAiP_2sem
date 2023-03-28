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

	string adres{ "C:\\Users\\Admin\\Desktop\\univer\\OAiP\\7\\dop3\\info.txt" };

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
	string adres{ "C:\\Users\\Admin\\Desktop\\univer\\OAiP\\7\\dop3\\info.txt"  };
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
	int first{}, second{}, t{};
	cout << "enter the miniml number:\t";
	cin >> first;
	if (!cin)
	{
		cin.clear();
		cin.ignore(100, '\n');
		return 0;
	}
	cout << "enter the maximum number:\t";
	cin >> second;
	if (!cin)
	{
		cin.clear();
		cin.ignore(100, '\n');
		return 0;
	}
	if (first > second)
		return 0;

	element* help;

	while (p)
	{
		help = p;
		p = p->next;
		if (help->numb >= first && help->numb <= second)
		{
			t++;
			cout << t << " : " << help->numb << '\n';
		}
		delete help;
	}

	return t;
}