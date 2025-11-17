#include "menu.h"
#include "json.hpp"
#include <iostream>
#include <fstream>
#include <sstream>

using json = nlohmann::json;
#include "admin.h"
#include "client.h"
Menu::Menu()
{
}

User* Menu::connection()
{
    std::string id_test;
    std::string password_test;

    std::cout << "Entrez votre identifiant: ";
    std::cin >> id_test;

    // Chercher l'utilisateur par identifiant
    User* user_found = nullptr;     // On crée un pointeur qui va servir à stocker l'utilisateur trouvé
    for (User* u : users) {
        if (u && u->get_id() == id_test) {  // Si l'utilisateur existe et son ID correspond
            user_found = u;
            break;
        }
    }

    if (!user_found) {
        std::cout << "Identifiant introuvable." << std::endl;
        return user_found;
    }

    const int max_attempts = 3;
    std::cout << "Entrez votre mot de passe: ";
    for (int attempt = 1; attempt <= max_attempts; ++attempt) {
        std::cin >> password_test;
        if (user_found->get_password() == password_test) {
            std::cout << "Bienvenue, " << user_found->get_id() << "!" << std::endl;
            // Suite pour passer à l'interface utilisateur (menu admin/client)
            return user_found;
        }
        if (attempt < max_attempts) {
            std::cout << "Mot de passe incorrect. Il vous reste " << (max_attempts - attempt) << " essais." << std::endl;
            std::cout << "Réessayez: ";
        } else {
            std::cout << "Trop d'essais. Connexion annulée." << std::endl;
        }
    }
}

void Menu::disconnection()
{

}

void Menu::add_user(User *user)
{
    users.push_back(user);
}

void Menu::del_user(User *user)
{
    for (auto it = users.begin(); it != users.end(); ++it) {
        if (*it == user) {
            users.erase(it);
            break;          //break car sinon it devient invalide apres le erase.
        }
    }
}

unsigned int Menu::get_user_count()
{
    return users.size();
}

User *Menu::get_user(unsigned int index)
{
    if (index < get_user_count()){
        return users[index];
    }
    return nullptr;
}

std::vector<User *> &Menu::getUsers()
{
    return users;
}

void Menu::saveToJson() {
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
        if(dynamic_cast<Admin*>(user)) {     //Cette ligne essaie de convertir le pointeur User* en Admin* si user point vers un objet de type admin le cast réussit et renvoie un pointeur non-null sinon nullptr
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
void Menu::loadFromJson() {
    // Ouvrir le fichier
    std::ifstream file("bank_data.json");
    if(!file.is_open()) { // cas où il n'y a pas encore de fichier de sauvgarde
        std::cout << "Aucun fichier de données trouvé." << std::endl;
        return;
    }
    
    try {
        // Parser le JSON (lit le contenu de file et convertit le texte JSON en un objoet C++ de type Json et les données persées sont stockées dans la variable data)
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
    } catch(const json::exception& e) { // e est l'objet de type exeption, une réference constante(pour éviter la copie) 
        std::cout << "Erreur lors du chargement du JSON: " << e.what() << std::endl; //what() methode qui retourne un message décrivant l'érreur
    }
    
    file.close();
}
