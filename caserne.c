#include "caserne.h"

t_caserne* caserne_creer()
{
    t_caserne* nouv;
    nouv=malloc(sizeof(t_caserne));

    nouv->temps_de_rechargement=0;
    nouv->occupe=0;
    nouv->case_de_referenceX = 0;
    nouv->case_de_referenceY = 0;

    return nouv;
}

void caserne_liberer(t_caserne* c)
{
    free(c);
}

int caserne_place_libre(int x,int y,t_case*** kase)
{
    int i,j;
    int libre=1;
    if(!caserne_depassement_matrice(x,y))
    {
        for(i=x;i<x+CASERNE_W;i++)
        {
            for(j=y;j<y+CASERNE_H;j++)
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

int caserne_depassement_matrice(int colonne,int ligne)
{
    int depasse=1;
    if((colonne>=0)&&(colonne<NB_CASES_COL-(CASERNE_W-1))&&(ligne>=0)&&(ligne<NB_CASES_LIG-(CASERNE_H-1)))
    {
        depasse=0;
    }
    return depasse;
}

void caserne_placer(t_caserne* caserne,int x,int y,t_case*** kase)
{
    int i,j;
    caserne->case_de_referenceX=x;
    caserne->case_de_referenceY=y;
    for(i=x;i<x+CASERNE_W;i++)
    {
        for(j=y;j<y+CASERNE_H;j++)
        {
            case_remplir(kase[j][i],CASERNE,caserne);
        }
    }
}

void caserne_afficher(t_caserne* caserne,int niveau)
{
    if(niveau==NIVEAU_SOL)
    {
        draw_sprite(graphs->buffer_ville,graphs->caserne,1+TAILLE_CASE*caserne->case_de_referenceX,1+TAILLE_CASE*caserne->case_de_referenceY);
    }
    draw_trans_sprite(graphs->buffer_ville,graphs->caserne,1+TAILLE_CASE*caserne->case_de_referenceX,1+TAILLE_CASE*caserne->case_de_referenceY);
}
