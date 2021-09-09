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
	auto var = 5;
	bool boolean = var ? true : false;
	read();
	string username, password;
	if (argv[1] == "-h" || argv[1] == "--help")
	{
		printHelp();
	}
	if (argv[1] == "--login" || argv[1] == "-l")
	{
		username = argv[2];
		password = argv[3];
	}
	if (argv[1] == "--pass" || argv[1] == "-p")
	{
		for (size_t i = 0; i < websitesCount; i++)
		{
			for (size_t j = 0; j < websites[i].getEntriesCount(); j++)
			{
				//if (websites[i].addWebsite )
				//{
				//
				//}
			}
		}
	}
	printIntCommands();
	while (1)
	{
		/*
		cout << "Password Manager is running enter integers to execute commands\n"
			"Log in to use Password Manager's commands\n"
			"-1 - print commands again\n"
			"0 - exit\n"
			"1 - login\n"
			"2 - logout\n"
			"3 - register\n"
			"4 - delete my profile and erase my data\n"
			"5 - list usernames of registered users\n"
			"6 - list websites\n"
			"7 - remove an empty website\n"
			"8 - clear empty websites\n"
			;
		*/
		int intinput;
		User emptyUsr = User();
		User& logged_in_usr = emptyUsr;
		cin >> intinput;
		switch (intinput)
		{
		case -1:printIntCommands(); break;
		case 0:save(); return 0;
		case 1:getLogin(); logged_in_usr = findLoggedInUser(); break;
		case 2: logout(); break;
		case 3: User::register_user(users); break;
		case 5: listAllUsers(); break;
		case 6: Website::listWebsites(); break;
		
		default:
			break;
		}
		while (User::check_logon())
		{
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
			case 0: logout(); break;
			case 1: logged_in_usr.printWebsites(); break;
			case 2: addPasswordEntry(); break;
			case 3: deletePasswordEntry(); break;
			case 4: logged_in_usr.delete_my_account(); printIntCommands(); break;
			case 5: 
					logged_in_usr.printWebsites();
					cout << "\nEnter website name to see history for: ";
					cin >> websiteName;
					logged_in_usr.printPasswordHistoryForWebsite(&logged_in_usr, websiteName);
					break;
			case 6: logged_in_usr.printActualPasswords(); break;
			default:
				break;
			}
			if (input == 0)
			{
				printIntCommands();
				break;
			}
		}
	}
	return 0;
}