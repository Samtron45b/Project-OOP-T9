#include <iostream>
#include <string>
#include <fstream>
#include <conio.h>
#include "Account.h"
#include "date.hpp"
#include "guest.hpp"
#include "item.hpp"
#include "person.hpp"
using namespace std;

/*bool create(Manager)
{}

bool create(Staff)
{}
*/
bool Account::create()
{
	string _username;
	string _password;
	int _ID;
	int _type;
	person* tmp;

	string read;
	ofstream print;
	print.open("account.txt");
	if (print.is_open())
	{
		while (!print.eof())
		{
				cout << "Your account type: ";
				cin >> _type;
				//if (type == 1)
				//	tmp = new manager;
				//if (type == 2)
				//	tmp = new staff;
				if (type == 3)
					tmp = new member;
				if (type == 4)
					tmp = new guest;
				cout << "Your new username: ";
				cin >> _username;
				print << _username;
				cout << "Your password: ";
				cin >> _password;
				print << _password;
				cout << "Your ID: ";
				cin >> _ID;
				print << _ID;
				print << _type;
		}
		print.close();
		return 1;
	}
	else
	{
		cout << "Error finding account file. Please try again." << endl;
		return 0;
	}
	return 0;
}

bool Account::removeAcc()
{
	int choice;
	string _username;
	string _password;
	int _ID;
	int _type;

	cout << "Would you like to remove this account?";
	cout << "1. Confirm." << endl;
	cout << "Any number: Cancel." << endl;
	cout << "Your choice: ";
	cin >> choice;
	if (choice == 1)
	{
		cout << "Please wait as the system delete your data..." << endl;

		string read;
		ifstream fetch;
		ofstream print;
		char file[] = "account.txt";
	    fetch.open(file);
		print.open("accountTmp.txt");

		if (fetch.is_open())
		{
			while (!fetch.eof())
			{
				getline(fetch, read);
				if (read == " " || read == "") continue;
				else
				{
					cin >> _username;
					if (_username != username) print << _username;
					cin >> _password;
					if (_password != password) print << _password;
					cin >> _ID;
					if (_ID != ID) print << _ID;
					cin >> _type;
					if (_type != type) print << _type;
				}
			}
			fetch.close();
			print.close();
			if (remove(file) != 0) 
				rename("accountTmp.txt", file);
			return 1;
		}
		else
		{
			cout << "Error finding account file. Please try again." << endl;
			return 0;
		}
	}
	else
		return 0;
}

bool Account::changePass()
{
	int choice;
	string _username;
	string _password;
	int _ID;
	int _type;
	string _newpassword;

	cout << "Would you like to change your password?";
	cout << "1. Confirm." << endl;
	cout << "Any number: Cancel." << endl;
	cout << "Your choice: ";
	cin >> choice;
	if (choice == 1)
	{
		cout << "Please type your new password: ";
		cin >> _newpassword;

		string read;
		ifstream fetch;
		ofstream print;
		char file[] = "account.txt";
		fetch.open(file);
		print.open("accountTmp.txt");

		if (fetch.is_open())
		{
			while (!fetch.eof())
			{
				getline(fetch, read);
				if (read == " " || read == "") continue;
				else
				{
					cin >> _username;
					if (_username != username) print << _username;
					cin >> _password;
					if (_password != password) print << _newpassword;
					cin >> _ID;
					if (_ID != ID) print << _ID;
					cin >> _type;
					if (_type != type) print << _type;
				}
			}
			fetch.close();
			print.close();
			if (remove(file) != 0)
				rename("accountTmp.txt", file);
			return 1;
		}
		else
		{
			cout << "Error finding account file. Please try again." << endl;
			return 0;
		}
	}
	else
		return 0;
}

bool Account::checkLogin(string _username, int _type)
{
	bool flag = 0;
	string read;
	ifstream fetch;
	fetch.open("account.txt");
	if (fetch.is_open())
	{
		while (!fetch.eof())
		{
			getline(fetch, read);
			if (read == " " || read == "") continue;
			else
			{
				username = read;
				if (username == _username)
				{
					getline(fetch, password);
					fetch >> ID;
					if (type == _type)
					{
						fetch >> type;
						flag = 1;
					}
				}
			}
		}
		fetch.close();
	}
	else
	{
		cout << "Error finding account file. Please try again." << endl;
	}
	if (flag) return 1; else return 0;
}

Account Account::login()
{
	//	This is for individual account login, cannot use a full scale searching without the missing classes
	string _username;
	string _password;
	int _ID;
	int type;
	cout << "Enter your account type (1 for Manager, 2 for Staff, 3 for Member, 4 for Guest): ";
	cin >> type;
	if (type == 1)
	{
		//myMan = new manager;
		//cout << "Please enter your username: ";
		//getline(cin, _username);
		//if (checkLogin(_username, type))
		//{
		//	cout << "Please enter your password: ";
		//	getline(cin, _password);
		//if (password == _password)
		//{
		//	cout << ID << " has logged in with username " << username << endl;
		//	return *this;
		//}
		//	else cout << "Password incorrect!" << endl;
		//}
		//else cout << "Username is not found or the account type is incorrect!" << endl;
	}

	if (type == 2)
	{
		//myMan = new staff;
		//cout << "Please enter your username: ";
		//getline(cin, _username);
		//if (checkLogin(_username, type))
		//{
		//	cout << "Please enter your password: ";
		//	getline(cin, _password);
		//if (password == _password)
		//{
		//	cout << ID << " has logged in with username " << username << endl;
		//	return *this;
		//}
		//	else cout << "Password incorrect!" << endl;
		//}
		//else cout << "Username is not found or the account type is incorrect!" << endl;
	}

	if (type == 3)
	{
		myMan = new member;
		cout << "Please enter your username: ";
		getline(cin, _username);
		if (checkLogin(_username, type))
		{
			cout << "Please enter your password: ";
			getline(cin, _password);
			if (password == _password)
			{
				cout << ID << " has logged in with username " << username << endl;
				return *this;
			}
			else cout << "Password incorrect!" << endl;
		}
		else cout << "Username is not found or the account type is incorrect!" << endl;
	}

	if (type == 4)
	{
		{
			myMan = new guest;
			cout << "Logged in as Guest!";
			return *this;
		}
	}
}

void menu()
{
	Account you;
	int option;
	bool flag;

	do
	{
		cout << "=======MENU=======" << endl;
		cout << "0. Exit." << endl;
		cout << "1. Create." << endl;
		cout << "2. Remove account." << endl;
		cout << "3. Password change." << endl;
		cout << "4. Login." << endl;
		cout << "Your choice: ";
		cin >> option;
		switch (option)
		{
		case 0:
			cout << "Exit confirmation. Saving your data....\n You may now exit. Thank you for using our program.";
			break;
		case 1:
			flag = you.create();
			if (flag)
				cout << "Account created successfully.";
			else cout << "Account created failed. File could not be found.";
			break;
		case 2:
			flag = you.removeAcc();
			if (flag)
				cout << "Removed account successfully.";
			else cout << "Account removal cancel or file could not be found.";
			break;
		case 3:
			flag = you.changePass();
			if (flag)
				cout << "Changed password successfully.";
			else cout << "Password changing cancel or file could not be found.";
			break;
		case 4:
			you.login();
			cout << endl << "Welcome!" << endl;
			break;
		default:
			cout << "The program may have experienced a problem or your option choice isn't available within the menu. Please try again." << endl;
			break;
		}
	} while (option != 0);
}

int main()
{
	menu();
	_getch();
	return 0;
}