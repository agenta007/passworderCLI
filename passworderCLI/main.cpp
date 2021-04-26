#include <iostream>
#include "User.h"
int usersCount = 1;
User *users = new User[1];
using namespace std;

void printHelp()
{
	cout << "Password Manager CLI.\n This is a simple app to manage your passwords for any offline and/or online accounts.\n"
		"pass -h / --help - prints this message"
		"";
}

int save()
{
	//ofstream.open("session");
	return 0;
}

void listAllUsers()
{
	for (size_t i = 0; i < usersCount; i++)
	{
		cout << users[i].getUsername() << "\n";
	}
}

int main(int argc, char** argv)
{
	if (users[0].getUsername() == " ")
	{
		cout << "Main user is uninitizized\nLet's sign you up!\nEnter your username: ";
		do
		{
			string firstUsername, firstPass, check;
			cin >> firstUsername;
			cout << "\nPassword: ";
			cin >> firstPass;
			cout << "\nConfirm password: ";
			cin >> check;
			if (check==firstPass)
			{
				User firstUser(firstUsername, firstPass);
				users[0] = firstUser;
				break;
			}
		} while (1);
		cout << "Master user initialized!\n";
	}
	string username;
	cout << argv[1] << endl;
	if (argv[1] == "-h" || argv[1] == "--help")
	{
		printHelp();
	}
	if (argv[1] == "--user" || argv[1] == "-u")
	{
		username = argv[2];
	}
	cout << "Password Manager is running enter integers to execute commands\n"
		"0 - exit\n"
		"1 - login\n"
		"2 - logout\n"
		"3 - register\n"
		"4 - delete my profile and erase my data\n"
		"5 - list registered usernames"
		"Log in to use Password Manager's commands\n";
	while (1)
	{
		int intinput;
		cin >> intinput;
		switch (intinput)
		{
		case 0: return 0;
		case 1: //User::login();
		case 2: //User::logout();
		case 3: users = User::register_user(users);
		case 5: listAllUsers();
		default:
			break;
		}

	}
	//if (argv[1] == )
	//{
	//
	//}
	//cout << "Welcome to Password Manager!\nType login to login.";
	return 0;
}