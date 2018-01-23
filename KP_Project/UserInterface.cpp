#include "stdafx.h"
#include "UserInterface.h"
#include <iostream>
#include <string>

UserInterface::UserInterface(){}


UserInterface::~UserInterface(){}

string UserInterface::from_DOS(string DOS_string) {
	char buf[50];
	OemToCharA(DOS_string.c_str(), buf);
	return buf;
}

void UserInterface::printError(int error) {
	switch (error) {
	case 1:
		cout << "\n\nТакой команды нет в меню!";
		cout << "\n\nПопытайтесь ещё раз.\n\n";
		system("pause");
		break;
	}
}

void UserInterface::startUserInterface() {
	int menuNumber; string enterNumber;

	database.loadDataAboutPatients();

	while (true) {
		system("cls");
		cout << "\n-----Меню пользователя-----\n\n";
		cout << "1.Работа с БД пациентов\n";
		cout << "2.Работа с файлом БД\n";
		cout << "3.Поиск пациента\n";
		cout << "4.Сортировка пациентов\n";
		cout << "0.Выход\n";
		try {
			cout << "\n\n\nВведите номер меню: "; cin >> enterNumber;
			menuNumber = stoi(enterNumber);
		}
		catch (...) { menuNumber = 404; }

		switch (menuNumber) {
		case 1:
			showMenuPatient();
			break;
		case 2:
			showMenuFileBD();
			break;
		case 3:
			//showMenuSort();
			break;
		case 4:
			//showMenuSort();
			break;
		case 0:
			return;
		case 404:
			printError(1);
			break;
		default:
			printError(1);
			break;
		}
	}
}



void UserInterface::showMenuPatient() {
	int menuNumber;
	string enterNumber;
	while (true) {
		system("cls");
		cout << "\n-----Меню работы со списком пациентов-----\n\n";
		cout << "1.Просмотр всех пациентов\n";
		cout << "2.Добавить нового пациента\n";
		cout << "3.Редактировать информацию о пациенте\n";
		cout << "4.Удалить пациента\n";
		cout << "0.Вернуться в главное меню\n";
		try {
			cout << "\n\n\nВведите номер меню: "; cin >> enterNumber;
			menuNumber = stoi(enterNumber);
		}
		catch (...) { menuNumber = 404; }
		switch (menuNumber) {
		case 1:
			database.viewAllPatients();
			break;
		case 2:
			database.addNewPatient();
			break;
		case 3:
			//showMenuEditPatient();
			break;
		case 4:
			database.deletePatient();
			break;
		case 0:
			return;
		case 404:
			printError(1);
			break;
		default:
			printError(1);
			break;
		}
	}
}


void UserInterface::showMenuFileBD() {
	int menuNumber;
	string enterNumber;
	while (true) {
		system("cls");
		cout << "\n-----Меню работы с файлом БД-----\n\n";
		cout << "1.Создать файл\n";
		cout << "2.Открыть файл\n";
		cout << "3.Удалить файл\n";
		cout << "0.Вернуться в главное меню\n";
		try {
			cout << "\n\n\nВведите номер меню: "; cin >> enterNumber;
			menuNumber = stoi(enterNumber);
		}
		catch (...) { menuNumber = 404; }
		switch (menuNumber) {
		case 1:
			database.createDatabaseFile();;
			break;
		case 2:
			database.openFile();
			break;
		case 3:
			database.removeFile();
			break;
		case 0:
			return;
		case 404:
			printError(1);
			break;
		default:
			printError(1);
			break;
		}
	}
}