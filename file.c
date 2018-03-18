#include "file.h"

// Alloue une file
t_file* file_creer()
{
    return liste_creer();
}

// Détruit une file
void file_detruire(t_file* file, tpf_detruire detruire)
{
    liste_detruire(file,detruire);
}

// Vide une file
void file_vider(t_file* file, tpf_detruire detruire)
{
    liste_vider(file,detruire);
}

// Enfile ( = ajoute ) un élément à la file
void file_enfiler(t_file* file, void* elem)
{
    liste_ajout_queue(file,elem);
}

// Défile ( = retire ) un élément à la file
void* file_defiler(t_file* file)
{
    return liste_recup_tete(file);
}

// Retourne l'élément du sommet de la file, sans le retirer de la file
void* file_elem_sommet(t_file* file)
{
    return liste_elem_tete(file);
}

// Retourne 1 si la file est vide, 0 sinon
int file_vide(t_file* file)
{
    return liste_vide(file);
}

// Retourne une copie (profonde) de la file reçue en paramètre
t_file* file_copier(t_file* file,tpf_copier copier)
{
    return liste_copier(file,copier);
}

// Retourne le nombre d'éléments de la file
int file_taille(t_file* file)
{
    return liste_taille(file);
}

// Affichage bilan allocations/libérations
void file_bilan(t_file* file)
{
    liste_bilan(file);
}
