#include <iostream>
#include <vector>
#include "User.h"
#include "funcs.h"
#include "globals.h"
#include "Website.h"
#include <sstream>
using std::vector;
using namespace std;

int main(int argc, char** argv)
{
	/*
	cout << "Password Manager CLI.\n This is a simple commandline tool to manage your passwords for any offline and/or online accounts.\n"
		"passworder -h, --help - prints this message\n"
		"CL options:\n"
		"passworder --login/-l USERNAME MASTERPASS\n"
		"passworder --register/-r USERNAME MASTERPASS\n"
		"passworder --pass/-p LOGIN_ON_WEBSITE MASTERPASS\n"
		"passworder --add/-a MASTERLOGIN MASTERPASS LOGIN PASSWORD"
		"passworder --import/-i /path/to/username_password_website.txt(firefox_decrypt format)"
		"";
	*/
	bool loggedInThroghTerminal = false;
	read();
	string* args = new string[argc];
	for (size_t i = 0; i < argc; i++)
	{
		string argument = "";
		for (size_t j = 0; j < strlen(argv[i]); j++)
		{
			argument += argv[i][j];
		}
		args[i] = argument;
		argument = "";
	}
	User emptyUsr = User();
	User* logged_in_usr = nullptr;
	string username, password;
	if (args[1] == "-h" || args[1] == "--help")
	{
		if (args->size() != 2)
			cout << "\n-h/--help is incompatible with  any other parameters\n";
		printHelp();
	}
	if (args[1] == "--login" || args[1] == "-l")
	{
		if (argc != 4)
		{
			cout << "Invalid  login  trial. passworder --login/-l master_username masterpass";
			return 1;
		}
		username = argv[2];
		password = argv[3];

		logged_in_usr = &getUserRefByCredentials(username, password);

		loggedInThroghTerminal = true;
	}
	if (args[1] == "--register" || args[1] == "-r")
	{
		if (argc != 4)
		{
			cout << "Invalid register trial. passworder  --register/-r master_username masterpass";
			return 1;
		}
		username = argv[2];
		password = argv[3];
		User::register_user_with_params(username, password);

	}


	if (args[1] == "--pass" || args[1] == "-p")
	{
		if (argc!=3)
		{
			cout << "Invalid usage of  --pass/-p => -p login_credential";
			return 0;
		}
		for (size_t i = 0; i < websitesCount; i++)
		{
			for (size_t j = 0; j < websites[i].getEntriesCount(); j++)
			{
				vector<UsernamePassPair>& reg_users = websites[i].getReggedUsers();
				for (size_t k = 0; k < reg_users.size(); k++)
				{
					if (reg_users[k].getUsername() != args[2])
					{
						continue;
					}
					cout << reg_users[k].getPlainPassword() << "\n";
					return 0;
				}
			}
		}
	}
	
	while (1)
	{
		/*
	cout << "\npassworderCLI\n"
		"Log in to use Password Manager\n"
		"-1 - print commands again\n"
		"0 - exit\n"
		"1 - login\n"
		"2 - logout\n"
		"3 - register\n"
		"5 - list usernames of registered users\n"
		"6 - list websites\n"
		//"7 - remove an empty website\n"
		"7 - clear empty websites\n"
		"8 - import credentials in format Website/Login/Username on separate lines\n"
		""
		;
		*/
		
		int intinput = -2;
		if (!loggedInThroghTerminal)
		{
			printIntCommands();
			cin >> intinput;
		}
		else if(!User::check_logon())
		{
			printIntCommands();
			cin >> intinput;
		}

		switch (intinput)
		{
		case -1:printIntCommands(); break;
		case 0:save(); return 0;
		case 1:getLogin(); logged_in_usr = &findLoggedInUser(); break;
		case 2: logout(); break;
		case 3: User::register_user(users); break;
		case 5: listAllUsers(); break;
		case 6: Website::listWebsites(); break;
		case 7: Website::clearEmptyWebsites(); break;
		
		default:
			break;
		}
		while (User::check_logon())
		{
			if (logged_in_usr == nullptr)
			{
				cout << "\nError : Trying to do user operations, but  logged_in_usr is nullptr.\n";
				break;
			}
			/*cout << "\nLogged in. Welcome, " << findLoggedInUser().getUsername() <<
				"\nUser menu:"
				"\n0 - logout"
				"\n1 - list websites you are registered on"
				"\n2 - add password entry"
				"\n3 - delete password entry"
				"\n4 - delete my profile and erase my data"
				"\n5 - print password history on a website"
				"\n6 - list all actual password entries"
				"\n"
				;
			*/
			printUserMenu();
			
			int input;
			string websiteName;
			cin >> input;
			switch (input)
			{
			case 0: logout(); emptyUsr.clearUser(); loggedInThroghTerminal = false; break;
			case 1: (*logged_in_usr).printWebsites(); break;
			case 2: addPasswordEntry(); break;
			case 3: deletePasswordEntry(); break;
			case 4: (*logged_in_usr).delete_my_account(); break;
			case 5: 
					(*logged_in_usr).printWebsites();
					cout << "\nEnter website name to see history for: ";
					cin >> websiteName;
					(*logged_in_usr).printPasswordHistoryForWebsite(logged_in_usr, websiteName);
					break;
			case 6: (*logged_in_usr).printActualPasswords(); break;
			default:
				break;
			}
			//if (input == 0)
			//{
			//	printIntCommands();
			//	break;
			//}
		}
	}
	delete[] args;
	args = nullptr;
	return 0;
}