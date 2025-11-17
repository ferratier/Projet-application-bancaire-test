#pragma once

#include <string>
#include <iostream>

class Account
{
public:
    Account(std::string iban_, std::string account_name_);

    float getBalance() const;
    std::string getIban() const;
    std::string getName() const;
    int deposit(float amount_);
    int withdraw(float amount_);
    int transfertMoney(float amount_, Account& account_to_receive);
    void printAccountInfo() const;

private:
    float balance=0;
    std::string iban;
    std::string account_name;
};