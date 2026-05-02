#pragma once

#include "tsp.h"

void initialiser_solution(Solution & solution);

void liberer_solution(Solution & solution);

void methode_glouton(const InstanceTSP & instance, Solution & solution, int depart);

void afficher_solution(const Solution & solution);
