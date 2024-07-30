#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
#include <vector>
#include <cstdlib>
#include <windows.h>
#include <algorithm>
#include <sstream>

using namespace std;

struct ticket {
	string num_train;
	string depart;
	string destin;
	string num_carriage;
	string carriage;
	string price;
	string date_depart;
};

struct list_carriage {
	string num_train;
	string num_carriage;
	string carriage;
	string price;
};

vector <ticket> data_tickets;
vector <ticket> original_data;
vector <ticket> search_data;
vector <list_carriage> list_data;
int n = 0;
string file_name;

void input() {
	ifstream fin("Входные данные.txt");
	string temp = ""; // String в котором будет построчно хранить файл
	int a = 0; // номер строки
	while (fin) {
		getline(fin, temp); // записываем в temp текущую строку
		temp.erase(remove_if(temp.begin(), temp.end(), isspace), temp.end()); // удаляем все пробелы

		if ((a > 2) && (a % 2 != 0) && (temp != "")) // не считываем шапку и разделители строк
		{
			ticket tick_input_file;

			temp = temp.substr(1, temp.size() - 2); // Убирает | в начале и в конце | 

			stringstream test(temp);
			string segment;
			vector<string> seglist;

			while (getline(test, segment, '|'))
			{
				seglist.push_back(segment);
			}

			tick_input_file.num_train = seglist[1];
			tick_input_file.depart = seglist[2];
			tick_input_file.destin = seglist[3];
			tick_input_file.num_carriage = seglist[4];
			tick_input_file.carriage = seglist[5];
			tick_input_file.price = seglist[6];
			tick_input_file.date_depart = seglist[7];

			data_tickets.push_back(tick_input_file);
			n++;
		}
		a++; 
	}
	cout << "Ввод данных успешно завершен" << endl;
	fin.close();
	copy(data_tickets.begin(), data_tickets.end(), back_inserter(original_data));
}

void save_data(vector <ticket> vec) {
	ofstream fout(file_name);
	fout << " -------------------------------------------------------------------------------------------------------------------" << endl;
	fout << " | N  | N поезда |  Пункт отправления  |  Пункт назначения  | N и тип вагона | Стоимость билета | Дата отправления |" << endl;
	fout << " -------------------------------------------------------------------------------------------------------------------" << endl;
	for (int i = 0; i < vec.size(); i++) {
		fout << " | " << setw(2) << i + 1 << " | " << setw(6) << vec[i].num_train << "   | " << setw(15) << vec[i].depart << "     | "\
			<< setw(16) << vec[i].destin << "   | ";
		if (vec[i].carriage == "купе") {
			fout << setw(6) << vec[i].num_carriage << " " << vec[i].carriage << "    | ";
		}
		else {
			fout << setw(4) << vec[i].num_carriage << " " << vec[i].carriage << "  | ";
		}
		fout << setw(16) << vec[i].price << " | " << setw(14) << vec[i].date_depart << "   | " << endl;
		fout << " -------------------------------------------------------------------------------------------------------------------" << endl;
	}
	fout.close();
	cout << "Таблица загружена в файл " << file_name << endl;
}

void save_list(vector <list_carriage> vec) {
	ofstream fout(file_name);
	fout << " -----------------------------------------------------" << endl;
	fout << " | N  | N поезда | N и тип вагона | Стоимость билета |" << endl;
	fout << " -----------------------------------------------------" << endl;
	for (int i = 0; i < vec.size(); i++) {
		fout << " | " << setw(2) << i + 1 << " | " << setw(6) << vec[i].num_train << "   | ";
		if (vec[i].carriage == "купе") {
			fout << setw(6) << vec[i].num_carriage << " " << vec[i].carriage << "    | ";
		}
		else {
			fout << setw(4) << vec[i].num_carriage << " " << vec[i].carriage << "  | ";
		}
		fout << setw(16) << vec[i].price << " | " << endl;
		fout << " -----------------------------------------------------" << endl;
	}
	fout.close();
	cout << "Перечень загружен в файл " << file_name << endl;
}

void add() {
	ticket tick_input_console;
	cout << "ВВЕДИТЕ ДАННЫЕ" << endl;
	cout << "Номер поезда : ";
	cin >> tick_input_console.num_train;
	cout << "Пункт отправления : ";
	cin >> tick_input_console.depart;
	cout << "Пункт назначения : ";
	cin >> tick_input_console.destin;
	cout << "N и тип вагона : ";
	cin >> tick_input_console.num_carriage;
	cin >> tick_input_console.carriage;
	cout << "Стоимость билета : ";
	cin >> tick_input_console.price;
	cout << "Дата отправления : ";
	cin >> tick_input_console.date_depart;
	data_tickets.push_back(tick_input_console);
	n++;
	cout << "Новая строка успешно введена" << endl;
}

