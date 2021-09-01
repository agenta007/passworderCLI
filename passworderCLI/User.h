#ifndef USER_H
#define USER_H
using namespace std;
#include <string>
#include "Website.h"
#include "user_not_found_exc.h"
#include <vector>
class User
{
	string username;
	string masterpass;
	bool logged_on;
	//only one at a time user will be able to be logged
	static bool is_anyone_logged_in;
	vector<string> registererd_to_websiteNames;
public:
	User();
	User(string, string, bool logged_on = false);
	bool login(bool are_credentials_typed);
	void logout();
	void logon();
	string getUsername()const;
	string getPass()const;
	int changePassWithParam(string);
	bool changePass();
	static void register_user(User*);
	//to read from file
	static void read_user(string, string, vector<string>&);
	static void delete_my_account();
	void operator=(const User&);
	void printCredentials()const { cout << username << " " << masterpass; }
	bool get_logged_in_state()const { return logged_on; }
	static bool check_logon() { return is_anyone_logged_in; }
	void printWebsites()const;
	void registerWebsiteName(string);
	void registered_to_websiteName_rm(string);
	void printActualPasswords();
	void printPasswordHistoryForWebsite(User*, string);
	int getRegisteredToWebsiteNamesCount()const { return registererd_to_websiteNames.size(); }
	string getRegisteredToWebsiteNameWithIndex(int index)const { return registererd_to_websiteNames[index]; }
	void readRegisteredToWebsiteNames(vector<string>&);
	bool checkUserRegistered(string);
	void removeWebsiteFromRegistered(string);
};
#endif