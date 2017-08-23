/* -------------------------------------------------------------------------*/
/* Sistema de coordenadas 2D, E. Camahort                                   */
/* -------------------------------------------------------------------------*/


#include <GL/gl.h>
#include <GL/glut.h>
#include <stdio.h>

#define numeroImagenes	   2  /* numero total de imagenes de ejemplo */
#define anchoVentana     512  /* ancho de la ventana */
#define altoVentana      512  /* alto de la ventana */
#define posicionVentanaX  50  /* pos. X de la esquina sup-izq de la ventana */
#define posicionVentanaY  50  /* pos. Y de la esquina sup-izq de la ventana */

int    imagenActual = 0;      /* imagen de ejemplo actual */
double aspecto;   	      /* relación ancho/alto de la ventana */

void cambiarImagen();

/* Función que establece la proyección -------------------------------------*/
void proyeccion (void) {

  if (imagenActual == 0)
    {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-1, 1, -1, 1);
    }
  else
    {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-1, 0.5, -0.5, 0.5);
    }
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
  default : cambiarImagen(); break;
  }
}

/* Rutina de dibujo de la escena -------------------------------------------*/
void Dibuja (void) {

  glClear(GL_COLOR_BUFFER_BIT); 

  glBegin(GL_TRIANGLES);
    glVertex2f(-0.5, 0);
    glVertex2f(0, -0.5);
    glVertex2f(0.75, 0.75);
  glEnd();

  glutSwapBuffers();
}

/* Opciones sobre la visualización de la escena ----------------------------*/
void opcionesVisualizacion (void) {

  glClearColor(0.0, 0.0, 0.0, 1.0);

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  glTranslatef(0, 0, 1);
} 

/* Establece las funciones que atienden los distintos eventos --------------*/
void  asociaEventos (void) {

  glutReshapeFunc  (eventoVentana);
  glutKeyboardFunc (eventoTeclado);
}

/* Abre la ventana de la aplicación ----------------------------------------*/
void abreVentana (int numParametros, char **listaParametros) {

  glutInit               (&numParametros, listaParametros);
  glutInitDisplayMode    (GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
  glutInitWindowSize     (anchoVentana, altoVentana);
  glutInitWindowPosition (posicionVentanaX, posicionVentanaY);
  glutCreateWindow       (listaParametros[0]);
}

/* Rutina para cambiar entre las distintas imagenes de ejemplo -------------*/
void cambiarImagen()  
{
  imagenActual = (imagenActual + 1) % numeroImagenes;
  proyeccion();
  Dibuja();
}

/* Programa principal ------------------------------------------------------*/
int main (int numParametros, char **listaParametros) {

  /* crea la ventana de la aplicación */
  abreVentana (numParametros, listaParametros);

  /* asocia funciones a eventos de ventana, teclado o ratón */
  asociaEventos ();              

  /* establece la función de dibujo de la escena */
  glutDisplayFunc (Dibuja);

  /* establece opciones sobre la visualización de la escena */
  opcionesVisualizacion();

  /* bucle a la espera de eventos */
  glutMainLoop();
}
