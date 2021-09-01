#include "UsernamePassPair.h"
#include "funcs.h"
#include <vector>
using std::cout;
using std::cin;
using std::string;
UsernamePassPair::UsernamePassPair() { username = owner = ""; }
UsernamePassPair::UsernamePassPair(string username, string password, string assigned_to) { this->username = username; this->passwords.push_back(Password(password, passwords.size())); this->owner = assigned_to; }
UsernamePassPair::UsernamePassPair(string login, string owner, vector<Password>& readPasses)
{
	username = login;
	this->owner = owner;
	passwords = readPasses;
}
UsernamePassPair::UsernamePassPair(const UsernamePassPair& obj)
{
	username = obj.username;
	owner = obj.owner;
	if (!(obj.passwords.empty()))
	{
		for (size_t i = 0; i < obj.passwords.size(); i++)
		{
			passwords.push_back(obj.passwords[i]);
		}
	}
}
UsernamePassPair UsernamePassPair::createNewUsernamePassPair()
{
	string username, password;
	cout << "\nEnter username to track passwords of:";
	cin >> username;
	cout << "\nEnter first password for " << username << " :";
	cin >> password;
	return UsernamePassPair(username, password, findLoggedInUser().getUsername());
}
UsernamePassPair UsernamePassPair::createNewUsernamePassPairWithParams(string usr, string pass)
{
	return UsernamePassPair();
}
void UsernamePassPair::updatePassword(string password) { passwords.push_back(Password(password, passwords.size())); }
void UsernamePassPair::deletePasswordAt(int index)
{
	for (size_t i = 0; i < passwords.size(); i++)
	{
		if (passwords[i].getIndex() == index)
		{
			passwords.erase(passwords.begin()+i);
		}
	}
	
}
void UsernamePassPair::printUserPassPair() { std::cout << "Username: " << username; passwords[passwords.size() - 1].printPass(); }
void UsernamePassPair::listPasswords() { for (Password pass : passwords) { pass.printPass(); } }
void UsernamePassPair::printActualPassword()
{
	passwords.back().printPass();
}
void UsernamePassPair::UPP_printHistory()
{
	for (size_t i = 0; i < passwords.size(); i++)
	{
		passwords[i].printPass();
	}
}
string UsernamePassPair::getUsername()const { return username; }
string UsernamePassPair::getOwner()const { return owner; }
void UsernamePassPair::operator=(const UsernamePassPair& rhs)
{
	this->username = rhs.username;
	this->owner = rhs.owner;
	if (!rhs.passwords.empty())
	{
		for (size_t i = 0; i < rhs.passwords.size(); i++)
		{
			this->passwords.push_back(rhs.passwords[i]);
		}
	}
}

void UsernamePassPair::mergeUPPs(const UsernamePassPair& obj)
{
	if (owner != obj.owner || username != obj.username)
	{
		cout << "Unsuccessful UPP merge.\n";
		return;
	}
	
	for (size_t i = 0; i < obj.passwords.size(); i++)
	{
		passwords.push_back(obj.passwords[i]);
	}

}

UsernamePassPair* Website::findUsernamePassPairByName(string name)
{
	for (size_t i = 0; i < registered_users.size(); i++)
	{
		if (registered_users[i].getOwner() == name)
		{
			return &registered_users[i];
		}
	}
	return nullptr;
}
string UsernamePassPair::convertToString()const
{
	string str;
	for (size_t i = 0; i < passwords.size(); i++)
	{
		str += passwords[i].convertToString();
	}
	return str;
}

bool UsernamePassPair::is_empty()const
{
	return passwords.empty();
}