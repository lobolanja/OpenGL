/* -------------------------------------------------------------------------*/
/* Definiendo materiales,  E. Camahort                                      */
/* -------------------------------------------------------------------------*/


#include <GL/gl.h>
#include <GL/glut.h>
#include <stdio.h>

#define numeroImagenes     3  /* numero total de imagenes de ejemplo */
#define anchoVentana     512  /* ancho de la ventana */
#define altoVentana      512  /* alto de la ventana */
#define posicionVentanaX  50  /* pos. X de la esquina sup-izq de la ventana */
#define posicionVentanaY  50  /* pos. Y de la esquina sup-izq de la ventana */

int    imagenActual = 0;      /* imagen de ejemplo actual */
double aspecto;               /* relación ancho/alto de la ventana */

void cambiarImagen();

/* Función que establece la proyección -------------------------------------*/
void proyeccion (void) {

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(30.0, aspecto, 1.0f, 10.0f); /* o glOrtho */
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

  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  glutSolidSphere(1.0, 15, 15);

  glutSwapBuffers();
}

/* Define los materiales ---------------------------------------------------*/
void material (void) {

  GLfloat color_difuso_y_ambiente[] = {0.3, 0.3, 0.3, 1.0};
  GLfloat color_especular_ninguno[] = {0.0, 0.0, 0.0, 1.0};
  GLfloat color_especular_blanco[]  = {1.0, 1.0, 0, 1.0};

  GLfloat brillo_especular_suave[]  = {10.0};
  GLfloat brillo_especular_fuerte[] = {100.0};


      glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, color_difuso_y_ambiente);
      glMaterialfv(GL_FRONT, GL_SPECULAR, color_especular_blanco);
      glMaterialfv(GL_FRONT, GL_SHININESS, brillo_especular_suave);

  
}

/* Define las fuentes de luz -----------------------------------------------*/
void iluminacion() {
  GLfloat posicion[]=  {1.0f, 1.0f, 1.0f, 0.0f};
  GLfloat difusa[]=    {0.0f, 0.7f, 0.0f, 1.0f};
  GLfloat especular[]= {0.7f, 0.7f, 0.0f, 1.0f};
  GLfloat ambiente[]=  {0.0f, 0.2f, 0.0f, 1.0f};

  glLightModelfv (GL_LIGHT_MODEL_AMBIENT, ambiente);

  glLightfv (GL_LIGHT0, GL_POSITION, posicion);
  glLightfv (GL_LIGHT0, GL_DIFFUSE,  difusa);
  glLightfv (GL_LIGHT0, GL_SPECULAR, especular);

  glEnable  (GL_LIGHTING);
  glEnable  (GL_LIGHT0);
}

/* Opciones sobre la visualización de la escena ----------------------------*/
void opcionesVisualizacion (void) {

  /* por ejemplo....*/
  glPolygonMode (GL_FRONT, GL_FILL);
  glFrontFace   (GL_CCW);
  glCullFace    (GL_BACK);
  glEnable      (GL_CULL_FACE);
  glShadeModel  (GL_SMOOTH);
  glDepthFunc   (GL_LEQUAL);
  glEnable      (GL_DEPTH_TEST);
  glEnable      (GL_NORMALIZE);

  glClearColor(0.0, 0.0, 0.0, 1.0);

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  glTranslatef(0, 0, -5);
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
  material();
  Dibuja();
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

  /* define las fuentes de luz */
  iluminacion();

  /* define los materiales */
  material ();

  /* bucle a la espera de eventos */
  glutMainLoop();
}
