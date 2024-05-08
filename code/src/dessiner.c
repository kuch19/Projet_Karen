#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "structures.h"
#include "variables.h"

//Dessine un point en SVG
char* dessinerPoint(FILE *file, POINT p, int r) { 
  char* codePoint = malloc (sizeof (*codePoint) * 500);
  sprintf(codePoint,"<circle cx=\"%f\" cy=\"%f\" r=\"%d\" stroke=\"black\" stroke-width=\"1\" fill=\"black\"/>",p.x,p.y,r);
  fprintf(file,"%s\n", codePoint);
  return codePoint;
}

void affichage_tous_les_points(POINT tab[], FILE* file , int N){
  for (int i = 0; i < N; i++) {
    POINT p;
    p.x = ((tab[i].x-inf)*1800/(sup-inf))+100;
    p.y = ((tab[i].y-inf)*1800/(sup-inf))+100;
    dessinerPoint(file, p, 8);
  }
}

char* dessinerCercle(FILE *file, double x, double y, double r, int algo)  {
  char* codeCercle = malloc (sizeof (*codeCercle) * 500);
  if (algo == 1) {
    sprintf(codeCercle,"<circle cx=\"%f\" cy=\"%f\" r=\"%f\" stroke=\"red\" stroke-width=\"3\" fill=\"transparent\" fill-opacity=\"0\" />",x,y,r);
  }else if (algo == 2){
    sprintf(codeCercle,"<circle cx=\"%f\" cy=\"%f\" r=\"%f\" stroke=\"blue\" stroke-width=\"5\" fill=\"transparent\" fill-opacity=\"0\" />",x,y,r);
  }
  fprintf(file,"%s\n", codeCercle);
  return codeCercle;
}