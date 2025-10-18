#ifndef ADMIN_8
#define ADMIN_8
#include <string>
#include "user.h"

class Admin : public User
{
    public:
        Admin(std::string id, std::string password) : User(id, password) {}
    
    private:

};

#endif