#ifndef _PASSWORD_
#define _PASSWORD_
#include <string>
#include <ctime>
using std::string;
class Password
{
	int length, securityLevelPoints, index;
	string plainText, encrypted, secLevel;
	time_t tmOfCrtn;
	string loadStr;
public:
	Password();
	Password(string, int);
	Password(string&, string&, string&, int, int, string&);
	Password(string&, string&, string&);
	int calcSecLevel();
	string getPlaintext()const;
	string getEncrypted()const;
	int getIndex()const { return index; }
	int setIndex(int setVal) { index = setVal;  return 0; }
	bool setPlainText(string);
	bool setSecLevel();
	string getSecLevel()const;
	int getLength()const;
	void printPass()const;
	string convertToString()const;
	static string decryptPass(string&);
	static string encryptPass(string&);
	void setLoadStr();
	void decrIdx();
};
class illegalCharactersException :public std::exception
{
	string msg = "Password containts illegal characters!";
public:
	string what() { return msg; }
};
#endif // !_PASSWORD_
