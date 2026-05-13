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


void amelioration_or_opt(const InstanceTSP & instance, Solution & solution)
{
    int n = solution.nb_villes;

    bool amelioration = true;

    while (amelioration)
    {
        amelioration = false;

        for (int i = 0; i < n && !amelioration; ++i)
        {
            int prev = (i - 1 + n) % n;
            int next = (i + 1) % n;

            int ville_prev = solution.ordre[prev];
            int ville_i    = solution.ordre[i];
            int ville_next = solution.ordre[next];

            double cout_actuel =
                distance_entre_villes(instance, ville_prev, ville_i) + distance_entre_villes(instance, ville_i, ville_next);

            double cout_sans_i = distance_entre_villes(instance, ville_prev, ville_next);

            for (int k = 0; k < n && !amelioration; ++k)
            {
                if (k == prev || k == i || k == next)
                {
                    continue;
                }

                int ville_k      = solution.ordre[k];
                int ville_k_next = solution.ordre[(k + 1) % n];

                double cout_insertion =
                    distance_entre_villes(instance, ville_k, ville_i) +
                    distance_entre_villes(instance, ville_i, ville_k_next) -
                    distance_entre_villes(instance, ville_k, ville_k_next);

                double delta =
                    cout_sans_i - cout_actuel + cout_insertion;

                if (delta < -1e-10)
                {
                    int * nouvel_ordre = new int[n];

                    int pos = 0;

                    for (int p = 0; p < n; ++p)
                    {
                        if (p != i)
                        {
                            nouvel_ordre[pos] = solution.ordre[p];
                            pos = pos + 1;
                        }
                    }

                    int pos_k = 0;

                    for (int p = 0; p < n - 1; ++p)
                    {
                        if (nouvel_ordre[p] == ville_k)
                        {
                            pos_k = p;
                        }
                    }

                    for (int p = n - 2; p > pos_k; --p)
                    {
                        nouvel_ordre[p + 1] = nouvel_ordre[p];
                    }

                    nouvel_ordre[pos_k + 1] = ville_i;

                    delete[] solution.ordre;

                    solution.ordre = nouvel_ordre;

                    solution.longueur = solution.longueur + delta;

                    amelioration = true;
                }
            }
        }
    }
}