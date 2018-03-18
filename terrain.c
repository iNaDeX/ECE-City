#include "terrain.h"

t_case*** terrain_allouer()
{
    int lig,col;
    t_case*** nouv;

    nouv = (t_case***)malloc(NB_CASES_LIG*sizeof(t_case**));
    for(lig=0;lig<NB_CASES_LIG;lig++)
    {
        nouv[lig] = (t_case**)malloc(NB_CASES_COL*sizeof(t_case*));
    }

    for(lig=0;lig<NB_CASES_LIG;lig++)
    {
        for(col=0;col<NB_CASES_COL;col++)
        {
            nouv[lig][col] = case_allouer();
        }
    }

    return nouv;
}

/// A APPELER APRES AVOIR LIBERE LES COLLECTIONS DE STRUCTURES (habitations, casernes, chateaux, centrales etc...)
/// SINON, fuite mémoire
void terrain_liberer(t_case*** mat)
{
    int lig,col;

    for(lig=0;lig<NB_CASES_LIG;lig++)
    {
        for(col=0;col<NB_CASES_COL;col++)
        {
            case_free(mat[lig][col]);
        }
    }

    for(lig=0;lig<NB_CASES_LIG;lig++)
    {
        free(mat[lig]);
    }

    free(mat);
}
