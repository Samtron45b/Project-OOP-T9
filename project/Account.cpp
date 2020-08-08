#include <iostream>
#include <string>
#include <fstream>
#include "Account.h"
using namespace std;

/*bool create(Manager)
{}

bool create(Staff)
{}

bbool create(Member)
{}*/

bool Account::remove()
{
	//	Missing classes needed for proper removal
	int fetch;
	cout << "Would you like to remove this account?";
	cout << "1. Confirm." << endl;
	cout << "Any number. Cancel." << endl;
	cout << "Your choice: ";
	cin >> fetch;
	if (fetch == 1)
		return 1;
	else
		return 0;
}

Account Account::login()
{
	//	This is for individual account login, cannot use a full scale searching without the missing classes
	string _username;
	string _password;
	int _type;
	cout << "Enter your account type (1 for Manager, 2 for Staff, 3 for Member, 4 for Guest): ";
	cin >> _type;
	if (type == _type)
	{
		cout << "Please enter your username: ";
		getline(cin, _username);
		if (username == _username)
		{
			cout << "Please enter your password: ";
			getline(cin, _password);
			if (password == _password)
				return *this;
			else cout << "Password incorrect!" << endl;
		}
		else cout << "No username found!" << endl;
	}
}

bool Account::loadFile()
{
	/*
		Due to missing classes the current syntax needed to be written within the file:

		<your username>
		<your password>
		<your ID>
		<your type>

	*/
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
				getline(fetch, password);
				getline(fetch, ID);
				fetch >> type;
			}
		}
		fetch.close();
		return 1;
	}
	else
	{
		cout << "Error finding account file. Please try again." << endl;
		return 0;
	}
	return 0;
}

bool Account::changePass()
{
	//	Missing classes needed for proper change
	int fetch;
	cout << "Would you like to change your password?";
	cout << "1. Confirm." << endl;
	cout << "Any number. Cancel." << endl;
	cout << "Your choice: ";
	cin >> fetch;
	if (fetch == 1)
		return 1;
	else
		return 0;
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
		cout << "1. Create. (Currently under maintenance)." << endl;
		cout << "2. Remove account." << endl;
		cout << "3. Load account." << endl;
		cout << "4. Password change." << endl;
		cout << "5. Login." << endl;
		cout << "Your choice: ";
		cin >> option;
		switch (option)
		{
		case 0:
			cout << "Exit confirmation. Saving your data....\n You may now exit. Thank you for using our program.";
			break;
		case 1:
			//you.create();
			break;
		case 2:
			flag = you.remove();
			if (flag)
				cout << "Removed account successfully.";
			else cout << "Account removal failed.";
			break;
		case 3:
			flag = you.loadFile();
			if (flag)
				cout << "Loading account file successfully.";
			else cout << "Account file loading failed.";
			break;
		case 4:
			flag = you.changePass();
			if (flag)
				cout << "Changed password successfully.";
			else cout << "Password changing failed.";
		case 5:
			you.login();
			break;
		default:
			cout << "The program may have experienced a problem or your option choice isn't available within the menu. Please try again." << endl;
			break;
		}
	} while (option != 0);
}