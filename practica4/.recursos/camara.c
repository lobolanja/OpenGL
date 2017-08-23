/* -------------------------------------------------------------------------*/
/* La cámara, R. Vivó                                                       */
/* -------------------------------------------------------------------------*/

#include <GL/glut.h>
#include <GL/glu.h>
#include <stdio.h>
#define anchoVentana 512 /* ancho de la ventana */
#define altoVentana 512 /* alto de la ventana */
#define posicionVentanaX 50 /* pos. X de la esquina sup-izq de la ventana */
#define posicionVentanaY 50 /* pos. Y de la esquina sup-izq de la ventana */

/* Rutina asociada a eventos de ventana ------------------------------------*/
void eventoVentana (GLsizei ancho, GLsizei alto) {
glViewport (0, 0, ancho, alto);
glMatrixMode(GL_PROJECTION);
glLoadIdentity();
glFrustum(-1.0,1.0,-1.0*(GLdouble)alto/ancho,1.0*(GLdouble)alto/ancho,1.0,20.0);
gluLookAt (0.0, 0.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
}
/* Establece las funciones que atienden los distintos eventos --------------*/
void asociaEventos (void) {
glutReshapeFunc (eventoVentana);
}
/* Rutina de dibujo de la escena -------------------------------------------*/
void Dibuja (void) {
glMatrixMode(GL_MODELVIEW);
glClearColor (1.0,1.0,1.0, 0.0);
glClear (GL_COLOR_BUFFER_BIT);
glColor3f (0.0, 0.0, 0.0);
glutWireTeapot(2.0);
glutSwapBuffers();
}
/* Abre la ventana de la aplicación ----------------------------------------*/
void abreVentana (int numParametros, char **listaParametros) {
glutInit (&numParametros, listaParametros);
glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
glutInitWindowSize (anchoVentana, altoVentana);
glutInitWindowPosition (posicionVentanaX, posicionVentanaY);
glutCreateWindow (listaParametros[0]);
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
