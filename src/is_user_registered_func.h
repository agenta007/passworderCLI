#ifndef _IS_USER_REGISTERED_F_
#define _IS_USER_REGISTERED_F_
#include <string>
#include "User.h"
using namespace std;
extern int usersCount;
extern User *users;
bool is_user_registered(string username)
{
	for (size_t i = 0; i < ::usersCount; i++)
	{
		if (username == users[i].getUsername())
		{
			return true;
		}
	}
	return false;
}
bool checkPass(string username, string password)
{
	for (size_t i = 0; i < usersCount; i++)
	{
		if (users[i].getUsername() == username)
		{
			try
			{
				if (users[i].getPass() == password)
				{
					return 1;
				}
				else
				{
					throw 1;
				}
			}
			catch (int)
			{
				string answer;
				cerr << "Wrong password.\nEnter retry or cancel: ";
				cin >> answer;
				if (answer=="retry")
				{
					checkPass(username, password);
				}
				else if (answer=="cancel")
				{
					return 0;
				}
				else
				{
					cerr << "Invalid command.\n";
					throw 1;
				}
			}
		}
	}
}
User findUser(string username)
{
	for (size_t i = 0; i < usersCount; i++)
	{
		if (users[i].getUsername() == username)
		{
			return users[i];
		}
	}
}
#endif