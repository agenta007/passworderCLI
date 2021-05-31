#include <iostream>
#include "User.h"
#include <fstream>
#include "vector"
#define printNewLine() outUsers.write("\n",1)
int usersCount = 1;
User *users = new User[1];
using std::vector;
vector<Website> websites;
using namespace std;

void printHelp()
{
	cout << "Password Manager CLI.\n This is a simple app to manage your passwords for any offline and/or online accounts.\n"
		"pass -h / --help - prints this message"
		"";
}

void printAsciiTable()
{
	//33-126 are valid
	char ch = 0;
	for (size_t i = 0; i < 500; i++)
	{
		cout << i << " = "<< ch++ << endl;
	}
}

int save()
{
	fstream outUsers("users.txt", ios::binary | ios::out | ios::out);
	if (!outUsers)
	{
		cerr << "Could not open file\n";
	}
	if (usersCount > 999)
	{
		cerr << "Error userCount value is more than 999\n";
		return 1;
	}
	char* usrCntStr = new char[4];
	_itoa(usersCount, usrCntStr, 100);
	outUsers.write(usrCntStr, 3);
	printNewLine();
	for (size_t i = 0; i < usersCount; i++)
	{
		outUsers.write(users[i].getUsername().c_str(), users[i].getUsername().size());
		printNewLine();
		outUsers.write(users[i].getPass().c_str(), users[i].getPass().size());
		printNewLine();
	}
	return 0;
}

void listAllUsers()
{
	for (size_t i = 0; i < usersCount; i++)
	{
		cout << users[i].getUsername() << "\n";
	}
}

void timeDemo()
{
	time_t now = time(0);
	char tm[26];
	ctime_s(tm, sizeof tm, &now);
	cout << tm << "\n";
}

int main(int argc, char** argv)
{
	User masterUser("st", "ks", 0);
	users[0] = masterUser;
	users[0].printCredentials();
	for (size_t i = 0; i < 5; i++)
	{
		cout << "\nAddress in main:" << users + i;
		User::register_user(users);
		cout << "\nAddress in main:" << users + i;
		users[i].printCredentials();
	}
	save();
	return 0;
	/*master user bullshit i wrote, later i changed the  workaround
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
	*/
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
		"6 - list websites"
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
		//case 3: users = User::register_user(users);
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