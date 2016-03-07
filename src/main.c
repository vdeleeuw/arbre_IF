// gcc main.c actions.o axes.o init.o lumiere.o switch_blend.o  switch_light.o VM_init.o -lm -lGL -lGLU -lglut -o test

#include "init.h"
#include "axes.h"
#include "VM_init.h"
#include "pave.h"
#include "arbre.h"
#include <stdlib.h>
#include <time.h>
#include <math.h>

//variable de lumiere
extern GLuint light;

//variables de camera
GLfloat xrot = 0.0f;   
GLfloat yrot = 0.0f;   
GLfloat z = -70.0f; 

//variables de mouvement
GLint dep=0;
GLint orientation=0;
GLint old_orien=0;
GLfloat brasun_rot1=0.0f;
GLfloat brasun_rot2=0.0f;
GLfloat brasdeux_rot1=0.0f;
GLfloat brasdeux_rot2=0.0f;

//variables de position
GLint posx=0.0f;
GLint posz=0.0f;
GLint xSoleil=0.0f;
GLint zSoleil=0.0f;
GLfloat t_arbre;
GLint tmp_posx=0;
GLint tmp_posz=0;

//variables de constructions
GLfloat t_monde=50.0f;

//tableau de texture
extern GLuint textures[13];
int num_image=1;
int vitesse_anim=0;

