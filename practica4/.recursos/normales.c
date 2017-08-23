/* -------------------------------------------------------------------------*/
/* Especificación de normales, I. Remolar                                   */
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
  glOrtho (-1.2, 1.2, -1.2, 1.2, -2.0, 2.0);
}

/* Rutina asociada a eventos de ventana ------------------------------------*/
void eventoVentana (GLsizei ancho, GLsizei alto) {
  
  glViewport (0, 0, ancho, alto);
  proyeccion();
}

/* Rutina de dibujo de la escena -------------------------------------------*/
void Dibuja () {

  glClearColor (1.0f, 1.0f, 1.0f, 0.0f);
  glClear(GL_COLOR_BUFFER_BIT );

  glMatrixMode (GL_MODELVIEW);
  glLoadIdentity ();
  glColor3f ( 0.5, 0.5, 0.5); 

	switch (p)
		{
		case 1:
			glBegin ( GL_POLYGON);	
			glNormal3f( 0.0, 0.0, 1.0);
			glVertex3f (-1.0, -1.0, 0.0);
			glVertex3f ( 1.0, -1.0, 0.0);
			glVertex3f (1.0, 1.0, 0.0);
			glVertex3f (-1.0, 1.0, 0.0);
			glEnd();
			break;
	
		case 2:
			glBegin ( GL_POLYGON);	
			glNormal3f( 0.0, -1.0, 1.0);
			glVertex3f (-1.0, -1.0, 0.0);
			glNormal3f( 0.0, -1.0, 1.0);
			glVertex3f ( 1.0, -1.0, 0.0);
			glNormal3f( 0.0, 1.0, 1.0);
			glVertex3f (1.0, 1.0, 0.0);
			glNormal3f( 0.0, 1.0, 1.0);	
			glVertex3f (-1.0, 1.0, 0.0);
			glEnd();
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

  printf( " z - Asigna distintas normales\n");
  printf( " x - Asigna la misma normal a todos los vertices del poligono\n");
}

/* Define los materiales ---------------------------------------------------*/
void material (void) {

  GLfloat difusa[]=    {0.7f, 0.7f, 0.7f, 1.0f};
  GLfloat especular[]= {0.2f, 0.2f, 0.2f, 1.0f};
  GLfloat brillo[]=    {50.0f};

  glMaterialfv (GL_FRONT, GL_AMBIENT_AND_DIFFUSE, difusa);
  glMaterialfv (GL_FRONT, GL_SPECULAR, especular);
  glMaterialfv (GL_FRONT, GL_SHININESS, brillo);

  glColorMaterial (GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
  glEnable (GL_COLOR_MATERIAL);
}

/* Define las fuentes de luz -----------------------------------------------*/
void iluminacion() {
  GLfloat posicion[]=  {0.0f, 10.0f, 10.0f, 1.0f};
  GLfloat difusa[]=    {0.7f, 0.7f,  0.7f, 1.0f};
  GLfloat especular[]= {0.2f, 0.2f,  0.2f, 1.0f};
  GLfloat ambiente[]=  {0.2f, 0.2f,  0.2f, 1.0f};

  //  glLightModelfv (GL_LIGHT_MODEL_AMBIENT, ambiente);

  glLightfv (GL_LIGHT0, GL_POSITION, posicion);
  glLightfv (GL_LIGHT0, GL_DIFFUSE,  difusa);
  glLightfv (GL_LIGHT0, GL_SPECULAR, especular);

  glEnable  (GL_LIGHTING);
  glEnable  (GL_LIGHT0);
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

  /* define las fuentes de luz */
  iluminacion();

  /* define los materiales */
  material ();

  /* establece opciones sobre la visualización de la escena */
  opcionesVisualizacion();

  /* bucle a la espera de eventos */
  glutMainLoop();
}

