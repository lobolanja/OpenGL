/* -------------------------------------------------------------------------*/
/* Transformación de las primitivas, I. Remolar                             */
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
  glOrtho (-30.0, 30.0, -30.0, 30.0, -30.0, 30.0);
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
  gluLookAt (0,0,0, -3,-3,-3, 0,1,0);

  glColor3f ( 0.0, 0.0, 0.6); 

	switch (p)
		{
		case 1:
			glutSolidCone (9.0, 20.0, 16, 16);
			glTranslatef(22,0.0,0.0);
			glutSolidTorus(3.0,7.0, 16,16);
			break;
	
		case 2:
   		        glRotatef (-90.0, 1.0, 0.0, 0.0);
			glutSolidCone (9.0, 20.0, 16, 16);
			glTranslatef(22,0.0,0.0);
			glutSolidTorus(3.0,7.0, 16,16);
			break;

		case 3:
		        glPushMatrix();
   		          glRotatef (-90.0, 1.0, 0.0, 0.0);
			  glutSolidCone (9.0, 20.0, 16, 16);
			glPopMatrix();
			glTranslatef(22,0.0,0.0);
			glutSolidTorus(3.0,7.0, 16,16);
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
  case 'x':  p =3; Dibuja(); break;
  case 'c':  p =1; Dibuja(); break;
  }
}

/* Opciones sobre la visualización de la escena ----------------------------*/
void opcionesVisualizacion (void) {

  printf( " z - Dibuja las primitivas con una rotacion para el toroide sin usar las pilas de matrices\n");
  printf( " x - Realiza la rotacion del toroide usando las matrices\n");
  printf( " c - Vuelve al dibujado inicial\n");
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

