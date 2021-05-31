#include "User.h"
#include <iostream>
#include "is_user_registered_func.h"
using namespace std;
extern int usersCount;
extern User* users;
int User::changePassWithParam(string pass)
{
	cout << "Enter password for " << username << "\n";
	string enteredPass;
	cin >> enteredPass;
	while (1)
	{
		if (!checkPass(username, enteredPass))
		{
			cout << "Invalid password!\nType abort or re-enter correctly!\n";
		}
		else
		{
			cout << "Password has been changed successfully.\n";
			break;
		}
	}
	masterpass = pass;
	return 0;
}
bool User::login() 
{
	string input;
	cout << "Enter username to login in: ";
	try
	{
		cin >> input;
		if (!is_user_registered(input))
		{
			cerr << "Error 404: User not found.\n";
			throw 1;
		}
		cout << "Enter password for " << input << ": ";
		string password;
		cin >> password;
		if (!checkPass(input, password))
		{
			cout << "Logging in has failed.\n";
			return 0;
		}
		findUser(input).logon();
		return 1;
	}
	catch (int)
	{
		string input;
		cout << "Enter retry and enter correct username or enter cancel: ";
		if (input=="cancel")
		{
			return 0;
		}
		else if(input=="retry")
		{
			login();
			return 1;
		}
		else
		{
			cerr << "Invalid command.\n";
			throw 1;
		}
	}
}
bool User::logon()
{
	logged_on = true;
	return 1;
}
bool User::logout()
{
	logged_on = false;
	return 1;
}
string User::getUsername()const
{
	return username;
}
string User::getPass()const
{
	return masterpass;
}
bool User::changePass()
{
	cout << "Enter password for " << username << "\n";
	string enteredPass;
	cin >> enteredPass;
	while (1)
	{
		if (!checkPass(username, enteredPass))
		{
			cout << "Invalid password!\nType abort or re-enter correctly!\n";
		}
		else
		{
			cout << "Please enter new password.\n";
			break;
		}
	}
	try
	{
		string nextPass;
		cin >> nextPass;
		cout << "Please, confirm your new password\n";
		string confirmPass;
		cin >> confirmPass;
		if (confirmPass!=nextPass)
		{
			throw "Passwords do not match!";
		}
	}
	catch (const char[])
	{
		cerr << "Passwords do not match!\nRetry or type abort: ";
		string nextPass, confirmPass;
		cin >> nextPass;
		if (nextPass == "abort")
		{
			cout << "Aborting...\n";
			return 0;
		}
		cout << "Please, confirm your password.\n";
		cin >> confirmPass;
		if (confirmPass != nextPass)
		{
			throw "Passwords do not match!";
		}
		return 1;
	}

	return 1;

}

void User::operator=(const User& rhs)
{
	this->username = rhs.username;
	this->masterpass = rhs.masterpass;
	this->logged_on = rhs.logged_on;
}

User::User(string username, string password, bool loggen_on)
{
	this->logged_on = logged_on;
	this->username = username;
	this->masterpass = password;
}
User::User()
{
	username = " ";
	masterpass = " ";
	logged_on = 0;
}
//TO BE FIXED
void User::register_user(User* users)
{
	++usersCount;
	User* tmp = new User[usersCount];
	for (size_t i = 0; i < usersCount-1; i++)
	{
		tmp[i] = users[i];
	}
	string username, password;
	cout << "Enter your username: ";
	cin >> username;
	cout << "\nEnter your password: ";
	cin >> password;
	User newUser(username, password, 0);
	tmp[usersCount-1] = newUser;
	delete[] users;
	users = new User[usersCount];
	for (size_t i = 0; i < usersCount; i++)
	{
		cout << "\nUser value: ";
		users[i].printCredentials();
		cout << "\ntmp value: ";
		tmp[i].printCredentials();
		*(users + i) = *(tmp + i);
		cout << "\nAddress:" << users+i;
		users[i].printCredentials();
	}
}
//TO BE FIXED
User* User::delete_user(User* users)
{
	string usrnm;
	cout << "Enter username of account you want to delete: ";
	cin >> usrnm;

	User* tmp = new User[usersCount - 1];
	for (size_t i = 0; i < usersCount-1; i++)
	{
		if (users[i].getUsername() == usrnm)
			continue;
		tmp[i] = users[i];
	}
	return tmp;
}
