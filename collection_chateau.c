#include "collection_chateau.h"

t_collection_chateau* collection_chateau_creer()
{
    t_collection_chateau* nouv;
    nouv=malloc(sizeof(t_collection_chateau));
    nouv->taille_actuelle=0;
    nouv->taille_max=TAILLE_INITIALE_COLLECTION;
    nouv->chateau=malloc(nouv->taille_max*sizeof(t_chateau*));
    return nouv;
}

void collection_chateau_ajouter_chateau(t_collection_chateau* collection_chateau,t_chateau* new_chateau)
{
    if(collection_chateau->taille_actuelle==collection_chateau->taille_max)
    {
        collection_chateau_reallouer(collection_chateau);
    }
    collection_chateau->chateau[collection_chateau->taille_actuelle]=new_chateau;
    collection_chateau->taille_actuelle++;
}

void collection_chateau_liberer(t_collection_chateau* collection_chateau)
{
    int i;

    for(i=0; i<collection_chateau->taille_actuelle; i++)
    {
        chateau_liberer(collection_chateau->chateau[i]);
    }
    free(collection_chateau->chateau);
    free(collection_chateau);
}

void collection_chateau_reallouer(t_collection_chateau* collection_chateau)
{
    collection_chateau->taille_max=3*collection_chateau->taille_max/2;
    collection_chateau->chateau=realloc(collection_chateau->chateau,collection_chateau->taille_max*sizeof(t_chateau*));
}

void collection_chateau_afficher(t_collection_chateau* collection_chateau,int niveau)
{
    int i;
    for(i=0; i<collection_chateau->taille_actuelle; i++)
    {
        chateau_afficher(collection_chateau->chateau[i],niveau);
    }
}

int** collection_chateau_tableau_longueurs(t_collection_chateau* collection_chateau,t_case*** kase,t_bfs* bfs,t_collection_habitation* collection_habitation)
{
    int i;
    int** longueurs_chateaux_maisons;

    longueurs_chateaux_maisons=malloc(collection_chateau->taille_actuelle*sizeof(int*));

    bfs->ordre=collection_habitation->taille_actuelle;
    for(i=0; i<collection_chateau->taille_actuelle; i++)
    {
        bfs->case_de_referenceX=collection_chateau->chateau[i]->case_de_referenceX;
        bfs->case_de_referenceY=collection_chateau->chateau[i]->case_de_referenceY;
        longueurs_chateaux_maisons[i]=recherchepluscourtchemin(bfs,kase);
    }
    return longueurs_chateaux_maisons;
}

void collection_chateau_distribuer_proche(t_collection_chateau* collection_chateau,t_collection_habitation* collection_habitation,int** longueurs)
{
    int i=0,j,distributeur,minimum;
    while(i<collection_habitation->taille_actuelle)
    {
            minimum=INFINI;
            distributeur=-1;
            for(j=0; j<collection_chateau->taille_actuelle; j++)
            {
                if((longueurs[j][i]<minimum)&&(collection_chateau->chateau[j]->capacite.capacite_disponible!=0)&&(longueurs[j][i]!=0))
                {
                    distributeur=j;
                    minimum=longueurs[j][i];
                }
            }
            if(distributeur!=-1)
            {
                chateau_distribuer(collection_chateau->chateau[distributeur],collection_habitation->habitation[i]);
            }
        i++;
    }
}

void collection_chateau_distribuer(t_collection_chateau* collection_chateau,t_collection_habitation* collection_habitation,int** longueurs_chateaux_habitations)
{
    if((collection_habitation->taille_actuelle!=0)&&(collection_chateau->taille_actuelle!=0))
    {
        collection_chateau_distribuer_minimiser(collection_chateau,collection_habitation,longueurs_chateaux_habitations);
    }
}

