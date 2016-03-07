#include "pave.h"

pave * creer_pave(GLfloat a, GLfloat b, GLfloat c, GLfloat rouge, GLfloat vert, GLfloat bleu){
	pave * un_pave=(pave *)malloc(sizeof(pave));
	un_pave->longueur=a;
	un_pave->largeur=b;
	un_pave->hauteur=c;
	int i;
	for(i=0;i<=7;i++)
		un_pave->les_sommets[i]=(sommet*)malloc(sizeof(sommet));
	
	for(i=0;i<=5;i++)
		un_pave->les_faces[i]=(face*)malloc(sizeof(face));	
	
	for(i=0;i<=5;i++){	
		un_pave->les_faces[i]->coul.r=rouge;
		un_pave->les_faces[i]->coul.g=vert;
		un_pave->les_faces[i]->coul.b=bleu;
	}

	un_pave->les_sommets[0]->x=-a/2.0;
	un_pave->les_sommets[0]->y=-b/2.0;
	un_pave->les_sommets[0]->z=c/2.0;

	un_pave->les_sommets[1]->x=a/2.0;
	un_pave->les_sommets[1]->y=-b/2.0;
	un_pave->les_sommets[1]->z=c/2.0;

	un_pave->les_sommets[2]->x=a/2.0;
	un_pave->les_sommets[2]->y=b/2.0;
	un_pave->les_sommets[2]->z=c/2.0;

	un_pave->les_sommets[3]->x=-a/2.0;
	un_pave->les_sommets[3]->y=b/2.0;
	un_pave->les_sommets[3]->z=c/2.0;

	un_pave->les_sommets[4]->x=a/2.0;
	un_pave->les_sommets[4]->y=-b/2.0;
	un_pave->les_sommets[4]->z=-c/2.0;

	un_pave->les_sommets[5]->x=-a/2.0;
	un_pave->les_sommets[5]->y=-b/2.0;
	un_pave->les_sommets[5]->z=-c/2.0;

	un_pave->les_sommets[6]->x=-a/2.0;
	un_pave->les_sommets[6]->y=b/2.0;
	un_pave->les_sommets[6]->z=-c/2.0;

	un_pave->les_sommets[7]->x=a/2.0;
	un_pave->les_sommets[7]->y=b/2.0;
	un_pave->les_sommets[7]->z=-c/2.0;

	for(i=0;i<=5;i++){
		calcul_normale(	un_pave->les_sommets[faces[i][0]]->x,
						un_pave->les_sommets[faces[i][0]]->y,
						un_pave->les_sommets[faces[i][0]]->z,
						un_pave->les_sommets[faces[i][1]]->x,
						un_pave->les_sommets[faces[i][1]]->y,
						un_pave->les_sommets[faces[i][1]]->z,
						un_pave->les_sommets[faces[i][2]]->x,
						un_pave->les_sommets[faces[i][2]]->y,
						un_pave->les_sommets[faces[i][2]]->z,
						&un_pave->les_faces[i]->norm);
						
	un_pave->les_faces[i]->centre.x=(un_pave->les_sommets[faces[i][0]]->x + un_pave->les_sommets[faces[i][2]]->x)/2	;		
	un_pave->les_faces[i]->centre.y=(un_pave->les_sommets[faces[i][0]]->y + un_pave->les_sommets[faces[i][2]]->y)/2	;		
	un_pave->les_faces[i]->centre.z=(un_pave->les_sommets[faces[i][0]]->z + un_pave->les_sommets[faces[i][2]]->z)/2	;		
						
	}




	return un_pave;
}


void affiche(pave *p){
	int i,j;
	glBegin(GL_QUADS);
	for(i=0;i<=5;i++){
		glNormal3f(p->les_faces[i]->norm.x,p->les_faces[i]->norm.y,p->les_faces[i]->norm.z);
		glColor3f(p->les_faces[i]->coul.r,p->les_faces[i]->coul.g,p->les_faces[i]->coul.b);
		for(j=0;j<=3;j++)
			glVertex3f(p->les_sommets[faces[i][j]]->x,p->les_sommets[faces[i][j]]->y,p->les_sommets[faces[i][j]]->z);
	}
	glEnd();
	
	glBegin(GL_LINES);	
	for(i=0;i<=5;i++){
		glColor3f(1.0f,1.0f,0.0f);
		glVertex3f(p->les_faces[i]->centre.x,p->les_faces[i]->centre.y,p->les_faces[i]->centre.z);
		glVertex3f(p->les_faces[i]->centre.x+p->les_faces[i]->norm.x,
			p->les_faces[i]->centre.y+p->les_faces[i]->norm.y,
			p->les_faces[i]->centre.z+p->les_faces[i]->norm.z);
	}
	glEnd();
}
