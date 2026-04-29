#pragma once

#include <array>
#include <string>

const int VMAX = 100;

struct Ville
{
    int num;
    double x;
    double y;
};

using TabVilles = std::array<Ville, VMAX>;
using MatriceDistances = std::array<std::array<int, VMAX>, VMAX>;
using Tournee = std::array<int, VMAX>;

struct InstanceTSP
{
    std::string nom;
    int nb_villes;
    std::string type_distance;

    TabVilles villes;
    MatriceDistances distances;
};

struct Solution
{
    Tournee ordre;
    int nb_villes;
    double longueur;
};

void initialiser_instance(InstanceTSP & instance);

void afficher_instance(const InstanceTSP & instance);

int distance_entre_villes(const InstanceTSP & instance, int i, int j);

double longueur_tournee(const InstanceTSP & instance, const Solution & solution);