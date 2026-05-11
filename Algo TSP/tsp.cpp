#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include "tsp.h"

void initialiser_instance(InstanceTSP & instance)
{
    instance.nom = "";
    instance.nb_villes = 0;
    instance.type_distance = "";
    instance.villes = nullptr;
    instance.distances = nullptr;
}

void liberer_instance(InstanceTSP & instance)
{
    if (instance.villes != nullptr)
    {
        delete[] instance.villes;
    }

    if (instance.distances != nullptr)
    {
        delete[] instance.distances;
    }

    instance.nom = "";
    instance.nb_villes = 0;
    instance.type_distance = "";
    instance.villes = nullptr;
    instance.distances = nullptr;
}

void allouer_instance(InstanceTSP & instance, int nb_villes)
{
    if (instance.villes != nullptr)
    {
        delete[] instance.villes;
    }

    if (instance.distances != nullptr)
    {
        delete[] instance.distances;
    }

    instance.nb_villes = nb_villes;

    instance.villes = new Ville[nb_villes];
    instance.distances = new double[nb_villes * nb_villes];

    for (int i = 0; i < nb_villes; ++i)
    {
        instance.villes[i].num = 0;
        instance.villes[i].x = 0;
        instance.villes[i].y = 0;
    }

    for (int i = 0; i < nb_villes * nb_villes; ++i)
    {
        instance.distances[i] = 0;
    }
}
double distance_entre_villes(const InstanceTSP & instance, int i, int j)
{
    return instance.distances[i * instance.nb_villes + j];
}

void modifier_distance(InstanceTSP & instance, int i, int j, double distance)
{
    instance.distances[i * instance.nb_villes + j] = distance;
}

double distance_euclidienne(Ville a, Ville b)
{
    double dx = a.x - b.x;
    double dy = a.y - b.y;

    return std::sqrt(dx * dx + dy * dy);
}

double distance_att(Ville a, Ville b)
{
    double dx = a.x - b.x;
    double dy = a.y - b.y;

    double rij = std::sqrt((dx * dx + dy * dy) / 10.0);
    int tij = std::round(rij);

    if (tij < rij)
    {
        return tij + 1;
    }

    return tij;
}

void calculer_distances_depuis_coordonnees(InstanceTSP & instance)
{
    for (int i = 0; i < instance.nb_villes; ++i)
    {
        for (int j = 0; j < instance.nb_villes; ++j)
        {
            if (i == j)
            {
                modifier_distance(instance, i, j, 0);
            }
            else if (instance.type_distance == "ATT")
            {
                modifier_distance(instance, i, j, distance_att(instance.villes[i], instance.villes[j]));
            }
            else
            {
                modifier_distance(instance, i, j, distance_euclidienne(instance.villes[i], instance.villes[j]));
            }
        }
    }
}

bool lire_instance(std::string nom_fichier, InstanceTSP & instance)
{
    std::ifstream fichier(nom_fichier);

    if (!fichier)
    {
        std::cout<<"Problème lors de l'ouverture du fichier."<<std::endl;
        return false;
    }

    std::string mot;

    while (fichier >> mot)
    {
        if (mot == "NAME:" || mot == "NAME")
        {
            if (mot == "NAME")
            {
                fichier >> mot;
            }

            fichier >> instance.nom;
        }
        else if (mot == "DIMENSION:" || mot == "DIMENSION")
        {
            if (mot == "DIMENSION")
            {
                fichier >> mot;
            }

            int n;
            fichier >> n;

            allouer_instance(instance, n);
        }
        else if (mot == "EDGE_WEIGHT_TYPE:" || mot == "EDGE_WEIGHT_TYPE")
        {
            if (mot == "EDGE_WEIGHT_TYPE")
            {
                fichier >> mot;
            }

            fichier >> instance.type_distance;
        }
        else if (mot == "NODE_COORD_SECTION")
        {
            for (int i = 0; i < instance.nb_villes; ++i)
            {
                fichier >> instance.villes[i].num
                        >> instance.villes[i].x
                        >> instance.villes[i].y;
            }

            calculer_distances_depuis_coordonnees(instance);
        }
        else if (mot == "EDGE_WEIGHT_SECTION")
        {
            for (int i = 0; i < instance.nb_villes; ++i)
            {
                modifier_distance(instance, i, i, 0);
            }

            for (int i = 0; i < instance.nb_villes - 1; ++i)
            {
                for (int j = i + 1; j < instance.nb_villes; ++j)
                {
                    double distance;
                    fichier >> distance;

                    modifier_distance(instance, i, j, distance);
                    modifier_distance(instance, j, i, distance);
                }
            }
        }
        else if (mot == "DISPLAY_DATA_SECTION")
        {
            for (int i = 0; i < instance.nb_villes; ++i)
            {
                fichier >> instance.villes[i].num
                        >> instance.villes[i].x
                        >> instance.villes[i].y;
            }
        }
        else if (mot == "EOF")
        {
            //break or continue or rien?
        }
    }

    fichier.close();
    return true;
}

void afficher_instance(const InstanceTSP & instance)
{
    std::cout << "Nom : " << instance.nom << std::endl;
    std::cout << "Nombre de villes : " << instance.nb_villes << std::endl;
    std::cout << "Type de distance : " << instance.type_distance << std::endl;

    std::cout << std::endl;
    std::cout << "Premieres villes :" << std::endl;

    int limite_villes = instance.nb_villes;

    if (limite_villes > 10)
    {
        limite_villes = 10;
    }

    for (int i = 0; i < limite_villes; ++i)
    {
        std::cout << instance.villes[i].num << " "
                  << instance.villes[i].x << " "
                  << instance.villes[i].y << std::endl;
    }

    if (instance.nb_villes > 10)
    {
        std::cout << "... (" << instance.nb_villes - 10 << " autres villes)" << std::endl;
    }

    std::cout << std::endl;
    std::cout << "Debut de la matrice des distances :" << std::endl;

    int limite = instance.nb_villes;

    if (limite > 10)
    {
        limite = 10;
    }


    std::cout << "\t";
    for (int j = 0; j < limite; ++j)
    {
        std::cout << j << "\t";
    }
    std::cout << std::endl;


    for (int i = 0; i < limite; ++i)
    {
        std::cout << i << "\t";

        for (int j = 0; j < limite; ++j)
        {
            std::cout << distance_entre_villes(instance, i, j) << "\t";
        }

        std::cout << std::endl;
    }

    if (instance.nb_villes > 10)
    {
        std::cout << "... matrice complete non affichee" << std::endl;
    }
}