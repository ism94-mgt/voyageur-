#include <iostream>
#include "tsp.h"

void initialiser_instance(InstanceTSP & instance)
{
    instance.nom = "";
    instance.nb_villes = 0;
    instance.type_distance = "";

    for (int i = 0; i < VMAX; ++i)
    {
        instance.villes[i].num = 0;
        instance.villes[i].x = 0;
        instance.villes[i].y = 0;

        for (int j = 0; j < VMAX; ++j)
        {
            instance.distances[i][j] = 0;
        }
    }
}

void afficher_instance(const InstanceTSP & instance)
{
    std::cout << "Nom : " << instance.nom << std::endl;
    std::cout << "Nombre de villes : " << instance.nb_villes << std::endl;
    std::cout << "Type de distance : " << instance.type_distance << std::endl;

    std::cout << "Villes :" << std::endl;

    for (int i = 0; i < instance.nb_villes; ++i)
    {
        std::cout << instance.villes[i].num << " "
                  << instance.villes[i].x << " "
                  << instance.villes[i].y << std::endl;
    }
}