#include "date.h"

t_date* date_allouer()
{
    t_date* nouv = NULL;
    nouv = (t_date*)malloc(1*sizeof(t_date));

    nouv->heures = 0;
    nouv->minutes = 0;
    nouv->secondes = 0;

    return nouv;
}

void date_actualiser(t_date* date)
{
    date->secondes = date->secondes + PAS_DU_TIMER;
    if(date->secondes>= 60)
    {
        date->minutes += 1;
        date->secondes = 0.00;
    }
    if(date->minutes>=60)
    {
        date->heures +=1;
        date->minutes = 0;
    }
}

void date_liberer(t_date* d)
{
    free(d);
}


