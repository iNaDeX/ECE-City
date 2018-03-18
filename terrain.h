#ifndef TERRAIN_H_INCLUDED
#define TERRAIN_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>

#include "case.h"
#include "define.h"

t_case*** terrain_allouer();

/// A APPELER APRES AVOIR LIBERE LES COLLECTIONS DE STRUCTURES (habitations, casernes, chateaux, centrales etc...)
/// SINON, fuite mémoire
void terrain_liberer(t_case*** mat);

#endif // TERRAIN_H_INCLUDED
