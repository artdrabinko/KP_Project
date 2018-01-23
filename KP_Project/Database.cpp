#include "stdafx.h"
#include "Database.h"
#include <iostream>

Database::Database(){}

Database::~Database(){}


string Database::from_DOS(string DOS_string) {
	char buf[50];
	OemToCharA(DOS_string.c_str(), buf);
	return buf;
}

void Database::printError(int error) {
	switch (error) {
	case 1:
		cout << "Файл базы пациентов не найден!\n";
		cout << "Был создан новый файл - patients!\n\n";
		system("pause");
		break;
	case 2:
		system("cls");
		cout << "\n--------------------------------------------\n\n";
		cout << "           Предупреждение!\n\n";
		cout << "Файл с информацией о пациентах пуст или отсутствует\n\n";
		cout << "Обратитесь к администратору!\n\n\n";
		cout << "Code Error 2, File patients is not found!" << endl;
		cout << "\n--------------------------------------------\n\n";
		system("pause");
		break;
	}

}

//Печать в консоль переданного символа определённое количество раз
void Database::multiPrint(char simbol, int count) {
	for (int i = 0; i < count; ++i) {
		cout << simbol;
	}
}

void Database::printHeaderPatients() {
	multiPrint('=', 66); cout << endl;
	cout << "| " << setw(4) << "№" << " | " << setw(22) << "ФИО пациента" << " | " << setw(16) << "Услуга" << " | " << setw(11) << "Стоимость" << " |" << endl;
	cout << "| " << setw(4) << " " << " | " << setw(22) << " "            << " | " << setw(16) << " "      << " | " << setw(11) << "руб."     << " |" << endl;
	multiPrint('=', 66); cout << endl;
}

//Печать строки с информацией о пациенте
void Database::printRowPatient(Patient *PtrPatient, int countPatients) {
	cout << "| " << setw(4) << countPatients << " | " 
		 << setw(22) << (*PtrPatient).getShortFullName() << " | "
		 << setw(16) << (*PtrPatient).getService() << " | " 
		 << setw(11) << (*PtrPatient).getCost() << " |" << endl;
	multiPrint('-', 66); cout << endl;
}

void Database::loadDataAboutPatients() {
	string lastName, firstName, patronymic;
	string service;
	float cost;

	ifstream file("patients");
	if (file.is_open()) {
		while (file) {
			file >> lastName >> firstName >> patronymic >> service >> cost;
			if (file.eof()) break;
			Patient patient(lastName, firstName, patronymic, service, cost);
			listPatients.push_back(patient);
		}
	}
	else {
		printError(2);
	}
	file.close();
}


void Database::addNewPatientInFileDB(Patient *PtrPatient) {
	ifstream file("patients");
	if (file.is_open()) {
		file.close();
		ofstream addInFile("patients", ios_base::app);
		addInFile << (*PtrPatient).getLastName() << " " << (*PtrPatient).getFirstName() << " "
			<< (*PtrPatient).getPatronymic() << " " << (*PtrPatient).getService() << " "
			<< (*PtrPatient).getCost() << endl;
		addInFile.close();
	}
	else {
		printError(1);
		ofstream newFile("patients", ios_base::app);
		newFile << (*PtrPatient).getLastName() << " " << (*PtrPatient).getFirstName() << " "
			<< (*PtrPatient).getPatronymic() << " " << (*PtrPatient).getService() << " "
			<< (*PtrPatient).getCost() << endl;
		newFile.close();
	}
}

void Database::saveData() {
	ofstream file("patients");
	for (auto iterP = listPatients.begin(); iterP != listPatients.end(); ++iterP) {
		file << (*iterP).getLastName() << " " << (*iterP).getFirstName() << " "
			<< (*iterP).getPatronymic() << " " << (*iterP).getService() << " "
			<< (*iterP).getCost() << endl;
	}
	file.close();
}


//Метод осуществляет вывод(отрисовку таблицы) в консоль всех пациентах
void Database::printAllPatients() {
	printHeaderPatients();
	int countPatients = 1;
	for (auto iterP = listPatients.begin(); iterP != listPatients.end(); ++iterP) {
		printRowPatient(&(*iterP), countPatients);
		countPatients++;
	}
}

