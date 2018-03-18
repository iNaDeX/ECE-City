#ifndef VILLE_H_INCLUDED
#define VILLE_H_INCLUDED

#include <stdlib.h>
#include <stdio.h>

#include "case.h"
#include "collection_habitations.h"
#include "collection_chateau.h"
#include "collection_centrales.h"
#include "collection_casernes.h"
#include "terrain.h"
#include "date.h"
#include "graphismes.h"
#include "define.h"
#include "bfs.h"
#include "route.h"
#include "file_explorer.h"

typedef struct ville
{
    t_case*** terrain;

    t_collection_habitation* collec_habitations;
    t_collection_chateau* collec_chateaux;
    t_collection_centrale* collec_centrales;
    t_collection_casernes* collec_casernes;

    t_date* temps_de_jeu;
    int argent;
    int nb_habitants;
    t_capacite qte_eau;
    t_capacite qte_elec;
    clock_t timer;
    int pause;
    int niveau_visualisation;
    int mode;

    t_bfs data_bfs;
} t_ville;

void afficher_utilisations(t_ville* v);

void ville_afficher(t_ville* v, int bouton_boite_a_outil);

void ville_gerer(t_ville* v, int bouton_boite_a_outil);

t_ville* ville_allouer_initialiser(int mode_de_jeu);

void ville_charger(const char* nom_fichier,t_ville* v);

void ville_actualiser_timer(t_ville* v);

void ville_liberer(t_ville* v);

void ville_gerer_actions_utilisateur(t_ville* v, int bouton_boite_a_outils);

#endif // VILLE_H_INCLUDED
