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

using Tabvilles = std::array<Ville, NMAX>;
using Matricedistances = std::array<std::array<int, NMAX>, NMAX>;
using Tournee = std::array<int, NMAX>;

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