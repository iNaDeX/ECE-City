#ifndef CHATEAU_H_INCLUDED
#define CHATEAU_H_INCLUDED

#include <stdio.h>

#include "habitation.h"
#include "bfs.h"
#include "define.h"
#include "compalleg.h"
#include "graphismes.h"

typedef struct chateau
{
    t_capacite capacite;
    int case_de_referenceX;
    int case_de_referenceY;
    t_id id_chateau;
}t_chateau;

t_chateau* chateau_creer();

void chateau_liberer(t_chateau*);

int chateau_depassement_matrice(int colonne,int ligne);

int chateau_place_libre(int x,int y,t_case*** kase);

void chateau_placer(t_chateau* chateau,int x,int y,t_case*** kase);

void chateau_afficher(t_chateau* chateau,int niveau);

int chateau_distribuer(t_chateau* chateau,t_habitation* habitation);

void chateau_debut_tour(t_chateau* chateau);

int chateau_eau_disponible(t_chateau* chateau);

#endif // CHATEAU_H_INCLUDED
