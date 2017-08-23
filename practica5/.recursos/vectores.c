/* -------------------------------------------------------------------------*/
/* Vectores de vértices, O. Belmonte                                        */
/* -------------------------------------------------------------------------*/


#include <GL/glut.h>
#include <stdio.h>

#define anchoVentana     512  /* ancho de la ventana */
#define altoVentana      512  /* alto de la ventana */
#define posicionVentanaX  50  /* pos. X de la esquina sup-izq de la ventana */
#define posicionVentanaY  50  /* pos. Y de la esquina sup-izq de la ventana */

float vertices[24] ={-0.5f, -0.5f, 0.5f, 0.5f, -0.5f, 0.5f, 0.5f, -0.5f, -0.5f,
					-0.5f, -0.5f, -0.5f, -0.5f, 0.5f, 0.5f, 0.5f, 0.5f, 0.5f,
					0.5f, 0.5f, -0.5f, -0.5f, 0.5f, -0.5f};

/* Dibujo de un cubo utilizando glArrayElement -----------------------------*/
void cuboArrayElement (void){

  glBegin (GL_LINE_LOOP);
    glArrayElement (0);
    glArrayElement (1);
    glArrayElement (2);
    glArrayElement (3);
    glArrayElement (7);
    glArrayElement (6);
    glArrayElement (5);
    glArrayElement (4);
  glEnd ();

  glBegin (GL_LINES);
    glArrayElement (0);
    glArrayElement (3);
    glArrayElement (1);
    glArrayElement (5);
    glArrayElement (2);
    glArrayElement (6);
    glArrayElement (4);
    glArrayElement (7);
  glEnd ();
}

void cuboDraw (void) {

  GLuint indices [8] = {0, 4, 1, 5, 2, 6, 3, 7};

  glDrawArrays (GL_LINE_LOOP, 0, 4);
  glDrawArrays (GL_LINE_LOOP, 4, 4);
  glDrawElements (GL_LINES, 8, GL_UNSIGNED_INT, indices);
}

/* Función que establece la proyección -------------------------------------*/
void proyeccion (void) {

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
	glOrtho(-2.0, 2.0, -2.0, 2.0, -2.0, 2.0);
}

/* Rutina asociada a eventos de ventana ------------------------------------*/
void eventoVentana (GLsizei ancho, GLsizei alto) {
  
  glViewport (0, 0, ancho, alto);
  proyeccion();
}

/* Rutina asociada a eventos de teclado ------------------------------------*/
void eventoTeclado (unsigned char tecla, int x, int y) {

  switch (tecla) {
  case  27: exit (0); break;
  case 'q': exit (0); break;
  case 'Q': exit (0); break;
  }
}

/* Rutina de dibujo de la escena -------------------------------------------*/
void Dibuja (void) {

  glClear (GL_COLOR_BUFFER_BIT); /* Borramos el buffer de color */
 
    /* Transformacion de la camara */
	glMatrixMode(GL_MODELVIEW); /* Seleccionamos la matriz modelo vista */
	glLoadIdentity(); /* Cargamos la matriz unidad sobre la modelo vista */

  glPushMatrix ();
  glTranslatef (-0.8f, 0.0f, 0.0f);
  glRotatef (30.0f, 1.0f, 0.0f, 0.0f);
  glRotatef (30.0f, 0.0f, 1.0f, 0.0f);
  cuboArrayElement ();
  glPopMatrix ();

  glPushMatrix ();
  glTranslatef (0.8f, 0.0f, 0.0);
  glRotatef (30.0f, 1.0f, 0.0f, 0.0f);
  glRotatef (30.0f, 0.0f, 1.0f, 0.0f);
  cuboDraw ();
  glPopMatrix ();

	glFlush();
}

/* Opciones sobre la visualización de la escena ----------------------------*/
void opcionesVisualizacion (void) {

  glPolygonMode (GL_FRONT_AND_BACK, GL_LINE);
  glClearColor (0.8f, 0.8f, 0.8f, 0.0f);
	glColor3f (0.0f, 0.0f,0.0f);
}

/* Establece las funciones que atienden los distintos eventos --------------*/
void  asociaEventos (void) {

  glutReshapeFunc  (eventoVentana);
  glutKeyboardFunc (eventoTeclado);
}

/* Abre la ventana de la aplicación ----------------------------------------*/
void abreVentana (int numParametros, char **listaParametros) {

  glutInit               (&numParametros, listaParametros);
  glutInitDisplayMode    (GLUT_SINGLE);
  glutInitWindowSize     (anchoVentana, altoVentana);
  glutInitWindowPosition (posicionVentanaX, posicionVentanaY);
  glutCreateWindow       (listaParametros[0]);
}

/* Programa principal ------------------------------------------------------*/
int main (int numParametros, char **listaParametros) {

  /* crea la ventana de la aplicación*/
  abreVentana (numParametros, listaParametros);

  /* asocia funciones a eventos de ventana, teclado o ratón*/
  asociaEventos ();              

  /* establece la función de dibujo de la escena */
  glutDisplayFunc (Dibuja);

  /* establece opciones sobre la visualización de la escena */
  opcionesVisualizacion();

  /* Se habilita el uso de un vector con coordenadas geometricas */
  glEnableClientState (GL_VERTEX_ARRAY);
  glVertexPointer (3, GL_FLOAT, 0, vertices);

  /* bucle a la espera de eventos */
  glutMainLoop();
}
