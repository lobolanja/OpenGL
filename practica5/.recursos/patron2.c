/* -------------------------------------------------------------------------*/
/* Patrones de línea y de relleno, O. Belmonte                              */
/* -------------------------------------------------------------------------*/


#include <GL/glut.h>
#include <stdio.h>

#define anchoVentana     512  /* ancho de la ventana */
#define altoVentana      512  /* alto de la ventana */
#define posicionVentanaX  50  /* pos. X de la esquina sup-izq de la ventana */
#define posicionVentanaY  50  /* pos. Y de la esquina sup-izq de la ventana */

GLuint id; /* Identificador para la Display List */

/* Patron de relleno */
GLubyte mosca[] = {
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x03, 0x80, 0x01, 0xC0, 0x06, 0xC0, 0x03, 0x60, 
  0x04, 0x60, 0x06, 0x20, 0x04, 0x30, 0x0C, 0x20, 
  0x04, 0x18, 0x18, 0x20, 0x04, 0x0C, 0x30, 0x20,
  0x04, 0x06, 0x60, 0x20, 0x44, 0x03, 0xC0, 0x22, 
  0x44, 0x01, 0x80, 0x22, 0x44, 0x01, 0x80, 0x22, 
  0x44, 0x01, 0x80, 0x22, 0x44, 0x01, 0x80, 0x22,
  0x44, 0x01, 0x80, 0x22, 0x44, 0x01, 0x80, 0x22, 
  0x66, 0x01, 0x80, 0x66, 0x33, 0x01, 0x80, 0xCC, 
  0x19, 0x81, 0x81, 0x98, 0x0C, 0xC1, 0x83, 0x30,
  0x07, 0xe1, 0x87, 0xe0, 0x03, 0x3f, 0xfc, 0xc0, 
  0x03, 0x31, 0x8c, 0xc0, 0x03, 0x33, 0xcc, 0xc0, 
  0x06, 0x64, 0x26, 0x60, 0x0c, 0xcc, 0x33, 0x30,
  0x18, 0xcc, 0x33, 0x18, 0x10, 0xc4, 0x23, 0x08, 
  0x10, 0x63, 0xC6, 0x08, 0x10, 0x30, 0x0c, 0x08, 
  0x10, 0x18, 0x18, 0x08, 0x10, 0x00, 0x00, 0x08};

/* Función que establece la proyección -------------------------------------*/
void proyeccion (void) {

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);
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
  case 'q': exit (0); break;
  case 'Q': exit (0); break;
  }
}

/* Rutina de dibujo de la escena -------------------------------------------*/
void Dibuja (void) {
  float vertices[4][2] = {{-0.5f, -0.5f}, {0.5f, -0.5f}, {0.5f, 0.5f}, {-0.5f, 0.5f}};

  glClear (GL_COLOR_BUFFER_BIT); /* Borramos el buffer de color */
 
  /* Transformacion de la camara */
  glMatrixMode(GL_MODELVIEW); /* Seleccionamos la matriz modelo vista */
  glLoadIdentity(); /* Cargamos la matriz unidad sobre la modelo vista */

  glBegin (GL_POLYGON);
    glVertex2fv (vertices[0]);
    glVertex2fv (vertices[1]);
    glVertex2fv (vertices[2]);
    glVertex2fv (vertices[3]);
  glEnd ();

  glFlush();
}

/* Opciones sobre la visualización de la escena ----------------------------*/
void opcionesVisualizacion (void) {

  //glPolygonMode (GL_FRONT_AND_BACK, GL_LINE);
  glPolygonStipple (mosca);
  glEnable (GL_POLYGON_STIPPLE);
  glClearColor (0.8f, 0.8f, 0.8f, 0.0f);
  glColor3f (0.0f, 0.0f,0.0f);
}

/* Establece las funciones que atienden los distintos eventos --------------*/
void  asociaEventos (void) {

  glutReshapeFunc  (eventoVentana);
  glutKeyboardFunc (eventoTeclado);
}

/* Abre la ventana de la aplicación ----------------------------------------*/
void abreVentana (int numParametros, char **listaParametros) {

  glutInit               (&numParametros, listaParametros);
  glutInitDisplayMode    (GLUT_SINGLE);
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
