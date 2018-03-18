#ifndef DATE_H_INCLUDED
#define DATE_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>

#include "define.h"

typedef struct date
{
    double secondes;
    int minutes;
    int heures;
} t_date;

t_date* date_allouer();

void date_actualiser(t_date* date);

void date_liberer(t_date* date);

#endif // DATE_H_INCLUDED
