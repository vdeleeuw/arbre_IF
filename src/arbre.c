#include "pave.h"

extern int dep;
extern GLfloat t_monde;

int posxR=0;
int poszR=0;

GLvoid randomArbre(int delai){
	usleep(delai);

	//variables de constructions
	GLfloat h_troncR=10.0f;
	GLfloat lL_troncR=5.0f;	
	GLfloat t_feuillageR=10.0f;
	GLfloat h_racineR=3.0f;
	GLfloat lL_racineR=1.0f;	
	GLfloat l_brasR=5.0f;
	GLfloat L_brasR=1.0f;
	GLfloat h_brasR=1.0f;
	GLfloat t_arbreR=(t_feuillageR>lL_troncR) ? t_feuillageR : lL_troncR;

	//variables de mouvements
	int orientationR=(rand()%4);

  // Entre glPushMatrix et glPopMatrix s'écrit la description de la scène.
  glPushMatrix();

		if(dep)
			glTranslatef(0.0f,h_racineR,0.0f);
		glTranslatef(posxR,0.0f,poszR);

		glRotatef(90.0f*orientationR,0.0f,1.0f,0.0f);	

		//tronc
		glPushMatrix();
			pave *troncR=creer_pave(lL_troncR,h_troncR,lL_troncR,0.36f,0.25f,0.20f);
			affiche(troncR);		
		glPopMatrix();

		//bras			
		glPushMatrix();
			glTranslatef(lL_troncR/2,0.0f,0.0f);
			if(!dep){
				glRotatef(90.0f,0.0f,0.0f,-1.0f);
			}else{
				glRotatef(rand()%201-100,0.0f,1.0f,0.0f);
				glRotatef(rand()%201-100,0.0f,0.0f,1.0f);
			}
			glTranslatef(l_brasR/2,0.0f,0.0f);			
			pave *bras_unR=creer_pave(l_brasR,h_brasR,L_brasR,0.36f,0.25f,0.20f);
			affiche(bras_unR);		
		glPopMatrix();

		glPushMatrix();
			glTranslatef(-lL_troncR/2,0.0f,0.0f);
			if(!dep){
				glRotatef(90.0f,0.0f,0.0f,1.0f);
			}else{
				glRotatef(rand()%201-100,0.0f,-1.0f,0.0f);
				glRotatef(rand()%201-100,0.0f,0.0f,-1.0f);
			}
			glTranslatef(-l_brasR/2,0.0f,0.0f);			
			pave *bras_deuxR=creer_pave(l_brasR,h_brasR,L_brasR,0.36f,0.25f,0.20f);
			affiche(bras_deuxR);		
		glPopMatrix();				

		//visage
		glPushMatrix();
			glTranslatef(-lL_troncR/4,h_troncR/2,lL_troncR/2);
			pave* oeil_unR=creer_pave(lL_troncR/5,h_troncR/10,1.0f,0.91f,0.76f,0.65f);
			affiche(oeil_unR);
			glTranslatef(lL_troncR/2,0.0f,0.0f);
			pave* oeil_deuxR=creer_pave(lL_troncR/5,h_troncR/10,1.0f,0.91f,0.76f,0.65f);
			affiche(oeil_deuxR);
			glTranslatef(-lL_troncR/4,-lL_troncR/4-0.5f,0.0f);
			pave* nezR=creer_pave(lL_troncR/5,lL_troncR/5,3.0f,0.91f,0.76f,0.65f);
			affiche(nezR);
			glTranslatef(0.0f,-lL_troncR/5-0.5f,0.0f);
			pave* boucheR=creer_pave((lL_troncR/4)*3,h_troncR/10,1.0f,0.91f,0.76f,0.65f);
			affiche(boucheR);
			if(dep){
				//sourire
				glTranslatef(-((lL_troncR/4)*3)/2,h_troncR/20,0.0f);
				pave* sourire_unR=creer_pave(lL_troncR/8,h_troncR/10,1.0f,0.91f,0.76f,0.65f);
				affiche(sourire_unR);
				glTranslatef((lL_troncR/4)*3,0.0f,0.0f);
				pave* sourire_deuxR=creer_pave(lL_troncR/8,h_troncR/10,1.0f,0.91f,0.76f,0.65f);
				affiche(sourire_deuxR);							
			}
		glPopMatrix();	

		//feuillage
		glPushMatrix();
			glTranslatef(0.0f,(h_troncR+t_feuillageR)/2,0.0f);
			pave *feuillageR=creer_pave(t_feuillageR,t_feuillageR,t_feuillageR,0.2f,0.3f,0.2f);
			affiche(feuillageR);
		glPopMatrix();

		int actionR=rand()%2;
		if(actionR)
				switch(orientationR){
					case 0:
						if((dep)&&((t_arbreR/2+poszR)<t_monde/2))
							poszR++;
					break;

					case 1:
						if((dep)&&((t_arbreR/2+posxR)<t_monde/2))
							posxR++;  
					break;

					case 2:
						if((dep)&&((-t_arbreR/2+poszR)>-t_monde/2)) 
							poszR--;
					break;

					case 3:
						if((dep)&&((-t_arbreR/2+posxR)>-t_monde/2)) 
							posxR--;
					break;
			}
		else
				switch(orientationR){
					case 0:
						if((dep)&&((-t_arbreR/2+poszR)>-t_monde/2)) 
							poszR--;  
					break;

					case 1:
						if((dep)&&((-t_arbreR/2+posxR)>-t_monde/2)) 
							posxR--;  
					break;

					case 2:
						if((dep)&&((t_arbreR/2+poszR)<t_monde/2)) 
							poszR++;
					break;

					case 3:
						if((dep)&&((t_arbreR/2+posxR)<t_monde/2)) 
							posxR++;
					break;
			}	

		//racines
		glPushMatrix();
			glTranslatef(-lL_troncR/2,-h_troncR/2,-lL_troncR/2);
			if((dep)&&(!(poszR % 2))&&((t_arbreR/2+poszR)<t_monde/2)&&((-t_arbreR/2+poszR)>-t_monde/2))
				glRotatef(30.0f,-1.0f,0.0f,0.0f);
			else if((dep)&&(!(posxR % 2))&&((t_arbreR/2+posxR)<t_monde/2)&&((-t_arbreR/2+posxR)>-t_monde/2))
				glRotatef(30.0f,-1.0f,0.0f,0.0f);
			glTranslatef(lL_racineR/2,-h_racineR/2,lL_racineR/2);
			pave *racine_unR=creer_pave(lL_racineR,h_racineR,lL_racineR,0.36f,0.25f,0.20f);
			affiche(racine_unR);
		glPopMatrix();

		glPushMatrix();
			glTranslatef(-lL_troncR/2,-h_troncR/2,lL_troncR/2);
			if((dep)&&(!(poszR % 2))&&((t_arbreR/2+poszR)<t_monde/2)&&((-t_arbreR/2+poszR)>-t_monde/2))
				glRotatef(30.0f,-1.0f,0.0f,0.0f);
			else if((dep)&&(!(posxR % 2))&&((t_arbreR/2+posxR)<t_monde/2)&&((-t_arbreR/2+posxR)>-t_monde/2))
				glRotatef(30.0f,-1.0f,0.0f,0.0f);
			glTranslatef(lL_racineR/2,-h_racineR/2,-lL_racineR/2);
			pave *racine_troisR=creer_pave(lL_racineR,h_racineR,lL_racineR,0.36f,0.25f,0.20f);
			affiche(racine_troisR);
		glPopMatrix();

		glPushMatrix();
			glTranslatef(lL_troncR/2,-h_troncR/2,-lL_troncR/2);
			if((dep)&&(poszR % 2)&&((t_arbreR/2+poszR)<t_monde/2)&&((-t_arbreR/2+poszR)>-t_monde/2))
				glRotatef(30.0f,-1.0f,0.0f,0.0f);
			else if((dep)&&(posxR % 2)&&((t_arbreR/2+posxR)<t_monde/2)&&((-t_arbreR/2+posxR)>-t_monde/2))
				glRotatef(30.0f,-1.0f,0.0f,0.0f);
			glTranslatef(-lL_racineR/2,-h_racineR/2,lL_racineR/2);
			pave *racine_deuxR=creer_pave(lL_racineR,h_racineR,lL_racineR,0.36f,0.25f,0.20f);
			affiche(racine_deuxR);
		glPopMatrix();

		glPushMatrix();
			glTranslatef(lL_troncR/2,-h_troncR/2,lL_troncR/2);
			if((dep)&&(poszR % 2)&&((t_arbreR/2+poszR)<t_monde/2)&&((-t_arbreR/2+poszR)>-t_monde/2))
				glRotatef(30.0f,-1.0f,0.0f,0.0f);
			else if((dep)&&(posxR % 2)&&((t_arbreR/2+posxR)<t_monde/2)&&((-t_arbreR/2+posxR)>-t_monde/2))
				glRotatef(30.0f,-1.0f,0.0f,0.0f);
			glTranslatef(-lL_racineR/2,-h_racineR/2,-lL_racineR/2);
			pave *racine_quatreR=creer_pave(lL_racineR,h_racineR,lL_racineR,0.36f,0.25f,0.20f);
			affiche(racine_quatreR);
		glPopMatrix();

  glPopMatrix();
}

