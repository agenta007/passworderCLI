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
	//to delete single or multiple indexes
	void deletePasswordAt(int);
	void deletePasswordAt(int*, int sz);
	void printUserPassPair();
	void listPasswords();
	void printActualPassword()const;
	string getActualPassPlainText()const;
	string getPlainPassword()const;
	void UPP_printHistory();
	void mergeUPPs(const UsernamePassPair&);
	string getUsername()const;
	string getOwner()const;
	int getPassCount()const;
	void operator=(const UsernamePassPair&);
	Password& operator[](int);
	string convertToString()const;
	bool is_empty()const;
	void erasePassHistory();
	void fixIndexes();
}; 
#endif // !_usernamepasspair_
