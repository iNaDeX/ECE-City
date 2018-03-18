#ifndef COLLECTION_HABITATION_H_INCLUDED
#define COLLECTION_HABITATION_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>

#include "habitation.h"
#include "define.h"

typedef struct collection_habitation
{
    t_habitation** habitation;
    int taille_actuelle;
    int taille_max;
}t_collection_habitation;

t_collection_habitation* collection_habitation_creer();

void collection_habitation_trier(t_collection_habitation* collection_habitation);

void collection_habitation_actualiser_timer(t_collection_habitation* collection_habitation);

void collection_habitation_ajouter_habitation(t_collection_habitation* collection_habitation,t_habitation* habitation);

void collection_habitation_reallouer(t_collection_habitation* collection_habitation);

void collection_habitation_afficher(t_collection_habitation* collection_habitation,int niveau);

void collection_habitation_liberer(t_collection_habitation* collection_habitation);

void collection_habitation_debut_tour(t_collection_habitation* collection_habitation, int* nb_habitants);

void collection_habitation_evolution(t_collection_habitation* collection_habitation,int mode, int* argent,int nb_chateaux,int nb_centrales,int** longueurs_chateaux,int** longueurs_centrales,int* capacite_chateaux,int* capacite_centrale);

int collection_habitation_nombre_habitants(t_collection_habitation* collection_habitation);

#endif // COLLECTION_HABITATION_H_INCLUDED
