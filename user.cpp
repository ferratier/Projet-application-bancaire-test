#include "user.h"

User::User(std::string id, std::string password)
{
    id_ = id;
    password_ = password;
}

const std::string& User::get_password() const
{
    return password_;
}

const std::string& User::get_id() const
{
    return id_;
}

void User::change_password(User user, std::string newPassword)
{
    user.password_ = newPassword;
}
