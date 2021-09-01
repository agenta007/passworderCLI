#ifndef _usernamepasspair_
#define _usernamepasspair_
#include "Password.h"
#include "iostream"
#include <vector>
#include <string>
using std::vector;
class UsernamePassPair
{
	string username;
	string owner;
	vector<Password> passwords;
public:
	UsernamePassPair();
	UsernamePassPair(string, string, string);
	UsernamePassPair(string, string, vector<Password>&);
	UsernamePassPair(const UsernamePassPair&);
	static UsernamePassPair createNewUsernamePassPair();
	static UsernamePassPair createNewUsernamePassPairWithParams(string usr, string pass);
	void updatePassword(string password);
	void deletePasswordAt(int);
	void printUserPassPair();
	void listPasswords();
	void printActualPassword();
	void UPP_printHistory();
	void mergeUPPs(const UsernamePassPair&);
	string getUsername()const;
	string getOwner()const;
	void operator=(const UsernamePassPair&);
	string convertToString()const;
	bool is_empty()const;
}; 
#endif // !_usernamepasspair_
