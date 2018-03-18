#include "boitaoutil.h"
#include "string.h"

t_boite_a_outils* boiteaoutils_creer()
{
    int i,j,cpt=0;
    //déclaration d'une instance boite à outil
    t_boite_a_outils* nouv;
    //allocation mémoire pour cette instance
    nouv=(t_boite_a_outils*)malloc(1*sizeof(t_boite_a_outils));
    //On en profite pour remplir directement les champs de l'instance
    //Car ils sont définis en DUR par le developeur
    nouv->x=COORDX;
    nouv->y=COORDY;

    nouv->bouton_choisi = -1;
    //On charge les images (outil%d.bmp)
    boiteaoutils_chargerimages(nouv);
    //on rempli la matrice MATACTION qui va définir
    //le comportement de l'utilisateur dans le jeu
    for(i=0;i<NB_BOUTONS_H;i++)
    {
        for(j=0;j<NB_BOUTONS_W;j++)
        {
            nouv->matbouton[i][j]=cpt;
            cpt++;
        }
    }
    return nouv;
}

void boiteaoutils_reinitialiser_boutons_uniques(t_boite_a_outils* boiteaoutils)
{
    switch(boiteaoutils->bouton_choisi)
    {
    case BOUTON_PAUSE:
    case BOUTON_SAUVEGARDER:
        boiteaoutils->bouton_choisi = -1;
    }
}

void boiteaoutils_chargerimages(t_boite_a_outils* boiteaoutils)
{
    int i,j,nb=0;
    char img_off[TAILLE_CHAINE];
    char img_on[TAILLE_CHAINE];
    //Pour chaque case de la boite à outil, on va charger l'image correspondante
    //NB:on effectue cette action 1 fois, en début de programme, afin de ne pas toujours charger les images
    for(i=0;i<NB_BOUTONS_H;i++)
    {
        for(j=0;j<NB_BOUTONS_W;j++)
        {
            sprintf(img_off,"fichiers/images/boite_a_outils/outil_off%d.bmp",nb);
            sprintf(img_on,"fichiers/images/boite_a_outils/outil_on%d.bmp",nb);
            boiteaoutils->img_bouton_off[i][j]=chargerImage(img_off);
            boiteaoutils->img_bouton_on[i][j]=chargerImage(img_on);
            nb++;
        }
    }
}

void boiteaoutils_afficher(t_boite_a_outils* boiteaoutils)
{
    int x,y;
    int i,j,b;

    x = boiteaoutils->x;
    y = boiteaoutils->y;
    //créer le rectangle de la boite à outil
    rectfill(page, x, y, x+NB_BOUTONS_W*(LARGEUR_CASE+TAILLE_BORDS), y+NB_BOUTONS_H*(LARGEUR_CASE+TAILLE_BORDS), COUL_FOND);
    rect(page, x, y, x+NB_BOUTONS_W*(LARGEUR_CASE+TAILLE_BORDS), y+NB_BOUTONS_H*(LARGEUR_CASE+TAILLE_BORDS), COUL_BORD);

    //la remplir avec les images
    for(i=0;i<NB_BOUTONS_H;i++)
    {
        for(j=0;j<NB_BOUTONS_W;j++)
        {
            if(boiteaoutils->bouton_choisi!=boiteaoutils->matbouton[i][j])
            {
                draw_sprite(page,boiteaoutils->img_bouton_off[i][j],x,y);
            }
            else
            {
                draw_sprite(page,boiteaoutils->img_bouton_on[i][j],x,y);
            }
            for(b=0;b<TAILLE_BORDS;b++)
            {
                rect(page,x-b,y-b,x+LARGEUR_CASE+b,y+LARGEUR_CASE+b,COUL_BORD);
            }
            x=x+LARGEUR_CASE+TAILLE_BORDS;
        }
        x= boiteaoutils->x;
        y=y+LARGEUR_CASE+TAILLE_BORDS;
    }
}

void boiteaoutils_gerer(t_boite_a_outils* boiteaoutils)
{
    boiteaoutils_reinitialiser_boutons_uniques(boiteaoutils);

    if((mouse_x>boiteaoutils->x)&&(mouse_x<boiteaoutils->x+NB_BOUTONS_W*(LARGEUR_CASE+TAILLE_BORDS))&&(mouse_y>boiteaoutils->y)&&(mouse_y<boiteaoutils->y+NB_BOUTONS_H*(LARGEUR_CASE+TAILLE_BORDS)))
    {//On récupère les coordonnées de la souris et on en profite pour changer de référentiel
        int xc = (mouse_x-boiteaoutils->x)/(LARGEUR_CASE+TAILLE_BORDS);
        int yc = (mouse_y-boiteaoutils->y)/(LARGEUR_CASE+TAILLE_BORDS);

        //on donne à la boîte à outil la valeur de l'action sur laquelle à cliqué l'utilisateur afin de définir
        //son comportement par rapport au programme
        if ( bouton=='g' && xc>=0 && xc<NB_BOUTONS_W && yc>=0 && yc<NB_BOUTONS_H )
        {
            boiteaoutils->bouton_choisi=boiteaoutils->matbouton[yc][xc];
        }
    }
    if(mouse_b&2)
    {
        boiteaoutils->bouton_choisi = -1; // Si clic-droit alors on réinitialise le bouton choisi
    }
}

void boiteaoutils_liberer(t_boite_a_outils* boiteaoutils)
{//Libération mémoire de la boite à outil
    int i,j;
    for(i=0;i<NB_BOUTONS_H;i++)
    {
        for(j=0;j<NB_BOUTONS_W;j++)
        {
            destroy_bitmap(boiteaoutils->img_bouton_off[i][j]);
            destroy_bitmap(boiteaoutils->img_bouton_on[i][j]);
        }
    }
    free(boiteaoutils);
}
