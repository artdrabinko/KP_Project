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
		cout << "���� ���� ��������� �� ������!\n";
		cout << "��� ������ ����� ���� - patients!\n\n";
		system("pause");
		break;
	case 2:
		system("cls");
		cout << "\n--------------------------------------------\n\n";
		cout << "           ��������������!\n\n";
		cout << "���� � ����������� � ��������� ���� ��� �����������\n\n";
		cout << "���������� � ��������������!\n\n\n";
		cout << "Code Error 2, File patients is not found!" << endl;
		cout << "\n--------------------------------------------\n\n";
		system("pause");
		break;
	}

}

//������ � ������� ����������� ������� ����������� ���������� ���
void Database::multiPrint(char simbol, int count) {
	for (int i = 0; i < count; ++i) {
		cout << simbol;
	}
}

void Database::printHeaderPatients() {
	multiPrint('=', 66); cout << endl;
	cout << "| " << setw(4) << "�" << " | " << setw(22) << "��� ��������" << " | " << setw(16) << "������" << " | " << setw(11) << "���������" << " |" << endl;
	cout << "| " << setw(4) << " " << " | " << setw(22) << " "            << " | " << setw(16) << " "      << " | " << setw(11) << "���."     << " |" << endl;
	multiPrint('=', 66); cout << endl;
}

//������ ������ � ����������� � ��������
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


//����� ������������ �����(��������� �������) � ������� ���� ���������
void Database::printAllPatients() {
	printHeaderPatients();
	int countPatients = 1;
	for (auto iterP = listPatients.begin(); iterP != listPatients.end(); ++iterP) {
		printRowPatient(&(*iterP), countPatients);
		countPatients++;
	}
}

//�������� ���� ���������
void Database::viewAllPatients() {
	system("cls");
	cout << "\n----������ ���� ���������----\n\n";
	printAllPatients();
	cout << "\n\n";
	system("pause");
}


void Database::addNewPatient() {
	system("cls");
	cout << "\n-----���������� ������ ��������-----\n\n";
	Patient * patient = new Patient();
	patient->enterNewData();
	cout << "\n�� ������������� ������ �������� ������ ��������?\n";
	cout << "\n��� : " + patient->getFullName();
	cout << "\n������: " + patient->getService();
	cout << "\n��������� ������: " << patient->getCost();
	cout << "\n\n�������� ������ �������� (��/���) - "; cin >> command; cout << endl;
	command = from_DOS(command);
	if (command == "��" || command == "y") {
		listPatients.push_back(*patient);
		addNewPatientInFileDB(patient);
		cout << "������� ������� �������� � ����!\n\n";
		system("pause");
	}
	else {
		delete patient;
		cout << "������ ���������� ��������.\n\n";
		system("pause");
	}
}


//�������� �������� �� ���������� ������
void Database::deletePatient() {
	string patientNumberForRemove; system("cls");
	cout << "\n-----�������� �������� �� ����-----\n" << endl;
	printAllPatients();
	cout << "\n�������  ����� �������� ��� �������� - "; cin >> patientNumberForRemove;
	int countPatients = 1;
	for (auto iterP = listPatients.begin(); iterP != listPatients.end(); ++iterP) {
		if (to_string(countPatients) == patientNumberForRemove) {
			system("cls"); cout << "\n������� ������� ������!\n\n";
			printHeaderPatients();
			printRowPatient(&(*iterP), countPatients);
			cout << "\n\n������� �������� (��/���) - "; cin >> command;
			command = from_DOS(command);
			if (command == "��" || command == "y") {
				listPatients.erase(iterP);
				saveData();
				cout << "\n������� ������� �����!\n\n";
				system("pause");
				return;
			}
			cout << "\n������ ��������!\n\n";
			system("pause");
			return;
		}
		countPatients++;
	}
	cout << "\n�������� � ����� ������� ��� � ������!\n\n";
	system("pause");
}


void Database::createDatabaseFile() {
	char nameNewFile[20]; string command;
	ofstream file;
	system("cls");
	cout << "\n-----�������� ����� ������ ����� ��-----\n\n";
	cout << "������� ��������  - "; cin >> nameNewFile;
	cout << "\n\n������� ���� " << nameNewFile << "  (��/���) - "; cin >> command;
	command = from_DOS(command);
	if (command == "��" || command == "y") {
		file.open(nameNewFile);
		file.close();
		cout << "\n���� �� ������� ������!\n\n";
		system("pause");
		return;
	}
	cout << "\n������ �������� ������ �����!\n\n";
	system("pause");
	return;
}

void Database::openFile() {
	char fileName[25];
	char strLine[200];
	system("cls");
	cout << "\n\n-----�������� ����� ���� ������-----\n\n";
	cout << "������� �������� ����� - "; cin >> fileName;
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
		cout << "\n���� �� ����������!\n" << endl;
		system("pause");
	}
	cout << "\n\n���� ��� ������� ��������!\n\n";
	system("pause");
	file.close();
}

void Database::removeFile() {
	char fileName[25];
	string command;
	system("cls");
	cout << "\n\n-----�������� ����� ���� ������-----\n\n";
	cout << "������� �������� ���������� ����� - "; cin >> fileName;
	cout << "\n������� ���� " << fileName << "  (��/���) - "; cin >> command;
	command = from_DOS(command);
	if (command == "��" || command == "y") {
		remove(fileName) == 0 ? cout << "\n���� ������� ������.\n\n" :
			cout << "\n������ ��������, ��������� �������� �����.\n\n";
		system("pause");
		return;
	}
	cout << "\n������ ��������!\n\n";
	system("pause");
	return;
}