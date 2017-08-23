/* -------------------------------------------------------------------------*/
/* Eliminación de parpadeo, J.Lluch                                         */
/* -------------------------------------------------------------------------*/


#include <GL/glut.h>
#include <stdio.h>

#define anchoVentana     512  /* ancho de la ventana */
#define altoVentana      512  /* alto de la ventana */
#define posicionVentanaX  50  /* pos. X de la esquina sup-izq de la ventana */
#define posicionVentanaY  50  /* pos. Y de la esquina sup-izq de la ventana */

double aspecto;   /* relación ancho/alto de la ventana */
static GLfloat x=100.0f, y=0.0f, incx=0.6f, incy=0.2f;

/* Función que establece la proyección -------------------------------------*/
void proyeccion (void) {

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(0.0, anchoVentana, 0.0, altoVentana, -1.0, 1.0);
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

/* Rutina asociada al estado sin eventos -----------------------------------*/
void sinEvento (void) {
   x = x + incx;
   y = y + incy;
   if (x > anchoVentana || x<0.0 ) incx=-incx;
   if (y > altoVentana || y<0.0 ) incy=-incy;

   // Indica que se debe de redibujar
   glutPostRedisplay();
}

/* Rutina de dibujo de la escena -------------------------------------------*/
void Dibuja (void) {
   glClear(GL_COLOR_BUFFER_BIT);

   //Movimiento del rectángulo
   glColor3f(1.0, 1.0, 1.0);
   glRectf(x, y, 25.0+x, 25.0+y);
   
   // Cambio de buffers
   glutSwapBuffers();
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
  glutDisplayFunc        (Dibuja);

  /* bucle a la espera de eventos */
  glutMainLoop();
}
