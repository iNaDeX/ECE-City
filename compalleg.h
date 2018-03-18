#ifndef GRAPHIQUES_H_INCLUDED
#define GRAPHIQUES_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>

#include "allegro.h"

#include "define.h"

/// Constantes

// Couleur initiale :
// 255,255,255 pour du blanc    0,0,0 pour du noir...
#define PAGE_COULEUR_INIT makecol(0,0,0)


/// Variables globales : visibles partout o� compalleg.h est inclus

// Le buffer sur lequel tout est dessin�
extern BITMAP *page;

// Couleur de fond du buffer page, modifiable � tout moment
// Exemple   page_couleur_fond = makecol( 0, 255, 0); // fond vert !
extern int page_couleur_fond;

/// Les globales suivantes n�cessitent un appel � rafraichir_clavier_souris
/// en d�but de boucle d'interaction pour �tre mises � jour � chaque tour de boucle

// La touche appuy�e depuis le dernier tour de boucle
// '\0' si aucun bouton appuy� au dernier tour de boucle
extern char touche;

// Le bouton souris appuy� depuis le dernier tour de boucle
// 'g' pour gauche, 'd' pour droit, 'm' pour milieu, '\0' pour aucun
extern char bouton;

// Le clic souris depuis le dernier tour de boucle
// s'utilise comme mouse_b mais contrairement � mouse_b
// n'est valable que pendant un tour de boucle (pas de r�p�tition)
// mouse_click&1 pour clic gauche, mouse_click&2 pour clic droit
extern int mouse_click;

// Le rel�chement du clic souris depuis le dernier tour de boucle
// d�tecte le passage de l'�tat enfonc� � l'�tat rel�ch�
// n'est valable que pendant un tour de boucle (pas de r�p�tition)
// mouse_unclick&1 pour clic gauche, mouse_unclick&2 pour clic droit
extern int mouse_unclick;

// M�me principe que key mais d�tecte les transitions (press�<->non press�)
// valable pendant un seul tour de boucle (pas de r�p�tition)
// exemple : if (key_unpress[KEY_RIGHT]) printf("touche droite relachee !\n");
extern int key_press[KEY_MAX];
extern int key_unpress[KEY_MAX];

// D�placement relatif de la souris depuis le dernier tour de boucle
extern int mouse_depx;
extern int mouse_depy;

/// Lancement et fermeture services Allegro

// A appeler une fois et une seule en d�but de main (apr�s les d�clarations)
void initialiser_allegro(int w, int h);

// Pour lib�rer le buffer et fermer tous les services
// pas indispensable : la fin du programme ferme et lib�re tout automatiquement
void fermer_allegro();


/// Buffer et sorties graphiques

// Efface le buffer (utilise page_couleur_fond)
// A appeler une fois dans la boucle d'interaction
// avant de redessiner le dessin (et �ventuellement
// autre chose apr�s)
void effacer_page();

// Affiche la page effectivement � l'�cran
// A appeler une fois dans la boucle d'interaction
// A LA FIN JUSTE AVANT rest(10);
void afficher_page();

// M�me proc�dure que line pour allegro, 3 pixels de large
void line_epaisse(BITMAP *bmp, int x1, int y1, int x2, int y2, int coul);

BITMAP *chargerImage(const char* nomFichierImage);

void changer_nom_fenetre(const char* ch);

SAMPLE* chargerSon(const char* nomfichier);

/// Entr�es clavier/souris

// un appel � rafraichir_clavier_souris doit �tre fait
// en d�but de boucle d'interaction pour mettre � jour les globales
void rafraichir_clavier_souris();

#endif // GRAPHIQUES_H_INCLUDED
