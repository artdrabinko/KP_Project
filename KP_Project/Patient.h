#ifndef PATIENT_H
#define PATIENT_H

#include "iostream"
#include "windows.h"
using namespace std;

class Patient {
private:
	string lastName, firstName, patronymic;
	string service;
	float cost;

public:
	Patient();

	Patient(string lastName, string firstName, string patronymic, string service, float cost);

	~Patient();

	string getLastName();

	string getFirstName();

	string getPatronymic();

	string getService();

	float getCost();

	string getFullName();

	string getShortFullName();

	string from_DOS(std::string DOS_string);

	void setFullName(string lastName, string firstName, string patronymic);

	void setService(string group);

	void setCost(float cost);

	void enterNewData();

};

#endif PATIENT_H