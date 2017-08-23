/* -------------------------------------------------------------------------*/
/* Atendiendo eventos de teclado, F. Abad                                   */
/* -------------------------------------------------------------------------*/

/*

Este programa permite inspeccionar una tetera desde varios puntos de vista 
con las teclas O,P,Q y A. Para salir del programa se puede utilizar X o ESC. 

*/

#include <GL/glut.h>
#include <stdio.h>


#define anchoVentana     512  /* ancho de la ventana */
#define altoVentana      512  /* alto de la ventana */
#define posicionVentanaX  50  /* pos. X de la esquina sup-izq de la ventana */
#define posicionVentanaY  50  /* pos. Y de la esquina sup-izq de la ventana */
#define INCR               4  /* incremento en grados */
 
static GLfloat rotX=0.0,rotY=0.0;

/* Rutina asociada a eventos de ventana ------------------------------------*/
void eventoVentana (GLsizei ancho, GLsizei alto) {
  glViewport (0, 0, ancho, alto);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(-50,50,-50,50,1,100);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
}

/* Rutina asociada a eventos de teclado ------------------------------------*/
void eventoTeclado (unsigned char tecla, int x, int y) {

  switch (tecla) {
  case 'O':
  case 'o':
    rotY+=INCR;
    if (rotY>=360.0) rotY-=360.0;
    break;
  case 'P':
  case 'p':
    rotY-=INCR;
    if (rotY<0.0) rotY+=360.0;
    break;
  case 'Q':
  case 'q':
    rotX+=INCR;
    if (rotX>=360.0) rotX-=360.0;
    break;
  case 'A':
  case 'a':
    rotX-=INCR;
    if (rotX<0.0) rotX+=360.0;
    break;
  case  27: 
  case 'X': 
  case 'x': 
    exit (0); break;
  }
  glutPostRedisplay();
}

/* Rutina de dibujo de la escena -------------------------------------------*/
void Dibuja (void) {
  glClear(GL_COLOR_BUFFER_BIT);
  glPushMatrix();
  glTranslatef(0.0,0.0,-30.0);
  glRotatef(rotX,1.0,0.0,0.0);
  glRotatef(rotY,0.0,1.0,0.0);
  glColor3f(1.0,1.0,1.0);
  glutWireTeapot(20);
  glPopMatrix();
  glutSwapBuffers();
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

  /* crea la ventana de la aplicación */
  abreVentana (numParametros, listaParametros);

  /* asocia funciones a eventos de ventana, teclado o ratón */
  asociaEventos ();              

  /* establece la función de dibujo de la escena */
  glutDisplayFunc (Dibuja);

  /* bucle a la espera de eventos */
  glutMainLoop();
}
