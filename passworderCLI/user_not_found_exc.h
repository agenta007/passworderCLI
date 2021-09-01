#ifndef _user_not_found_
#define _user_not_found_
#include <string>
class user_not_found_exception : public std::exception
{
	string msg;
	string notFoundUsername;
public:
	//constructor when program searches for logged on user without username
	user_not_found_exception(string explanation)
	{
		msg = explanation;
	}
	//constructor with 2 (all) needed parameters
	user_not_found_exception(string explanation, string notFoundUsername)
	{
		msg = explanation;
		this->notFoundUsername = notFoundUsername;
	}
	//default
	user_not_found_exception()
	{
		msg = "Reason unspecified.";
		notFoundUsername = "Username not specified.";
	}
	string what()
	{
		return msg;
	}
	string getUnfoundUsername()
	{
		return notFoundUsername;
	}
};
#endif