void delete_field(int field) {
	if (data_tickets.empty()) {
		cout << "Таблица пустая" << endl;
	}
	else {
		auto iter = data_tickets.cbegin();
		data_tickets.erase(iter + field - 1);
		n -= 1;
		cout << "Строка " << field << " удалена из таблицы" << endl;
	}
}

void output() {
	cout << " -------------------------------------------------------------------------------------------------------------------" << endl;
	cout << " | N  | N поезда |  Пункт отправления  |  Пункт назначения  | N и тип вагона | Стоимость билета | Дата отправления |" << endl;
	cout << " -------------------------------------------------------------------------------------------------------------------" << endl;
	for (int i = 0; i < n; i++) {
		cout << " | " << setw(2) << i + 1 << " | " << setw(6) << data_tickets[i].num_train << "   | " << setw(15) << data_tickets[i].depart << "     | "\
			<< setw(16) << data_tickets[i].destin << "   | ";
		if (data_tickets[i].carriage == "купе") {
			cout << setw(6) << data_tickets[i].num_carriage << " " << data_tickets[i].carriage << "    | ";
		}
		else {
			cout << setw(4) << data_tickets[i].num_carriage << " " << data_tickets[i].carriage << "  | ";
		}
		cout << setw(16) << data_tickets[i].price << " | " << setw(14) << data_tickets[i].date_depart << "   | " << endl;
		cout << " -------------------------------------------------------------------------------------------------------------------" << endl;
	}
	cout << "Вывод данных успешно завершен" << endl;
}

bool cmp_num_train(ticket& a, ticket& b) {
	return a.num_train < b.num_train;
}

void sort_num() {
	sort(data_tickets.begin(), data_tickets.end(), cmp_num_train);
	cout << "Таблица отсортирована по номеру поезда" << endl;
}

bool cmp_depart(ticket& a, ticket& b) {
	if (a.depart == b.depart) {
		if (a.date_depart.substr(6, 4) < b.date_depart.substr(6, 4)) return true;
		if (a.date_depart.substr(6, 4) > b.date_depart.substr(6, 4)) return false;
		if (a.date_depart.substr(3, 2) < b.date_depart.substr(3, 2)) return true;
		if (a.date_depart.substr(3, 2) < b.date_depart.substr(3, 2)) return false;
		return a.date_depart.substr(0, 2) < b.date_depart.substr(0, 2);
	}
	else return a.depart < b.depart;
}

void sort_alf() {
	sort(data_tickets.begin(), data_tickets.end(), cmp_depart);
	cout << "Таблица отсортирована алфавитно по пункту отправления и по дате отправления" << endl;
}

void search_destination(string city) {
	ticket search;
	cout << " -------------------------------------------------------------------------------------------------------------------" << endl;
	cout << " | N  | N поезда |  Пункт отправления  |  Пункт назначения  | N и тип вагона | Стоимость билета | Дата отправления |" << endl;
	cout << " -------------------------------------------------------------------------------------------------------------------" << endl;
	for (int i = 0; i < n; i++) {
		if (data_tickets[i].destin == city) {

			search.num_train = data_tickets[i].num_train;
			search.depart = data_tickets[i].depart;
			search.destin = data_tickets[i].destin;
			search.num_carriage = data_tickets[i].num_carriage;
			search.carriage = data_tickets[i].carriage;
			search.price = data_tickets[i].price;
			search.date_depart = data_tickets[i].date_depart;
			search_data.push_back(search);

			cout << " | " << setw(2) << i + 1 << " | " << setw(6) << data_tickets[i].num_train << "   | " << setw(15) << data_tickets[i].depart << "     | "\
				<< setw(16) << data_tickets[i].destin << "   | ";
			if (data_tickets[i].carriage == "купе") {
				cout << setw(6) << data_tickets[i].num_carriage << " " << data_tickets[i].carriage << "    | ";
			}
			else {
				cout << setw(4) << data_tickets[i].num_carriage << " " << data_tickets[i].carriage << "  | ";
			}
			cout << setw(16) << data_tickets[i].price << " | " << setw(14) << data_tickets[i].date_depart << "   | " << endl;
			cout << " -------------------------------------------------------------------------------------------------------------------" << endl;
		}
	}
}

