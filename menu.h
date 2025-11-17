#ifndef MENU_H
#define MENU_H
#include "user.h"

// forward declarations to avoid circular includes ???? (à voir)
class Client;
class Admin;

#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>

class Menu
{
    public:
        Menu();
        User* connection();
        void disconnection();
        void add_user(User* user);
        void del_user(User* user);
        unsigned int get_user_count();
        User* get_user(unsigned int index);
        
        // Méthodes de sauvegarde/chargement JSON
        void saveToJson();
        void loadFromJson();

    private:
        std::vector<User*> users;
};

#endif