#ifndef COLLECTION_ROUTES_H_INCLUDED
#define COLLECTION_ROUTES_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include "route.h"

typedef struct collection_route
{
    t_route** route;
    int taille_actuelle;
    int taille_max;
}t_collection_route;

t_collection_route* collection_route_creer();

void collection_route_ajouter_route(t_collection_route* collection_route,t_route* route);

void collection_route_reallouer(t_collection_route* collection_route);

void collection_route_afficher(t_collection_route* collection_route);

void collection_route_liberer(t_collection_route* collection_route);

#endif // COLLECTION_ROUTES_H_INCLUDED
