#pragma once

#include <string>

struct Ville
{
    int num;
    double x;
    double y;
};

struct InstanceTSP
{
    std::string nom;
    int nb_villes;
    std::string type_distance;
    bool possede_coordonnees;
    Ville * villes;
    double * distances;
};

void initialiser_instance(InstanceTSP & instance);

void allouer_instance(InstanceTSP & instance, int nb_villes);

void liberer_instance(InstanceTSP & instance);

bool lire_instance(std::string nom_fichier, InstanceTSP & instance);

void afficher_instance(const InstanceTSP & instance);

double distance_entre_villes(const InstanceTSP & instance, int i, int j);

void modifier_distance(InstanceTSP & instance, int i, int j, double distance);

