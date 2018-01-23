#include "stdafx.h"
#include "Patient.h"
#include <string>


Patient::Patient() {}

Patient::Patient(string lastName, string firstName, string patronymic, string service, float cost) {
	this->lastName = lastName;
	this->firstName = firstName;
	this->patronymic = patronymic;
	this->service = service;
	this->cost = cost;
}

Patient::~Patient() {}

string Patient::from_DOS(string DOS_string) {
	char buf[50];
	OemToCharA(DOS_string.c_str(), buf);
	return buf;
}

string Patient::getLastName() { return lastName; }

string Patient::getFirstName() { return firstName; }

string Patient::getPatronymic() { return patronymic; }

string Patient::getService() { return service; }

float Patient::getCost() { return cost; }

string Patient::getFullName() {
	return lastName + " " + firstName + " " + patronymic;
}

string Patient::getShortFullName() {
	return lastName + " " + firstName[0] + "." + patronymic[0] + ".";
}

void Patient::setFullName(string lastName, string firstName, string patronymic) {
	this->lastName = lastName;
	this->firstName = firstName;
	this->patronymic = patronymic;
}

void Patient::setService(string service) { this->service = service; }

void Patient::setCost(float cost) { this->cost = cost; }

void Patient::enterNewData() {
	string tmpCost;
	while (true) {
		try {
			cout << "\nВведите фамилию - "; cin >> lastName;
			lastName = from_DOS(lastName);
			cout << "Введите имя - "; cin >> firstName;
			firstName = from_DOS(firstName);
			cout << "Введите отчество- "; cin >> patronymic;
			patronymic = from_DOS(patronymic);
			cout << "\nВведите название услуги - "; cin >> service;
			service = from_DOS(service);
			cout << "\nВведите стоимость услуги- "; cin >> tmpCost;
			cost = stof(tmpCost);
			break;
		}
		catch (...) {
			system("cls");
			cout << "\n\n-----ОШИБКА!-----\n";
			cout << "\nСтоимость услуги не могжет содержать строковые символы!\n";
			cout << "Проверьте корректность введённых данных и попробуйте ещё раз!\n\n";
			system("pause");
			system("cls");
		}
	}
}