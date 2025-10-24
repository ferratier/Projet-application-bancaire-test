cmake_minimum_required(VERSION 3.15)

project(BankApp)

# Spécifier le standard C++
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Ajouter l'exécutable principal
add_executable(BankApp 
    main.cpp
    user.cpp
    admin.cpp
    client.cpp
    menu.cpp
)


#mkdir build      # 1. Crée dossier pour les fichiers de build
#cd build        # 2. Va dans ce dossier
#cmake ..        # 3. Génère les fichiers de build (.. = dossier parent)
#cmake --build . --config Debug  # 4. Compile le projet