/* -------------------------------------------------------------------------*/
/* Patrones de línea y de relleno, O. Belmonte                              */
/* -------------------------------------------------------------------------*/


#include <GL/glut.h>
#include <stdio.h>

#define anchoVentana     512  /* ancho de la ventana */
#define altoVentana      512  /* alto de la ventana */
#define posicionVentanaX  50  /* pos. X de la esquina sup-izq de la ventana */
#define posicionVentanaY  50  /* pos. Y de la esquina sup-izq de la ventana */

GLuint id; /* Identificador para la Display List */

/* Función que establece la proyección -------------------------------------*/
void proyeccion (void) {

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
	glOrtho(-2.0, 4.0, -1.0, 2.0, -2.0, 2.0);
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

	glEnable (GL_LINE_STIPPLE);
	glLineStipple (1, 0xAAAA);
	glBegin (GL_LINES);
	glVertex2f (-1.5f, 1.5f);
	glVertex2f (1.5f, 1.5f);
	glEnd ();

	glLineStipple (1, 0x00FF);
	glBegin (GL_LINES);
	glVertex2f (-1.5f, 1.3f);
	glVertex2f (1.5f, 1.3f);
	glEnd ();

	glLineStipple (1, 0x1234);
	glBegin (GL_LINES);
	glVertex2f (-1.5f, 1.1f);
	glVertex2f (1.5f, 1.1f);
	glEnd ();

	glLineStipple (1, 0xF1E2);
	glBegin (GL_LINES);
	glVertex2f (-1.5f, 0.9f);
	glVertex2f (1.5f, 0.9f);
	glEnd ();

	glLineStipple (3, 0xAAAA);
	glBegin (GL_LINES);
	glVertex2f (-1.5f, 0.7f);
	glVertex2f (1.5f, 0.7f);
	glEnd ();

	glLineStipple (3, 0x00FF);
	glBegin (GL_LINES);
	glVertex2f (-1.5f, 0.5f);
	glVertex2f (1.5f, 0.5f);
	glEnd ();

	glLineStipple (3, 0x1234);
	glBegin (GL_LINES);
	glVertex2f (-1.5f, 0.3f);
	glVertex2f (1.5f, 0.3f);
	glEnd ();

	glLineStipple (3, 0xF1E2);
	glBegin (GL_LINES);
	glVertex2f (-1.5f, 0.1f);
	glVertex2f (1.5f, 0.1f);
	glEnd ();
	glDisable (GL_LINE_STIPPLE);

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

  /* bucle a la espera de eventos */
  glutMainLoop();
}
