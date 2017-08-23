//camaras  
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
// variables que definen la posicion de la camara en coordenadas polares



struct camaras {
double aspecto;
void proyeccionPerspectivaTeclado (void) {

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(30.0, aspecto, 1.0f, 10000.0f); /* o glOrtho */
	//glOrtho(-1.5f*aspecto, 1.5f*aspecto, -1.5f, 1.5f, -2.0f, 2.0f); 
}
/* Función que establece la proyección perspectiva */
void proyeccionPerspectivaRaton (void) {

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(14.0, aspecto, 1.0f, 10000.0f); 
}

/* Función que establece la proyección paralela */
void proyeccionParalela (void) {

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(-1.5f*aspecto, 1.5f*aspecto, -1.5f, 1.5f, -2.0f, 2.0f); 
}
	
};
