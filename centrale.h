#ifndef CENTRALE_H_INCLUDED
#define CENTRALE_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>

#include "habitation.h"
#include "bfs.h"
#include "define.h"
#include "compalleg.h"
#include "graphismes.h"

typedef struct centrale
{
    t_capacite capacite;
    int case_de_referenceX;
    int case_de_referenceY;
    t_id id_centrale;
}t_centrale;

t_centrale* centrale_creer();

void centrale_liberer(t_centrale*);

int centrale_depassement_matrice(int colonne,int ligne);

void centrale_distribuer(t_centrale* centrale,t_habitation* habitation,int quantitee);

int centrale_place_libre(int x,int y,t_case*** kase);

void centrale_placer(t_centrale* centrale,int x,int y,t_case*** kase);

void centrale_afficher(t_centrale* centrale,int niveau);

void centrale_debut_tour(t_centrale* centrale);

int centrale_elec_disponible(t_centrale* centrale);

#endif // CENTRALE_H_INCLUDED
