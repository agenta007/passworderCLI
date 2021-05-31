#ifndef _USERNAME_PASS_PAIR_
#define _USERNAME_PASS_PAIR_
#include "string"
#include "vector"
#include "Password.h"
#include "iostream"
using std::string;
using std::vector;
class UsernamePassPair
{
	string username;
	vector<Password> passwords;
public:
	UsernamePassPair() { username = "unknown"; }
	UsernamePassPair(string username, string password) {this->username = username; this->passwords.push_back(Password(password));}
	void updatePassword(string password) { passwords.push_back(Password(password)); }
	void printUserPassPair() { std::cout << "Username: " << username; passwords[passwords.size() - 1].printPass(); }
	void listPasswords() { for (Password pass : passwords) { pass.printPass(); } }
	string getUsername()const { return username; }
	void operator=(const UsernamePassPair& rhs) {
		username = rhs.username; 
		if (!passwords.empty())
			passwords.erase(passwords.begin(), passwords.end());
		//!!!!!
		passwords = rhs.passwords;
	}
};
#endif
