/* -------------------------------------------------------------------------*/
/* Describiendo puntos, líneas y polígonos, J. Huerta                       */
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
  gluOrtho2D (0.0, 10.0, 0.0, 10.0);
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
  }
}

/* Opciones sobre la visualización de la escena ----------------------------*/
void opcionesVisualizacion (void) {

  glLineWidth(2.0f);
  glPointSize(4.0);
}

/* Establece las funciones que atienden los distintos eventos --------------*/
void  asociaEventos (void) {

  glutReshapeFunc  (eventoVentana);
  glutKeyboardFunc (eventoTeclado);
}

/* Rutina de dibujo de la escena -------------------------------------------*/
void Dibuja (void) {

  glClearColor (1.0f, 1.0f, 1.0f, 0.0f);
  glClear (GL_COLOR_BUFFER_BIT);

  glMatrixMode (GL_MODELVIEW);
  glLoadIdentity ();
  glColor3f(0.0, 0.0, 0.0);

  /* Dibuja un  punto utilizando un vértice --------------------------------*/
   glBegin(GL_POINTS);
     glVertex2f(1.0, 1.0); /* Punto 1 */
     glVertex2f(9.0, 1.0); /* Punto 2 */
     glVertex2f(1.0, 9.0); /* Punto 3 */
     glVertex2f(9.0, 9.0); /* Punto 4 */
   glEnd();

  /* Dibuja dos líneas conectando dos pares de vértices --------------------*/
  glBegin(GL_LINES);

    /* Vértice 1 línea 1 ---------------------------------------------------*/
    glVertex2f(1.0, 2.0);

    /* Vértice 2 línea 1 ---------------------------------------------------*/
    glVertex2f(4.0, 3.0);

    /* Vértice 3 línea 2 ---------------------------------------------------*/
    glVertex2f(1.0, 4.0);

    /* Vértice 4 línea 2 ---------------------------------------------------*/
    glVertex2f(4.0, 3.5);
  glEnd();

  /* Dibuja un triángulo utilizando tres vértices  -------------------------*/
  glBegin(GL_TRIANGLES);
    glVertex2f(1.0, 8.0); /* v1 */
    glVertex2f(5.0, 9.0); /* v2 */
    glVertex2f(2.0, 5.0); /* v3 */
  glEnd();

  /* Dibuja un cuadrilátero ------------------------------------------------*/
  glBegin(GL_QUADS);
    glVertex2f(5.0, 1.0); /* v1 */
    glVertex2f(6.0, 4.0); /* v2 */
    glVertex2f(8.5, 5.0); /* v3 */
    glVertex2f(9.0, 2.0); /* v4 */
  glEnd(); 
 
  /* Dibuja un polígono ----------------------------------------------------*/
  glBegin(GL_POLYGON);
    glVertex2f(6.0, 6.0); /* v1 */
    glVertex2f(5.0, 7.0); /* v2 */
    glVertex2f(7.0, 9.0); /* v3 */
    glVertex2f(9.0, 7.0); /* v4 */
    glVertex2f(8.0, 6.0); /* v5 */
  glEnd();

/* Vacia el  buffer para forzar el dibujo de todos los objetos -------------*/
  glFlush();

  glutSwapBuffers();
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

