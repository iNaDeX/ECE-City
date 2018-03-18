#include "editeur.h"

t_editeur* editeur_allouer(int mode_de_jeu) // sera envoyé par le menu
{
    t_editeur* nouv = NULL;

    nouv = (t_editeur*)malloc(1*sizeof(t_editeur));

    nouv->maville = ville_allouer_initialiser(mode_de_jeu);
    nouv->boite_a_outils = boiteaoutils_creer();

    return nouv;
}

void editeur_gerer(t_editeur* ed)
{
    boiteaoutils_gerer(ed->boite_a_outils);
    ville_gerer(ed->maville, ed->boite_a_outils->bouton_choisi);
}

void editeur_afficher(t_editeur* ed)
{
    // on vide le buffer page
    clear_bitmap(page);

    // on construit notre affichage sur le buffer page
    ville_afficher(ed->maville,ed->boite_a_outils->bouton_choisi);
    boiteaoutils_afficher(ed->boite_a_outils);
    /***** il faudra aussi rajouter les variables du style: argent, nombre d'habitants etc..*****/
    textprintf_ex(page,font,112,20,makecol(255,255,255),-1,"Nombre habitants: %d",ed->maville->nb_habitants);
    textprintf_ex(page,font,300,20,makecol(255,255,255),-1,"Argent: %d",ed->maville->argent);
    textprintf_ex(page,font,500,20,makecol(255,255,255),-1,"Temps de jeu: %d:%d:%.0f",ed->maville->temps_de_jeu->heures,ed->maville->temps_de_jeu->minutes,ed->maville->temps_de_jeu->secondes);
    textprintf_ex(page,font,112,40,makecol(255,255,255),-1,"Elec dispo:%d/%d",ed->maville->qte_elec.capacite_disponible,ed->maville->qte_elec.capacite_max);
    textprintf_ex(page,font,500,40,makecol(255,255,255),-1,"Eau dispo:%d/%d",ed->maville->qte_eau.capacite_disponible,ed->maville->qte_eau.capacite_max);
    if(ed->maville->pause == PAUSE_ACTIVEE) textprintf_ex(page,font,700,40,makecol(255,255,255),-1,"PAUSE ACTIVEE");

    // on affiche le buffer page sur l'écran
    //blit(page,screen,0,0,0,0, SCREEN_W, SCREEN_H);
    stretch_blit(page, screen, 0, 0, TAILLE_FENETRE_W, TAILLE_FENETRE_H, 0, 0, SCREEN_W, SCREEN_H);// permet de gérer les ordis
    // incapables d'ouvrir un mode graphique 1024*768
}

void editeur_liberer(t_editeur* ed)
{
    boiteaoutils_liberer(ed->boite_a_outils);
    ville_liberer(ed->maville);

    free(ed);
}
