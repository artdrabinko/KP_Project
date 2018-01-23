#ifndef DATABASE_H
#define DATABASE_H

#include "Patient.h"
#include <list>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>
#include "windows.h"

using namespace std;

class Database
{
private:
	string command;

	//string sellectedFileDB;

	list<Patient> listPatients;

	string from_DOS(string DOS_string);

	void printError(int error);

	void multiPrint(char simbol, int count);

	void printHeaderPatients();

	void printRowPatient(Patient *PtrPatient, int countPatients);

	void printAllPatients();

	void addNewPatientInFileDB(Patient *PtrPatient);

public:
	Database();

	~Database();
	
	void loadDataAboutPatients();

	void saveData();

	void viewAllPatients();

	void addNewPatient();

	//void searchFlightsByKey(string keyForSearch);

	//void sortAndViewFlightsByKey(string keyForSort);

	//void editFlightByNumber(int number);

	void deletePatient();

	void createDatabaseFile();

	void openFile();

	void removeFile();

};


#endif DATABASE_H
