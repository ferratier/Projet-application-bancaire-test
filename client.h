#ifndef CLIENT_H
#define CLIENT_H

#include <vector>
#include <string>

#include "user.h"
#include "account.h"

class Client : public User
{
    public:
        Client(std::string id, std::string password) : User(id, password) {}

        int addAccount(Account& account);
        Account* getAccountByIBAN(std::string iban);

    private:
        std::vector<Account> list_accounts_;

};

#endif
