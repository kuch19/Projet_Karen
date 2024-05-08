#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "structures.h"
#include "variables.h"
#include "dessiner.h"

double x_dessin,y_dessin,rayon_dessin;
POINT reference;

double dis(POINT p1, POINT p2) {
    return sqrt(pow(p2.x - p1.x, 2) + pow(p2.y - p1.y, 2));
}

void val_dessin (POINT p1, double centrex,double centrey){
    x_dessin = ((centrex-inf)*1800/(sup-inf))+100;
    y_dessin = ((centrey-inf)*1800/(sup-inf))+100;
    double n_pix = ((p1.x-inf)*1800/(sup-inf))+100;
    double n_piy = ((p1.y-inf)*1800/(sup-inf))+100;
    rayon_dessin= sqrt(pow(x_dessin - n_pix, 2) + pow(y_dessin - n_piy, 2));
}

CERCLE deux_colineaires_vertical(POINT p1, POINT p2, POINT p3){
    CERCLE my_cercle = {0,0,-1};
    double xm_BC = (p2.x + p3.x) / 2;
    double ym_BC = (p2.y + p3.y) / 2;
    double m_BC = (p3.y - p2.y) / (p3.x - p2.x);
    double a = -1 / m_BC;
    double b = ym_BC - a * xm_BC;
    // Intersection 
    my_cercle.cy = (p1.y+p2.y)/2;
    my_cercle.cx = (my_cercle.cy-b)/a;
    // Calculate the radius
    my_cercle.r = sqrt(pow(my_cercle.cx - p1.x, 2) + pow(my_cercle.cy - p1.y, 2));
    val_dessin(p1,my_cercle.cx, my_cercle.cy);
    return my_cercle;
}

CERCLE deux_colineaires_horizontal(POINT p1, POINT p2, POINT p3){
    CERCLE my_cercle = {0,0,-1};
    double xm_BC = (p2.x + p3.x) / 2;
    double ym_BC = (p2.y + p3.y) / 2;
    double m_BC = (p3.y - p2.y) / (p3.x - p2.x);
    double a = -1 / m_BC;
    double b = ym_BC - a * xm_BC;
    // Intersection 
    my_cercle.cx = (p1.x+p2.x)/2;
    my_cercle.cy = a * my_cercle.cx + b;
    // Calculate the radius
    my_cercle.r = sqrt(pow(my_cercle.cx - p1.x, 2) + pow(my_cercle.cy - p1.y, 2));
    val_dessin(p1,my_cercle.cx, my_cercle.cy);
    return my_cercle;
}

CERCLE findCircle_welz(POINT p1, POINT p2, POINT p3) {
    CERCLE trouve = {0,0,-1.0};
    printf("\n P1 x %.2f,  y %.2f",p1.x, p1.y);
    printf("\n P2 x %.2f,  y %.2f",p2.x, p2.y);
    printf("\n P3 x %.2f,  y %.2f",p3.x, p3.y);
    if (p1.x == p2.x){
        trouve = deux_colineaires_vertical(p1,p2,p3);
    }else if (p1.x == p3.x){
        trouve = deux_colineaires_vertical(p1, p3, p2);
    }else if (p2.x == p3.x){
        trouve  = deux_colineaires_vertical(p2,p3, p1);
    }else if (p1.y == p2.y){
        trouve  = deux_colineaires_horizontal(p1,p2, p3);
    }else if (p1.y == p3.y){
        trouve  = deux_colineaires_horizontal(p1,p3, p2);
    }else if (p2.y == p3.y){
        trouve  = deux_colineaires_horizontal(p2,p3, p1);
    }else{
        // AUCUN POINT COLINEAIRE
        double m1 = (p2.y - p1.y) / (p2.x - p1.x);
        double m2 = (p3.y - p2.y) / (p3.x - p2.x);
        trouve.cx = (m1 * m2 * (p3.y - p1.y) + m1 * (p2.x + p3.x) - m2 * (p1.x + p2.x)) / (2 * (m1 - m2));
        trouve.cy = -1 * (trouve.cx - (p1.x + p2.x) / 2) / m1 + (p1.y + p2.y) / 2;
        trouve.r = sqrt(pow(trouve.cx - p1.x, 2) + pow(trouve.cy- p1.y, 2));
    }
    printf("\n MI CERCLE x %.2f,  y %.2f, r %.2f\n\n", trouve.cx, trouve.cy, trouve.r);
    return trouve;
}

int colinaires(POINT p, POINT q, POINT r){
    if ((p.x == q.x && p.x == r.x) || (p.y == q.y && p.y == r.y)){
        return 1; ///Colineaires vertical ou horizontalement 
    }else{
        if (p.y != q.y && p.y != r.y){
            //POints avec des y differents et au moins un x différent 
            double d = (p.x * (q.y - r.y) + q.x * (r.y - p.y) + r.x * (p.y - q.y)) * 2 ;
            if (d == 0){
                return 1; //COLINAIRES
            }else{
                return 0; // NON COLINAIRES
            }
        }else{
            return 0; //NON COLINEAIRES 
        }
    }
}

CERCLE min_cercle_trivial(POINT* R, int tailleR){
    CERCLE dc = {0,0,-1};
    if (tailleR==0){
        return dc;
    }else if (tailleR == 1){
        dc = (CERCLE){R[0].x,R[0].y,0};
    }else if (tailleR == 2){
        double distancia = dis(R[0],R[1])/2;
        dc = (CERCLE){(R[0].x+R[1].x)/2,(R[0].y+R[1].y)/2,distancia};
        reference = R[0];
    }else{
        if(colinaires(R[0],R[1],R[2])==0){
            dc = findCircle_welz (R[0],R[1],R[2]);
            reference = R[0];
        } 
    }
    return dc;
}

int point_in_cercle_welz(POINT test, CERCLE d){
  POINT centre;
  centre.x = d.cx; 
  centre.y = d.cy; 
  double dist_point_center = dis(centre, test); 
  if (dist_point_center > d.r){
    return 0; //DEHORS
  }else{
    return 1; //INTERIEUR
  }
}

CERCLE recursion_welz (POINT* tab_copy, POINT* R, int N, int tailleR){
    CERCLE dc = {0,0,-1};
    if (N==0 || tailleR==3){
        return min_cercle_trivial(R, tailleR);
    }else{
        int indice = rand()%N;
        POINT p = tab_copy[indice];
        tab_copy[indice] = tab_copy[N-1];
        dc = recursion_welz (tab_copy, R, N-1, tailleR);
        tab_copy[N-1]= p;
        if ( point_in_cercle_welz(p,dc) == 0){
            R[tailleR] = p; 
            dc = recursion_welz (tab_copy, R, N-1, tailleR+1);  
        }            
    }
    return dc;
}

void solution_welz (POINT* tab,FILE *file, int N){
    ///Initialisation des variables 
    POINT *tab_copy = malloc(N * sizeof(POINT));
    for(int i = 0; i< N ; i++){
        tab_copy[i] = tab[i];
    }
    POINT *R = malloc(3 * sizeof(POINT));
    reference.x =0;
    reference.y =0; 

    //CALCUL CERCLE 
    CERCLE welz = recursion_welz (tab_copy, R, N, 0);
    free(tab_copy);
    free(R);

    printf("WELZ\n\ncentreX %.2f, centreY %.2f, rayon %.2f \n\n", welz.cx, welz.cy,welz.r);
    if (welz.r != -1){
        val_dessin(reference, welz.cx, welz.cy);
        dessinerCercle(file, x_dessin, y_dessin, rayon_dessin,1);
    }else{
        printf("PAS DE CERCLE DISPONIBLE");
    }
}