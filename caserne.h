#ifndef CASERNE_H_INCLUDED
#define CASERNE_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>

#include "compalleg.h"
#include "graphismes.h"
#include "case.h"
#include "define.h"

typedef struct caserne
{
    int case_de_referenceX;
    int case_de_referenceY;
    int temps_de_rechargement; // permettra de savoir si les pompiers sont disponibles
    int occupe; // permettra de savoir si les pompiers sont disponibles
} t_caserne;


t_caserne* caserne_creer();

void caserne_afficher(t_caserne* caserne,int niveau);

void caserne_liberer(t_caserne*);

int caserne_depassement_matrice(int colonne,int ligne);

int caserne_place_libre(int x,int y,t_case*** kase);

void caserne_placer(t_caserne* caserne,int x,int y,t_case*** kase);

#endif // CASERNE_H_INCLUDED
