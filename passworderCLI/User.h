#ifndef USER_H
#define USER_H
using namespace std;
#include <string>
class User
{
	string username;
	string masterpass;
	bool logged_on;
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
	static User* register_user(User*);
	static User* delete_user(User*);
	User& operator=(const User&);
};
#endif