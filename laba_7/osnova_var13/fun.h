#pragma once

struct element//���� � ���� ���������
{
	int numb;
	element* next;
};

int dob(element*&);//������� ���������� ��������

int clear(element*&);//������� �������� ����� �����

int save(element*&);//������� ���������� ����� � ����

int read(element*&);//������� ������ ����� �� �����

int schet(element*&);//������� ���������