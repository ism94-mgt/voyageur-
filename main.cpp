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

double meilleure_longueur = -1;
int meilleur_depart = 0;

for (int depart = 0; depart < instance.nb_villes; ++depart)
{
    Solution temp;
    initialiser_solution(temp);

    methode_glouton(instance, temp, depart);

    std::cout << "Depart " << depart
              << " -> longueur : "
              << temp.longueur << std::endl;

    if (meilleure_longueur == -1 ||
        temp.longueur < meilleure_longueur)
    {
        meilleure_longueur = temp.longueur;


        solution.nb_villes = temp.nb_villes;
        solution.longueur = temp.longueur;

        solution.ordre = new int[temp.nb_villes];

        for (int i = 0; i < temp.nb_villes; ++i)
        {
            solution.ordre[i] = temp.ordre[i];
        }

        meilleur_depart = depart;
    }

    liberer_solution(temp);
}

std::cout << std::endl;
std::cout << "Meilleur depart est a la ville : "
          << meilleur_depart << std::endl;

afficher_solution(solution);
    }
    else
    {
        std::cout << "Problème lors de l'ouverture du fichier. " << nom_fichier << std::endl;
    }

    liberer_solution(solution);
    liberer_instance(instance);
}

int main()
{
    //traiter_fichier("bayg29.tsp");

    std::cout << std::endl;

    //traiter_fichier("att48.tsp");

    //traiter_fichier("gr24.tsp");

    traiter_fichier("ch150.tsp");

    return 0;
}
/*int main(int argc, char** argv)
{
    if (argc < 2)
    {
        std::cout << "Usage: " << argv[0] << " fichier.tsp" << std::endl;
        return 1;
    }

    traiter_fichier(argv[1]);

    return 0;
}*/
