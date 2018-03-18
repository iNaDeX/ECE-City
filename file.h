#ifndef FILE_H_INCLUDED
#define FILE_H_INCLUDED

//#include "memcheck.h"

// Ceci est un module de file g�n�rique.

// Pour l'utiliser correctement, il faut juste appeler les fonctions list�es ci dessous.
// Il faudra bien entendu coder un module correspondant aux traitements � effectuer sur les �l�ments
// par exemple pour une file de films, il faudra coder le module "film" (film_creer, film_afficher etc..)

/*// Attention, certaines fonctions n�cessitent de recevoir une fonction en param�tre
// par exemple: t_file* file_copier(t_file* file, tpf_copier copier);
// Il est logique que pour copier chaque �l�ment de la file
// il faut avoir une fonction qui se charge de copier 1 �l�ment.
// Cette fonction doit �tre transmise en param�tre.
// L'appel � file_copier sera donc par exemple:
// file_copier(mafile, (tpf_copier)point_copier);
// avec point_copier le nom de la fonction qui copie 1 point.
// dont le prototype serait par exemple:
// t_point* point_copier(t_point* p);
*/

//On inclut les librairies standard
#include <stdio.h>
#include <stdlib.h>

// On inclut la libraire liste_generique_simple_chainage
// En effet ce module de file g�n�rique repose sur une impl�mentation en liste
#include "liste_generique_simple_chainage.h"

// On cr�e un alias du type t_liste, c'est � dire qu'on le renomme en t_file pour une coh�rence logique
// Ainsi l'utilisateur du module n'utilisera pas le type t_liste ni le mot "liste" dans son code.
typedef t_liste t_file;

// Alloue une file
t_file* file_creer();

// D�truit une file
void file_detruire(t_file* file, tpf_detruire detruire);

// Vide une file
void file_vider(t_file* file, tpf_detruire detruire);

// Enfile ( = ajoute ) un �l�ment � la file
void file_enfiler(t_file* file, void* elem);

// D�file ( = retire ) un �l�ment � la file
void* file_defiler(t_file* file);

// Retourne l'�l�ment du sommet de la file, sans le retirer de la file
void* file_elem_sommet(t_file* file);

// Retourne 1 si la file est vide, 0 sinon
int file_vide(t_file* file);

// Retourne une copie (profonde) de la file re�ue en param�tre
t_file* file_copier(t_file* file,tpf_copier copier);

// Retourne le nombre d'�l�ments de la file
int file_taille(t_file* file);

// Affichage bilan allocations/lib�rations
void file_bilan(t_file* file);


#endif // FILE_H_INCLUDED
