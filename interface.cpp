#include "interface.h"
#include "json.hpp" // nlohmann::json header; download json.hpp into project root
#include <iostream>
#include <fstream>
#include <sstream>

using json = nlohmann::json;
#include "admin.h"
#include "client.h"
Interface::Interface()
{
}

void Interface::connection()
{
    std::string id_test;
    std::string password_test;

    std::cout << "Entrez votre identifient" << std::endl;
    std::cin >> id_test;
    

}

void Interface::disconnection()
{

}

void Interface::add_user(User *user)
{
    users.push_back(user);
}

void Interface::del_user(User *user)
{
    for (auto it = users.begin(); it != users.end(); ++it) {
        if (*it == user) {
            users.erase(it);
            break;          //break car sinon it devient invalide apres le erase.
        }
    }
}

unsigned int Interface::get_user_count()
{
    return users.size();
}

User *Interface::get_user(unsigned int index)
{
    if (index < get_user_count()){
        return users[index];
    }
    return nullptr;
}

void Interface::saveToJson() {
    // Créer un objet JSON
    json data;
    
    // Créer un tableau pour les utilisateurs
    data["users"] = json::array();
    
    // Pour chaque utilisateur
    for(User* user : users) {
        // Créer un objet JSON pour cet utilisateur
        json userData;
        
        // Ajouter les informations de base
        userData["id"] = user->get_id();
        userData["password"] = user->get_password();
        
        // Vérifier le type d'utilisateur et ajouter les informations spécifiques
        if(dynamic_cast<Admin*>(user)) {
            userData["type"] = "admin";
        } else if(dynamic_cast<Client*>(user)) {
            userData["type"] = "client";
            // Ici vous pourriez ajouter d'autres informations spécifiques aux clients
        }
        
        // Ajouter cet utilisateur au tableau
        data["users"].push_back(userData);
    }
    
    // Ouvrir le fichier pour écriture
    std::ofstream file("bank_data.json");
    if(file.is_open()) {
        // Écrire le JSON avec une indentation de 4 espaces pour la lisibilité
        file << data.dump(4) << std::endl;
        file.close();
    }
}

// Charger les données depuis le JSON
void Interface::loadFromJson() {
    // Ouvrir le fichier
    std::ifstream file("bank_data.json");
    if(!file.is_open()) {
        std::cout << "Aucun fichier de données trouvé." << std::endl;
        return;
    }
    
    try {
        // Parser le JSON
        json data = json::parse(file);
        
        // Nettoyer les utilisateurs existants
        for(User* user : users) {
            delete user;
        }
        users.clear();
        
        // Pour chaque utilisateur dans le JSON
        for(const auto& userData : data["users"]) {
            std::string type = userData["type"];
            std::string id = userData["id"];
            std::string password = userData["password"];
            
            // Créer le bon type d'utilisateur
            User* user = nullptr;
            if(type == "admin") {
                user = new Admin(id, password);
            } else if(type == "client") {
                user = new Client(id, password);
            }
            
            // Si l'utilisateur a été créé, l'ajouter à la liste
            if(user) {
                users.push_back(user);
            }
        }
    } catch(const json::exception& e) {
        std::cout << "Erreur lors du chargement du JSON: " << e.what() << std::endl;
    }
    
    file.close();
}
