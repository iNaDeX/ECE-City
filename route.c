#include "route.h"

t_route* route_creer()
{
    t_route* nouv;
    nouv=malloc(sizeof(t_route));

    nouv->case_de_referenceX = 0;
    nouv->case_de_referenceY = 0;
    nouv->type = TYPE_ROUTE_HORIZONTALE;

    return nouv;
}

void route_liberer(t_route* route)
{
    free(route);
}

void route_actualiser(t_route* route,t_case*** kase)
{
    int colonne,ligne;
    colonne=route->case_de_referenceX;
    ligne=route->case_de_referenceY;
    route->type=TYPE_ROUTE_HORIZONTALE;
    if(ligne>0)
    {
        if(kase[ligne-1][colonne]->type==ROUTE) route->type=TYPE_ROUTE_VERTICALE;
    }
    if(ligne<NB_CASES_LIG-1)
    {
        if(kase[ligne+1][colonne]->type==ROUTE) route->type=TYPE_ROUTE_VERTICALE;
    }
    if(colonne>0)
    {
        if(kase[ligne][colonne-1]->type==ROUTE) route->type=TYPE_ROUTE_HORIZONTALE;
    }
    if(colonne<NB_CASES_COL-1)
    {
        if(kase[ligne][colonne+1]->type==ROUTE) route->type=TYPE_ROUTE_HORIZONTALE;
    }
    if((colonne>0)&&(ligne>0))
    {
        if((kase[ligne][colonne-1]->type==ROUTE)&&(kase[ligne-1][colonne]->type==ROUTE)) route->type=TYPE_ROUTE_HAUT_GAUCHE;
    }
    if((colonne<NB_CASES_COL-1)&&(ligne<NB_CASES_LIG-1))
    {
        if((kase[ligne][colonne+1]->type==ROUTE)&&(kase[ligne+1][colonne]->type==ROUTE)) route->type=TYPE_ROUTE_BAS_DROITE;
    }
    if((colonne<NB_CASES_COL-1)&&(ligne>0))
    {
        if((kase[ligne][colonne+1]->type==ROUTE)&&(kase[ligne-1][colonne]->type==ROUTE)) route->type=TYPE_ROUTE_HAUT_DROITE;
    }
    if((colonne>0)&&(ligne<NB_CASES_LIG-1))
    {
        if((kase[ligne][colonne-1]->type==ROUTE)&&(kase[ligne+1][colonne]->type==ROUTE)) route->type=TYPE_ROUTE_BAS_GAUCHE;
    }
    if((colonne<NB_CASES_COL-1)&&(ligne<NB_CASES_LIG-1)&&(colonne>0))
    {
        if((kase[ligne][colonne+1]->type==ROUTE)&&(kase[ligne+1][colonne]->type==ROUTE)&&(kase[ligne][colonne-1]->type==ROUTE)) route->type=TYPE_ROUTE_GAUCHE_DROITE_BAS;
    }
    if((colonne<NB_CASES_COL-1)&&(ligne>0)&&(colonne>0))
    {
        if((kase[ligne][colonne+1]->type==ROUTE)&&(kase[ligne-1][colonne]->type==ROUTE)&&(kase[ligne][colonne-1]->type==ROUTE)) route->type=TYPE_ROUTE_GAUCHE_DROITE_HAUT;
    }
    if((colonne<NB_CASES_COL-1)&&(ligne<NB_CASES_LIG-1)&&(ligne>0))
    {
        if((kase[ligne][colonne+1]->type==ROUTE)&&(kase[ligne+1][colonne]->type==ROUTE)&&(kase[ligne-1][colonne]->type==ROUTE)) route->type=TYPE_ROUTE_DROITE_BAS_HAUT;
    }
    if((colonne>0)&&(ligne<NB_CASES_LIG-1)&&(ligne>0))
    {
        if((kase[ligne][colonne-1]->type==ROUTE)&&(kase[ligne+1][colonne]->type==ROUTE)&&(kase[ligne-1][colonne]->type==ROUTE)) route->type=TYPE_ROUTE_GAUCHE_BAS_HAUT;
    }
    if((colonne<NB_CASES_COL-1)&&(ligne<NB_CASES_LIG-1)&&(ligne>0)&&(colonne>0))
    {
        if((kase[ligne][colonne+1]->type==ROUTE)&&(kase[ligne+1][colonne]->type==ROUTE)&&(kase[ligne-1][colonne]->type==ROUTE)&&(kase[ligne][colonne-1]->type==ROUTE)) route->type=TYPE_ROUTE_INTERSECTION;
    }
}

void route_actualiser_voisins(t_route* route,t_case*** kase)
{
    int ligne,colonne;

    ligne=route->case_de_referenceY;
    colonne=route->case_de_referenceX;

    if(colonne>0)
    {
        if(kase[ligne][colonne-1]->type==ROUTE)
        {
            route_actualiser(kase[ligne][colonne-1]->elem,kase);
        }
    }
    if(colonne<NB_CASES_COL-1)
    {
        if(kase[ligne][colonne+1]->type==ROUTE)
        {
            route_actualiser(kase[ligne][colonne+1]->elem,kase);
        }
    }
    if(ligne<NB_CASES_LIG-1)
    {
        if(kase[ligne+1][colonne]->type==ROUTE)
        {
            route_actualiser(kase[ligne+1][colonne]->elem,kase);
        }
    }
    if(ligne>0)
    {
        if(kase[ligne-1][colonne]->type==ROUTE)
        {
            route_actualiser(kase[ligne-1][colonne]->elem,kase);
        }
    }
}

int route_place_libre(int colonne,int ligne,t_case*** kase)
{
    int libre=1;
    if(!route_depassement_matrice(colonne,ligne))
    {
        libre=case_libre(kase[ligne][colonne]);
    }
    else libre=0;
    return libre;
}

int route_depassement_matrice(int colonne,int ligne)
{
    int depasse=1;
    if((colonne>=0)&&(colonne<NB_CASES_COL)&&(ligne>=0)&&(ligne<NB_CASES_LIG))
    {
        depasse=0;
    }
    return depasse;
}

void route_placer(t_route* route,int colonne,int ligne,t_case*** kase)
{
    route->case_de_referenceX=colonne;
    route->case_de_referenceY=ligne;

    route_actualiser(route,kase);

    case_remplir(kase[ligne][colonne],ROUTE,route);
    route_actualiser_voisins(route,kase);
}

void route_afficher(t_route* route,int niveau)
{
    draw_sprite(graphs->buffer_ville,graphs->route[niveau][route->type],1+TAILLE_CASE*route->case_de_referenceX,1+TAILLE_CASE*route->case_de_referenceY);
}
