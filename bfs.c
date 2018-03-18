#include "bfs.h"

int* recherchepluscourtchemin(t_bfs* bfs,t_case*** kase)
{
    t_file* file;
    t_case* temp;
    int marque[NB_CASES_LIG][NB_CASES_COL];
    int ligne,colonne,compteur;
    int* longueurs;

    longueurs=malloc(bfs->ordre*sizeof(int));
    for(compteur=0;compteur<bfs->ordre;compteur++)
    {
        longueurs[compteur]=0;
    }

    file=file_creer();
    for(ligne=0;ligne<NB_CASES_LIG;ligne++)
    {
        for(colonne=0;colonne<NB_CASES_COL;colonne++)
        {
            marque[ligne][colonne]=0;
        }
    }

    if(kase[bfs->case_de_referenceY][bfs->case_de_referenceX]->type==CHATEAU)
    {
        for(ligne=bfs->case_de_referenceY;ligne<bfs->case_de_referenceY+CHATEAU_H;ligne++)
        {
            for(colonne=bfs->case_de_referenceX;colonne<bfs->case_de_referenceX+CHATEAU_W;colonne++)
            {
                tester_voisins(kase,ligne,colonne,longueurs,marque,file);

            }
        }
    }

    if(kase[bfs->case_de_referenceY][bfs->case_de_referenceX]->type==CASERNE)
    {
        for(ligne=bfs->case_de_referenceY;ligne<bfs->case_de_referenceY+CASERNE_H;ligne++)
        {
            for(colonne=bfs->case_de_referenceX;colonne<bfs->case_de_referenceX+CASERNE_W;colonne++)
            {
                tester_voisins(kase,ligne,colonne,longueurs,marque,file);

            }
        }
    }

    if(kase[bfs->case_de_referenceY][bfs->case_de_referenceX]->type==CENTRALE)
    {
        for(ligne=bfs->case_de_referenceY;ligne<bfs->case_de_referenceY+CENTRALE_H;ligne++)
        {
            for(colonne=bfs->case_de_referenceX;colonne<bfs->case_de_referenceX+CENTRALE_W;colonne++)
            {
                tester_voisins(kase,ligne,colonne,longueurs,marque,file);

            }
        }
    }
    while(!file_vide(file))
    {
        temp=file_defiler(file);
        ligne=((t_route*)temp->elem)->case_de_referenceY;
        colonne=((t_route*)temp->elem)->case_de_referenceX;
        tester_voisins(kase,ligne,colonne,longueurs,marque,file);
    }
    free(file); // free et non pas file_detruire car il ne faut pas détruire les éléments de la file, qui sont directement
    // des éléments (des cases) de notre terrain !
    return longueurs;
}

void tester_voisins(t_case*** kase,int ligne,int colonne,int* longueurs,int marque[NB_CASES_LIG][NB_CASES_COL],t_file* file)
{
    if(ligne>0)
    {
        if(marque[ligne-1][colonne]==0)
        {
            if(kase[ligne-1][colonne]->type==ROUTE)
            {
                file_enfiler(file,kase[ligne-1][colonne]);
                marque[ligne-1][colonne]=marque[ligne][colonne]+1;
            }
            if(kase[ligne-1][colonne]->type==HABITATION)
            {
                if((longueurs[((t_habitation*) kase[ligne-1][colonne]->elem)->indice]>marque[ligne][colonne])||(longueurs[((t_habitation*) kase[ligne-1][colonne]->elem)->indice]==0))
                {
                    longueurs[((t_habitation*) kase[ligne-1][colonne]->elem)->indice]=marque[ligne][colonne];
                }
            }
        }
    }
    if(ligne<NB_CASES_LIG-1)
    {
        if(marque[ligne+1][colonne]==0)
        {
            if(kase[ligne+1][colonne]->type==ROUTE)
            {
                file_enfiler(file,kase[ligne+1][colonne]);
                marque[ligne+1][colonne]=marque[ligne][colonne]+1;
            }
            if(kase[ligne+1][colonne]->type==HABITATION)
            {
                if((longueurs[((t_habitation*) kase[ligne+1][colonne]->elem)->indice]>marque[ligne][colonne])||(longueurs[((t_habitation*) kase[ligne+1][colonne]->elem)->indice]==0))
                {
                    longueurs[((t_habitation*) kase[ligne+1][colonne]->elem)->indice]=marque[ligne][colonne];
                }
            }
        }
    }
    if(colonne<NB_CASES_COL-1)
    {
        if(marque[ligne][colonne+1]==0)
        {
            if(kase[ligne][colonne+1]->type==ROUTE)
            {
                file_enfiler(file,kase[ligne][colonne+1]);
                marque[ligne][colonne+1]=marque[ligne][colonne]+1;
            }
            if(kase[ligne][colonne+1]->type==HABITATION)
            {
                if((longueurs[((t_habitation*) kase[ligne][colonne+1]->elem)->indice]>marque[ligne][colonne])||(longueurs[((t_habitation*) kase[ligne][colonne+1]->elem)->indice]==0))
                {
                    longueurs[((t_habitation*) kase[ligne][colonne+1]->elem)->indice]=marque[ligne][colonne];
                }
            }
        }
    }
    if(colonne>0)
    {
        if(marque[ligne][colonne-1]==0)
        {
            if(kase[ligne][colonne-1]->type==ROUTE)
            {
                file_enfiler(file,kase[ligne][colonne-1]);
                marque[ligne][colonne-1]=marque[ligne][colonne]+1;
            }
            if(kase[ligne][colonne-1]->type==HABITATION)
            {
                if((longueurs[((t_habitation*) kase[ligne][colonne-1]->elem)->indice]>marque[ligne][colonne])||(longueurs[((t_habitation*) kase[ligne][colonne-1]->elem)->indice]==0))
                {
                    longueurs[((t_habitation*) kase[ligne][colonne-1]->elem)->indice]=marque[ligne][colonne];
                }
            }
        }
    }
}
