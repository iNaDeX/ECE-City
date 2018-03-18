#ifndef COLLECTION_CENTRALE_H_INCLUDED
#define COLLECTION_CENTRALE_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>

#include "centrale.h"
#include "collection_habitations.h"
#include "define.h"

typedef struct collection_centrale
{
    t_centrale** centrale;
    int taille_actuelle;
    int taille_max;
}t_collection_centrale;

t_collection_centrale* collection_centrale_creer();

void collection_centrale_ajouter_centrale(t_collection_centrale* collection_centrale,t_centrale* centrale);

void collection_centrale_reallouer(t_collection_centrale* collection_centrale);

void collection_centrale_afficher(t_collection_centrale* collection_centrale,int niveau_de_visualisation);

void collection_centrale_liberer(t_collection_centrale* collection_centrale);

void collection_centrale_distribuer(t_collection_centrale* collection_centrale,t_collection_habitation* collection_habitation,int** longueurs);

int** collection_centrale_tableau_longueurs(t_collection_centrale* collection_centrale,t_case*** kase,t_bfs* bfs,t_collection_habitation* collection_habitation);

void collection_centrale_debut_tour(t_collection_centrale* collection_centrale);

int collection_centrale_elec_disponible(t_collection_centrale* collection_centrale);

int* collection_centrale_tableau_capacite(t_collection_centrale* collection_centrale);

#endif // COLLECTION_CENTRALE_H_INCLUDED
