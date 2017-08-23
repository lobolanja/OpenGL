/* -------------------------------------------------------------------------*/
/* Antialiasing, I. Remolar                                                 */
/* -------------------------------------------------------------------------*/


#include <GL/glut.h>
#include <stdio.h>

#define anchoVentana     512  /* ancho de la ventana */
#define altoVentana      512  /* alto de la ventana */
#define posicionVentanaX  50  /* pos. X de la esquina sup-izq de la ventana */
#define posicionVentanaY  50  /* pos. Y de la esquina sup-izq de la ventana */

int p = 1;

/* Función que establece la proyección -------------------------------------*/
void proyeccion (void) {

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluOrtho2D (-0.2, 1.2, -0.2, 1.2);
}

/* Rutina asociada a eventos de ventana ------------------------------------*/
void eventoVentana (GLsizei ancho, GLsizei alto) {
  
  glViewport (0, 0, ancho, alto);
  proyeccion();
}

/* Rutina de dibujo de la escena -------------------------------------------*/
void Dibuja () {

  glClearColor (.95f, .95f, .95f, 0.0f);
  glClear(GL_COLOR_BUFFER_BIT );

  glMatrixMode (GL_MODELVIEW);
  glLoadIdentity ();
  glColor3f ( 0.5, 0.0, 0.2); 

	switch (p)
		{
		case 1:
			glBegin ( GL_LINES);
				glVertex2f (0.02, 0.02);
				glVertex2f (0.3, 0.9);
			glEnd();

			glBegin ( GL_LINES);
				glVertex2f (0.4, 0.02);
				glVertex2f (0.5, 0.9);
			glEnd();

			glBegin ( GL_LINES);
				glVertex2f (0.6, 0.02);
				glVertex2f (0.98, 0.5);
			glEnd();

			break;
	
		case 2:
			glEnable (GL_LINE_SMOOTH);
			glEnable( GL_BLEND);
			glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
			glHint ( GL_LINE_SMOOTH_HINT, GL_NICEST);
		
			glBegin ( GL_LINES);
				glVertex2f (0.02, 0.02);
				glVertex2f (0.3, 0.9);
			glEnd();

			glBegin ( GL_LINES);
				glVertex2f (0.4, 0.02);
				glVertex2f (0.5, 0.9);
			glEnd();

			glBegin ( GL_LINES);
				glVertex2f (0.6, 0.02);
				glVertex2f (0.98, 0.5);
			glEnd();

			glDisable (GL_LINE_SMOOTH);
			glDisable( GL_BLEND);

			break;


		default:
			break;

 }

  glutSwapBuffers();
}

/* Rutina asociada a eventos de teclado ------------------------------------*/
void eventoTeclado (unsigned char tecla, int x, int y) {

  switch (tecla) {
  case  27: exit (0); break;
  case 'z':  p =2; Dibuja(); break;
  case 'x':  p =1; Dibuja(); break;
  }
}

/* Opciones sobre la visualización de la escena ----------------------------*/
void opcionesVisualizacion (void) {

  glLineWidth (30.0);


  printf( " z - Aplica el efecto anti-aliasing a la linea\n");
  printf( " x - Dibuja la linea \n");
}


/* Establece las funciones que atienden los distintos eventos --------------*/
void  asociaEventos (void) {

  glutReshapeFunc  (eventoVentana);
  glutKeyboardFunc (eventoTeclado);
}

/* Abre la ventana de la aplicación ----------------------------------------*/
void abreVentana (int numParametros, char **listaParametros) {

  glutInit               (&numParametros, listaParametros);
  glutInitDisplayMode    (GLUT_DOUBLE | GLUT_RGB );
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

