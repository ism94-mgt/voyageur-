#include <iostream>
#include "tsp.h"
#include "algorithmes.h"

void traiter_fichier(std::string nom_fichier)
{
    InstanceTSP instance;
    Solution solution;
    Solution solution_or_opt;

    initialiser_instance(instance);
    initialiser_solution(solution);
    initialiser_solution(solution_or_opt);

    std::cout << "====================================" << std::endl;
    std::cout << "Lecture de " << nom_fichier << std::endl;
    std::cout << "====================================" << std::endl;

    if (lire_instance(nom_fichier, instance))
    {
        afficher_instance(instance);

        std::cout << std::endl;
        std::cout << "Algorithme glouton + OR-opt :" << std::endl;

        double meilleure_longueur = -1;
        double meilleure_longueur_or_opt = -1;

        int meilleur_depart = 0;
        int meilleur_depart_or_opt = 0;

        for (int depart = 0; depart < instance.nb_villes; ++depart)
        {
            Solution temp;
            Solution temp_or_opt;

            initialiser_solution(temp);
            initialiser_solution(temp_or_opt);

            methode_glouton(instance, temp, depart);

            temp_or_opt.nb_villes = temp.nb_villes;
            temp_or_opt.longueur = temp.longueur;

            temp_or_opt.ordre = new int[temp.nb_villes];

            for (int i = 0; i < temp.nb_villes; ++i)
            {
                temp_or_opt.ordre[i] = temp.ordre[i];
            }

            amelioration_or_opt(instance, temp_or_opt);

            if (meilleure_longueur == -1 ||
                temp.longueur < meilleure_longueur)
            {
                meilleure_longueur = temp.longueur;
                meilleur_depart = depart;

                liberer_solution(solution);

                solution.nb_villes = temp.nb_villes;
                solution.longueur = temp.longueur;

                solution.ordre = new int[temp.nb_villes];

                for (int i = 0; i < temp.nb_villes; ++i)
                {
                    solution.ordre[i] = temp.ordre[i];
                }
            }

            if (meilleure_longueur_or_opt == -1 ||
                temp_or_opt.longueur < meilleure_longueur_or_opt)
            {
                meilleure_longueur_or_opt = temp_or_opt.longueur;
                meilleur_depart_or_opt = depart;

                liberer_solution(solution_or_opt);

                solution_or_opt.nb_villes = temp_or_opt.nb_villes;
                solution_or_opt.longueur = temp_or_opt.longueur;

                solution_or_opt.ordre =
                    new int[temp_or_opt.nb_villes];

                for (int i = 0;
                     i < temp_or_opt.nb_villes;
                     ++i)
                {
                    solution_or_opt.ordre[i] =
                        temp_or_opt.ordre[i];
                }
            }

            liberer_solution(temp);
            liberer_solution(temp_or_opt);
        }

        std::cout << std::endl;

        std::cout << "Meilleur depart glouton : "<< meilleur_depart << std::endl;

        afficher_solution(solution);

        std::cout << std::endl;

        std::cout << "Solution OR-opt obtenue depuis le depart :"<< meilleur_depart_or_opt << std::endl;

        afficher_solution(solution_or_opt);
    }
    else
    {
        std::cout << "Probleme lors de l'ouverture du fichier : "
                  << nom_fichier << std::endl;
    }

    liberer_solution(solution);
    liberer_solution(solution_or_opt);

    liberer_instance(instance);
}

int main()
{
    //traiter_fichier("bayg29.tsp");

    std::cout << std::endl;

    traiter_fichier("att48.tsp");

    //traiter_fichier("gr24.tsp");

    //traiter_fichier("ch150.tsp");

    return 0;
}

/*int main(int argc, char** argv)
{
    if (argc < 2)
    {
        std::cout << "Usage : " << argv[0] << " fichier1.tsp fichier2.tsp ..."<< std::endl;

        return 1;
    }

    for (int i = 1; i < argc; ++i)
    {
        std::cout << std::endl;

        traiter_fichier(argv[i]);
    }

    return 0;
}*/