#pragma once

#include <string>
#include <iostream>

class Account
{
public:
    Account(std::string iban_, std::string account_name_);

    float getBalance() const;
    void getInfo() const;
    int deposit(float amount_);
    int withdraw(float amount_);
    int transfertMoney(float amount_, Account& account_to_receive);

private:
    float balance=0;
    std::string iban;
    std::string account_name;
};