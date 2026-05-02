#include <iostream>
#include "tsp.h"
#include "algorithmes.h"

void traiter_fichier(std::string nom_fichier)
{
    InstanceTSP instance;
    Solution solution;

    initialiser_instance(instance);
    initialiser_solution(solution);

    std::cout << "====================================" << std::endl;
    std::cout << "Lecture de " << nom_fichier << std::endl;
    std::cout << "====================================" << std::endl;

    if (lire_instance(nom_fichier, instance))
    {
        afficher_instance(instance);

        std::cout << std::endl;
        std::cout << "Algorithme glouton :" << std::endl;

        methode_glouton(instance, solution, 0);
        afficher_solution(solution);
    }
    else
    {
        std::cout << "Erreur : impossible d'ouvrir " << nom_fichier << std::endl;
    }

    liberer_solution(solution);
    liberer_instance(instance);
}

int main()
{
    traiter_fichier("att48.tsp");

    std::cout << std::endl;

    traiter_fichier("bayg29.tsp");

    return 0;
}