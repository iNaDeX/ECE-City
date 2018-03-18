#include "collection_routes.h"

t_collection_route* collection_route_creer()
{
    t_collection_route* nouv;
    nouv=malloc(sizeof(t_collection_route));
    nouv->taille_actuelle=0;
    nouv->taille_max=10;
    nouv->route=malloc(nouv->taille_max*sizeof(t_route*));
    return nouv;
}

void collection_route_ajouter_route(t_collection_route* collection_route,t_route* new_route)
{
    if(collection_route->taille_actuelle==collection_route->taille_max)
    {
        collection_route_reallouer(collection_route);
    }
    collection_route->route[collection_route->taille_actuelle]=new_route;
    collection_route->taille_max++;
}

void collection_route_liberer(t_collection_route* collection_route)
{
    int i;

    for(i=0;i<collection_route->taille_max;i++)
    {
        route_liberer(collection_route->route[i]);
    }
    free(collection_route);
}

void collection_route_reallouer(t_collection_route* collection_route)
{
    collection_route->taille_max=3*collection_route->taille_max/2;
    collection_route->route=realloc(collection_route->route,collection_route->taille_max*sizeof(t_route*));
}

void collection_route_afficher(t_collection_route* collection_route)
{
    int i;
    for(i=0;i<collection_route->taille_actuelle;i++)
    {
        route_afficher(collection_route->route[i]);
    }
}
