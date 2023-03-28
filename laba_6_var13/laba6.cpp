#include<iostream>
#include<Windows.h>
#include<iomanip>
#include<fstream>
#define n 20
using namespace std;
int u{};
//funci
int locate();
int dob();
int del();
int save();
int show();
int look();
//struct
struct MyStruct
{
	int number{}, day{}, time_end{}, time_start{};
	string end{};
};
MyStruct vakzal[n];

HANDLE col{ GetStdHandle(STD_OUTPUT_HANDLE) };

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	setlocale(LC_ALL, "ru");
	while (true)
	{
		SetConsoleTextAttribute(col, 15);
		system("cls");
		cin.ignore(100, '\n');
		char var{};

		cout << "1 - Добавить расписание\n2 - Убрать расписание\n3 - Найти расписание по адресу прибытия\n4 - Сохранить в папку\n5 - Вывести всю инфу из папки\n6 - показать все\n7 - конец:\n";
		cin >> var;
		//action choice
		switch (var)
		{
		case '1':
			dob();
			cout << "Информация успешно добавлена\n";
			SetConsoleTextAttribute(col, 0);
			system("pause");
			break;

		case '2':
			del();
			cout << "Информация успешно удалена\n";
			SetConsoleTextAttribute(col, 0);
			system("pause");
			break;

		case '3':
			locate();
			break;

		case '4':
			save();
			cout << "Информация успешно занесена в папку\n";
			SetConsoleTextAttribute(col, 0);
			system("pause");
			break;

		case '5':
			show();
			cout << "Информация успешно занесена\n";
			SetConsoleTextAttribute(col, 0);
			system("pause");
			break;

		case '6':
			look();
			break;

		case '7':
			cout << "Конец\n\n";
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
	SetConsoleTextAttribute(col, 0);
	return 0;
}

int dob()
{
	int houer{}, minut{};
	while (true)
	{
		cout << "Введите номер поезда:\t";
		cin >> vakzal[u].number;
		//examination
		if (!cin)
		{
			cin.clear();
			cin.ignore(100, '\n');
			cout << "Это не число\n";
		}
		else
			break;
	}
	cout << "Введите пункт назначения:\t";
	cin >> vakzal[u].end;
	//examination
	while (true)
	{
		cout << "Введите дату отправки:\t";
		cin >> vakzal[u].day;
		if (vakzal[u].day < 1 || vakzal[u].day>31)
			cout << "Такой даты не может быть\n";
		else
			break;
	}
	//examination
	while (true)
	{
		cout << "Введите время отправки(ччмм(ч-час, м-минуты)):\t";
		cin >> vakzal[u].time_start;
		houer = (vakzal[u].time_start / 100);
		minut = (vakzal[u].time_start - houer * 100);
		if (houer >= 24 || minut >= 60 || vakzal[u].time_start < 0)
			cout << "Такого времени не может быть\n";
		else
			break;

	}
	//examination
	while (true)
	{
		cout << "Введите время прибытия(ччмм(ч-час, м-минуты)):\t";
		cin >> vakzal[u].time_end;
		houer = (vakzal[u].time_end / 100);
		minut = (vakzal[u].time_end - houer * 100);
		if (houer >= 24 || minut >= 60 || vakzal[u].time_end < 0)
			cout << "Такого времени не может быть\n";
		else
			break;

	}

	u++;
	return 0;
}

int del()
{
	//schedules shift each other and the last one is reset
	int k{};
	cout << "Какое по счету расписание вы хотите удолить:\t";
	cin >> k;
	if (k > u)
	{
		cout << "Такого билета нет\n";
		SetConsoleTextAttribute(col, 0);
		system("pause");
		return 0;
	}
	k--;
	for (int i = k; i <= u; i++)
	{
		if (i == u)
		{
			vakzal[i].number = 0;
			vakzal[i].end = "";
			vakzal[i].day = 0;
			vakzal[i].time_start = 0;
			vakzal[i].time_end = 0;
			u--;
		}
		else
		{
			vakzal[i].number = vakzal[i + 1].number;
			vakzal[i].end = vakzal[i + 1].end;
			vakzal[i].day = vakzal[i + 1].day;
			vakzal[i].time_start = vakzal[i + 1].time_start;
			vakzal[i].time_end = vakzal[i + 1].time_end;
		}
	}

	return 0;
}

int locate()
{
	int help{}, s_houer{}, s_minut{}, e_houer{}, e_minut{};
	string plase;
	cout << "Введите место назначения:\t";
	cin >> plase;
	for (int i = 0; i < u; i++)
	{
		if (plase == vakzal[i].end)
		{
			help++;
			s_houer = (vakzal[i].time_start / 100);
			s_minut = vakzal[i].time_start - s_houer * 100;
			e_houer = (vakzal[i].time_end / 100);
			e_minut = vakzal[i].time_end - e_houer * 100;
			cout << "\n\nПоезд под номером " << vakzal[i].number << "\nЕдит в " << vakzal[i].end << "\nДата выезда " << vakzal[i].day << "\nВ " << s_houer << " часов и " << s_minut << " минут" << "\nИ добереться до места назначения в " << e_houer << " часов и " << e_minut << " минут" << "\n\n";
			cout << setw(n * 3) << setfill('=') << '=' << "\n\n";
		}
	}
	if (help == 0)
		cout << "Туда не направляеться ни один поезд";
	SetConsoleTextAttribute(col, 0);
	system("pause");
	return 0;
}

int save()
{
	string adres{ "D:\\семестр2\\ОАиП\\4\\osnova\\file\\file.txt" };
	ofstream file;
	file.open(adres);
	if (!file.is_open())
	{
		cout << "error file";
		return 0;
	}
	for (int i = 0; i < u; i++)
	{
		file << vakzal[i].number << '\n' << vakzal[i].end << '\n' << vakzal[i].day << '\n' << vakzal[i].time_start << '\n' << vakzal[i].time_end << "\n\n";
	}
	file.close();
	return 0;
}

int show()
{
	string adres{ "D:\\семестр2\\ОАиП\\4\\osnova\\file\\file.txt" };
	ifstream file{};
	int i{}, t{};
	file.open(adres);
	if (!file.is_open())
	{
		cout << "error file";
		return 0;
	}
	while (!file.eof())
	{
		char copia[n][n];
		int help{}, chisl{};
		file.getline(copia[chisl], n);
		if (t == 0)
		{
			help = atoi(copia[chisl]);
			vakzal[i].number = help;
		}
		if (t == 1)
			vakzal[i].end = copia[chisl];
		if (t == 2)
		{
			help = atoi(copia[chisl]);
			vakzal[i].day = help;
		}
		if (t == 3)
		{
			help = atoi(copia[chisl]);
			vakzal[i].time_start = help;
		}
		if (t == 4)
		{
			help = atoi(copia[chisl]);
			vakzal[i].time_end = help;
		}
		if (t == 5)
		{
			i++;
			t = -1;
			chisl++;
		}
		t++;
	}
	u = i;
	file.close();
	return 0;
}

int look()
{
	int s_houer{}, s_minut{}, e_houer{}, e_minut{};
	for (int i = 0; i < u; i++)
	{
		s_houer = (vakzal[i].time_start / 100);
		s_minut = vakzal[i].time_start - s_houer * 100;
		e_houer = (vakzal[i].time_end / 100);
		e_minut = vakzal[i].time_end - e_houer * 100;
		cout << "\n\nПоезд под номером " << vakzal[i].number << "\nЕдит в " << vakzal[i].end << "\nДата выезда " << vakzal[i].day << "\nВ " << s_houer << " часов и " << s_minut << " минут" << "\nИ добереться до места назначения в " << e_houer << " часов и " << e_minut << " минут" << "\n\n";
		cout << setw(n * 3) << setfill('=') << '=' << "\n\n";
	}
	if (u == 0)
		cout << "Никаких расписаний нет";
	SetConsoleTextAttribute(col, 0);
	system("pause");

	return 0;
}