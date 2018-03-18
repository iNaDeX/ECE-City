#ifndef GRAPHISMES_H_INCLUDED
#define GRAPHISMES_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>

#include "compalleg.h"
#include "define.h"

/// ne contient que les images du jeu, PAS du menu NI de la boite à outils
typedef struct graphismes
{
    BITMAP* buffer_ville;
    BITMAP* fond_herbe;
    BITMAP* grille;

    BITMAP* route[NB_NIVEAUX][NB_IMG_ROUTES];

    BITMAP* terrain_vague;
    BITMAP* ruine;
    BITMAP* pompier;

    BITMAP* cabane[NB_IMG_CABANES];
    BITMAP* maison[NB_IMG_MAISONS];
    BITMAP* immeuble[NB_IMG_IMMEUBLES];
    BITMAP* gratte_ciel[NB_IMG_GRATTECIELS];

    BITMAP* chateau;
    BITMAP* centrale;
    BITMAP* caserne;
}t_graphismes;

extern t_graphismes* graphs;

t_graphismes* graphismes_charger();

void graphismes_liberer(t_graphismes* graph);

#endif // GRAPHISMES_H_INCLUDED
