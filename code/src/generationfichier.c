#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "structures.h"
#include "variables.h"
#include "algowelz.h"
#include "dessiner.h"
#include "sidecenter.h"

FILE *file;
void GenerationFichierSVG(POINT* tab , int N, int choix){
  //creation et ouverture du fichier
  remove("Points.svg");
  file= fopen("Points.svg", "w");
  
  //ecriture de l'entete
  fprintf(file,"<?xml version=\"1.0\" encoding=\"utf-8\"?>\n");
  fprintf(file,"<!DOCTYPE svg PUBLIC \"-//W3C//DTD SVG 1.1//EN\"\n");
  fprintf(file,"\"http://www.w3.org/Graphics/SVG/1.1/DTD/svg11.dtd\">\n");
  fprintf(file,"<svg width=\"2000\" height=\"2000\" version=\"1.1\"\n");
  fprintf(file, "xmlns=\"http://www.w3.org/2000/svg\" style=\"background-color: white\">\n");
  fprintf(file, "<rect x=\"0\" y=\"0\" width=\"2000\" height=\"2000\" fill=\"#ffffff\" />\n");
  fprintf(file, "<line x1=\"100\" y1=\"100\" x2=\"1900\" y2=\"100\" stroke=\"black\" />\n"); // Axe x
  fprintf(file, "<text x=\"1900\" y=\"100\" font-family=\"Arial\" font-size=\"20\">%d</text>\n", sup);
  fprintf(file, "<line x1=\"100\" y1=\"100\" x2=\"100\" y2=\"1900\" stroke=\"black\" />\n"); // Axe y
  fprintf(file, "<text x=\"100\" y=\"100\" font-family=\"Arial\" font-size=\"20\">%d</text>\n", inf);
  fprintf(file, "<text x=\"100\" y=\"1900\" font-family=\"Arial\" font-size=\"20\">%d</text>\n", sup);    

   //affichage des points
  affichage_tous_les_points(tab, file, N);

  if(choix == 1) {
    //solution_algo_naif(tab, file, N); //CALCULE ET DESSINE
  }else if (choix == 2){
    POINT center;
    center.x = 0;
    center.y = 0; 
    POINT* I = malloc(N * sizeof(POINT));
    I[0].x = 1; 
    I[0].y = 2; 
    I[1].x = 2; 
    I[1].y = 2; 
    I[2].x = 3; 
    I[2].y = 2; 
    int cote = side_center(center,I, 3);
    printf("COTE %.d", cote);
    solution_welz(tab, file, N); //CALCULE ET DESSINE
  }  
  //fin du programme et fermer le fichier
  fprintf(file, "</svg>\n");
  fclose(file);
}
