#ifndef ALGOWELZ_H
#define ALGOWELZ_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "structures.h"
#include "variables.h"

double dis(POINT p1, POINT p2);
void val_dessin (POINT p1, double centrex,double centrey);
CERCLE deux_colineaires_horizontal(POINT p1, POINT p2, POINT p3);
CERCLE deux_colineaires_vertical(POINT p1, POINT p2, POINT p3);
CERCLE findCircle_welz(POINT p1, POINT p2, POINT p3) ;
int colinaires(POINT p, POINT q, POINT r);
CERCLE min_cercle_trivial(POINT* R, int tailleR);
int point_in_cercle_welz(POINT test, CERCLE d);
CERCLE recursion_welz (POINT* tab_copy, POINT* R, int N, int tailleR);
void solution_welz (POINT* tab,FILE *file, int N);

#endif
