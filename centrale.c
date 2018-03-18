#include "centrale.h"

t_centrale* centrale_creer()
{
    t_centrale* nouv;
    nouv=malloc(sizeof(t_centrale));

    nouv->capacite.capacite_disponible = CAPACITE_CENTRALE;
    nouv->capacite.capacite_max = CAPACITE_CENTRALE;
    nouv->case_de_referenceX = 0;
    nouv->case_de_referenceY = 0;
    nouv->id_centrale.caseX = -1;
    nouv->id_centrale.caseX = -1;
    return nouv;
}

void centrale_liberer(t_centrale* c)
{
    free(c);
}

void centrale_distribuer(t_centrale* centrale,t_habitation* habitation,int quantitee)
{
    habitation->id_centrale_fournisseuse.caseX = centrale->id_centrale.caseX; // on recopie l'ID de la centrale
    habitation->id_centrale_fournisseuse.caseY = centrale->id_centrale.caseY; // on recopie l'ID de la centrale
    centrale->capacite.capacite_disponible-=quantitee;
    habitation->electricite=1;
}

int centrale_place_libre(int col,int lig,t_case*** kase)
{
    int i,j;
    int libre=1;
    if(!centrale_depassement_matrice(col,lig))
    {
        for(i=lig;i<lig+CENTRALE_H;i++)
        {
            for(j=col;j<col+CENTRALE_W;j++)
            {
                if(kase[i][j]->type!=VIDE)
                {
                    libre=0;
                }
            }
        }
    }
    else libre=0;
    return libre;
}

int centrale_depassement_matrice(int colonne,int ligne)
{
    int depasse=1;
    if((colonne>=0)&&(colonne<=NB_CASES_COL-CENTRALE_W)&&(ligne>=0)&&(ligne<=NB_CASES_LIG-CENTRALE_H))
    {
        depasse=0;
    }
    return depasse;
}

void centrale_placer(t_centrale* centrale,int col,int lig,t_case*** kase)
{
    int i,j;
    centrale->case_de_referenceX=col;
    centrale->case_de_referenceY=lig;
    centrale->id_centrale.caseX = col;
    centrale->id_centrale.caseY = lig;
    for(i=lig;i<lig+CENTRALE_H;i++)
    {
        for(j=col;j<col+CENTRALE_W;j++)
        {
            case_remplir(kase[i][j],CENTRALE,centrale);
        }
    }
}

void centrale_afficher(t_centrale* centrale,int niveau)
{
    if(niveau==NIVEAU_EAU)
    {
        draw_trans_sprite(graphs->buffer_ville,graphs->centrale,1+TAILLE_CASE*centrale->case_de_referenceX,1+TAILLE_CASE*centrale->case_de_referenceY);
    }
    else
    {
    draw_sprite(graphs->buffer_ville,graphs->centrale,1+TAILLE_CASE*centrale->case_de_referenceX,1+TAILLE_CASE*centrale->case_de_referenceY);
    }
}

void centrale_debut_tour(t_centrale* centrale)
{
    centrale->capacite.capacite_disponible = CAPACITE_CENTRALE;
}

int centrale_elec_disponible(t_centrale* centrale)
{
    return centrale->capacite.capacite_disponible;
}
