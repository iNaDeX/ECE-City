#ifndef MENU_H_INCLUDED
#define MENU_H_INCLUDED

#include "define.h"
#include "editeur.h"
#include "ville.h"
#include "compalleg.h"
#include "file_explorer.h"

#define NB_BOUTONS 5

#define MENU_BOUTON_NOUVEAU 0
#define MENU_BOUTON_CHARGER 1
#define MENU_BOUTON_CREDITS 2
#define MENU_BOUTON_QUITTER 3
#define MENU_BOUTON_RETOUR 4

#define NB_BOUTONS_SOUS_MENU 2
#define NB_IMG_OISEAU 15
#define SOUS_MENU_COMMUNISTE 0
#define SOUS_MENU_CAPITALISTE 1

typedef struct graphsousMenu
{
    BITMAP* img_boutons_on[NB_BOUTONS_SOUS_MENU];
    BITMAP* img_boutons_off[NB_BOUTONS_SOUS_MENU];
    BITMAP* fond;
    BITMAP* oiseau[NB_IMG_OISEAU];
    int boutons_x[NB_BOUTONS_SOUS_MENU];
    int boutons_y[NB_BOUTONS_SOUS_MENU];
}t_graphsousMenu;

typedef struct graphMenu // on déclarera une instance de t_graphMenu dans le main
{
    BITMAP* cursor;
    BITMAP* fond;
    BITMAP* contenu_credits;

    BITMAP* img_boutons_on[NB_BOUTONS];
    BITMAP* img_boutons_off[NB_BOUTONS];

    SAMPLE* music;

    t_graphsousMenu graphsdusousmenu;

    int boutons_x[NB_BOUTONS];
    int boutons_y[NB_BOUTONS];

}t_graphMenu;

// libère les bitmaps du menu, à la fin du programme.
void menu_liberer(t_graphMenu* graph);

// charge les informations du menu
void menu_charger(t_graphMenu* graph);

// affiche le menu
void menu_afficher(t_graphMenu graph);

// affichage du sous-menu a propos
void menu_afficher_credits(t_graphMenu graph);

void menu_boucle_jeu(int mode_choisi,const char* nom_fichier);

int menu_selection_mode(t_graphMenu graph);

void sous_menu_liberer(t_graphsousMenu* g);

void sous_menu_charger(t_graphsousMenu* g);

#endif // MENU_H_INCLUDED
