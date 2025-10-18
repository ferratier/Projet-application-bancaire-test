#ifndef USER_H
#define USER_H
#include <string>

class User
{
    public:
        User(std::string id, std::string password);
        std::string get_password();
        std::string get_id();
    
    private:
        std::string id_;
        std::string password_;
};

#endif
