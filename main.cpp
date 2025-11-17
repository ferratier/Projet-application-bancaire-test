#include <iostream>
#include "user.h"
#include "admin.h"
#include "client.h"
#include "menu.h"

int main(){
    Client test("JP", "password");
    Account compte("FR76", "Compte courant");
    test.addAccount(compte);
    Account* ok = test.getAccountByIBAN("FR76");
    ok->printAccountInfo();
    Menu menu;
    
    // Charger les données au démarrage
    menu.loadFromJson();
    
    // Si c'est la première exécution (pas d'utilisateurs)
    if(menu.get_user_count() == 0) {
        Admin* admin = new Admin("Lucas", "jesuisadmin");
        menu.add_user(admin);
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
                menu.connection();
                break;
            case 2:
                running = false;
                break;
            default:
                std::cout << "Choix invalide" << std::endl;
        }
    }

    // Sauvegarder avant de quitter
    menu.saveToJson();
    
    // Nettoyer la mémoire
    for(unsigned int i = 0; i < menu.get_user_count(); i++) {
        User* user = menu.get_user(i);
        delete user;
    }

    return 0;
}