/*--------------------------------------------------------------------------*/
/* Atendiendo eventos de ratón, F. Abad                                     */
/*--------------------------------------------------------------------------*/


#include <GL/glut.h>
#include <stdlib.h>

#define anchoVentana     512  /* ancho de la ventana */
#define altoVentana      512  /* alto de la ventana */
#define posicionVentanaX  50  /* pos. X de la esquina sup-izq de la ventana */
#define posicionVentanaY  50  /* pos. Y de la esquina sup-izq de la ventana */


/* Rutina asociada a eventos de ventana ------------------------------------*/
void eventoVentana (GLsizei ancho, GLsizei alto) {
  glViewport (0, 0, ancho, alto);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluOrtho2D(0.0,(GLdouble) ancho, 0.0, (GLdouble) alto);
}

/* Rutina asociada a eventos de teclado ------------------------------------*/
void eventoTeclado (unsigned char tecla, int x, int y) {

  switch (tecla) {
  case  27: exit (0); break;
  case 'q': exit (0); break;
  case 'Q': exit (0); break;
  }
}

/* Rutina asociada a eventos de ratón --------------------------------------*/
void eventoRaton (int boton, int estado, int x, int y) {
  char texto[200];
  strcpy(texto,"Has ");
  if (estado==GLUT_UP) strcat(texto,"soltado el botón ");
  else strcat(texto,"pulsado el botón ");
  switch (boton) {
  case GLUT_LEFT_BUTTON:
    strcat(texto,"izquierdo");
    break;
  case GLUT_RIGHT_BUTTON:
    strcat(texto,"derecho");
    break;
  case GLUT_MIDDLE_BUTTON:
    strcat(texto,"central");
    break;
  }
  printf("%s en (%d,%d)\n",texto,x,y);
}

/* Rutina asociada a movimiento del ratón ----------------------------------*/
void eventoMovimientoRaton (int x, int y) {
  printf("pasando por (%d,%d)...\n",x,y);
}

/* Rutina de dibujo de la escena -------------------------------------------*/
void Dibuja (void) {
  glClear(GL_COLOR_BUFFER_BIT);

  glutSwapBuffers();
}

/* Establece las funciones que atienden los distintos eventos --------------*/
void  asociaEventos (void) {

  glutReshapeFunc  (eventoVentana);
  glutKeyboardFunc (eventoTeclado);
  glutMouseFunc    (eventoRaton);
  glutMotionFunc   (eventoMovimientoRaton);
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

  /* crea la ventana de la aplicación */
  abreVentana (numParametros, listaParametros);

  /* asocia funciones a eventos de ventana, teclado o ratón */
  asociaEventos ();              

  /* establece la función de dibujo de la escena */
  glutDisplayFunc (Dibuja);

  /* bucle a la espera de eventos */
  glutMainLoop();
}
