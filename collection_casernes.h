#ifndef COLLECTION_CASERNES_H_INCLUDED
#define COLLECTION_CASERNES_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>

#include "caserne.h"
#include "habitation.h"
#include "bfs.h"
#include "define.h"

typedef struct collection_casernes
{
    t_caserne** caserne;
    int taille_actuelle;
    int taille_max;
}t_collection_casernes;


t_collection_casernes* collection_casernes_creer();

void collection_casernes_ajouter_caserne(t_collection_casernes* collection_casernes,t_caserne* caserne);

void collection_casernes_reallouer(t_collection_casernes* collection_casernes);

void collection_casernes_afficher(t_collection_casernes* collection_casernes,int niveau);

void collection_casernes_liberer(t_collection_casernes* collection_casernes);

void collection_casernes_proteger(t_collection_casernes* collection_casernes,t_collection_habitation* collection_habitation,int** longueurs);

int** collection_casernes_tableau_longueurs(t_collection_casernes* collection_casernes,t_case*** kase,t_bfs* bfs,t_collection_habitation* collection_habitation);

#endif // COLLECTION_CASERNES_H_INCLUDED
