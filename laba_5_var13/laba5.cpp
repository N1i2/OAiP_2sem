#include<iostream>
#include<iomanip>
#include<Windows.h>
#include<fstream>
using namespace std;
//Создать список, содержащий элементы целого типа. Найти сумму отрицательных двухзначных элементов или выдать сообщение, что таких элементов нет.

//Список
struct element
{
	int numb{};
	element* next{};
};
//добавить новое число
int dob(element*&);

//удолить число
int dell(element*&);

//показать все числа
int show(element*);

//сохранить в папку
int save(element*);

//вывести инфу из папки
int read(element*&);

//счет
int sum(element*);

int main()
{
	//указатель на первый элимент списка
	element* first{ NULL };
	setlocale(LC_ALL, "ru");
	HANDLE col{ GetStdHandle(STD_OUTPUT_HANDLE) };
	int var{};

	while (true)
	{
		SetConsoleTextAttribute(col, 15);
		system("cls");
		cout << "Выберите вариант\n1 - Добавить новое число\n2 - Удолить число\n3 - Просмотреть все числа\n4 - Записать числа в файл\n5 - Вывести числа из файла\n6 - Найти сумму двухзначных отрицательных чисел\n7 - Конец\n";

		cin >> var;
		if (!cin)
		{
			cout << "Это не число\n";
			SetConsoleTextAttribute(col, 0);
			system("pause");
			cin.clear();
			cin.ignore(100, '\n');
			continue;
		}

		switch (var)
		{
		case 1:
			dob(first);
			SetConsoleTextAttribute(col, 0);
			system("pause");
			break;

		case 2:
			//проверка есть ли такое число и есть ли числа вообще
			if (first == NULL)
				cout << "Нет чисел так что и удолять нечего\n";
			else if (dell(first))
				cout << "Число удолено\n";
			else
				cout << "Такого числа нет\n";
			SetConsoleTextAttribute(col, 0);
			system("pause");
			break;

		case 3:
			show(first);
			SetConsoleTextAttribute(col, 0);
			system("pause");
			break;

		case 4:
			if (save(first))
				cout << "Информация успешно сохранен\n";
			SetConsoleTextAttribute(col, 0);
			system("pause");
			break;

		case 5:
			read(first);
			//проверка есть ли что то в папке
			if (first == NULL)
				cout << "Папка пуста\n";
			else
				cout << "Информация из файла сохранена\n";
			SetConsoleTextAttribute(col, 0);
			system("pause");
			break;

		case 6:
			sum(first);
			SetConsoleTextAttribute(col, 0);
			system("pause");
			break;

		case 7:
			cout << "Конец\n";
			SetConsoleTextAttribute(col, 0);
			return 0;
			break;

		default:
			cout << "Такого варианта нет\n";
			SetConsoleTextAttribute(col, 0);
			system("pause");
			break;
		}
	}
}

int dob(element*& p)
{
	int numb{};
	cout << "Введите число:\t";
	cin >> numb;
	if (!cin)
	{
		cin.clear();
		cin.ignore(100, '\n');
		return 0;
	}
	element* newP = new element;//выдиление памяти для будующего элемента списка

	if (newP != NULL)//если еще хватает памяти записать
	{
		newP->numb = numb;//присваеваем только что созданому элименту значение
		newP->next = p;//присваевыем адрес новому значению
		p = newP;//связываем новое значение с предыдущим
		cout << "Цифра успешно добавлена\n";
	}
	else
		cout << "Не получилось добавить число\n";


	return 0;
}

