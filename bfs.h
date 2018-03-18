#ifndef BFS_H_INCLUDED
#define BFS_H_INCLUDED

#include <stdlib.h>
#include <stdio.h>

#include "case.h"
#include "file.h"
#include "define.h"
#include "collection_habitations.h"
#include "route.h"

typedef struct bfs
{
    int ordre;
    int case_de_referenceX;
    int case_de_referenceY;

}t_bfs;

int* recherchepluscourtchemin(t_bfs* bfs,t_case*** kase);

void tester_voisins(t_case*** kase,int ligne,int colonne,int* longueurs,int marque[NB_CASES_LIG][NB_CASES_COL],t_file* file);

#endif // BFS_H_INCLUDED
