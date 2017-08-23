/* -------------------------------------------------------------------------*/
/* Atendiendo eventos de ventana, F. Abad                                   */
/* -------------------------------------------------------------------------*/

/* 

Dibuja una tetera en proyección ortográfica manteniendo el mismo tamaño y 
aspecto, independientemente del tamaño de la ventana.

*/


#include <GL/glut.h>
#include <stdio.h>


#define anchoVentana     512  /* ancho de la ventana */
#define altoVentana      512  /* alto de la ventana */
#define posicionVentanaX  50  /* pos. X de la esquina sup-izq de la ventana */
#define posicionVentanaY  50  /* pos. Y de la esquina sup-izq de la ventana */

int rotY=0;                   /* Ángulo de rotación sobre el eje Y */

/* Rutina asociada a eventos de ventana ------------------------------------*/
void eventoVentana (GLsizei ancho, GLsizei alto) {
  float xx,yy;
  glViewport (0, 0, ancho, alto);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  xx=50.0*ancho/anchoVentana;
  yy=50.0*alto/altoVentana;
  glOrtho(-xx,xx,-yy,yy,1,100);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
}

/* Rutina asociada a eventos de teclado ------------------------------------*/
void eventoTeclado (unsigned char tecla, int x, int y) {

  switch (tecla) {
  case  27: 
  case 'X': 
  case 'x': 
    exit (0); break;
  }
}

/* Rutina de dibujo de la escena -------------------------------------------*/
void Dibuja (void) {
  glClear(GL_COLOR_BUFFER_BIT);
  glColor3f(1.0,1.0,1.0);
  glTranslatef(0.0,0.0,-50.0f);
  glRotatef((float)rotY,0.0,1.0,0.0);
  glutWireTeapot(20);
  glLoadIdentity();
  glutSwapBuffers();
}

/* Rutina asociada al estado sin eventos -----------------------------------*/
void sinEvento (void) {
  static int BIT=0;
  if (BIT) {
    rotY=(rotY+1)%360;
    glutPostRedisplay();
  } 
  BIT=!BIT;
}

/* Establece las funciones que atienden los distintos eventos --------------*/
void  asociaEventos (void) {

  glutReshapeFunc  (eventoVentana);
  glutKeyboardFunc (eventoTeclado);
  glutIdleFunc     (sinEvento);
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

  /* crea la ventana de la aplicación */
  abreVentana (numParametros, listaParametros);

  /* asocia funciones a eventos de ventana, teclado o ratón */
  asociaEventos ();              

  /* establece la función de dibujo de la escena */
  glutDisplayFunc        (Dibuja);

  /* bucle a la espera de eventos */
  glutMainLoop();
}
