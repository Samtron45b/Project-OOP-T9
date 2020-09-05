#ifndef ACCOUNT_H_
#define ACCOUNT_H_

#include <iostream>
#include <string>
#include "guest.hpp"
#include "person.hpp"
#include "myLib.hpp"
#include "item.hpp"
#include "account.hpp"
using namespace std;

//void menu();

class Account
{
private:
	person* myMan;
	string username;
	string password;
	int ID;
	int type;	//	1. Manager | 2. Staff | 3. Member | 4. Guest
public:
	Account() { username = ""; password = ""; ID = 0; type = 0; }
	Account(string _username) : username(_username), password(""), ID(0), type(0) {}
	Account(string _username, string _password) : username(_username), password(_password), ID(0), type(0) {}
	Account(string _username, string _password, int _ID) : username(_username), password(_password), ID(_ID), type(0) {}
	Account(string _username, string _password, int _ID, int _type) : username(_username), password(_password), ID(_ID), type(_type) {}
	~Account() { delete myMan; }
	bool create();
	bool removeAcc();
	Account login();
	bool changePass();
	bool checkLogin(string _username, int _type);
};

#endif