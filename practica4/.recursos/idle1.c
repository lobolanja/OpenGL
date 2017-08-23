/* -------------------------------------------------------------------------*/
/* Que trabaje!!: glutIdleFunc, glutTimer, O. Belmonte                      */
/* -------------------------------------------------------------------------*/


#include <GL/glut.h>
#include <stdio.h>

#define anchoVentana     512  /* ancho de la ventana */
#define altoVentana      512  /* alto de la ventana */
#define posicionVentanaX  50  /* pos. X de la esquina sup-izq de la ventana */
#define posicionVentanaY  50  /* pos. Y de la esquina sup-izq de la ventana */

float R = 1.0f, B = 1.0f;

/* Función que dibuja un cuadrado con el origen de coordenadas en su centro */
void cuadrado (void){
	float vertices[4][2] = {{-0.5f, -0.5f}, {0.5f, -0.5f}, {0.5f, 0.5f}, {-0.5f, 0.5f}};

	glBegin (GL_POLYGON);
		glVertex2fv (vertices[0]);
		glVertex2fv (vertices[1]);
		glVertex2fv (vertices[2]);
		glVertex2fv (vertices[3]);
	glEnd ();
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

/* Rutina asociada al estado sin eventos -----------------------------------*/
void rojo (void) {
  R = R - 0.01f;
  if (R < 0.0f) R = R + 1.0f;

  glutPostRedisplay ();
}

void azul (void) {
  B = B - 0.01f;
  if (B < 0.0f) B = B + 1.0f;

  glutPostRedisplay ();
}

/* Rutina asociada a eventos de teclado ------------------------------------*/
void eventoTeclado (unsigned char tecla, int x, int y) {

  switch (tecla) {
  case  27:
  case 'q':
  case 'Q': exit (0); break;
  case 'r':
  case 'R': glutIdleFunc (rojo); break;
  case 'b':
  case 'B': glutIdleFunc (azul); break;
  case 's':
  case 'S': glutIdleFunc (NULL); break;
  }
}

/* Rutina de dibujo de la escena -------------------------------------------*/
void Dibuja (void) {
  glClear (GL_COLOR_BUFFER_BIT); /* Borramos el buffer de color */
 
  /* Transformacion de la camara */
  glMatrixMode(GL_MODELVIEW); /* Seleccionamos la matriz modelo vista */
  glLoadIdentity(); /* Cargamos la matriz unidad sobre la modelo vista */
  glPushMatrix ();
  glTranslatef (-0.6f, 0.0f, 0.0f);
  glColor3f (R, 0.0f, 0.0f);
  cuadrado ();
  glPopMatrix ();

  glPushMatrix ();
  glTranslatef (0.6f, 0.0f, 0.0f);
  glColor3f (0.0f, 0.0f, B);
  cuadrado ();
  glPopMatrix ();

  glutSwapBuffers ();
}

/* Opciones sobre la visualización de la escena ----------------------------*/
void opcionesVisualizacion (void) {

  /* por ejemplo....*/
  glClearColor (0.0f, 0.0f, 0.0f, 0.0f);
  glColor3f (1.0f, 1.0f, 1.0f);
}

/* Establece las funciones que atienden los distintos eventos --------------*/
void  asociaEventos (void) {

  glutReshapeFunc  (eventoVentana);
  glutKeyboardFunc (eventoTeclado);
}

/* Abre la ventana de la aplicación ----------------------------------------*/
void abreVentana (int numParametros, char **listaParametros) {

  glutInit               (&numParametros, listaParametros);
  glutInitDisplayMode    (GLUT_DOUBLE | GLUT_RGB);
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
