/* -------------------------------------------------------------------------*/
/* Primitivas de dibujo eficientes, O. Belmonte                             */
/* -------------------------------------------------------------------------*/


#include <GL/glut.h>
#include <stdio.h>

#define anchoVentana     512  /* ancho de la ventana */
#define altoVentana      512  /* alto de la ventana */
#define posicionVentanaX  50  /* pos. X de la esquina sup-izq de la ventana */
#define posicionVentanaY  50  /* pos. Y de la esquina sup-izq de la ventana */

/* Función que establece la proyección -------------------------------------*/
void proyeccion (void) {

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(-0.5, 8.0, -6.0, 6.0, -2.0, 2.0);
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
  float v[8][2] = {{0.0f,0.0f}, {0.1f, 1.0f}, {0.9f, 0.2f}, {1.1f, 1.1f}, {1.9f, 0.3f},
  {1.8f, 0.9f}, {2.7f, 0.0f}, {2.9f, 1.2f}}; /* Vertices */

  glClear (GL_COLOR_BUFFER_BIT); /* Borramos el buffer de color */
 
    /* Transformacion de la camara */
	glMatrixMode(GL_MODELVIEW); /* Seleccionamos la matriz modelo vista */
	glLoadIdentity(); /* Cargamos la matriz unidad sobre la modelo vista */

	glPushMatrix ();
		glTranslatef (0.0f, 2.0f, 0.0f);
		glBegin (GL_LINE_STRIP); /* Inicio de la definicion de una tira de segmentos */
			glVertex2fv (v[0]);
			glVertex2fv (v[1]);
			glVertex2fv (v[2]);
			glVertex2fv (v[3]);
			glVertex2fv (v[4]);
			glVertex2fv (v[5]);
			glVertex2fv (v[6]);
			glVertex2fv (v[7]);
		glEnd (); /* Fin de la definicion */
	glPopMatrix ();

	glPushMatrix ();
		glTranslatef (4.0f, 2.0f, 0.0f);
		glBegin (GL_LINE_LOOP); /* Inicio de la definicion de un lazo de segmentos */
			glVertex2fv (v[0]);
			glVertex2fv (v[1]);
			glVertex2fv (v[3]);
			glVertex2fv (v[5]);
			glVertex2fv (v[7]);
			glVertex2fv (v[6]);
			glVertex2fv (v[4]);
			glVertex2fv (v[2]);
		glEnd (); /* Fin de la definicion */
	glPopMatrix ();

	glPushMatrix ();
		glTranslatef (0.0f, -0.4f, 0.0f);
		glBegin (GL_TRIANGLE_STRIP); /* Inicio de la definicion de una tira de triangulos */
			glVertex2fv (v[0]);
			glVertex2fv (v[1]);
			glVertex2fv (v[2]);
			glVertex2fv (v[3]);
			glVertex2fv (v[4]);
			glVertex2fv (v[5]);
			glVertex2fv (v[6]);
			glVertex2fv (v[7]);
		glEnd (); /* Fin de la definicion */
	glPopMatrix ();

	glPushMatrix ();
		glTranslatef (4.0f, -0.4f, 0.0f);
		glBegin (GL_TRIANGLE_FAN); /* Inicio de la definicion de un abanico de triangulos */
			glVertex2fv (v[2]);
			glVertex2fv (v[0]);
			glVertex2fv (v[1]);
			glVertex2fv (v[3]);
			glVertex2fv (v[5]);
			glVertex2fv (v[4]);
		glEnd (); /* Fin de la definicion */
	glPopMatrix ();

	glPushMatrix ();
		glTranslatef (2.0f, -2.6f, 0.0f);
		glBegin (GL_QUAD_STRIP); /* Inicio de la definicion de una tira de romboides */
			glVertex2fv (v[0]);
			glVertex2fv (v[1]);
			glVertex2fv (v[2]);
			glVertex2fv (v[3]);
			glVertex2fv (v[4]);
			glVertex2fv (v[5]);
			glVertex2fv (v[6]);
			glVertex2fv (v[7]);
		glEnd (); /* Fin de la definicion */
	glPopMatrix ();
	glFlush();
}

/* Opciones sobre la visualización de la escena ----------------------------*/
void opcionesVisualizacion (void) {

  /* Inicio de la definicion de un abanico de triangulos */
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

  /* crea la ventana de la aplicación */
  abreVentana (numParametros, listaParametros);

  /* asocia funciones a eventos de ventana, teclado o ratón */
  asociaEventos ();              

  /* establece la función de dibujo de la escena */
  glutDisplayFunc (Dibuja);

  /* establece opciones sobre la visualización de la escena */
  opcionesVisualizacion();

  /* bucle a la espera de eventos */
  glutMainLoop();
}
