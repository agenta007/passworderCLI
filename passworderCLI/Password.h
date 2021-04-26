#ifndef _PASSWORD_
#define _PASSWORD_
#include <string>
using std::string;
class Password
{
	int length, securityLevel;
	string plainText, encrypted;
public:
	Password();
	Password(char*);
	bool calcSecLevel();
	char* getPlaintext()const;
	char* getEncrypted()const;
	int getSecLevel()const;
	int getLength()const;
};
#endif // !_PASSWORD_
