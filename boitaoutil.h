#ifndef BOITAOUTIL_H_INCLUDED
#define BOITAOUTIL_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>

#include "compalleg.h"
#include "define.h"

//géométrie de la boite

#define COORDX 10
#define COORDY 56
#define LARGEUR_CASE 50
#define TAILLE_BORDS 2
#define NB_BOUTONS_H 10
#define NB_BOUTONS_W 1
//#define NB_BOUTONS 5
#define COUL_BORD makecol(140,140,140)
#define COUL_FOND makecol(180,180,180)

typedef struct boiteaoutils
{
    int x; //coordonnées d'affichage de la boite à outils
    int y; //coordonnées d'affichage de la boite à outils
    int bouton_choisi;
    int matbouton[NB_BOUTONS_H][NB_BOUTONS_W];
    BITMAP *img_bouton_off[NB_BOUTONS_H][NB_BOUTONS_W];
    BITMAP *img_bouton_on[NB_BOUTONS_H][NB_BOUTONS_W];
}t_boite_a_outils;

t_boite_a_outils* boiteaoutils_creer();

void boiteaoutils_reinitialiser_boutons_uniques(t_boite_a_outils* boiteaoutils);

void boiteaoutils_chargerimages(t_boite_a_outils* boiteaoutils);

void boiteaoutils_afficher(t_boite_a_outils* boiteaoutils);

void boiteaoutils_gerer(t_boite_a_outils* boiteaoutils);

void boiteaoutils_liberer(t_boite_a_outils* boiteaoutils);


#endif // BOITAOUTIL_H_INCLUDED
