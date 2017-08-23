/* -------------------------------------------------------------------------*/
/* La c�mara, R. Viv�                                                       */
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
glMatrixMode(GL_PROJECTION);
glLoadIdentity();
glOrtho(-4.0,4.0,-4.0*(GLdouble)altoVentana/anchoVentana,4.0*(GLdouble)altoVentana/anchoVentana,1.0,20.0);
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
/* Fotograf�a del alzado */
glViewport (0, altoVentana/2, anchoVentana/2, altoVentana/2);
glMatrixMode(GL_PROJECTION);
glPushMatrix();
gluLookAt (0.0, 0.0, 4.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
glMatrixMode(GL_MODELVIEW);
glutWireTeapot(2.0);
glMatrixMode(GL_PROJECTION);
glPopMatrix();
glMatrixMode(GL_MODELVIEW);
/* Fotograf�a del perfil */
glViewport (anchoVentana/2, altoVentana/2, anchoVentana/2, altoVentana/2);
glMatrixMode(GL_PROJECTION);
glPushMatrix();
gluLookAt (4.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
glMatrixMode(GL_MODELVIEW);
glutWireTeapot(2.0);
glMatrixMode(GL_PROJECTION);
glPopMatrix();
glMatrixMode(GL_MODELVIEW);
/* Fotograf�a de la planta */
glViewport (0, 0, anchoVentana/2, altoVentana/2);
glMatrixMode(GL_PROJECTION);
glPushMatrix();
gluLookAt (0.0, 4.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, -1.0);
glMatrixMode(GL_MODELVIEW);
glutWireTeapot(2.0);
glMatrixMode(GL_PROJECTION);
glPopMatrix();
glMatrixMode(GL_MODELVIEW);
/* Fotograf�a isom�trica */
glViewport (anchoVentana/2, 0, anchoVentana/2, altoVentana/2);
glMatrixMode(GL_PROJECTION);
glPushMatrix();
gluLookAt (4.0, 4.0, 4.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
glMatrixMode(GL_MODELVIEW);
glutWireTeapot(2.0);
glMatrixMode(GL_PROJECTION);
glPopMatrix();
glMatrixMode(GL_MODELVIEW);
glutSwapBuffers();
}
/* Abre la ventana de la aplicaci�n ----------------------------------------*/
void abreVentana (int numParametros, char **listaParametros) {
glutInit (&numParametros, listaParametros);
glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
glutInitWindowSize (anchoVentana, altoVentana);
glutInitWindowPosition (posicionVentanaX, posicionVentanaY);
glutCreateWindow (listaParametros[0]);
}
/* Programa principal ------------------------------------------------------*/
int main (int numParametros, char **listaParametros) {
/* crea la ventana de la aplicaci�n */
abreVentana (numParametros, listaParametros);
/* asocia funciones a eventos de ventana, teclado o rat�n */
asociaEventos ();
/* establece la funci�n de dibujo de la escena */
glutDisplayFunc (Dibuja);
/* bucle a la espera de eventos */
glutMainLoop();
}
