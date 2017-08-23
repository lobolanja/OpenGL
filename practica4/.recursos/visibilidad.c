/* -------------------------------------------------------------------------*/
/* Visibilidad, C. Rebollo                                                  */
/* -------------------------------------------------------------------------*/


#include <GL/glut.h>
#include <stdio.h>

#define anchoVentana     512  /* ancho de la ventana */
#define altoVentana      512  /* alto de la ventana */
#define posicionVentanaX  50  /* pos. X de la esquina sup-izq de la ventana */
#define posicionVentanaY  50  /* pos. Y de la esquina sup-izq de la ventana */

int op = 1;

/* Función que establece la proyección -------------------------------------*/
void proyeccion (void) {

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho (-0.2, 1.2, -0.2, 1.2, -2.0, 2.0);
}

/* Rutina asociada a eventos de ventana ------------------------------------*/
void eventoVentana (GLsizei ancho, GLsizei alto) {
  
  glViewport (0, 0, ancho, alto);
  proyeccion();
}


/* Rutina de dibujo de la escena -------------------------------------------*/
void Dibuja (void) {

  glClearColor (.95f, .95f, .95f, 0.0f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  glMatrixMode (GL_MODELVIEW);
  glLoadIdentity ();
 
  switch (op)
  {
  case 1:
	// Esfera de color rojo
	glTranslatef(0.5,0.3,0.0);
	glColor3f ( 1.0, 0.0, 0.0);
	glutSolidSphere(0.25,20, 20);
	break;
  case 2:
 	// Esfera de color rojo
	glTranslatef(0.5,0.3,0.0);
	glColor3f ( 1.0, 0.0, 0.0);
	glutSolidSphere(0.25,20, 20);

	// Esfera de color verde
	glTranslatef(0.2,0.0,-0.3);
	glColor3f ( 0.0, 1.0, 0.0);
	glutSolidSphere(0.3,20,20);
	break;
  case 3:
 	// Esfera de color rojo
	glTranslatef(0.5,0.3,0.0);
	glColor3f ( 1.0, 0.0, 0.0);
	glutSolidSphere(0.25,20, 20);

	// Esfera de color verde
	glTranslatef(0.2,0.0,-0.3);
	glColor3f ( 0.0, 1.0, 0.0);
	glutSolidSphere(0.3,20,20);

	// Cubo azul
	glTranslatef(-0.2,0.2,-0.5);
	glColor3f ( 0.0, 0.0, 1.0);
	glutSolidCube(0.5);
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
  case  '1': op=1; Dibuja(); break;
  case  '2': op=2; Dibuja(); break;
  case  '3': op=3; Dibuja(); break;

  case 'z': printf( "Z-Buffer Desactivado\n"); glDisable (GL_DEPTH_TEST); Dibuja(); break;
  case 'x': printf( "Z-Buffer Activado\n");glEnable (GL_DEPTH_TEST); Dibuja(); break;

  }
}

/* Opciones sobre la visualización de la escena ----------------------------*/
void opcionesVisualizacion (void) {

  glDepthFunc   (GL_LEQUAL);
  glEnable      (GL_DEPTH_TEST);
  printf (" Pulsando sucesivamente las teclas 1, 2, 3 apareceren las figuras geometricas\n");
  printf( " z - desactiva el Z-Buffer\n");
  printf( " x - activa el Z-Buffer\n");
  printf( "--------------------------------------------------\n");
}

/* Establece las funciones que atienden los distintos eventos --------------*/
void  asociaEventos (void) {

  glutReshapeFunc  (eventoVentana);
  glutKeyboardFunc (eventoTeclado);
}

/* Abre la ventana de la aplicación ----------------------------------------*/
void abreVentana (int numParametros, char **listaParametros) {

  glutInit               (&numParametros, listaParametros);
  glutInitDisplayMode    (GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
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