void carriages() {
	list_carriage list_local;

	cout << " -----------------------------------------------------" << endl;
	cout << " | N  | N поезда | N и тип вагона | Стоимость билета |" << endl;
	cout << " -----------------------------------------------------" << endl;
	for (int i = 0; i < n; i++) {

		list_local.num_train = data_tickets[i].num_train;
		list_local.num_carriage = data_tickets[i].num_carriage;
		list_local.carriage = data_tickets[i].carriage;
		list_local.price = data_tickets[i].price;
		list_data.push_back(list_local);

		cout << " | " << setw(2) << i + 1 << " | " << setw(6) << data_tickets[i].num_train << "   | ";
		if (data_tickets[i].carriage == "купе") {
			cout << setw(6) << data_tickets[i].num_carriage << " " << data_tickets[i].carriage << "    | ";
		}
		else {
			cout << setw(4) << data_tickets[i].num_carriage << " " << data_tickets[i].carriage << "  | ";
		}
		cout << setw(16) << data_tickets[i].price << " | " << endl;
		cout << " -----------------------------------------------------" << endl;
	}
}

void date(string s_date) {
	ticket search;
	cout << " -------------------------------------------------------------------------------------------------------------------" << endl;
	cout << " | N  | N поезда |  Пункт отправления  |  Пункт назначения  | N и тип вагона | Стоимость билета | Дата отправления |" << endl;
	cout << " -------------------------------------------------------------------------------------------------------------------" << endl;
	for (int i = 0; i < n; i++) {
		if (data_tickets[i].date_depart == s_date) {

			search.num_train = data_tickets[i].num_train;
			search.depart = data_tickets[i].depart;
			search.destin = data_tickets[i].destin;
			search.num_carriage = data_tickets[i].num_carriage;
			search.carriage = data_tickets[i].carriage;
			search.price = data_tickets[i].price;
			search.date_depart = data_tickets[i].date_depart;
			search_data.push_back(search);

			cout << " | " << setw(2) << i + 1 << " | " << setw(6) << data_tickets[i].num_train << "   | " << setw(15) << data_tickets[i].depart << "     | "\
				<< setw(16) << data_tickets[i].destin << "   | ";
			if (data_tickets[i].carriage == "купе") {
				cout << setw(6) << data_tickets[i].num_carriage << " " << data_tickets[i].carriage << "    | ";
			}
			else {
				cout << setw(4) << data_tickets[i].num_carriage << " " << data_tickets[i].carriage << "  | ";
			}
			cout << setw(16) << data_tickets[i].price << " | " << setw(14) << data_tickets[i].date_depart << "   | " << endl;
			cout << " -------------------------------------------------------------------------------------------------------------------" << endl;
		}
	}
}


int main()
{
	setlocale(LC_ALL, "Russian");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	cout << "Выберете функцию : " << endl;
	cout << "0) Закрыть программу" << endl;
	cout << "1) Загрузка из файла" << endl;
	cout << "2) Сохранение результата обработки в файл" << endl;
	cout << "3) Добавление записи" << endl;
	cout << "4) Удаление записи" << endl;
	cout << "5) Вывод данных в консоль" << endl;
	cout << "6) Числовая сортировка по номеру поезда" << endl;
	cout << "7) Алфавитная сортировка по пункту отправления" << endl;
	cout << "8) Поиск по пункту назначения" << endl;
	cout << "9) Перечень типов вагонов с указанием стоимости" << endl;
	cout << "10) Поиск по дате отправления пункта назначения" << endl;
	int num = -1;
	int num_delete;
	string s;
	while (num != 0) {
		cin >> num;
		if (num == 1) {
			input();
		}
		else if (num == 2) {
			int num_file;
			cout << "Выберете файл для вывода : " << endl;
			cout << "1) Исходная таблица" << endl;
			cout << "2) Отсортированная таблица" << endl;
			cout << "3) Поиск по таблице" << endl;
			cout << "4) Перечень" << endl;
			cin >> num_file;
			if (num_file == 1) {
				file_name = "Исходная таблица.txt";
				save_data(original_data);
			}
			else if (num_file == 2) {
				file_name = "Отсортированная таблица.txt";
				save_data(data_tickets);
			}
			else if (num_file == 3) {
				file_name = "Поиск по таблице.txt";
				save_data(search_data);
			}
			else if (num_file == 4) {
				file_name = "Перечень.txt";
				save_list(list_data);
			}
			else cout << "Такого файла нет. Повторите попытку" << endl;
		}
		else if (num == 3) {
			add();
		}
		else if (num == 4) {
			cout << "Номер строки, которую нужно удалить : ";
			cin >> num_delete;
			delete_field(num_delete);
		}
		else if (num == 5) {
			output();
		}
		else if (num == 6){
			sort_num();
		}
		else if (num == 7) {
			sort_alf();
		}
		else if (num == 8) {
			cout << "Введите пункт назначения" << endl;
			cin >> s;
			search_destination(s);
		}
		else if (num == 9) {
			carriages();
		}
		else if (num == 10) {
			cout << "Введите дату отправления" << endl;
			cin >> s;
			date(s);
		}
		else if (num != 0) {
			cout << "Такого пункта нет. Повторите попытку" << endl;
		}
	}
}