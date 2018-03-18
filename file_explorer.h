#ifndef FILE_EXPLORER_H_INCLUDED
#define FILE_EXPLORER_H_INCLUDED

#include <allegro.h>
#include <winalleg.h>
#include <tchar.h>
#include <stdio.h>
#include <commdlg.h>
#include <string.h>
#include <direct.h>

#include "define.h"

#define TAILLE_BUFFER 1024

/// penser à linker libComdlg32.a dans le projet

/// Module permettant le choix d'un fichier à charger ou à sauvegarder via un explorateur de fichiers Windows.
/// Le contenu des fonctions qui obtiennent le chemin du fichier est majoritairement tiré d'un tutoriel de "fvirtman"
/// voir: http://fvirtman.free.fr/recueil/04_01_02_getopenfilename.c.php
/// Mon travail sur ces fonctions a permis de blinder la réussite de l'obtention du chemin.
/// Les fonctions qui blindent l'extension du fichier ont été entièrement codées par moi même.

// met le chemin du fichier choisi dans la chaine de caractères envoyée en paramètre
// s'assure qu'il n'y a pas une double extension dans le nom du fichier
// retourne un booléen correspondant à la réussite ou à l'échec du choix du fichier (pour savoir si l'utilisateur a annulé)
// informe l'utilisateur via un printf si le choix du fichier a été annulé
int obtenir_chemin_sauvegarde(char* chemin);

// met le chemin du fichier choisi dans la chaine de caractères envoyée en paramètre
// retourne un booléen correspondant à la réussite ou à l'échec du choix du fichier (pour savoir si l'utilisateur a annulé)
// informe l'utilisateur via un printf si le choix du fichier a été annulé
int obtenir_chemin_chargement(char* chemin);

// reçoit le chemin d'un fichier en parametre
// informe l'utilisateur via un printf de la validité de l'extension du fichier choisi, et retourne un booléen correspondant.
int verif_type_fichier(const char* chemin);

// retourne une chaine de caractères, allouée dynamiquement, contenant l'extension du fichier dont le chemin est passé en paramètre
char* return_extension_blindee(const char* chemin);

// sert à supprimer le point et ce qu'il y a après le point dans une chaine de caractère
// permet plusieurs choses:
// - d'écraser un fichier (car on choisit un fichier portant déjà l'extension .txt, mais dans le code on rajoute nous meme un .txt
// - de récupérer un nom de fichier convenable si jamais l'utilisateur tapait comme nom de fichier à créer: "dessin.txt", alors qu'il devrait plutot logiquement taper "dessin"
void supprimer_contenu_chaine_apres_point(char* chemin);

// remplit le chemin, retourne 0 si il y a eu un problème
int remplit_chemin_sauvegarde(char* chemin);

// remplit le chemin, retourne 0 si il y a eu un problème
int remplit_chemin_chargement(char* chemin);

// à partir d'un chemin, récupère le nom du fichier choisi
void recup_nom_fichier(const char* chemin, char* nom);


#endif // FILE_EXPLORER_H_INCLUDED