//Просмотр всех пациентов
void Database::viewAllPatients() {
	system("cls");
	cout << "\n----Список всех пациентов----\n\n";
	printAllPatients();
	cout << "\n\n";
	system("pause");
}


void Database::addNewPatient() {
	system("cls");
	cout << "\n-----Добавление нового пациента-----\n\n";
	Patient * patient = new Patient();
	patient->enterNewData();
	cout << "\nВы действительно хотите добавить нового пациента?\n";
	cout << "\nФИО : " + patient->getFullName();
	cout << "\nУслуга: " + patient->getService();
	cout << "\nСтоимость услуги: " << patient->getCost();
	cout << "\n\nДобавить нового пациента (да/нет) - "; cin >> command; cout << endl;
	command = from_DOS(command);
	if (command == "да" || command == "y") {
		listPatients.push_back(*patient);
		addNewPatientInFileDB(patient);
		cout << "Пациент успешно добавлен в базу!\n\n";
		system("pause");
	}
	else {
		delete patient;
		cout << "Отмена добавления пациента.\n\n";
		system("pause");
	}
}


//Удаление пациента по пордковому номеру
void Database::deletePatient() {
	string patientNumberForRemove; system("cls");
	cout << "\n-----Удаление пациента из базы-----\n" << endl;
	printAllPatients();
	cout << "\nВведите  номер пациента для удаления - "; cin >> patientNumberForRemove;
	int countPatients = 1;
	for (auto iterP = listPatients.begin(); iterP != listPatients.end(); ++iterP) {
		if (to_string(countPatients) == patientNumberForRemove) {
			system("cls"); cout << "\nПациент успешно найден!\n\n";
			printHeaderPatients();
			printRowPatient(&(*iterP), countPatients);
			cout << "\n\nУдалить пациента (да/нет) - "; cin >> command;
			command = from_DOS(command);
			if (command == "да" || command == "y") {
				listPatients.erase(iterP);
				saveData();
				cout << "\nПациент успешно удалён!\n\n";
				system("pause");
				return;
			}
			cout << "\nОтмена удаления!\n\n";
			system("pause");
			return;
		}
		countPatients++;
	}
	cout << "\nПациента с таким номером нет в списке!\n\n";
	system("pause");
}


void Database::createDatabaseFile() {
	char nameNewFile[20]; string command;
	ofstream file;
	system("cls");
	cout << "\n-----Создание файла нового файла БД-----\n\n";
	cout << "Введите название  - "; cin >> nameNewFile;
	cout << "\n\nСоздать файл " << nameNewFile << "  (да/нет) - "; cin >> command;
	command = from_DOS(command);
	if (command == "да" || command == "y") {
		file.open(nameNewFile);
		file.close();
		cout << "\nФайл БД успешно создан!\n\n";
		system("pause");
		return;
	}
	cout << "\nОтмена создания нового файла!\n\n";
	system("pause");
	return;
}

void Database::openFile() {
	char fileName[25];
	char strLine[200];
	system("cls");
	cout << "\n\n-----Открытие файла базы данных-----\n\n";
	cout << "Введите название файла - "; cin >> fileName;
	cout << "\n\n" << fileName << "\n\n";
	ifstream file(fileName);
	if (file.is_open()) {
		while (file) {
			file.getline(strLine, 200);
			if (file.eof()) break;
			cout << strLine << endl;
		}
	}
	else {
		cout << "\nФайл не существует!\n" << endl;
		system("pause");
	}
	cout << "\n\nФайл был успешно прочитан!\n\n";
	system("pause");
	file.close();
}

void Database::removeFile() {
	char fileName[25];
	string command;
	system("cls");
	cout << "\n\n-----Удаление файла базы данных-----\n\n";
	cout << "Введите название удаляемого файла - "; cin >> fileName;
	cout << "\nУдалить файл " << fileName << "  (да/нет) - "; cin >> command;
	command = from_DOS(command);
	if (command == "да" || command == "y") {
		remove(fileName) == 0 ? cout << "\nФайл успешно удален.\n\n" :
			cout << "\nОшибка удаления, проверьте название файла.\n\n";
		system("pause");
		return;
	}
	cout << "\nОтмена удаления!\n\n";
	system("pause");
	return;
}