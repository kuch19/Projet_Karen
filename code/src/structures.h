#ifndef STRUCTURES_H
#define STRUCTURES_H

typedef struct model_point{
	double x;
	double y;
} POINT;

typedef struct model_cercle{
	double cx;
	double cy;
	double r;
} CERCLE;

typedef struct model_convex{
	POINT p;
	double pente; 
} CONVEX;


#endif
