#include "graphismes.h"

#define VITESSE_AFFICHAGE 5
#define POSX 266
#define POSY 348
#define BARRE_W 2

BITMAP* selectionaleatoirecouleurbarrechargement();
void avancerchargement(BITMAP* barrechargement,int barres_a_afficher,int* barres_deja_affichees);

BITMAP* selectionaleatoirecouleurbarrechargement()
{
    int x;
    BITMAP* nouv;
    char ch[TAILLE_CHAINE];
    x= rand()%6;
    sprintf(ch,"fichiers/images/barrechargement%d.bmp",x);
    nouv= chargerImage(ch);
    return nouv;
}

void avancerchargement(BITMAP* barrechargement,int barres_a_afficher,int* barres_deja_affichees)
{
    int i;
    for(i=0; i<barres_a_afficher; i++)
    {
        draw_sprite(page,barrechargement,POSX+BARRE_W*i+BARRE_W* (*barres_deja_affichees),POSY);
        rest(2);
        blit(page,screen,0,0,0,0,SCREEN_W,SCREEN_H);
    }
    (*barres_deja_affichees) = (*barres_deja_affichees) + barres_a_afficher;
}

t_graphismes* graphismes_charger()
{
    int i,j;
    int barres_deja_affichees=0;
    char nom_fichier[TAILLE_CHAINE];
    t_graphismes* nouv = NULL;
    nouv = (t_graphismes*)malloc(1*sizeof(t_graphismes));

    BITMAP* fondchargement=chargerImage("fichiers/images/fondchargement.bmp");
    BITMAP* barrechargement= selectionaleatoirecouleurbarrechargement();

    blit(fondchargement,page,0,0,0,0,SCREEN_W,SCREEN_H);

    ///////////////////////////////////////////

    nouv->buffer_ville = create_bitmap(GAME_W,GAME_H);
    avancerchargement(barrechargement,VITESSE_AFFICHAGE,&barres_deja_affichees);
    clear_bitmap(nouv->buffer_ville);

    nouv->fond_herbe = chargerImage("fichiers/images/jeu/fond_herbe.bmp");
    avancerchargement(barrechargement,VITESSE_AFFICHAGE,&barres_deja_affichees);
    nouv->grille = chargerImage("fichiers/images/jeu/grille.bmp");
    avancerchargement(barrechargement,VITESSE_AFFICHAGE,&barres_deja_affichees);

    for(j=0; j<NB_NIVEAUX; j++)
    {
        for(i=0; i<NB_IMG_ROUTES; i++)
        {
            sprintf(nom_fichier,"fichiers/images/jeu/route%d-%d.bmp",j,i);
            nouv->route[j][i] = chargerImage(nom_fichier);
            avancerchargement(barrechargement,VITESSE_AFFICHAGE,&barres_deja_affichees);
        }
    }

    nouv->terrain_vague = chargerImage("fichiers/images/jeu/terrain_vague.bmp");
    avancerchargement(barrechargement,VITESSE_AFFICHAGE,&barres_deja_affichees);
    nouv->ruine = chargerImage("fichiers/images/jeu/ruine.bmp");
    avancerchargement(barrechargement,VITESSE_AFFICHAGE,&barres_deja_affichees);
    nouv->pompier = chargerImage("fichiers/images/jeu/pompier.bmp");

    for(i=0; i<NB_IMG_CABANES; i++)
    {
        sprintf(nom_fichier,"fichiers/images/jeu/cabane%d.bmp",i);
        nouv->cabane[i] = chargerImage(nom_fichier);
        avancerchargement(barrechargement,VITESSE_AFFICHAGE,&barres_deja_affichees);
    }

    for(i=0; i<NB_IMG_MAISONS; i++)
    {
        sprintf(nom_fichier,"fichiers/images/jeu/maison%d.bmp",i);
        nouv->maison[i] = chargerImage(nom_fichier);
        avancerchargement(barrechargement,VITESSE_AFFICHAGE,&barres_deja_affichees);
    }

    for(i=0; i<NB_IMG_IMMEUBLES; i++)
    {
        sprintf(nom_fichier,"fichiers/images/jeu/immeuble%d.bmp",i);
        nouv->immeuble[i] = chargerImage(nom_fichier);
        avancerchargement(barrechargement,VITESSE_AFFICHAGE,&barres_deja_affichees);
    }

    for(i=0; i<NB_IMG_GRATTECIELS; i++)
    {
        sprintf(nom_fichier,"fichiers/images/jeu/gratte_ciel%d.bmp",i);
        nouv->gratte_ciel[i] = chargerImage(nom_fichier);
        avancerchargement(barrechargement,VITESSE_AFFICHAGE,&barres_deja_affichees);
    }

    nouv->chateau = chargerImage("fichiers/images/jeu/chateau.bmp");
    avancerchargement(barrechargement,VITESSE_AFFICHAGE,&barres_deja_affichees);
    nouv->centrale = chargerImage("fichiers/images/jeu/centrale.bmp");
    avancerchargement(barrechargement,VITESSE_AFFICHAGE,&barres_deja_affichees);
    nouv->caserne = chargerImage("fichiers/images/jeu/caserne.bmp");
    avancerchargement(barrechargement,VITESSE_AFFICHAGE,&barres_deja_affichees);

    destroy_bitmap(fondchargement);
    destroy_bitmap(barrechargement);

    return nouv;
}

void graphismes_liberer(t_graphismes* graph)
{
    int i,j;

    destroy_bitmap(graph->buffer_ville);

    destroy_bitmap(graph->fond_herbe);

    destroy_bitmap(graph->grille);

    for(j=0; j<NB_NIVEAUX; j++)
    {
        for(i=0; i<NB_IMG_ROUTES; i++)
        {
            destroy_bitmap(graph->route[j][i]);
        }
    }

    destroy_bitmap(graph->terrain_vague);
    destroy_bitmap(graph->ruine);
    destroy_bitmap(graph->pompier);

    for(i=0; i<NB_IMG_CABANES; i++)
    {
        destroy_bitmap(graph->cabane[i]);
    }

    for(i=0; i<NB_IMG_MAISONS; i++)
    {
        destroy_bitmap(graph->maison[i]);
    }

    for(i=0; i<NB_IMG_IMMEUBLES; i++)
    {
        destroy_bitmap(graph->immeuble[i]);
    }

    for(i=0; i<NB_IMG_GRATTECIELS; i++)
    {
        destroy_bitmap(graph->gratte_ciel[i]);
    }

    destroy_bitmap(graph->chateau);
    destroy_bitmap(graph->centrale);
    destroy_bitmap(graph->caserne);

    free(graph);
}