void collection_chateau_distribuer_minimiser(t_collection_chateau* collection_chateau,t_collection_habitation* collection_habitation,int** longueur)
{
    int i=0;
    int eau_dispo;
    int taille1,taille2,compteur,j,compteur2,k,l;
    int mini,distributeur=0,receveur;
    //pour toutes les maisons
    while(i<collection_habitation->taille_actuelle)
    {//on cherche TOUTES les plus grosses
        compteur=i;
        taille1=collection_habitation->habitation[i]->stade;
        taille2=collection_habitation->habitation[i]->stade;
        while(taille1==taille2)
        {
            compteur++;
            if(compteur<collection_habitation->taille_actuelle) taille2=collection_habitation->habitation[compteur]->stade;
            else taille2=INFINI;
        }
        //Pour CHACUNE de ces habitations (il y en a compteur-1)
        for(l=i;l<compteur;l++)
        {
            mini=INFINI;
            receveur=-1;
            for(k=0;k<collection_chateau->taille_actuelle;k++)
            {
                for(j=i;j<compteur;j++)
                {
                    if((longueur[k][j]!=0)&&(longueur[k][j]<mini)&&(collection_habitation->habitation[j]->electricite==1)&&(collection_habitation->habitation[j]->eau!=1))
                    {
                        mini=longueur[k][j];
                        receveur=j;
                    }
                }
            }
            if(receveur!=-1)
            {
                //on compte l'eau disponible sur le réseau
                eau_dispo=0;
                for(compteur2=0;compteur2<collection_chateau->taille_actuelle;compteur2++)
                {
                    if(longueur[compteur2][receveur]!=0)
                    {
                        eau_dispo+=collection_chateau->chateau[compteur2]->capacite.capacite_disponible;
                    }
                }//TANT que l'habitation n'est pas alimenté et que l'eau disponible n'est pas épuisée et qu'on a pas atteint la limite des fournisseur
                while((collection_habitation->habitation[receveur]->eau!=1)&&(eau_dispo>0)&&(collection_habitation->habitation[receveur]->chateaux_fournisseurs[FOURNISSEUR_MAX-1].qte_eau_distribuee==0))
                {
                    //On recherche la centrale sur le réseau la plus proche
                    mini=INFINI;
                    for(compteur2=0;compteur2<collection_chateau->taille_actuelle;compteur2++)
                    {
                        if((longueur[compteur2][receveur]!=0)&&(longueur[compteur2][receveur]<mini)&&(collection_chateau->chateau[compteur2]->capacite.capacite_disponible!=0))
                        {
                            distributeur=compteur2;
                            mini=longueur[compteur2][receveur];
                        }
                    }//on alimente l'habitation et on tient à jours la quantitee d'eau dispo
                    eau_dispo-=chateau_distribuer(collection_chateau->chateau[distributeur],collection_habitation->habitation[receveur]);
                }
            }

        }
        i=compteur;
    }
}

int collection_chateau_eau_disponible(t_collection_chateau* collection_chateau)
{
    int eau_totale_dispo = 0;
    int i;

    for(i=0; i<collection_chateau->taille_actuelle; i++)
    {
        eau_totale_dispo = eau_totale_dispo + chateau_eau_disponible(collection_chateau->chateau[i]);
    }

    return eau_totale_dispo;
}

void collection_chateau_debut_tour(t_collection_chateau* collection_chateau)
{
    int i;
    for(i=0; i<collection_chateau->taille_actuelle; i++)
    {
        chateau_debut_tour(collection_chateau->chateau[i]);
    }
}

int* collection_chateau_tableau_capacite(t_collection_chateau* collection_chateau)
{
    int* capacite_chateau;
    int i;
    capacite_chateau=malloc(collection_chateau->taille_actuelle*sizeof(int));
    for(i=0;i<collection_chateau->taille_actuelle;i++)
    {
        capacite_chateau[i]=collection_chateau->chateau[i]->capacite.capacite_disponible;
    }
    return capacite_chateau;
}
