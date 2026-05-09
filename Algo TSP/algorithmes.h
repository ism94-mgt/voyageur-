#pragma once

#include "tsp.h"

struct Solution
{
    int * ordre;
    int nb_villes;
    double longueur;
};

void initialiser_solution(Solution & solution);

void liberer_solution(Solution & solution);

void methode_glouton(const InstanceTSP & instance, Solution & solution, int depart);

void afficher_solution(const Solution & solution);