#ifndef USERINTERFACE_H
#define USERINTERFACE_H

#include "Database.h"
#include "iostream"
#include "windows.h"
#include "ctime"
using namespace std;


class UserInterface
{
private:
	Database database;

	void printError(int error);

	string from_DOS(string DOS_string);

	void showMenuPatient();

	void showMenuFileBD();

	//void showMenuSearch();

	//void showMenuSort();


public:
	UserInterface();
	~UserInterface();

	void startUserInterface();
};

#endif // USERINTERFACE_H