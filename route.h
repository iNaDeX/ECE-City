#ifndef ROUTE_H_INCLUDED
#define ROUTE_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>

#include "case.h"
#include "define.h"
#include "graphismes.h"

typedef struct route
{
    int type;
    int case_de_referenceX;
    int case_de_referenceY;
}t_route;

t_route* route_creer();

void route_liberer(t_route* route);

int route_place_libre(int colonne,int ligne,t_case*** kase);

void route_placer(t_route* route,int colonne,int ligne,t_case*** kase);

int route_depassement_matrice(int colonne,int ligne);

void route_actualiser(t_route* route,t_case*** kase);

void route_actualiser_voisins(t_route* route,t_case*** kase);

void route_afficher(t_route* route,int niveau);

#endif // ROUTE_H_INCLUDED
