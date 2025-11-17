#ifndef USER_H
#define USER_H
#include <string>

class User
{
    public:
        User(std::string id, std::string password);
        virtual ~User() = default;  // <-- rend la classe polymorphique, permet dynamic_cast
        const std::string& get_password() const;
        const std::string& get_id() const;
    
    private:
        std::string id_;
        std::string password_;
};

#endif