GLvoid Modelisation()
{
	//lumieres 
	glEnable(GL_LIGHTING);
	glEnable(GL_COLOR_MATERIAL);

	GLfloat la[4] = {0.25,0.25,0.25,0.0};
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, la);

	GLfloat l0a[4] = {0.0,0.0,0.0,0.0};
	glLightfv(GL_LIGHT0, GL_AMBIENT, l0a);
	GLfloat l0d[4] = {0.5,0.5,0.5,0.0};
	glLightfv(GL_LIGHT0, GL_DIFFUSE, l0d);
	GLfloat l0s[4] = {0.9,0.9,0.9,0.0};
	glLightfv(GL_LIGHT0, GL_SPECULAR, l0s);

	GLfloat l1a[4] = {0.0,0.0,0.0,0.0};
	glLightfv(GL_LIGHT1, GL_AMBIENT, l1a);
	GLfloat l1d[4] = {0.5,0.5,0.5,0.0};
	glLightfv(GL_LIGHT1, GL_DIFFUSE, l1d);
	GLfloat l1s[4] = {0.9,0.9,0.9,0.0};
	glLightfv(GL_LIGHT1, GL_SPECULAR, l1s);

  // Entre glPushMatrix et glPopMatrix s'écrit la description de la scène.
  VM_init();
	
	randomArbre(5000);

	//variables de constructions
	GLfloat h_tronc=10.0f;
	GLfloat lL_tronc=5.0f;	
	GLfloat t_feuillage=10.0f;
	GLfloat h_racine=3.0f;
	GLfloat lL_racine=1.0f;	
	GLfloat l_bras=5.0f;
	GLfloat L_bras=1.0f;
	GLfloat h_bras=1.0f;
	t_arbre=(t_feuillage>lL_tronc) ? t_feuillage : lL_tronc;

	if(old_orien != orientation){
		tmp_posx=0;
		tmp_posz=0;
		old_orien=orientation;
	}

  // Entre glPushMatrix et glPopMatrix s'écrit la description de la scène.
  glPushMatrix();

		glPushMatrix();
			if(light){
				glDisable(GL_LIGHTING);
				glDisable(GL_COLOR_MATERIAL);
			}		

			glPushMatrix();
				glTranslatef(xSoleil,h_tronc+t_feuillage+2.0f,zSoleil);
				glutSolidSphere(2.0f,20.0f,20.0f);
			glPopMatrix();	
		
			if(light){
				glEnable(GL_LIGHTING);
				glEnable(GL_COLOR_MATERIAL);
				GLfloat LightPosition[] = {xSoleil,h_tronc+t_feuillage+2.0f,zSoleil, 1.0f };
				glLightfv(GL_LIGHT0, GL_POSITION, LightPosition);
				glEnable(GL_LIGHT0);
			}else
				glDisable(GL_LIGHT0);
		
			GLfloat LightDirection[] = { 0.0f, 1.0f, 0.0f, 0.0f };
			glLightfv(GL_LIGHT1, GL_POSITION, LightDirection);
			glEnable(GL_LIGHT1);
		glPopMatrix();

		//mise en place du sol ou la scene se déroule
		glPushMatrix();
			glColor3f(1.0f,1.0f,1.0f);	
			glTranslatef(0.0f,-h_tronc/2,0.0f);
			glEnable(GL_TEXTURE_2D);{
				glBindTexture(GL_TEXTURE_2D,textures[0]);
				glBegin(GL_QUADS);
					glTexCoord2f(0.0f,t_monde/2); 		glVertex3f(t_monde,0.0f,t_monde); 
					glTexCoord2f(t_monde/2,t_monde/2); 	glVertex3f(-t_monde,0.0f,t_monde);
					glTexCoord2f(t_monde/2,0.0f);		glVertex3f(-t_monde,0.0f,-t_monde);
					glTexCoord2f(0.0f,0.0f); 		glVertex3f(t_monde,0.0f,-t_monde);
				glEnd();
			}glDisable(GL_TEXTURE_2D);
		glPopMatrix();
					
		//panneau de l'animation
		glPushMatrix();
			glTranslatef(t_monde-0.5f,-h_tronc/4,0.0f);
			pave *piquet_panneau=creer_pave(1.0f,h_tronc/2,1.0f,0.65f,0.50f,0.39f);
			affiche(piquet_panneau);
			
			glTranslatef(0.0f,h_tronc/2,0.0f);
			pave *ecran_panneau=creer_pave(1.0f,5.0f,5.0f,0.65f,0.50f,0.39f);
			affiche(ecran_panneau);
			
			//ecran
			glTranslatef(-0.5f,0.0f,0.0f);
			glEnable(GL_TEXTURE_2D);{
				glBindTexture(GL_TEXTURE_2D,textures[num_image]); 
				glBegin(GL_QUADS);
					glColor3f(1.0f,1.0f,1.0f); 
					glTexCoord2f(0.0f,0.0f); 	glVertex3f(0.0f,1.5f,1.5f); 
					glTexCoord2f(0.0f,1.0f); 	glVertex3f(0.0f,-1.5f,1.5f);
					glTexCoord2f(1.0f,1.0f);	glVertex3f(0.0f,-1.5f,-1.5f);
					glTexCoord2f(1.0f,0.0f);	glVertex3f(0.0f,1.5f,-1.5f);
				glEnd();
			}glDisable(GL_TEXTURE_2D);
		glPopMatrix();

		vitesse_anim++;
		if(vitesse_anim==10){
			vitesse_anim=0;
			if(num_image==12)
				num_image=1;
			num_image++;
		}

		//creation de l'arbre controlé par l'humain
		if(dep)
			glTranslatef(0.0f,h_racine,0.0f);
		glTranslatef(posx,0.0f,posz);

		glRotatef(90.0f*orientation,0.0f,1.0f,0.0f);	

		//tronc
		glPushMatrix();
			pave *tronc=creer_pave(lL_tronc,h_tronc,lL_tronc,0.36f,0.25f,0.20f);
			affiche(tronc);		
		glPopMatrix();

		//bras			
		glPushMatrix();
			glTranslatef(lL_tronc/2,0.0f,0.0f);
			if(!dep){
				glRotatef(90.0f,0.0f,0.0f,-1.0f);
			}else{
				glRotatef(brasun_rot1,0.0f,1.0f,0.0f);
				glRotatef(brasun_rot2,0.0f,0.0f,1.0f);
			}
			glTranslatef(l_bras/2,0.0f,0.0f);			
			pave *bras_un=creer_pave(l_bras,h_bras,L_bras,0.36f,0.25f,0.20f);
			affiche(bras_un);		
		glPopMatrix();

		glPushMatrix();
			glTranslatef(-lL_tronc/2,0.0f,0.0f);
			if(!dep){
				glRotatef(90.0f,0.0f,0.0f,1.0f);
			}else{
				glRotatef(brasdeux_rot1,0.0f,-1.0f,0.0f);
				glRotatef(brasdeux_rot2,0.0f,0.0f,-1.0f);
			}
			glTranslatef(-l_bras/2,0.0f,0.0f);			
			pave *bras_deux=creer_pave(l_bras,h_bras,L_bras,0.36f,0.25f,0.20f);
			affiche(bras_deux);		
		glPopMatrix();				

		//visage
		glPushMatrix();
			glTranslatef(-lL_tronc/4,h_tronc/2,lL_tronc/2);
			pave* oeil_un=creer_pave(lL_tronc/5,h_tronc/10,1.0f,0.91f,0.76f,0.65f);
			affiche(oeil_un);
			glTranslatef(lL_tronc/2,0.0f,0.0f);
			pave* oeil_deux=creer_pave(lL_tronc/5,h_tronc/10,1.0f,0.91f,0.76f,0.65f);
			affiche(oeil_deux);
			glTranslatef(-lL_tronc/4,-lL_tronc/4-0.5f,0.0f);
			pave* nez=creer_pave(lL_tronc/5,lL_tronc/5,3.0f,0.91f,0.76f,0.65f);
			affiche(nez);
			glTranslatef(0.0f,-lL_tronc/5-0.5f,0.0f);
			pave* bouche=creer_pave((lL_tronc/4)*3,h_tronc/10,1.0f,0.91f,0.76f,0.65f);
			affiche(bouche);
			if(dep){
				//sourire
				glTranslatef(-((lL_tronc/4)*3)/2,h_tronc/20,0.0f);
				pave* sourire_un=creer_pave(lL_tronc/8,h_tronc/10,1.0f,0.91f,0.76f,0.65f);
				affiche(sourire_un);
				glTranslatef((lL_tronc/4)*3,0.0f,0.0f);
				pave* sourire_deux=creer_pave(lL_tronc/8,h_tronc/10,1.0f,0.91f,0.76f,0.65f);
				affiche(sourire_deux);							
			}
		glPopMatrix();	

		//feuillage
		glPushMatrix();
			glTranslatef(0.0f,(h_tronc+t_feuillage)/2,0.0f);
			pave *feuillage=creer_pave(t_feuillage,t_feuillage,t_feuillage,0.2f,0.3f,0.2f);
			affiche(feuillage);
		glPopMatrix();

		//racines
		glPushMatrix();
			glTranslatef(-lL_tronc/2,-h_tronc/2,-lL_tronc/2);
			if((dep)&&(!(tmp_posz % 2))&&(tmp_posz)&&((t_arbre/2+posz)<t_monde/2)&&((-t_arbre/2+posz)>-t_monde/2))
				glRotatef(30.0f,-1.0f,0.0f,0.0f);
			else if((dep)&&(!(tmp_posx % 2))&&(tmp_posx)&&((t_arbre/2+posx)<t_monde/2)&&((-t_arbre/2+posx)>-t_monde/2))
				glRotatef(30.0f,-1.0f,0.0f,0.0f);
			glTranslatef(lL_racine/2,-h_racine/2,lL_racine/2);
			pave *racine_un=creer_pave(lL_racine,h_racine,lL_racine,0.36f,0.25f,0.20f);
			affiche(racine_un);
		glPopMatrix();

		glPushMatrix();
			glTranslatef(-lL_tronc/2,-h_tronc/2,lL_tronc/2);
			if((dep)&&(!(tmp_posz % 2))&&(tmp_posz)&&((t_arbre/2+posz)<t_monde/2)&&((-t_arbre/2+posz)>-t_monde/2))
				glRotatef(30.0f,-1.0f,0.0f,0.0f);
			else if((dep)&&(!(tmp_posx % 2))&&(tmp_posx)&&((t_arbre/2+posx)<t_monde/2)&&((-t_arbre/2+posx)>-t_monde/2))
				glRotatef(30.0f,-1.0f,0.0f,0.0f);
			glTranslatef(lL_racine/2,-h_racine/2,-lL_racine/2);
			pave *racine_trois=creer_pave(lL_racine,h_racine,lL_racine,0.36f,0.25f,0.20f);
			affiche(racine_trois);
		glPopMatrix();

		glPushMatrix();
			glTranslatef(lL_tronc/2,-h_tronc/2,-lL_tronc/2);
			if((dep)&&(tmp_posz % 2)&&(tmp_posz)&&((t_arbre/2+posz)<t_monde/2)&&((-t_arbre/2+posz)>-t_monde/2))
				glRotatef(30.0f,-1.0f,0.0f,0.0f);
			else if((dep)&&(tmp_posx % 2)&&(tmp_posx)&&((t_arbre/2+posx)<t_monde/2)&&((-t_arbre/2+posx)>-t_monde/2))
				glRotatef(30.0f,-1.0f,0.0f,0.0f);
			glTranslatef(-lL_racine/2,-h_racine/2,lL_racine/2);
			pave *racine_deux=creer_pave(lL_racine,h_racine,lL_racine,0.36f,0.25f,0.20f);
			affiche(racine_deux);
		glPopMatrix();

		glPushMatrix();
			glTranslatef(lL_tronc/2,-h_tronc/2,lL_tronc/2);
			if((dep)&&(tmp_posz % 2)&&(tmp_posz)&&((t_arbre/2+posz)<t_monde/2)&&((-t_arbre/2+posz)>-t_monde/2))
				glRotatef(30.0f,-1.0f,0.0f,0.0f);
			else if((dep)&&(tmp_posx % 2)&&(tmp_posx)&&((t_arbre/2+posx)<t_monde/2)&&((-t_arbre/2+posx)>-t_monde/2))
				glRotatef(30.0f,-1.0f,0.0f,0.0f);
			glTranslatef(-lL_racine/2,-h_racine/2,-lL_racine/2);
			pave *racine_quatre=creer_pave(lL_racine,h_racine,lL_racine,0.36f,0.25f,0.20f);
			affiche(racine_quatre);
		glPopMatrix();
  glPopMatrix();

  axes();
  glutSwapBuffers();
}

int main(int argc, char **argv) 
{  
	srand(time(NULL));
  return notre_init(argc, argv, &Modelisation);
}
