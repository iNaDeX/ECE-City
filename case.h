#ifndef CASE_H_INCLUDED
#define CASE_H_INCLUDED

#include <stdlib.h>
#include <stdio.h>

#include "define.h"

typedef struct kase
{
    int type;
    void* elem;
}t_case;

void case_vider(t_case*);

int case_libre(t_case*);

t_case* case_allouer();

void case_free(t_case*);

void case_remplir(t_case*, int, void*);

#endif // CASE_H_INCLUDED
