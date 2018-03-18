#include "habitation.h"

t_habitation* habitation_creer()
{
    int i;
    t_habitation* nouv;

    nouv=malloc(sizeof(t_habitation));
    nouv->chateaux_fournisseurs=malloc(FOURNISSEUR_MAX*sizeof(t_fournisseur));
    for(i=0; i<FOURNISSEUR_MAX; i++)
    {
        nouv->chateaux_fournisseurs[i].id_fournisseur.caseX = -1;
        nouv->chateaux_fournisseurs[i].id_fournisseur.caseY = -1;
        nouv->chateaux_fournisseurs[i].qte_eau_distribuee = 0;
    }

    nouv->chrono = 0.00;
    nouv->feu= PAS_EN_FEU;
    nouv->stade= STADE_TERRAIN_VAGUE;
    nouv->case_de_referenceX = 0;
    nouv->case_de_referenceY = 0;
    nouv->electricite = 0;
    nouv->eau = 0;
    nouv->indice = 0;
    nouv->id_centrale_fournisseuse.caseX = -1;
    nouv->id_centrale_fournisseuse.caseY = -1;
    return nouv;
}

void habitation_liberer(t_habitation* h)
{
    free(h->chateaux_fournisseurs);
    free(h);
}

int habitation_place_libre(int col,int lig,t_case*** kase)
{
    int i,j;
    int libre=1;
    if(!habitation_depassement_matrice(col,lig))
    {
        for(i=lig; i<lig+HABITATION_H; i++)
        {
            for(j=col; j<col+HABITATION_W; j++)
            {
                ///PEUT MIEUX FAIRE (RETURN LIBRE IF LIBRE ==0)
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

int habitation_depassement_matrice(int colonne,int ligne)
{
    int depasse=1;
    if((colonne>=0)&&(colonne<=NB_CASES_COL-HABITATION_W)&&(ligne>=0)&&(ligne<=NB_CASES_LIG-HABITATION_H))
    {
        depasse=0;
    }
    return depasse;
}

void habitation_placer(t_habitation* h,int col,int lig,t_case*** kase)
{
    int i,j;
    h->case_de_referenceX=col;
    h->case_de_referenceY=lig;
    for(i=lig; i<lig+HABITATION_H; i++)
    {
        for(j=col; j<col+HABITATION_W; j++)
        {
            case_remplir(kase[i][j],HABITATION,h);
        }
    }
}

int habitation_nbhabitants(t_habitation* habitation)
{
    int habitants = NB_HABITANTS_RUINE;

    switch(habitation->stade)
    {
    case STADE_RUINE :
        habitants=NB_HABITANTS_RUINE; // ruine
        break;

    case STADE_TERRAIN_VAGUE :
        habitants=NB_HABITANTS_TERRAIN_VAGUE; // terrain vague
        break;

    case STADE_CABANE :
        habitants=NB_HABITANTS_CABANE; // cabane
        break;

    case STADE_MAISON :
        habitants=NB_HABITANTS_MAISON; // maison
        break;

    case STADE_IMMEUBLE :
        habitants=NB_HABITANTS_IMMEUBLE; // immeuble
        break;

    case STADE_GRATTECIEL:
        habitants=NB_HABITANTS_GRATTECIEL; // gratte-ciel
    }
    return habitants;
}

int habitation_comparer(const void* a, const void* b) // il manque un degré de const, pourquoi?
{
    const t_habitation* const* h1 = a; // en théorie ici il manque un degré de "const", comment savoir que c'était un pointeur constant sur pointeur (non constant) d'habitation constante qu'on voulait??
    const t_habitation* const* h2 = b;
    if((*h1)->stade < (*h2)->stade)
    {
        return 1;
    }
    else if((*h1)->stade > (*h2)->stade)
    {
        return -1;
    }
    else
        return 0;
}

void habitation_charger(t_habitation* hab, FILE* fp)
{
    fscanf(fp,"%d %d %d %f %d",&hab->case_de_referenceX,&hab->case_de_referenceY,&hab->stade,&hab->chrono,&hab->feu);
}

void habitation_sauvegarder(t_habitation* hab, FILE* fp)
{
    fprintf(fp,"%d %d %d %f %d\n",hab->case_de_referenceX, hab->case_de_referenceY,hab->stade, hab->chrono, hab->feu);
}

void habitation_afficher(t_habitation* hab,int niveau)
{
    int img_utilisee;

    if(hab->feu >= EN_FEU)
    {
        img_utilisee=0;
    }
    else
    {
        img_utilisee=1;
    }


    switch(hab->stade)
    {
    case 0:if(((niveau==NIVEAU_EAU)&&(!hab->eau))||((niveau==NIVEAU_ELEC)&&(!hab->electricite)))
        {
            draw_lit_sprite(graphs->buffer_ville,graphs->ruine,1+TAILLE_CASE*hab->case_de_referenceX,1+TAILLE_CASE*hab->case_de_referenceY,makecol(255,0,0));
        }
        else draw_sprite(graphs->buffer_ville,graphs->ruine,1+TAILLE_CASE*hab->case_de_referenceX,1+TAILLE_CASE*hab->case_de_referenceY);
        break;
    case 1:if(((niveau==NIVEAU_EAU)&&(!hab->eau))||((niveau==NIVEAU_ELEC)&&(!hab->electricite)))
        {
            draw_lit_sprite(graphs->buffer_ville,graphs->terrain_vague,1+TAILLE_CASE*hab->case_de_referenceX,1+TAILLE_CASE*hab->case_de_referenceY,makecol(255,0,0));
        }
        else draw_sprite(graphs->buffer_ville,graphs->terrain_vague,1+TAILLE_CASE*hab->case_de_referenceX,1+TAILLE_CASE*hab->case_de_referenceY);
        break;
    case 2:if(((niveau==NIVEAU_EAU)&&(!hab->eau))||((niveau==NIVEAU_ELEC)&&(!hab->electricite)))
        {
            draw_lit_sprite(graphs->buffer_ville,graphs->cabane[img_utilisee],1+TAILLE_CASE*hab->case_de_referenceX,1+TAILLE_CASE*hab->case_de_referenceY,makecol(255,0,0));
        }
        else draw_sprite(graphs->buffer_ville,graphs->cabane[img_utilisee],1+TAILLE_CASE*hab->case_de_referenceX,1+TAILLE_CASE*hab->case_de_referenceY);
        break;
    case 3:if(((niveau==NIVEAU_EAU)&&(!hab->eau))||((niveau==NIVEAU_ELEC)&&(!hab->electricite)))
        {
            draw_lit_sprite(graphs->buffer_ville,graphs->maison[img_utilisee],1+TAILLE_CASE*hab->case_de_referenceX,1+TAILLE_CASE*hab->case_de_referenceY,makecol(255,0,0));
        }
        else draw_sprite(graphs->buffer_ville,graphs->maison[img_utilisee],1+TAILLE_CASE*hab->case_de_referenceX,1+TAILLE_CASE*hab->case_de_referenceY);
        break;
    case 4:if(((niveau==NIVEAU_EAU)&&(!hab->eau))||((niveau==NIVEAU_ELEC)&&(!hab->electricite)))
        {
            draw_lit_sprite(graphs->buffer_ville,graphs->immeuble[img_utilisee],1+TAILLE_CASE*hab->case_de_referenceX,1+TAILLE_CASE*hab->case_de_referenceY,makecol(255,0,0));
        }
        else draw_sprite(graphs->buffer_ville,graphs->immeuble[img_utilisee],1+TAILLE_CASE*hab->case_de_referenceX,1+TAILLE_CASE*hab->case_de_referenceY);
        break;
    case 5:if(((niveau==NIVEAU_EAU)&&(!hab->eau))||((niveau==NIVEAU_ELEC)&&(!hab->electricite)))
        {
            draw_lit_sprite(graphs->buffer_ville,graphs->gratte_ciel[img_utilisee],1+TAILLE_CASE*hab->case_de_referenceX,1+TAILLE_CASE*hab->case_de_referenceY,makecol(255,0,0));
        }
        else draw_sprite(graphs->buffer_ville,graphs->gratte_ciel[img_utilisee],1+TAILLE_CASE*hab->case_de_referenceX,1+TAILLE_CASE*hab->case_de_referenceY);
        break;
    }
    if((hab->feu)&&(hab->protegee))
        {
            draw_sprite(graphs->buffer_ville,graphs->pompier,1+TAILLE_CASE*hab->case_de_referenceX,1+TAILLE_CASE*hab->case_de_referenceY);
        }
}

void habitation_actualiser_timer(t_habitation* habitation)
{
    habitation->chrono = habitation->chrono + PAS_DU_TIMER;
}

void habitation_evoluer(t_habitation* habitation,int mode,int* argent,int nb_chateaux,int nb_centrales,int** longueurs_chateaux,int** longueurs_centrales,int* capacite_chateau,int* capacite_centrale)
{
    if(habitation->feu)
    {
        if(habitation->feu==DUREE_INCENDIE)
        {
            habitation->feu=PAS_EN_FEU;
            if(!habitation->protegee)
            {
                habitation->stade=STADE_RUINE;
            }
        }
        if( habitation->chrono >= DUREE_CYCLE)
        {
            habitation->chrono = 0;
        }
    }
    else if( habitation->chrono >= DUREE_CYCLE) // si 15 secondes se sont écoulées
    {
        habitation->chrono = 0; // on remet à 0 la durée
        *argent = *argent + habitation_recolter_impots(habitation);

        switch(mode)
        {
            case MODE_CAPITALISTE : habitation_evolution_capitaliste(habitation,nb_chateaux,nb_centrales,longueurs_chateaux,longueurs_centrales);

            break;

            case MODE_COMMUNISTE : habitation_evolution_communiste(habitation,nb_chateaux,nb_centrales,longueurs_chateaux,longueurs_centrales,capacite_chateau,capacite_centrale);
            break;
        }
    }
}

void habitation_progression(t_habitation* habitation)
{
    if((habitation->stade<STADE_GRATTECIEL)&&(habitation->stade!=STADE_RUINE))
    {
        habitation->stade+=1;
    }
}

void habitation_regression(t_habitation* habitation)
{
    if(habitation->stade==STADE_CABANE)
    {
        habitation->stade=STADE_RUINE;
    }
    if(habitation->stade>STADE_TERRAIN_VAGUE)
    {
        habitation->stade-=1;
    }
}

void habitation_evolution_communiste(t_habitation* habitation,int nb_chateaux,int nb_centrales,int** longueurs_chateaux,int** longueurs_centrales,int* capacite_chateaux,int* capacite_centrale)
{
    int i,eau_dispo=0,elec_dispo=0,quantitee_future;
    for(i=0;i<nb_chateaux;i++)
    {///ON REGARDE L'EAU DISPO SUR LE RESEAU
        if(longueurs_chateaux[i][habitation->indice])
        {
            eau_dispo+=capacite_chateaux[i];
        }
    }
    for(i=0;i<nb_centrales;i++)
    {///ON REGARDE L'ELEC DISPO SUR LE RESEAU
        if(longueurs_centrales[i][habitation->indice])
        {
            elec_dispo+=capacite_centrale[i];
        }
    }
    if((habitation->eau==0)||(habitation->electricite==0)) ///SI L'HABITATION N'EST PAS ALIM, ELLE REGRESSE
    {
        habitation_regression(habitation);
    }
    else
    {///ON REGARDE LA QUANTITEE DONT ELLE AURA BESOIN SI ELLE EVOLUE
            quantitee_future=habitation->stade+1;
            switch(quantitee_future)
            {
                case STADE_CABANE : quantitee_future = NB_HABITANTS_CABANE;
                break;

                case STADE_MAISON : quantitee_future = NB_HABITANTS_MAISON;
                break;

                case STADE_IMMEUBLE : quantitee_future = NB_HABITANTS_IMMEUBLE;
                break;

                case STADE_GRATTECIEL : quantitee_future = NB_HABITANTS_GRATTECIEL;
                break;
            }
            quantitee_future-=habitation_nbhabitants(habitation);
            if((eau_dispo>=quantitee_future)&&(elec_dispo>=quantitee_future)) ///SI LA QUANTITEE DISPONIBLE EST SUPERIEURE A LA
            {                                                               ///QUANTITEE FUTURE, ON AUGMENTE LE BATIMENT
                habitation_progression(habitation);
            }
    }
}

void habitation_evolution_capitaliste(t_habitation* habitation,int nb_chateaux,int nb_centrales,int** longueurs_chateaux,int** longueurs_centrales)
{
    int connect_elec=0,connect_eau=0,i;
    for(i=0;i<nb_chateaux;i++)
    {
        if(longueurs_chateaux[i][habitation->indice])
        {
            connect_eau=1;
        }
    }
    for(i=0;i<nb_centrales;i++)
    {
        if(longueurs_centrales[i][habitation->indice])
        {
            connect_elec=1;
        }
    }
    if((habitation->stade==STADE_TERRAIN_VAGUE)&&(connect_eau)&&(connect_elec))
    {
        habitation_progression(habitation);
    }
    else
    {
        if((habitation->eau==0)||(habitation->electricite==0))
        {
            if(habitation->stade>STADE_TERRAIN_VAGUE)
                habitation_regression(habitation);
        }
        else
        {
            if(habitation->stade<STADE_GRATTECIEL)
                    habitation_progression(habitation);
        }
    }
}

int habitation_recolter_impots(t_habitation* hab)
{
    return IMPOTS_PAR_HABITANT*habitation_nbhabitants(hab);
}

void habitation_debut_tour(t_habitation* hab)
{
    int i,alea;
    hab->eau =0;
    hab->electricite=0;
    hab->id_centrale_fournisseuse.caseX = -1;
    hab->id_centrale_fournisseuse.caseX = -1;
    ///DECLARATION ALEATOIRE D'UN INCENDIE
    if(hab->stade>=STADE_CABANE)
    {
        if(!hab->feu)
        {
            alea=rand()%PROBABILITE_INCENDIE+1;
            if(alea==PROBABILITE_INCENDIE)
            {
                hab->feu=EN_FEU;
            }
        }
        else
        {
            hab->feu+=1;
        }
    }
    hab->protegee=PAS_PROTEGEE;

    for(i=0;i<FOURNISSEUR_MAX;i++)
    {
        hab->chateaux_fournisseurs[i].qte_eau_distribuee=0;
        hab->chateaux_fournisseurs[i].id_fournisseur.caseX= -1;
        hab->chateaux_fournisseurs[i].id_fournisseur.caseY= -1;
    }
}
