#include "collection_centrales.h"

t_collection_centrale* collection_centrale_creer()
{
    t_collection_centrale* nouv;
    nouv=malloc(sizeof(t_collection_centrale));
    nouv->taille_actuelle=0;
    nouv->taille_max=TAILLE_INITIALE_COLLECTION;
    nouv->centrale=malloc(nouv->taille_max*sizeof(t_centrale*));
    return nouv;
}

void collection_centrale_ajouter_centrale(t_collection_centrale* collection_centrale,t_centrale* new_centrale)
{
    if(collection_centrale->taille_actuelle==collection_centrale->taille_max)
    {
        collection_centrale_reallouer(collection_centrale);
    }
    collection_centrale->centrale[collection_centrale->taille_actuelle]=new_centrale;
    collection_centrale->taille_actuelle++;
}

void collection_centrale_liberer(t_collection_centrale* collection_centrale)
{
    int i;

    for(i=0; i<collection_centrale->taille_actuelle; i++)
    {
        centrale_liberer(collection_centrale->centrale[i]);
    }
    free(collection_centrale->centrale);
    free(collection_centrale);
}

void collection_centrale_reallouer(t_collection_centrale* collection_centrale)
{
    collection_centrale->taille_max=3*collection_centrale->taille_max/2;
    collection_centrale->centrale=realloc(collection_centrale->centrale,collection_centrale->taille_max*sizeof(t_centrale*));
}

void collection_centrale_afficher(t_collection_centrale* collection_centrale,int niveau)
{
    int i;
    for(i=0; i<collection_centrale->taille_actuelle; i++)
    {
        centrale_afficher(collection_centrale->centrale[i],niveau);
    }
}

void collection_centrale_distribuer(t_collection_centrale* collection_centrale,t_collection_habitation* collection_habitation,int** longueurs)
{
    int i=0,j=0;
    int quantitee;

    for(i=0; i<collection_centrale->taille_actuelle; i++)
    {
        for(j=0; j<collection_habitation->taille_actuelle; j++)
        {
            if((collection_habitation->habitation[j]->electricite==0)&&(longueurs[i][j]!=0))
            {
                quantitee=habitation_nbhabitants(collection_habitation->habitation[j]); ///retourne le nombre d'habitant en fonction du stade de développement
                if(collection_centrale->centrale[i]->capacite.capacite_disponible>=quantitee)
                {
                    centrale_distribuer(collection_centrale->centrale[i],collection_habitation->habitation[j],quantitee);
                }
            }
        }
    }
}

void collection_centrale_debut_tour(t_collection_centrale* collection_centrale)
{
    int i;
    for(i=0; i<collection_centrale->taille_actuelle; i++)
    {
        centrale_debut_tour(collection_centrale->centrale[i]);
    }
}

int collection_centrale_elec_disponible(t_collection_centrale* collection_centrale)
{
    int elec_totale_dispo = 0;
    int i;
    for(i=0;i<collection_centrale->taille_actuelle;i++)
    {
        elec_totale_dispo += centrale_elec_disponible(collection_centrale->centrale[i]);
    }
    return elec_totale_dispo;
}

int** collection_centrale_tableau_longueurs(t_collection_centrale* collection_centrale,t_case*** kase,t_bfs* bfs,t_collection_habitation* collection_habitation)
{
    int i;
    int** longueurs_centrales_maisons;

    longueurs_centrales_maisons=malloc(collection_centrale->taille_actuelle*sizeof(int*));

    bfs->ordre=collection_habitation->taille_actuelle;
    for(i=0; i<collection_centrale->taille_actuelle; i++)
    {
        bfs->case_de_referenceX=collection_centrale->centrale[i]->case_de_referenceX;
        bfs->case_de_referenceY=collection_centrale->centrale[i]->case_de_referenceY;
        longueurs_centrales_maisons[i]=recherchepluscourtchemin(bfs,kase);
    }
    return longueurs_centrales_maisons;
}

int* collection_centrale_tableau_capacite(t_collection_centrale* collection_centrale)
{
    int* capacite_centrale;
    int i;
    capacite_centrale=malloc(collection_centrale->taille_actuelle*sizeof(int));
    for(i=0;i<collection_centrale->taille_actuelle;i++)
    {
        capacite_centrale[i]=collection_centrale->centrale[i]->capacite.capacite_disponible;
    }
    return capacite_centrale;
}
