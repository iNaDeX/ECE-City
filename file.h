#ifndef FILE_H_INCLUDED
#define FILE_H_INCLUDED

//#include "memcheck.h"

// Ceci est un module de file générique.

// Pour l'utiliser correctement, il faut juste appeler les fonctions listées ci dessous.
// Il faudra bien entendu coder un module correspondant aux traitements à effectuer sur les éléments
// par exemple pour une file de films, il faudra coder le module "film" (film_creer, film_afficher etc..)

/*// Attention, certaines fonctions nécessitent de recevoir une fonction en paramètre
// par exemple: t_file* file_copier(t_file* file, tpf_copier copier);
// Il est logique que pour copier chaque élément de la file
// il faut avoir une fonction qui se charge de copier 1 élément.
// Cette fonction doit être transmise en paramètre.
// L'appel à file_copier sera donc par exemple:
// file_copier(mafile, (tpf_copier)point_copier);
// avec point_copier le nom de la fonction qui copie 1 point.
// dont le prototype serait par exemple:
// t_point* point_copier(t_point* p);
*/

//On inclut les librairies standard
#include <stdio.h>
#include <stdlib.h>

// On inclut la libraire liste_generique_simple_chainage
// En effet ce module de file générique repose sur une implémentation en liste
#include "liste_generique_simple_chainage.h"

// On crée un alias du type t_liste, c'est à dire qu'on le renomme en t_file pour une cohérence logique
// Ainsi l'utilisateur du module n'utilisera pas le type t_liste ni le mot "liste" dans son code.
typedef t_liste t_file;

// Alloue une file
t_file* file_creer();

// Détruit une file
void file_detruire(t_file* file, tpf_detruire detruire);

// Vide une file
void file_vider(t_file* file, tpf_detruire detruire);

// Enfile ( = ajoute ) un élément à la file
void file_enfiler(t_file* file, void* elem);

// Défile ( = retire ) un élément à la file
void* file_defiler(t_file* file);

// Retourne l'élément du sommet de la file, sans le retirer de la file
void* file_elem_sommet(t_file* file);

// Retourne 1 si la file est vide, 0 sinon
int file_vide(t_file* file);

// Retourne une copie (profonde) de la file reçue en paramètre
t_file* file_copier(t_file* file,tpf_copier copier);

// Retourne le nombre d'éléments de la file
int file_taille(t_file* file);

// Affichage bilan allocations/libérations
void file_bilan(t_file* file);


#endif // FILE_H_INCLUDED
