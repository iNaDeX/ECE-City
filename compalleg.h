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


/// Variables globales : visibles partout où compalleg.h est inclus

// Le buffer sur lequel tout est dessiné
extern BITMAP *page;

// Couleur de fond du buffer page, modifiable à tout moment
// Exemple   page_couleur_fond = makecol( 0, 255, 0); // fond vert !
extern int page_couleur_fond;

/// Les globales suivantes nécessitent un appel à rafraichir_clavier_souris
/// en début de boucle d'interaction pour être mises à jour à chaque tour de boucle

// La touche appuyée depuis le dernier tour de boucle
// '\0' si aucun bouton appuyé au dernier tour de boucle
extern char touche;

// Le bouton souris appuyé depuis le dernier tour de boucle
// 'g' pour gauche, 'd' pour droit, 'm' pour milieu, '\0' pour aucun
extern char bouton;

// Le clic souris depuis le dernier tour de boucle
// s'utilise comme mouse_b mais contrairement à mouse_b
// n'est valable que pendant un tour de boucle (pas de répétition)
// mouse_click&1 pour clic gauche, mouse_click&2 pour clic droit
extern int mouse_click;

// Le relâchement du clic souris depuis le dernier tour de boucle
// détecte le passage de l'état enfoncé à l'état relâché
// n'est valable que pendant un tour de boucle (pas de répétition)
// mouse_unclick&1 pour clic gauche, mouse_unclick&2 pour clic droit
extern int mouse_unclick;

// Même principe que key mais détecte les transitions (pressé<->non pressé)
// valable pendant un seul tour de boucle (pas de répétition)
// exemple : if (key_unpress[KEY_RIGHT]) printf("touche droite relachee !\n");
extern int key_press[KEY_MAX];
extern int key_unpress[KEY_MAX];

// Déplacement relatif de la souris depuis le dernier tour de boucle
extern int mouse_depx;
extern int mouse_depy;

/// Lancement et fermeture services Allegro

// A appeler une fois et une seule en début de main (après les déclarations)
void initialiser_allegro(int w, int h);

// Pour libérer le buffer et fermer tous les services
// pas indispensable : la fin du programme ferme et libère tout automatiquement
void fermer_allegro();


/// Buffer et sorties graphiques

// Efface le buffer (utilise page_couleur_fond)
// A appeler une fois dans la boucle d'interaction
// avant de redessiner le dessin (et éventuellement
// autre chose après)
void effacer_page();

// Affiche la page effectivement à l'écran
// A appeler une fois dans la boucle d'interaction
// A LA FIN JUSTE AVANT rest(10);
void afficher_page();

// Même procédure que line pour allegro, 3 pixels de large
void line_epaisse(BITMAP *bmp, int x1, int y1, int x2, int y2, int coul);

BITMAP *chargerImage(const char* nomFichierImage);

void changer_nom_fenetre(const char* ch);

SAMPLE* chargerSon(const char* nomfichier);

/// Entrées clavier/souris

// un appel à rafraichir_clavier_souris doit être fait
// en début de boucle d'interaction pour mettre à jour les globales
void rafraichir_clavier_souris();

#endif // GRAPHIQUES_H_INCLUDED
