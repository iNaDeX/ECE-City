#ifndef LISTE_GENERIQUE_SIMPLE_CHAINAGE_H_INCLUDED
#define LISTE_GENERIQUE_SIMPLE_CHAINAGE_H_INCLUDED

#include "define.h"

// Ceci est un module de liste g�n�rique, � simple chainage et double ancrage.

// Pour l'utiliser correctement, il faut juste appeler les fonctions list�es ci dessous.
// Il faudra bien entendu coder un module correspondant aux traitements � effectuer sur les �l�ments
// par exemple pour une liste chain�e de films, il faudra coder le module "film" (film_creer, film_afficher etc..)

// Attention, certaines fonctions n�cessitent de recevoir une fonction en param�tre
// par exemple: void liste_afficher(t_liste* lst, tpf_afficher afficher);
// Il est logique que pour afficher chaque �l�ment de la liste, il faut avoir une fonction qui se charge d'afficher 1 �l�ment.
// Cette fonction doit �tre transmise en param�tre.
// L'appel � liste_afficher pour afficher des points par exemple sera:
// liste_afficher(maliste, (tpf_afficher)point_afficher);
// avec point_afficher le nom de la fonction qui affiche 1 point.
// dont le prototype serait par exemple:
// void point_afficher(t_point* p);

/*
Par rapport � une liste simple chainage double ancrage, une liste double chainage double ancrage aurait permis:

- un acc�s � l'�l�ment pr�c�dent efficace.
- une suppression en queue efficace.

*/

// Inclusion des librairies n�cessaires au fonctionnement du module
#include <stdio.h>
#include <stdlib.h>

/// D�finition des structures
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

// Vider la liste sans la d�truire
void liste_vider(t_liste* lst, tpf_detruire detruire);

// Constructeur par copie
t_liste* liste_copier(t_liste* lst, tpf_copier copier);

// Ajout d'�l�ment en t�te
void liste_ajout_tete(t_liste* lst, void* elem);

// Ajout d'�l�ment en queue
void liste_ajout_queue(t_liste* lst, void* elem);

// Nombre d'�l�ments r�f�renc�s
int liste_taille(t_liste* lst);

// Retourne 1 (Vrai) si la liste est vide
int liste_vide(t_liste* lst);

// Acc�s �l�ment en t�te
void* liste_elem_tete(t_liste* lst);

// Acc�s �l�ment en queue
void* liste_elem_queue(t_liste* lst);

// Acc�s �l�ment courant
void* liste_elem_courant(t_liste* lst);

// On retire la t�te de la liste, et on retourne la donn�e qu'elle pointait.
void* liste_recup_tete(t_liste* lst);

// On retire la queue de la liste, et on retourne la donn�e qu'elle pointait.
// PAS EFFICACE ICI CAR SIMPLE CHAINAGE
void* liste_recup_queue(t_liste* lst);

// Supprime l'�l�ment de t�te
void liste_supprimer_tete(t_liste* lst, tpf_detruire detruire);

// Initialiser un parcours
void liste_demarrer(t_liste* lst);

// Il reste encore des �l�ments � parcourir
int liste_encore(t_liste* lst);

// D�placement du courant au suivant
void liste_suivant(t_liste* lst);

// Affichage bilan allocations/lib�rations
void liste_bilan();

////////////////////////////////////////////////////////
/* Petites fonctions suppl�mentaires*/

// Affiche les �l�ments de la liste, dans l'ordre tete --> queue
void liste_afficher(t_liste* lst, tpf_afficher afficher);

// Ajoute lst2 � la suite (en queue) de lst1 (copie les �l�ments de lst2, et les rajoute � lst1.
// Lst2 garde ses �lements (Lst2 reste inchang�e)
void liste_fusionner(t_liste* lst1, t_liste* lst2, tpf_copier copier);

// Supprime l'�l�ment de queue de la liste (PAS EFFICACE CAR SIMPLE CHAINAGE ICI)
void liste_supprimer_queue(t_liste* lst, tpf_detruire detruire);

// Trie les �lements d'une liste, en fonction du r�sultat retourn� par la fonction de comparaison des �lements
// on �vitera de trier tout le temps, on pr�f�rera l'ajout tri�.
void liste_trier(t_liste* lst, tpf_trier trier);

// ajout tri� dans la liste ( = ajout � la bonne position selon une fonction de comparaison)
void liste_ajout_trie(t_liste* lst, void* elem, tpf_trier trier);

// Recherche dans la liste tous les maillons contenant les donn�es demand�es
// (via une fonction element_rechercher, qui analyse un maillon et dit si ce maillon est int�ressant)
// Afin de g�rer le cas o� plusieurs �lements contiendraient les m�mes donn�es
// -> on retourne une liste chain�e de pointeurs sur �l�ments trouv�s :)
// ATTENTION, la liste retourn�e est une liste de REFERENCES vers des �l�ments existant dans lst.
// les �l�ments de la liste retourn�e sont CEUX de lst.
// ce ne sont PAS des copies.
t_liste* liste_rechercher(t_liste* lst, tpf_recherche recherche);

// On recoit un �l�ment forc�ment dans la liste, qu'on veut supprimer
// puis on parcourt la liste jusqu'� tomber dessus, et on le supprime, peu importe sa position (tete,milieu,queue)
void liste_supprimer_precis(t_liste* lst, void* elem, tpf_detruire detruire);

// On recoit la liste dont il faut supprimer certains �l�ments, et une liste r�f�ren�ant tous les �l�ments � supprimer.
// On va chercher les �l�ments de lst_elem_a_supprimer DANS lst, et quand on tombe dessus on les supprime.
void liste_supprimer_partie(t_liste* lst, t_liste* lst_elem_a_supprimer, tpf_detruire detruire);

// Supprime le maillon de t�te de liste, sans d�truire la donn�e point�e
void liste_dereferencer_tete(t_liste* lst);

// Supprime tous les maillons de la liste, sans d�truire les donn�es point�es
void liste_dereferencer(t_liste* lst);

// Ajoute dans la liste l'�lement � ins�rer juste avant l'�l�ment de r�f�rence
void liste_ajout_avant(t_liste* lst, void* elem_a_inserer, void* elem_ref);

/*
Tester tous les sc�narios

R�soudre probl�me qsort liste_trier
Ameliorer la fonction liste_rechercher : param�tre facultatif � rajouter
Coder liste_traiter_chaque
*/

#endif // LISTE_GENERIQUE_SIMPLE_CHAINAGE_H_INCLUDED
