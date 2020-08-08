#ifndef ACCOUNT_H_
#define ACCOUNT_H_

#include <iostream>
#include <string>
using namespace std;

void menu();

class Account
{
private:
	string username;
	string password;
	string ID;
	int type;	//	1. Manager | 2. Staff | 3. Member | 4. Guest
public:
	Account() { username = ""; password = ""; ID = ""; type = 0; }
	//bool create(Manager);
	//bool create(Staff);
	//bool create(Member);
	bool remove();
	Account login();
	bool loadFile();
	bool changePass();
};

#endif