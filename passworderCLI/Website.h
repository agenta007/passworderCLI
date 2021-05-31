#ifndef _WEBSITE_
#define _WEBSITE_
#include <string>
#include "UsernamePassPair.h"
using std::string;
class Website
{
	string link, domain;
	UsernamePassPair* registered_users;
	int registeredUsersCount;
public:
	string getLink()const { return link; }
	string getDomain()const { return domain; }
	void setDomain(string domain) { this->domain = domain; }
	void setLink() { link += "https://www." + domain; }
	Website() { domain = link = ""; registered_users = nullptr; registeredUsersCount = 0; }
	Website(string domain) { setDomain(domain); setLink(); registeredUsersCount = 0; }

	void add_user(string usrnm, string password) 
	{
		for (size_t i = 0; i < registeredUsersCount; i++)
		{
			if (registered_users[i].getUsername() == usrnm)
			{
				cerr << "User already exists.\nReturning.\n";
				return;
			}
		}
		++registeredUsersCount;
		UsernamePassPair *tmp = new UsernamePassPair[registeredUsersCount];
		for (size_t i = 0; i < registeredUsersCount; i++)
		{
			tmp[i] = registered_users[i];
		}
		tmp[registeredUsersCount] = UsernamePassPair(usrnm, password);
		delete[] registered_users;
		registered_users = new UsernamePassPair[registeredUsersCount];
		for (size_t i = 0; i < registeredUsersCount; i++)
		{
			registered_users[i] = tmp[i];
		}
		delete[] tmp;
	}
};
#endif