#ifndef CLIENT_H
#define CLIENT_H
#include <string>
#include "user.h"

class Client : public User
{
    public:
        Client(std::string id, std::string password) : User(id, password) {}
    private:

};

#endif
