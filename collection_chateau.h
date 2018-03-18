#ifndef COLLECTION_CHATEAU_H_INCLUDED
#define COLLECTION_CHATEAU_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>

#include "chateau.h"
#include "define.h"

typedef struct collection_chateau
{
    t_chateau** chateau;
    int taille_actuelle;
    int taille_max;
}t_collection_chateau;

t_collection_chateau* collection_chateau_creer();


void collection_chateau_distribuer_proche(t_collection_chateau* collection_chateau,t_collection_habitation* collection_habitation,int** longueurs);

void collection_chateau_distribuer(t_collection_chateau* collection_chateau,t_collection_habitation* collection_habitation,int** longueurs_chateaux_habitations);

void collection_chateau_distribuer_minimiser(t_collection_chateau* collection_chateau,t_collection_habitation* collection_habitation,int** longueur);

void collection_chateau_debut_tour(t_collection_chateau* collection_chateau);

int collection_chateau_eau_disponible(t_collection_chateau* collection_chateau);


void collection_chateau_ajouter_chateau(t_collection_chateau* collection_chateau,t_chateau* chateau);

void collection_chateau_reallouer(t_collection_chateau* collection_chateau);

void collection_chateau_afficher(t_collection_chateau* collection_chateau,int niveau);

void collection_chateau_liberer(t_collection_chateau* collection_chateau);

int** collection_chateau_tableau_longueurs(t_collection_chateau* collection_chateau,t_case*** kase,t_bfs* bfs,t_collection_habitation* collection_habitation);

int* collection_chateau_tableau_capacite(t_collection_chateau* collection_chateau);
#endif // COLLECTION_CHATEAU_H_INCLUDED
