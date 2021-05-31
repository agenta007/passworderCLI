#ifndef USER_H
#define USER_H
using namespace std;
#include <string>
#include "Website.h"
class User
{
	string username;
	string masterpass;
	bool logged_on;
	//Website* webEntries;
public:
	User();
	User(string, string,bool logged_on=false);
	static bool login();
	bool logon();
	bool logout();
	string getUsername()const;
	string getPass()const;
	int changePassWithParam(string);
	bool changePass();
	static void register_user(User*);
	static User* delete_user(User*);
	void operator=(const User&);
	void printCredentials() { cout << username << " " << masterpass; }
};
#endif