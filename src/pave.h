#ifndef PAVE_H
#define PAVE_H

#include "normale.h"
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <unistd.h>
#include <stdio.h> 
#include <stdlib.h> 

/* CCW FACE_AVANT, FACE_ARRIERE, ... */
static int faces[][4]={{0,1,2,3},{4,5,6,7},{1,4,7,2},{0,3,6,5},{2,7,6,3},{1,0,5,4}};
static int sommets[][3]={{0,3,5},{0,2,5},{0,2,4},{0,3,4},{1,2,5},{1,3,5},{1,3,4},{1,2,4}};

struct s_point{
	GLfloat x,y,z;
};typedef struct s_point point;

struct s_sommet{
	GLfloat x,y,z;
}; typedef struct s_sommet sommet;

struct s_couleur{
	GLfloat r,g,b,alpha;
}; typedef struct s_couleur couleur;

struct s_face{
	struct normale norm;
	couleur coul;
	point centre;
}; typedef struct s_face face;

struct s_pave{
	GLfloat longueur;
	GLfloat largeur;
	GLfloat hauteur;
	sommet * les_sommets[8];
	face * les_faces[6];
}; typedef struct s_pave pave;

pave * creer_pave(GLfloat, GLfloat, GLfloat, GLfloat, GLfloat, GLfloat);
void affiche(pave*);

#endif
