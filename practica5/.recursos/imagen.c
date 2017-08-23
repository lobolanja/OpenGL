/* -------------------------------------------------------------------------*/
/* Guardar y visualizar imágenes, A. López                                  */
/* -------------------------------------------------------------------------*/


#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>

#define anchoVentana     640  /* ancho de la ventana */
#define altoVentana      480  /* alto de la ventana */
#define posicionVentanaX  50  /* pos. X de la esquina sup-izq de la ventana */
#define posicionVentanaY  50  /* pos. Y de la esquina sup-izq de la ventana */

double aspecto;   /* relación ancho/alto de la ventana */
GLubyte *pixeles;

/* Función que establece la proyección -------------------------------------*/
void proyeccion (void) {

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluOrtho2D(0.0f, 640.0f, 0.0f, 480.0f); 
}

/* Rutina asociada a eventos de ventana ------------------------------------*/
void eventoVentana (GLsizei ancho, GLsizei alto) {
  
  glViewport (0, 0, ancho, alto);
  aspecto= (GLdouble) ancho/alto;
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

  FILE *fichero;
  int ancho, alto;

  glClearColor (0,0,0,0);
  glClear (GL_COLOR_BUFFER_BIT);

  glBegin (GL_LINES); 
    glVertex2i(0,0); 
    glVertex2i(640,480); 
    glVertex2i(640,0); 
    glVertex2i(0,480); 
  glEnd();

  glRecti(270, 190, 370, 290);
  
  /* que la alineación sea múltiplo de 1 */
  glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
  glPixelStorei(GL_PACK_ALIGNMENT, 1);

  /* transferio la imagen a memoria */
  glReadPixels (0, 0, 640, 480, GL_RGB, GL_UNSIGNED_BYTE, pixeles);
  glClear (GL_COLOR_BUFFER_BIT); /* borro la ventana */

  /* transfiero la imagen a la ventana */
  glRasterPos2i (0, 0);
  glDrawPixels (640, 480, GL_RGB, GL_UNSIGNED_BYTE, pixeles);

  glFlush();
}

/* Establece las funciones que atienden los distintos eventos --------------*/
void  asociaEventos (void) {

  glutKeyboardFunc (eventoTeclado);
  glutReshapeFunc  (eventoVentana);
}

/* Abre la ventana de la aplicación ----------------------------------------*/
void abreVentana (int numParametros, char **listaParametros) {

  glutInit               (&numParametros, listaParametros);
  glutInitDisplayMode    (GLUT_SINGLE | GLUT_RGB);
  glutInitWindowSize     (anchoVentana, altoVentana);
  glutInitWindowPosition (posicionVentanaX, posicionVentanaY);
  glutCreateWindow       (listaParametros[0]);
}

/* Programa principal ------------------------------------------------------*/
int main (int numParametros, char **listaParametros) {

  pixeles = (GLubyte *) calloc (sizeof (GLubyte), 640*480*3);

  /* crea la ventana de la aplicación*/
  abreVentana (numParametros, listaParametros);

  /* asocia funciones a eventos de ventana, teclado o ratón*/
  asociaEventos ();              

  /* asocia la rutina de dibujo */
  glutDisplayFunc (Dibuja);

  /* bucle a la espera de eventos */
  glutMainLoop();
}
