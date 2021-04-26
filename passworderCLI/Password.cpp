#include "Password.h"
#include <string>
//	int length, securityLevel;
//  char* plainText, * encypted;

int countContains(string input)
{
	int points = 0;
	for (int i = 0; i < input.length(); i++)
	{
		if (input[i] == )
		{

		}
	}
	return 0;
}

Password::Password()
{
	plainText = encrypted = "";
	length = securityLevel = 0;
}
Password::Password(string setPass)
{
	plainText = setPass;
	length = setPass.length();

}
bool Password::calcSecLevel()
{
	//secLevels
	//lowest, low, below average, average, better than average, good, high, very high, extreme, insane
	int points = 0;
	if (length > 10)
	{
		++points;
	}
	if (length > 20)
	{
		++points;
	}
	return points;
}
//char* getPlaintext()const;
//char* getEncrypted()const;
//int getSecLevel()const;
//int getLength()const;
