#ifndef ADMIN_8
#define ADMIN_8
#include <string>
#include "user.h"
#include "client.h"

class Admin : public User
{
    public:
        Admin(std::string id, std::string password) : User(id, password) {}
        void create_client(std::string nom, std::string prenom);
        void delete_client(Client* client);


    private:

};

#endif