#include "actions.h"
#include <stdio.h>

//variables de camera
extern GLfloat xrot;
extern GLfloat yrot; 
extern blend;
extern light;

//variables de mouvement
extern GLint dep;
extern GLint orientation;
extern GLfloat brasun_rot1;
extern GLfloat brasun_rot2;
extern GLfloat brasdeux_rot1;
extern GLfloat brasdeux_rot2;

//variables de position
extern GLint posx;
extern GLint posz;
extern GLint tmp_posx;
extern GLint tmp_posz;
extern GLfloat t_monde;
extern GLfloat t_arbre;
extern GLint xSoleil;
extern GLint zSoleil;

void touche_pressee(unsigned char key, int x, int y){
	usleep(100);

	switch (key){    
		//quitter
		case ESCAPE: 
			exit(1);                   	
		break; 

		//remise a zero
    case ESPACE:
      xrot = 0.0f;
      yrot = 0.0f;
			dep=0;
			brasun_rot1=0;				
			brasun_rot2=0;
			brasdeux_rot1=0;
			brasdeux_rot2=0;
			posx=0;
			posz=0;
			orientation=0;
			xSoleil=0;
			zSoleil=0;
    break;

		//blend
    case TOUCHE_MIN_B: 
    case TOUCHE_MAJ_B: 
     blend=switch_blend(blend);
    break;

		//light
    case TOUCHE_MIN_L: 
    case TOUCHE_MAJ_L:
		if(light)
			light=0;
		else
			light=1;
    break;

		//deplacement soleil
    case TOUCHE_MIN_W: 
    case TOUCHE_MAJ_W:
		if(xSoleil<t_monde/2)
			xSoleil++;
    break;

    case TOUCHE_MIN_X: 
    case TOUCHE_MAJ_X:
		if(xSoleil>-t_monde/2)
			xSoleil--;
    break;

    case TOUCHE_MIN_C: 
    case TOUCHE_MAJ_C:
		if(zSoleil<t_monde/2)
			zSoleil++;
    break;

    case TOUCHE_MIN_V: 
    case TOUCHE_MAJ_V:
		if(zSoleil>-t_monde/2)
			zSoleil--;
    break;

		//deplacement possible de l'arbre
		case TOUCHE_MIN_A: 
    case TOUCHE_MAJ_A: 
    	if(dep)
				dep=0;
			else
				dep=1;   	
	 	break;

		//deplacement bras un
		case TOUCHE_MIN_T: 
    case TOUCHE_MAJ_T:
			if((dep)&&(brasun_rot1<90))
				brasun_rot1+=2;	    	
	 	break;

		case TOUCHE_MIN_Y: 
    case TOUCHE_MAJ_Y:
			if((dep)&&(brasun_rot1>-90))
				brasun_rot1-=2;	  	
	 	break;

		case TOUCHE_MIN_U: 
    case TOUCHE_MAJ_U:
			if((dep)&&(brasun_rot2<90))
				brasun_rot2+=2;	  
	 	break;

		case TOUCHE_MIN_I: 
    case TOUCHE_MAJ_I:    	
			if((dep)&&(brasun_rot2>-90))
				brasun_rot2-=2;	 
	 	break;

		//deplacement bras deux
		case TOUCHE_MIN_G: 
    case TOUCHE_MAJ_G:   
			if((dep)&&(brasdeux_rot1<90))
				brasdeux_rot1+=2;	 
	 	break;

		case TOUCHE_MIN_H: 
    case TOUCHE_MAJ_H:   
			if((dep)&&(brasdeux_rot1>-90))
				brasdeux_rot1-=2;	 	
	 	break;

		case TOUCHE_MIN_J: 
    case TOUCHE_MAJ_J:   
			if((dep)&&(brasdeux_rot2<90))
				brasdeux_rot2+=2;	    	
	 	break;

		case TOUCHE_MIN_K: 
    case TOUCHE_MAJ_K:   
			if((dep)&&(brasdeux_rot2>-90))
				brasdeux_rot2-=2;		
	 	break;

		//deplacement arbre
		case TOUCHE_MIN_Z: 
    case TOUCHE_MAJ_Z:
				switch(orientation){
					case 0:
						if((dep)&&((t_arbre/2+posz)<t_monde/2)){
							posz++;  
							tmp_posz++;
						}
					break;

					case 1:
						if((dep)&&((t_arbre/2+posx)<t_monde/2)){
							posx++;  
							tmp_posx++;
						}
					break;

					case 2:
						if((dep)&&((-t_arbre/2+posz)>-t_monde/2)){
							posz--;
							tmp_posz--;
						}
					break;

					case 3:
						if((dep)&&((-t_arbre/2+posx)>-t_monde/2)){
							posx--;
							tmp_posx--;
						}
					break;
			}
		break;

		case TOUCHE_MIN_D: 
    case TOUCHE_MAJ_D:
			if(orientation>0) 		
				orientation--;
			else
				orientation=3;
	 	break;

		case TOUCHE_MIN_S: 
    case TOUCHE_MAJ_S:   
				switch(orientation){
					case 0:
						if((dep)&&((-t_arbre/2+posz)>-t_monde/2)){
							posz--;  
							tmp_posz--;
						}
					break;

					case 1:
						if((dep)&&((-t_arbre/2+posx)>-t_monde/2)){ 
							posx--;  
							tmp_posx--;
						}
					break;

					case 2:
						if((dep)&&((t_arbre/2+posz)<t_monde/2)){
							posz++;
							tmp_posz++;
						}
					break;

					case 3:
						if((dep)&&((t_arbre/2+posx)<t_monde/2)){
							posx++;
							tmp_posx++;
						}
					break;
			}	
	 	break;

		case TOUCHE_MIN_Q: 
    case TOUCHE_MAJ_Q:
			if(orientation<3)
				orientation++;
			else 
				orientation=0;
	 	break;
	}	
}

