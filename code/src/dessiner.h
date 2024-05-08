#ifndef DESSINER_H
#define DESSINER_H

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "structures.h"
#include "variables.h"

char* dessinerPoint(FILE *file, POINT p, int r);
void affichage_tous_les_points(POINT tab[], FILE* file , int N);
char* dessinerCercle(FILE *file, double x, double y, double r, int algo);

#endif
