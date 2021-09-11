#include "Website.h"
#include "User.h"
#include "globals.h"
User* users = new User[8];
int usersCap = 8;
int usersCount = 0;
Website* websites = new Website[8];
int websitesCap = 8;
int websitesCount = 0;