#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "structures.h"
#include "variables.h"

int rand_a_b (int a, int b){
  return rand() % (b - a) + a;
}

void coord_aleatoires(POINT* tab){
    char *used = calloc(1000 * 1000, sizeof(char));
    if (!used) {
        perror("Allocation failed");
        exit(EXIT_FAILURE);
    }
    int xx, yy, idx;
    for (int i = 0 ; i < N ; i++){
        do{
            if (xmin != xmax){
                xx = rand_a_b(xmin, xmax);
            }else{
                xx = xmin;
            } 
            if (ymin != ymax){
                yy = rand_a_b(ymin, ymax);
            }else{
                yy = ymin;
            } 
            idx = (xx - xmin) * 1000 + (yy - ymin);
        }while(used[idx]);
        used[idx]=1; //marqué

        tab[i].x = xx;
        tab[i].y = yy;
        printf("%d , %d \n", xx,yy);
    }
    if (inf == sup ){
        inf = sup - 1; 
        sup = sup+1;
    }
    free(used);
}