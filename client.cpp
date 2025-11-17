#include "client.h"

int Client::addAccount(Account& account)
{
    list_accounts_.push_back(account);
    return 0;
}

Account* Client::getAccountByIBAN(std::string iban)
{
    for (int i = 0; i < list_accounts_.size(); i++)
    {
        if (list_accounts_[i].getIban() == iban)
            return &list_accounts_[i];
    }
    return nullptr;
}
