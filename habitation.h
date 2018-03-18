#ifndef HABITATION_H_INCLUDED
#define HABITATION_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "case.h"
#include "define.h"
#include "graphismes.h"

typedef struct habitation
{
    int stade;
    int case_de_referenceX;
    int case_de_referenceY;
    float chrono;
    int feu;
    int electricite;
    int protegee;
    int indice;
    int eau;
    t_id id_centrale_fournisseuse;
    t_fournisseur* chateaux_fournisseurs;
}t_habitation;

typedef struct capacite
{
    int capacite_max;
    int capacite_disponible;
}t_capacite;

void habitation_progression(t_habitation* habitation);

void habitation_regression(t_habitation* habitation);

t_habitation* habitation_creer();

int habitation_place_libre(int,int,t_case***);

void habitation_placer(t_habitation*,int,int,t_case***);

void habitation_actualiser_timer(t_habitation* habitation);

int habitation_depassement_matrice(int colonne,int ligne);

int habitation_nbhabitants(t_habitation* habitation);

void habitation_liberer(t_habitation*);

int habitation_comparer(const void* a, const void* b);

void habitation_afficher(t_habitation* hab,int niveau);

int habitation_recolter_impots(t_habitation* hab);

void habitation_evoluer(t_habitation* habitation,int mode,int* argent,int nb_chateaux,int nb_centrales,int** longueurs_chateaux,int** longueurs_centrales,int* capacite_chateau,int* capacite_centrale);

void habitation_evolution_communiste(t_habitation* habitation,int nb_chateaux,int nb_centrales,int** longueurs_chateaux,int** longueurs_centrales,int* capacite_chateaux,int* capacite_centrale);

void habitation_evolution_capitaliste(t_habitation* habitation,int nb_chateaux,int nb_centrales,int** longueurs_chateaux,int** longueurs_centrales);

void habitation_debut_tour(t_habitation* hab);

void habitation_sauvegarder(t_habitation* hab, FILE* fp);

void habitation_charger(t_habitation* hab, FILE* fp);

#endif // HABITATION_H_INCLUDED
