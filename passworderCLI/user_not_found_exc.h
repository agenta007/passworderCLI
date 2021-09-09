#ifndef _user_not_found_exc_
#define _user_not_found_exc_
#include <string>
using std::string;
class user_not_found_exception : public std::exception
{
	string msg;
	string notFoundUsername;
public:
	user_not_found_exception(string);
	user_not_found_exception(string, string);
	user_not_found_exception();
	string what();
	string getUnfoundUsername();
};
#endif