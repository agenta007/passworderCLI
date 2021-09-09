#include "user_not_found_exc.h"

user_not_found_exception::user_not_found_exception(string explanation)
{
	msg = explanation;
}
//constructor with 2 (all) needed parameters
user_not_found_exception::user_not_found_exception(string explanation, string notFoundUsername)
{
	msg = explanation;
	this->notFoundUsername = notFoundUsername;
}
//default
user_not_found_exception::user_not_found_exception()
{
	msg = "Reason unspecified.";
	notFoundUsername = "Username not specified.";
}
string user_not_found_exception::what()
{
	return msg;
}
string user_not_found_exception::getUnfoundUsername()
{
	return notFoundUsername;
}
