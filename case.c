#include <stdio.h>
#include "case.h"

void case_vider(t_case* k)
{
    k->elem=NULL;
    k->type=VIDE;
}

void case_remplir(t_case* k,int type,void* elem)
{
    k->type=type;
    k->elem=elem;
}

t_case* case_allouer()
{
    t_case* nouv;
    nouv=malloc(sizeof(t_case));

    case_vider(nouv);

    return nouv;
}

int case_libre(t_case* kase)
{
    int libre=1;

    if(kase->type!=VIDE)
    {
        libre=0;
    }
    return libre;
}

void case_free(t_case* k)
{
    free(k);
}
