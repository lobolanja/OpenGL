/* -------------------------------------------------------------------------*/
/* Grosor de punto y l�nea, J. Huerta                                       */
/* -------------------------------------------------------------------------*/


#include <GL/glut.h>
#include <stdio.h>

#define anchoVentana      512  /* ancho de la ventana */
#define altoVentana       512  /* alto de la ventana */
#define posicionVentanaX   50  /* pos. X de la esquina sup-izq de la ventana */
#define posicionVentanaY   50  /* pos. Y de la esquina sup-izq de la ventana */

/* Funci�n que establece la proyecci�n -------------------------------------*/
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

/* Rutina asociada a eventos de teclado ------------------------------------*/
void eventoTeclado (unsigned char tecla, int x, int y) {

  switch (tecla) {
  case  27: exit (0); break;
  }
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
  glColor3f(1.0, 0.0, 0.0);

  /* V�rtice 1 de grosor 1 (grosor por defecto) ---------------------------*/
    glPointSize(1.0);
    glBegin(GL_POINTS);
    glVertex2f(0.0, 1.0);
    glEnd();
  /* V�rtice 2 de grosor 5 -------------------------------------------------*/
    glPointSize(5.0);
    glBegin(GL_POINTS);
    glVertex2f(0.0, 0.8);
    glEnd();

  /* V�rtice 3 de grosor 10 ------------------------------------------------*/
    glPointSize(10.0);
    glBegin(GL_POINTS);
    glVertex2f(0.0, 0.6);
    glEnd();

  /* Cambia a el color azul para dibujar las l�neas -------------------------*/
  glColor3f(0.0, 0.0, 1.0);

  /* L�nea 1 de grosor 1 (grosor por defecto) -------------------------------*/
    glLineWidth(1.0);
    glBegin(GL_LINES);
    glVertex2f(0.0, 0.4);
    glVertex2f(1.0, 0.4);
    glEnd();

 /* L�nea 2 de grosor 5 -----------------------------------------------------*/
    glLineWidth(5.0);
    glBegin(GL_LINES);
    glVertex2f(0.0, 0.2);
    glVertex2f(1.0, 0.2);
    glEnd();


  /* L�nea 3 de grosor 10 ---------------------------------------------------*/
  
    glLineWidth(10.0);
    glBegin(GL_LINES);
    glVertex2f(0.0, 0.0);
    glVertex2f(1.0, 0.0);
    glEnd();


/* Vacia el  buffer para forzar el dibujo de todos los objetos -------------*/
  glFlush();

  glutSwapBuffers();
}
/* Abre la ventana de la aplicaci�n ----------------------------------------*/
void abreVentana (int numParametros, char **listaParametros) {

  glutInit               (&numParametros, listaParametros);
  glutInitDisplayMode    (GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
  glutInitWindowSize     (anchoVentana, altoVentana);
  glutInitWindowPosition (posicionVentanaX, posicionVentanaY);
  glutCreateWindow       (listaParametros[0]);
}

/* Programa principal ------------------------------------------------------*/
int main (int numParametros, char **listaParametros) {

  /* crea la ventana de la aplicaci�n */
  abreVentana (numParametros, listaParametros);

  /* asocia funciones a eventos de ventana, teclado o rat�n */
  asociaEventos ();              

  /* establece la funci�n de dibujo de la escena */
  glutDisplayFunc        (Dibuja);

  /* bucle a la espera de eventos */
  glutMainLoop();
}

