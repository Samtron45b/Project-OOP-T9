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

bool anonymous=false;

bool Account::isExist(string _username)
{
	bool flag=false;
	string read;
	ifstream fetch;
	fetch.open("./data/account/account.txt");
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
					cout << "This username is taken! Please try another one." << endl;
					flag = 1;
				}
			}
		}
		fetch.close();
	}
	else
	{
		cout << "Error finding account file. Please try again." << endl;
	}
	return flag;
}

bool Account::create(int mode)
{
	string _username;
	string _password;
	int _ID;
	int _type;
	person* tmp=new guest;

	string read;
	ofstream print;
	print.open("./data/account/account.txt",ios::app);
	if (!mode)
	{
		cout << "Your account type: ";
		cin >> _type;
		delete tmp;
		if (_type == 1)
		{
			tmp = new manager;
		}
		if (_type == 2)
		{
			tmp = new staff;
		}
		if (_type == 3)
		{
			tmp = new member;
		}
	}
	else
	{
		delete tmp;
		if (mode==1)
		{
			tmp = new staff;
		}
		else
		{
			tmp = new member;
		}
		_type = mode + 1;
	}
	if (print.is_open())
	{
				
				do
				{
					cout << "Your new username: ";
					cin >> _username;
				} while (isExist(_username));
				print << _username << endl;
				cout << "Your password: ";
				_password=passwordBuffer();
				print << _password << endl;
				cin.ignore(1);
				tmp->input();
				print<<tmp->getID() << endl;
				print << _type << endl;
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
		char file[] = "./data/account/account.txt";
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
		_newpassword = passwordBuffer();

		string read;
		ifstream fetch;
		ofstream print;
		char file[] = "./data/account/account.txt";
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
	fetch.open("./data/account/account.txt");
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

void Account::login()
{
	string _username;
	string _password;
	int _ID;
	cout << "Enter your account type (1 for Manager, 2 for Staff, 3 for Member, 4 for Guest): ";
	cin >> type;
	cin.ignore(1);
	if (type == 4)
	{
		{
			myMan = new guest;
			anonymous = true;
			cout << "Logged in as Guest!\n";
			return;
		}
	}

	if (type == 1)
	{
		myMan = new manager;
	}	

	if (type == 2)
	{
	myMan = new staff;
	}

	if (type == 3)
	{
		myMan = new member;
	}
		cout << "Please enter your username: ";
		getline(cin, _username);
		if (checkLogin(_username, type))
		{
			cout << "Please enter your password: ";
			_password = passwordBuffer();
			if (password == _password)
			{
				cout <<"Login success"<< endl;
				myMan->get(ID);
			}
			else cout << "Password incorrect!" << endl;
		}
		else cout << "Username is not found or the account type is incorrect!" << endl;
}

void Account::menu()
{
	Account you;
	int option=0;
	bool flag;
	bool checkInput;
	bool first = true;
	do
	{
		if (you.myMan == nullptr)
		{
			cout << "=======MENU=======" << endl;
			cout << "0. Exit." << endl;
			cout << "1. Create." << endl;
			cout << "2. Login." << endl;
			cout << "==================" << endl;
			cout << "Your choice: ";
			checkInput = cinIg(cin, option);
			if (!checkInput || option < 0 || option>2)
			{
				option = 0;
			}
		}
		else if(!anonymous)
		{
			myMan->person::output(false);
			cout << "\n\n";
			cout << "=======MENU=======" << endl;
			cout << "0. Exit." << endl;
			cout << "1. Remove account." << endl;
			cout << "2. Password change." << endl;
			cout << "3. Go to the shop." << endl;
			cout << "==================" << endl;
			cout << "Your choice: ";
			checkInput = cinIg(cin, option);
			if (!checkInput || option < 0 || option>3)
			{
				option = 0;
			}
			else
			{
				if(option)
					option += 2;
			}
		}
		else if(first)
		{
			option = 5;
			first = false;
		}
		else
		{
			option = 0;
			cout << "=======MENU=======" << endl;
			cout << "Input anything to exit\n";
			cout << "==================" << endl;
			system("pause");
		}
		clearConsole();
		switch (option)
		{
		case 0:
			cout << "Exit confirmation. Saving your data...." << endl << "You may now exit. Thank you for using our program.";
			break;
		case 1:
			flag = you.create();
			if (flag)
				cout << "Account created successfully.\n";
			else cout << "Account created failed. File could not be found.\n";
			break;
		case 2:
			you.login();
			break;
		case 3:
			flag = you.removeAcc();
			if (flag)
				cout << "Removed account successfully.\n";
			else cout << "Account removal cancel or file could not be found.\n";
			break;
		case 4:
			flag = you.changePass();
			if (flag)
				cout << "Changed password successfully.\n";
			else cout << "Password changing cancel or file could not be found.\n";
			break;
		case 5:
		{
			myMan->menu();
		}
		default:
			cout << "The program may have experienced a problem or your option choice isn't available within the menu. Please try again." << endl;
			break;
		}
		clearConsole();
	} while (option != 0);
}