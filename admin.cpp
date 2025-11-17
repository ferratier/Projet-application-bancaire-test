#include "admin.h"
#include "menu.h"

void Admin::create_client(Menu& menu)
{
    std::string id;
    std::string password;
    std::string confirmed_password;
    bool id_exists = true;
    while(id_exists)
    {
        std::cout << "Entrer l'identifient du nouveau client" << std::endl;
        std::cin >> id;
        id_exists = false;
        for (User* user : menu.getUsers()){
            if (user->get_id() == id){
                std::cout << "Cet identifiant est déjà urilisé, réessayez !" << std::endl;
                id_exists = true;
                break;
            }
        }
    }
    std::cout << "Entrer un mot de passe pour le nouveau client" << std::endl;
    std::cin >> password;
    std::cout << "Confirmer le mot de passe" << std::endl;
    std::cin >> confirmed_password;
    while (password != confirmed_password)
    {
        std::cout << "Mot de passe different, réésseyer !" << std::endl;
        std::cout << "Entrer un mot de passe pour le nouveau client" << std::endl;
        std::cin >> password;
        std::cout << "Confirmer le mot de passe" << std::endl;
        std::cin >> confirmed_password;
    }
    Client* client = new Client(id, confirmed_password);
    std::cout << "Le client à bien été créé" << std::endl;
}

void Admin::delete_client(Client *client)
{
}

