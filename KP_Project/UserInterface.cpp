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
		cout << "\n\n����� ������� ��� � ����!";
		cout << "\n\n����������� ��� ���.\n\n";
		system("pause");
		break;
	}
}

void UserInterface::startUserInterface() {
	int menuNumber; string enterNumber;

	database.loadDataAboutPatients();

	while (true) {
		system("cls");
		cout << "\n-----���� ������������-----\n\n";
		cout << "1.������ � �� ���������\n";
		cout << "2.������ � ������ ��\n";
		cout << "3.����� ��������\n";
		cout << "4.���������� ���������\n";
		cout << "0.�����\n";
		try {
			cout << "\n\n\n������� ����� ����: "; cin >> enterNumber;
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
		cout << "\n-----���� ������ �� ������� ���������-----\n\n";
		cout << "1.�������� ���� ���������\n";
		cout << "2.�������� ������ ��������\n";
		cout << "3.������������� ���������� � ��������\n";
		cout << "4.������� ��������\n";
		cout << "0.��������� � ������� ����\n";
		try {
			cout << "\n\n\n������� ����� ����: "; cin >> enterNumber;
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
		cout << "\n-----���� ������ � ������ ��-----\n\n";
		cout << "1.������� ����\n";
		cout << "2.������� ����\n";
		cout << "3.������� ����\n";
		cout << "0.��������� � ������� ����\n";
		try {
			cout << "\n\n\n������� ����� ����: "; cin >> enterNumber;
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