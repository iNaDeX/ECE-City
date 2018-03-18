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

/// penser � linker libComdlg32.a dans le projet

/// Module permettant le choix d'un fichier � charger ou � sauvegarder via un explorateur de fichiers Windows.
/// Le contenu des fonctions qui obtiennent le chemin du fichier est majoritairement tir� d'un tutoriel de "fvirtman"
/// voir: http://fvirtman.free.fr/recueil/04_01_02_getopenfilename.c.php
/// Mon travail sur ces fonctions a permis de blinder la r�ussite de l'obtention du chemin.
/// Les fonctions qui blindent l'extension du fichier ont �t� enti�rement cod�es par moi m�me.

// met le chemin du fichier choisi dans la chaine de caract�res envoy�e en param�tre
// s'assure qu'il n'y a pas une double extension dans le nom du fichier
// retourne un bool�en correspondant � la r�ussite ou � l'�chec du choix du fichier (pour savoir si l'utilisateur a annul�)
// informe l'utilisateur via un printf si le choix du fichier a �t� annul�
int obtenir_chemin_sauvegarde(char* chemin);

// met le chemin du fichier choisi dans la chaine de caract�res envoy�e en param�tre
// retourne un bool�en correspondant � la r�ussite ou � l'�chec du choix du fichier (pour savoir si l'utilisateur a annul�)
// informe l'utilisateur via un printf si le choix du fichier a �t� annul�
int obtenir_chemin_chargement(char* chemin);

// re�oit le chemin d'un fichier en parametre
// informe l'utilisateur via un printf de la validit� de l'extension du fichier choisi, et retourne un bool�en correspondant.
int verif_type_fichier(const char* chemin);

// retourne une chaine de caract�res, allou�e dynamiquement, contenant l'extension du fichier dont le chemin est pass� en param�tre
char* return_extension_blindee(const char* chemin);

// sert � supprimer le point et ce qu'il y a apr�s le point dans une chaine de caract�re
// permet plusieurs choses:
// - d'�craser un fichier (car on choisit un fichier portant d�j� l'extension .txt, mais dans le code on rajoute nous meme un .txt
// - de r�cup�rer un nom de fichier convenable si jamais l'utilisateur tapait comme nom de fichier � cr�er: "dessin.txt", alors qu'il devrait plutot logiquement taper "dessin"
void supprimer_contenu_chaine_apres_point(char* chemin);

// remplit le chemin, retourne 0 si il y a eu un probl�me
int remplit_chemin_sauvegarde(char* chemin);

// remplit le chemin, retourne 0 si il y a eu un probl�me
int remplit_chemin_chargement(char* chemin);

// � partir d'un chemin, r�cup�re le nom du fichier choisi
void recup_nom_fichier(const char* chemin, char* nom);


#endif // FILE_EXPLORER_H_INCLUDED
