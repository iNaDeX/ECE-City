#ifndef EDITEUR_H_INCLUDED
#define EDITEUR_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>

#include "ville.h"
#include "boitaoutil.h"

#include "define.h"


typedef struct editeur
{
    t_ville* maville;
    t_boite_a_outils* boite_a_outils;
} t_editeur;

t_editeur* editeur_allouer(int mode_de_jeu);

void editeur_gerer(t_editeur* ed);

void editeur_afficher(t_editeur* ed);

void editeur_liberer(t_editeur* ed);

#endif // EDITEUR_H_INCLUDED
