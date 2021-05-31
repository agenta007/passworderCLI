#ifndef _PASSWORD_
#define _PASSWORD_
#include <string>
#include <ctime>
using std::string;
class Password
{
	int length, securityLevelPoints;
	string plainText, encrypted, secLevel;
	time_t tmOfCrtn;
public:
	Password();
	Password(string);
	int calcSecLevel();
	string getPlaintext()const;
	string getEncrypted()const;
	bool setPlainText(string);
	bool setSecLevel();
	string getSecLevel()const;
	int getLength()const;
	void printPass()const;
};
class illegalCharactersException:public std::exception
{
	string msg = "Password containts illegal characters!";
public:
	string what() { return msg; }
};
#endif // !_PASSWORD_
