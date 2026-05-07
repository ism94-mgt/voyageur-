#include <iostream>
#include "algorithmes.h"

void initialiser_solution(Solution & solution)
{
    solution.ordre = nullptr;
    solution.nb_villes = 0;
    solution.longueur = 0;
}

void liberer_solution(Solution & solution)
{
    if (solution.ordre != nullptr)
    {
        delete[] solution.ordre;
    }

    solution.ordre = nullptr;
    solution.nb_villes = 0;
    solution.longueur = 0;
}


void methode_glouton(const InstanceTSP & instance, Solution & solution, int depart)
{
    int n = instance.nb_villes;

    solution.nb_villes = n;
    solution.longueur = 0;

    solution.ordre = new int[n];

    bool * visite = new bool[n];

    for (int i = 0; i < n; ++i)
    {
        visite[i] = false;
    }

    int ville_courante = depart;

    solution.ordre[0] = ville_courante;
    visite[ville_courante] = true;

    for (int position = 1; position < n; ++position)
    {
        int meilleure_ville = -1;
        double meilleure_distance = -1;

        for (int ville = 0; ville < n; ++ville)
        {
            if (!visite[ville])
            {
                double distance = distance_entre_villes(instance, ville_courante, ville);

                if (meilleure_ville == -1 || distance < meilleure_distance)
                {
                    meilleure_ville = ville;
                    meilleure_distance = distance;
                }
            }
        }

        solution.ordre[position] = meilleure_ville;
        visite[meilleure_ville] = true;

        solution.longueur = solution.longueur + meilleure_distance;

        ville_courante = meilleure_ville;
    }

    solution.longueur = solution.longueur + distance_entre_villes(instance, ville_courante, depart);

    delete[] visite;
}

void afficher_solution(const Solution & solution)
{
    std::cout << "Solution trouvee :" << std::endl;

    for (int i = 0; i < solution.nb_villes; ++i)
    {
        std::cout << solution.ordre[i];

        if (i < solution.nb_villes - 1)
        {
            std::cout << " -> ";
        }
    }

    if (solution.nb_villes > 0)
    {
        std::cout << " -> " << solution.ordre[0];
    }

    std::cout << std::endl;

    std::cout << "Longueur totale : " << solution.longueur << std::endl;
}