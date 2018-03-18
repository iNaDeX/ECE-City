#include "chateau.h"

t_chateau* chateau_creer()
{
    t_chateau* nouv;
    nouv=malloc(sizeof(t_chateau));

    nouv->capacite.capacite_disponible = CAPACITE_CHATEAU;
    nouv->capacite.capacite_max = CAPACITE_CHATEAU;
    nouv->case_de_referenceX = 0;
    nouv->case_de_referenceY = 0;
    nouv->id_chateau.caseX = -1;
    nouv->id_chateau.caseY = -1;

    return nouv;
}

void chateau_debut_tour(t_chateau* chateau)
{
    chateau->capacite.capacite_disponible=CAPACITE_CHATEAU;
}

void chateau_liberer(t_chateau* c)
{
    free(c);
}

int chateau_place_libre(int col,int lig,t_case*** kase)
{
    int i,j;
    int libre=1;
    if(!chateau_depassement_matrice(col,lig))
    {
        for(i=col;i<col+CHATEAU_W;i++)
        {
            for(j=lig;j<lig+CHATEAU_H;j++)
            {
                if(kase[j][i]->type!=VIDE)
                {
                    libre=0;
                }
            }
        }
    }
    else libre=0;
    return libre;
}

int chateau_depassement_matrice(int colonne,int ligne)
{
    int depasse=1;
    if((colonne>=0)&&(colonne<=NB_CASES_COL-CHATEAU_W)&&(ligne>=0)&&(ligne<=NB_CASES_LIG-CHATEAU_H))
    {
        depasse=0;
    }
    return depasse;
}

void chateau_placer(t_chateau* chateau,int col,int lig,t_case*** kase)
{
    int i,j;
    chateau->case_de_referenceX=col;
    chateau->case_de_referenceY=lig;
    chateau->id_chateau.caseX = col;
    chateau->id_chateau.caseY = lig;
    for(i=col;i<col+CHATEAU_W;i++)
    {
        for(j=lig;j<lig+CHATEAU_H;j++)
        {
            case_remplir(kase[j][i],CHATEAU,chateau);
        }
    }
}

void chateau_afficher(t_chateau* chateau,int niveau)
{
    if(niveau==NIVEAU_ELEC)
    {
    draw_trans_sprite(graphs->buffer_ville,graphs->chateau,1+TAILLE_CASE*chateau->case_de_referenceX,1+TAILLE_CASE*chateau->case_de_referenceY);
    }
    else
    {
        draw_sprite(graphs->buffer_ville,graphs->chateau,1+TAILLE_CASE*chateau->case_de_referenceX,1+TAILLE_CASE*chateau->case_de_referenceY);
    }
}

int chateau_distribuer(t_chateau* chateau,t_habitation* habitation)
{
    int eau_distribuee=0,quantitee,i,eau_distrib;
    int index = 0;

    for(i=0;i<FOURNISSEUR_MAX;i++)
    {
        eau_distribuee+=habitation->chateaux_fournisseurs[i].qte_eau_distribuee;
    }
    quantitee=habitation_nbhabitants(habitation)-eau_distribuee;
    if(chateau->capacite.capacite_disponible>=quantitee)
    {
        //////////////////////////////////////////////////////////////// on cherche l'indice du 1er chateau fournisseur
                                                                      // qui n'a pas encore distribué d'eau
                                                                      // (on cherche à savoir s'il reste une place dans
                                                                      // le tableau des fournisseurs)
        i=0;
        do
        {
            eau_distrib= habitation->chateaux_fournisseurs[i].qte_eau_distribuee;
            if(eau_distrib == 0) index = i;
            i++;
        }while(eau_distrib != 0 && i<FOURNISSEUR_MAX);
        ///////////////////////////////////////////////////////////////
        if(eau_distrib == 0) // si on a trouvé une place dans le tableau des fournisseurs, on alimente. sinon non.
        {
            habitation->chateaux_fournisseurs[index].qte_eau_distribuee=quantitee;
            habitation->chateaux_fournisseurs[index].id_fournisseur.caseX =chateau->id_chateau.caseX;
            habitation->chateaux_fournisseurs[index].id_fournisseur.caseY =chateau->id_chateau.caseY;
            chateau->capacite.capacite_disponible-=quantitee;
            habitation->eau=1;
        }
        else // on n'a pas trouvé de place, on n'alimente pas, donc la quantité distribuée est nulle
        {
            quantitee=0;
        }
    }
    else if(chateau->capacite.capacite_disponible<quantitee)
    {
        //////////////////////////////////////////////////////////////// on cherche l'indice du 1er chateau fournisseur
                                                                      // qui n'a pas encore distribué d'eau
                                                                      // (on cherche à savoir s'il reste une place dans
                                                                      // le tableau des fournisseurs)
        i=0;
        do
        {
            eau_distrib= habitation->chateaux_fournisseurs[i].qte_eau_distribuee;
            if(eau_distrib == 0) index = i;
            i++;
        }while(eau_distrib != 0 && i<FOURNISSEUR_MAX);
        ///////////////////////////////////////////////////////////////
        if(eau_distrib == 0) // si on a trouvé une place dans le tableau des fournisseurs, on alimente. sinon non.
        {
            quantitee =chateau->capacite.capacite_disponible;
            chateau->capacite.capacite_disponible=0;

            habitation->chateaux_fournisseurs[index].qte_eau_distribuee=quantitee;
            habitation->chateaux_fournisseurs[index].id_fournisseur=chateau->id_chateau;
        }
        else // on n'a pas trouvé de place, on n'alimente pas, donc la quantité distribuée est nulle
        {
            quantitee = 0;
        }
    }
    return quantitee;
}

int chateau_eau_disponible(t_chateau* chateau)
{
    return chateau->capacite.capacite_disponible;
}
