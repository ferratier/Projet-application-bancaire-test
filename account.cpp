#include "account.h"

Account::Account(std::string iban_, std::string account_name_) : iban(iban_), account_name(account_name_)
{
}

float Account::getBalance() const
{
    return balance;
}

std::string Account::getIban() const
{
    return iban;
}

std::string Account::getName() const
{
    return account_name;
}

int Account::deposit(float amount_)
{
    balance+=amount_;
    return 0;
}

int Account::withdraw(float amount_)
{
    if(balance-amount_<0)
    {
        std::cout << "Error: Insufficient balance";
        return 1;
    }
    balance-=amount_;
    std::cout << "Withdraw succeed!" << std::endl;
    return 0;
}

int Account::transfertMoney(float amount_, Account &account_to_receive)
{
    if(withdraw(amount_)==0)
    {
        account_to_receive.deposit(amount_);
        std::cout << "Transfert succeed" << std::endl;
        return 0;
    }
    else
    {
        std::cout << "Error: Transfert abort" << std::endl;
        return 1;
    }
}

void Account::printAccountInfo() const
{
    std::cout << "--- Account informations ---" << std::endl;
    std::cout << "Name: " << account_name << std::endl;
    std::cout << "IBAN : " << iban << std::endl;
    std::cout << "Balance : " << balance << std::endl;
    std::cout << "----------------------------" << std::endl;
}