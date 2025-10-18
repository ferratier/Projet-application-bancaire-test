#include "user.h"

User::User(std::string id, std::string password)
{
    id_ = id;
    password_ = password;
}

std::string User::get_id()
{
    return id_;
}

std::string User::get_password()
{
    return password_;
}