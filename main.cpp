#include <iostream>
#include "user.h"
#include "admin.h"
#include "client.h"
#include "interface.h"

int main(){
    Interface interface;
    
    // Charger les données au démarrage
    interface.loadFromJson();
    
    // Si c'est la première exécution (pas d'utilisateurs)
    if(interface.get_user_count() == 0) {
        Admin* admin = new Admin("Lucas", "jesuisadmin");
        interface.add_user(admin);
    }
    
    bool running = true;
    while(running) {
        std::cout << "\nMenu Principal:" << std::endl;
        std::cout << "1. Connection" << std::endl;
        std::cout << "2. Quitter" << std::endl;
        
        int choix;
        std::cin >> choix;
        
        switch(choix) {
            case 1:
                interface.connection();
                break;
            case 2:
                running = false;
                break;
            default:
                std::cout << "Choix invalide" << std::endl;
        }
    }

    // Sauvegarder avant de quitter
    interface.saveToJson();
    
    // Nettoyer la mémoire
    for(unsigned int i = 0; i < interface.get_user_count(); i++) {
        User* user = interface.get_user(i);
        delete user;
    }

    return 0;
}