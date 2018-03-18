#ifndef LISTE_GENERIQUE_SIMPLE_CHAINAGE_H_INCLUDED
#define LISTE_GENERIQUE_SIMPLE_CHAINAGE_H_INCLUDED

#include "define.h"

// Ceci est un module de liste générique, à simple chainage et double ancrage.

// Pour l'utiliser correctement, il faut juste appeler les fonctions listées ci dessous.
// Il faudra bien entendu coder un module correspondant aux traitements à effectuer sur les éléments
// par exemple pour une liste chainée de films, il faudra coder le module "film" (film_creer, film_afficher etc..)

// Attention, certaines fonctions nécessitent de recevoir une fonction en paramètre
// par exemple: void liste_afficher(t_liste* lst, tpf_afficher afficher);
// Il est logique que pour afficher chaque élément de la liste, il faut avoir une fonction qui se charge d'afficher 1 élément.
// Cette fonction doit être transmise en paramètre.
// L'appel à liste_afficher pour afficher des points par exemple sera:
// liste_afficher(maliste, (tpf_afficher)point_afficher);
// avec point_afficher le nom de la fonction qui affiche 1 point.
// dont le prototype serait par exemple:
// void point_afficher(t_point* p);

/*
Par rapport à une liste simple chainage double ancrage, une liste double chainage double ancrage aurait permis:

- un accès à l'élément précédent efficace.
- une suppression en queue efficace.

*/

// Inclusion des librairies nécessaires au fonctionnement du module
#include <stdio.h>
#include <stdlib.h>

/// Définition des structures
typedef struct maillon
{
    void* elem;
    struct maillon* p_suiv;
}t_maillon;

typedef struct liste
{
    int longueur;
    struct maillon* p_tete;
    struct maillon* p_queue;
    struct maillon* p_courant;
}t_liste;

/// Alias pour les pointeurs de fonction
typedef void  (*tpf_detruire) (void*);
typedef void* (*tpf_copier)   (void*);
typedef void  (*tpf_afficher) (void*);
typedef int   (*tpf_trier)    (const void*, const void*);
typedef int   (*tpf_recherche)(void*);

/// Prototypes

// Constructeur
t_liste* liste_creer();

// Destructeur
void liste_detruire(t_liste* lst, tpf_detruire detruire);

// Vider la liste sans la détruire
void liste_vider(t_liste* lst, tpf_detruire detruire);

// Constructeur par copie
t_liste* liste_copier(t_liste* lst, tpf_copier copier);

// Ajout d'élément en tête
void liste_ajout_tete(t_liste* lst, void* elem);

// Ajout d'élément en queue
void liste_ajout_queue(t_liste* lst, void* elem);

// Nombre d'éléments référencés
int liste_taille(t_liste* lst);

// Retourne 1 (Vrai) si la liste est vide
int liste_vide(t_liste* lst);

// Accès élément en tête
void* liste_elem_tete(t_liste* lst);

// Accès élément en queue
void* liste_elem_queue(t_liste* lst);

// Accès élément courant
void* liste_elem_courant(t_liste* lst);

// On retire la tête de la liste, et on retourne la donnée qu'elle pointait.
void* liste_recup_tete(t_liste* lst);

// On retire la queue de la liste, et on retourne la donnée qu'elle pointait.
// PAS EFFICACE ICI CAR SIMPLE CHAINAGE
void* liste_recup_queue(t_liste* lst);

// Supprime l'élément de tête
void liste_supprimer_tete(t_liste* lst, tpf_detruire detruire);

// Initialiser un parcours
void liste_demarrer(t_liste* lst);

// Il reste encore des éléments à parcourir
int liste_encore(t_liste* lst);

// Déplacement du courant au suivant
void liste_suivant(t_liste* lst);

// Affichage bilan allocations/libérations
void liste_bilan();

////////////////////////////////////////////////////////
/* Petites fonctions supplémentaires*/

// Affiche les éléments de la liste, dans l'ordre tete --> queue
void liste_afficher(t_liste* lst, tpf_afficher afficher);

// Ajoute lst2 à la suite (en queue) de lst1 (copie les éléments de lst2, et les rajoute à lst1.
// Lst2 garde ses élements (Lst2 reste inchangée)
void liste_fusionner(t_liste* lst1, t_liste* lst2, tpf_copier copier);

// Supprime l'élément de queue de la liste (PAS EFFICACE CAR SIMPLE CHAINAGE ICI)
void liste_supprimer_queue(t_liste* lst, tpf_detruire detruire);

// Trie les élements d'une liste, en fonction du résultat retourné par la fonction de comparaison des élements
// on évitera de trier tout le temps, on préférera l'ajout trié.
void liste_trier(t_liste* lst, tpf_trier trier);

// ajout trié dans la liste ( = ajout à la bonne position selon une fonction de comparaison)
void liste_ajout_trie(t_liste* lst, void* elem, tpf_trier trier);

// Recherche dans la liste tous les maillons contenant les données demandées
// (via une fonction element_rechercher, qui analyse un maillon et dit si ce maillon est intéressant)
// Afin de gérer le cas où plusieurs élements contiendraient les mêmes données
// -> on retourne une liste chainée de pointeurs sur éléments trouvés :)
// ATTENTION, la liste retournée est une liste de REFERENCES vers des éléments existant dans lst.
// les éléments de la liste retournée sont CEUX de lst.
// ce ne sont PAS des copies.
t_liste* liste_rechercher(t_liste* lst, tpf_recherche recherche);

// On recoit un élément forcément dans la liste, qu'on veut supprimer
// puis on parcourt la liste jusqu'à tomber dessus, et on le supprime, peu importe sa position (tete,milieu,queue)
void liste_supprimer_precis(t_liste* lst, void* elem, tpf_detruire detruire);

// On recoit la liste dont il faut supprimer certains éléments, et une liste référençant tous les éléments à supprimer.
// On va chercher les éléments de lst_elem_a_supprimer DANS lst, et quand on tombe dessus on les supprime.
void liste_supprimer_partie(t_liste* lst, t_liste* lst_elem_a_supprimer, tpf_detruire detruire);

// Supprime le maillon de tête de liste, sans détruire la donnée pointée
void liste_dereferencer_tete(t_liste* lst);

// Supprime tous les maillons de la liste, sans détruire les données pointées
void liste_dereferencer(t_liste* lst);

// Ajoute dans la liste l'élement à insérer juste avant l'élément de référence
void liste_ajout_avant(t_liste* lst, void* elem_a_inserer, void* elem_ref);

/*
Tester tous les scénarios

Résoudre problème qsort liste_trier
Ameliorer la fonction liste_rechercher : paramètre facultatif à rajouter
Coder liste_traiter_chaque
*/

#endif // LISTE_GENERIQUE_SIMPLE_CHAINAGE_H_INCLUDED
