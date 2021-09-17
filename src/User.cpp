#include "User.h"
#include <iostream>
#include "funcs.h"
#include "globals.h"
#include "Website.h"
using namespace std;

bool User::is_anyone_logged_in = false;

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
bool User::login(bool are_credentials_typed)
{
	if (!are_credentials_typed)
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
			if (input == "cancel")
			{
				return 0;
			}
			else if (input == "retry")
			{
				login(false);
				return 1;
			}
			else
			{
				cerr << "Invalid command.\n";
				throw 1;
			}
		}
	}
	else
	{
		this->logon();
		is_anyone_logged_in = true;
		return true;
	}
	return false;
}

bool User::tryLogin(string username, string pass)
{
	for (size_t i = 0; i < usersCount; i++)
	{
		if (users[i].getUsername() == username && users[i].getPass() == pass)
		{
			return true;
		}
	}
	return false;
}

void User::logon()
{
	logged_on = true;
}
void User::logout()
{
	logged_on = false;
	is_anyone_logged_in = false;
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
		if (confirmPass != nextPass)
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
	for (size_t i = 0; i < rhs.registererd_to_websiteNames.size(); i++)
	{
		this->registererd_to_websiteNames.push_back(rhs.registererd_to_websiteNames[i]);
	}
}

User::User(string username, string password, bool loggen_on)
{
	this->logged_on = logged_on;
	this->username = username;
	this->masterpass = password;
}
User::User()
{
	username = masterpass = "";
	logged_on = false;
}

void printUsers()
{
	for (size_t i = 0; i < usersCount; i++)
	{
		cout << "\nUser value: ";
		users[i].printCredentials();
		//cout << "\nAddress:" << users + i;
		//users[i].printCredentials();
	}
}

//TO BE FIXED
void User::register_user(User* users)
{
	++usersCount;
	if (usersCount > usersCap)
	{
		usersCap *= 2;
		User* tmp = new User[usersCap];
		for (size_t i = 0; i < usersCount - 2; i++)
		{
			tmp[i] = users[i];
		}
		tmp[usersCount - 1] = createNewUser();
		delete[] users;
		users = new User[usersCap];
		for (size_t i = 0; i < usersCount; i++)
		{
			users[i] = tmp[i];
		}
		delete[] tmp;
	}
	else
	{
		users[usersCount - 1] = createNewUser();
	}
	cout << "Successfuly registered!\n";
}

void User::register_user_with_params(string& username, string& password)
{
	++usersCount;
	if (usersCount > usersCap)
	{
		usersCap *= 2;
		User* tmp = new User[usersCap];
		for (size_t i = 0; i < usersCount - 2; i++)
		{
			tmp[i] = users[i];
		}
		tmp[usersCount - 1] = User(username, password);
		delete[] users;
		users = new User[usersCap];
		for (size_t i = 0; i < usersCount; i++)
		{
			users[i] = tmp[i];
		}
		delete[] tmp;
	}
	else
	{
		users[usersCount - 1] = User(username, password);
	}

}

void User::read_user(string username, string password, vector<string>& websiteNames)
{
	password = decryptMasterPass(password);
	++usersCount;
	if (usersCount > usersCap)
	{
		usersCap *= 2;
		User* tmp = new User[usersCap];
		for (size_t i = 0; i < usersCount - 2; i++)
		{
			tmp[i] = users[i];
		}
		tmp[usersCount - 1] = User(username, password);
		tmp[usersCount - 1].readRegisteredToWebsiteNames(websiteNames);
		delete[] users;
		users = new User[usersCap];
		for (size_t i = 0; i < usersCount; i++)
		{
			users[i] = tmp[i];
		}
		delete[] tmp;
	}
	else
	{
		users[usersCount - 1] = User(username, password);
		users[usersCount - 1].readRegisteredToWebsiteNames(websiteNames);
	}

}
void User::delete_my_account()
{
	User* tmp = new User[usersCount-1];
	User& usr = findLoggedInUser();
	int tmpIter = 0;
	for(int i = 0; i < websitesCount;++i)
	{
		websites[i].remove_user(usr.getUsername());
	}
	for (size_t i = 0; i < usersCount; i++)
	{
		if (!(users[i].getUsername() == usr.getUsername()))
		{
			tmp[tmpIter++] = users[i];
		}
	}

	delete[] users;
	--usersCount;
	users = new User[usersCount];
	for (size_t i = 0; i < usersCount; i++)
	{
		users[i] = tmp[i];
	}
	delete[] tmp;
	usr.logout();
	is_anyone_logged_in = false;
	return;
}
void User::printWebsites()const
{
	if (registererd_to_websiteNames.size()==0)
	{
		cout << "\nYou haven't imported credentials for any website yet!\n";
		return;
	}
	for (size_t i = 0; i < registererd_to_websiteNames.size(); i++)
	{
		cout << "\n" << registererd_to_websiteNames[i];
	}
}
void User::registerWebsiteName(string name)
{
	for (size_t i = 0; i < registererd_to_websiteNames.size(); i++)
	{
		if (name == registererd_to_websiteNames[i])
		{
			return;
		}
	}
	registererd_to_websiteNames.push_back(name);
}
void User::registered_to_websiteName_rm(string name)
{
	int idx;
	for (size_t i = 0; i < registererd_to_websiteNames.size(); i++)
	{
		if (registererd_to_websiteNames[i] == name)
		{
			idx = i;
			break;
		}
	}
	registererd_to_websiteNames.erase(registererd_to_websiteNames.begin()+idx);
}
void User::printActualPasswords()
{
	for (string web_reg : registererd_to_websiteNames)
	{
		Website* current_website = Website::findWebsiteByName(web_reg);
		UsernamePassPair* usr_on_website = current_website->findUsernamePassPairByName(findLoggedInUser().getUsername());
		usr_on_website->printActualPassword();
	}
}
void User::printPasswordHistoryForWebsite(User* usr, string name)
{
	Website* websiteToPrintHistory = Website::findWebsiteByName(name);
	if (websiteToPrintHistory==nullptr)
	{
		cout << "\nWebsite is not found.\n";
		return;
	}
	websiteToPrintHistory->printHistoryOnWebsiteForUser();
}
void User::readRegisteredToWebsiteNames(vector<string>& registeredToWebsiteNames)
{
	for (vector<string>::iterator it = registeredToWebsiteNames.begin(); it != registeredToWebsiteNames.end(); ++it)
	{
		this->registererd_to_websiteNames.push_back(*it);
	}
}

bool User::checkUserRegistered(string name)
{
	for (size_t i = 0; i < registererd_to_websiteNames.size(); i++)
	{
		if (registererd_to_websiteNames[i] == name)
		{
			return true;
		}
	}
	return false;
}

void User::removeWebsiteFromRegistered(string name)
{
	for (size_t i = 0; i < registererd_to_websiteNames.size(); i++)
	{
		if (registererd_to_websiteNames[i]==name)
		{
			registererd_to_websiteNames.erase(registererd_to_websiteNames.begin() + i);
			return;
		}
	}
}

void User::clearUser()
{
	username = masterpass = "";
	logged_on = false;
}

bool User::is_default()
{
	if (username ==  " "  && masterpass == " " && logged_on	== 0)
	{
		return true;
	}
	return false;
}