int dell(element*& p)
{
	element* help{}, * adre{}, * tmp{};

	int numb{};
	cout << "Введите число которое надо удолить:\t";
	cin >> numb;
	if (!cin)
	{
		cin.clear();
		cin.ignore(100, '\n');
		return 0;
	}

	if (numb == p->numb)//проверка если число которое надо удолить первое в списке
	{
		tmp = p;//присваеваем адрес этой памяти другой
		p = p->next;//Делаем переход на следующюю ячейку
		tmp = NULL;//обнуляем ранее переписаную память
		return 1;//выводим число 1 что бы в main указать что все прошло успешно и 0 если ошибка
	}
	else
	{
		help = p;//адрес первой ячейки
		adre = p->next;//адрес следующей ячейки
		while (adre != NULL && adre->numb != numb)//цикл будет идти пока лобо следующая ячейка не будет равна NULL(такого числа нет) либо пока в следующей ячейке не будет искмое число)
		{
			//ход цикла
			help = adre;//переходим с ячейки на которой стоим сейчас на следующкю
			adre = adre->next;//следующуу также двигаем на один элимент вперед
		}
		if (adre != NULL)//если число было найдено до того как закончился список
		{
			tmp = adre;//присваеваем адрес этой памяти другой
			help->next = adre->next;//адрес ячейки на которой мы были связываем с адресолм на который указывает следующий элимент
			free(tmp);//освобождаем память переписанного элимента
			return 1;
		}
	}

	return 0;
}

int show(element* p)
{
	if (p == NULL)//проверка есть ли элементы списка
		cout << "Тут ничего не записано\n";
	else
	{
		cout << "Список всех чисел\n";
		while (p != NULL)//цикл будет иддти пока укозатель на следующюю ячейку не покажет NULL (конец списка)
		{
			cout << p->numb << '\n';
			p = p->next;//двигаемся вперед по адресам
		}
	}

	return 0;
}

int save(element* p)
{
	if (p == NULL)//проверка есть ли вообще что то в списке
	{
		cout << "Нечего записывать\n";
		return 0;//вывод 0 значит не получилось сохранить 1 - все хорошо
	}
	string adres{ "D:\\семестр2\\ОАиП\\6\\osnov\\file\\info.txt" };//адрес папки

	ofstream file{};//открываем папку
	file.open(adres);//находим папку по ранее заданому адресу
	if (!file.is_open())//проверка что такая папака есть
	{
		cout << "Ошипка доступа к файлу\n";
		return 0;
	}

	while (p)//пока р не равно NULL
	{
		file << p->numb << '\n';//запись элемента списка в файл
		p = p->next;//переход по адресам
	}


	file.close();//закрытие списка

	return 1;
}

int read(element*& p)
{
	string adres{ "D:\\семестр2\\ОАиП\\6\\osnov\\file\\info.txt" };//адрес файла

	ifstream file{};//открыть файл
	file.open(adres);//найти файл по адресу
	if (!file.is_open())//проверка существованя файла
	{
		cout << "Ошипка доступа к файлу\n";
		return 0;
	}

	int t{};//переменная помошник

	while (!file.eof())
	{
		int help{};//переменная куда выводяться числа из файла
		file >> help;//вывод из файла
		if (!cin)//проверка что выведеное это число
		{
			cin.clear();
			cin.ignore(100, '\n');
			continue;
		}
		if (help == 0 && t == 0)//если первыфй элемент 0 то его не записывать
		{
			continue;
		}
		t++;

		element* newP = new element;//выделение памяти для элемента списка

		newP->numb = help;//присвоение элементу списка числа из файла
		newP->next = p;//переход к следующему
		p = newP;//связь нового с предыдущим
	}

	file.close();//закрытие файла

	return 0;
}

int sum(element* p)
{
	int sum{};//сумма

	if (p == NULL)//проверка на то что в списке есть числа
		cout << "Список пуст\n";
	else
	{
		while (p)//цикл пока не закончиться список
		{
			if (p->numb <= -100)
				sum += p->numb;
			p = p->next;//переход к следующему элементу
		}
	}

	if (sum == 0)//если сумма только отрицательных чисел равно 0 значит и чисел нет
		cout << "Таких чисел нет\n";
	else
		cout << "Сумма двузначных отрицательных чисел = " << sum;

	return 0;
}