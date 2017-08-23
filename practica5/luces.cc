#include <iostream>
#include "stdlib.h"
#include "stdio.h" 
#include <GL/glut.h>
#include <ctype.h>
#include <vector>
#include <vertex.h>
#include "file_ply_stl.h"
#include <math.h>
#include <unistd.h>
#include <unistd.h>


// luces 
struct luces{
void posicional(int imagenActual=0) {

  GLfloat luz_ambiente[] = {0.5, 0.5, 0.5, 0.2};

  GLfloat luz_blanca_ambiente[]  = {1, 1, 1, 1.0};
  GLfloat luz_blanca_difusa[]    = {1, 1, 1, 1.0};
  GLfloat luz_blanca_especular[] = {1, 1, 1, 1.0};

  GLfloat luz_posicion_baja[] = {0.0, -16, 16, 1.0};
  GLfloat luz_posicion_alta[] = {0.0, -32, 32, 1.0};

  glLightModelfv(GL_LIGHT_MODEL_AMBIENT, luz_ambiente);

		glLightfv(GL_LIGHT0, GL_AMBIENT,  luz_blanca_ambiente);
	   glLightfv(GL_LIGHT0, GL_DIFFUSE,  luz_blanca_difusa);
	   glLightfv(GL_LIGHT0, GL_SPECULAR, luz_blanca_especular);
	   glLightfv(GL_LIGHT0, GL_POSITION, luz_posicion_baja);
  	   glLightf(GL_LIGHT0, GL_CONSTANT_ATTENUATION,  1.0);
	   glLightf(GL_LIGHT0, GL_LINEAR_ATTENUATION,    0.0);
	   glLightf(GL_LIGHT0, GL_QUADRATIC_ATTENUATION, 0.0);
  glEnable  (GL_LIGHTING);
  glEnable  (GL_LIGHT0);
} 

void roja(int imagenActual=0) {

  GLfloat luz_ambiente[] = {1, 0, 0, 0.2};

  GLfloat luz_blanca_ambiente[]  = {1, 1, 1, 1.0};
  GLfloat luz_blanca_difusa[]    = {1, 1, 1, 1.0};
  GLfloat luz_blanca_especular[] = {1, 1, 1, 1.0};

  GLfloat luz_posicion_baja[] = {0.0, -16, 16, 1.0};
  GLfloat luz_posicion_alta[] = {0.0, -32, 32, 1.0};

  glLightModelfv(GL_LIGHT_MODEL_AMBIENT, luz_ambiente);

		glLightfv(GL_LIGHT3, GL_AMBIENT,  luz_ambiente);
	   glLightfv(GL_LIGHT3, GL_DIFFUSE,  luz_blanca_difusa);
	   glLightfv(GL_LIGHT3, GL_SPECULAR, luz_blanca_especular);
	   glLightfv(GL_LIGHT3, GL_POSITION, luz_posicion_baja);
  	   glLightf(GL_LIGHT3, GL_CONSTANT_ATTENUATION,  1.0);
	   glLightf(GL_LIGHT3, GL_LINEAR_ATTENUATION,    0.0);
	   glLightf(GL_LIGHT3, GL_QUADRATIC_ATTENUATION, 0.0);
	  

  glEnable  (GL_LIGHTING);
  glEnable  (GL_LIGHT3);
} 

void direccional(int imagenActual=0) {

  GLfloat luz_ambiente[] = {0.5, 0.5, 0.5, 0.2};
 
  GLfloat luz_blanca_ambiente[]  = {1,1,1, 1};
  GLfloat luz_blanca_difusa[]    = {1,1,1, 1};
  GLfloat luz_blanca_especular[] = {1,1,1, 1};

	GLfloat luz_direccion[] = {10, 10, 10, 0};

  glLightModelfv(GL_LIGHT_MODEL_AMBIENT, luz_ambiente);
	
		glLightfv(GL_LIGHT1, GL_AMBIENT,  luz_blanca_ambiente);
	   glLightfv(GL_LIGHT1, GL_DIFFUSE,  luz_blanca_difusa);
	   glLightfv(GL_LIGHT1, GL_SPECULAR, luz_blanca_especular);
	   glLightfv(GL_LIGHT1, GL_POSITION, luz_direccion);

 
  glEnable  (GL_LIGHTING);
  glEnable  (GL_LIGHT1);
}
};
