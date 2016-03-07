#include "VM_init.h"

extern GLfloat z, xrot, yrot;

void VM_init(){
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);		
	glLoadIdentity();			
	glTranslatef(0.0,0.0,z);
	glRotatef(xrot,1.0,0.0,0.0);
	glRotatef(yrot,0.0,1.0,0.0);
}
