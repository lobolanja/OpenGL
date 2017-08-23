/* -------------------------------------------------------------------------*/
/* Luz posicional, E. Camahort                                             */
/* -------------------------------------------------------------------------*/


#include <GL/gl.h>
#include <GL/glut.h>
#include <stdio.h>

#define numeroImagenes     4  /* numero total de imagenes de ejemplo */
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

  glutSolidSphere(1.0, 256, 256);

  glutSwapBuffers();
}

/* Define los materiales ---------------------------------------------------*/
void material (void) {

  GLfloat color_esfera_ambiente[]   = {0.5, 0.5, 0.5, 1.0};
  GLfloat color_esfera_difuso[]     = {0.8, 0.8, 0.8, 1.0};
  GLfloat color_esfera_especular[]  = {0.5, 0.5, 0.5, 1.0};
  GLfloat brillo_esfera_especular[] = {5.0};

  glMaterialfv(GL_FRONT, GL_AMBIENT,   color_esfera_ambiente);
  glMaterialfv(GL_FRONT, GL_DIFFUSE,   color_esfera_difuso);
  glMaterialfv(GL_FRONT, GL_SPECULAR,  color_esfera_especular);
  glMaterialfv(GL_FRONT, GL_SHININESS, brillo_esfera_especular);
}

/* Define las fuentes de luz -----------------------------------------------*/
void iluminacion() {

  GLfloat luz_ambiente[] = {0.2, 0.2, 0.2, 1.0};

  GLfloat luz_blanca_ambiente[]  = {0.1, 0.1, 0.1, 1.0};
  GLfloat luz_blanca_difusa[]    = {0.8, 0.8, 0.8, 1.0};
  GLfloat luz_blanca_especular[] = {0.4, 0.4, 0.4, 1.0};

  GLfloat luz_roja_ambiente[]  = {0.2, 0.0, 0.0, 1.0};
  GLfloat luz_roja_difusa[]    = {0.8, 0.3, 0.3, 1.0};
  GLfloat luz_roja_especular[] = {0.4, 0.1, 0.1, 1.0};

  GLfloat luz_posicion_baja[] = {0.0, 1.6, 1.6, 1.0};
  GLfloat luz_posicion_alta[] = {0.0, 0.8, 0.8, 1.0};

  glLightModelfv(GL_LIGHT_MODEL_AMBIENT, luz_ambiente);

  switch (imagenActual) {
  case 0 : glLightfv(GL_LIGHT0, GL_AMBIENT,  luz_blanca_ambiente);
	   glLightfv(GL_LIGHT0, GL_DIFFUSE,  luz_blanca_difusa);
	   glLightfv(GL_LIGHT0, GL_SPECULAR, luz_blanca_especular);
	   glLightfv(GL_LIGHT0, GL_POSITION, luz_posicion_baja);
  	   glLightf(GL_LIGHT0, GL_CONSTANT_ATTENUATION,  1.0);
	   glLightf(GL_LIGHT0, GL_LINEAR_ATTENUATION,    0.0);
	   glLightf(GL_LIGHT0, GL_QUADRATIC_ATTENUATION, 0.0);
	   break;
  case 1 : glLightfv(GL_LIGHT0, GL_AMBIENT,  luz_roja_ambiente);
	   glLightfv(GL_LIGHT0, GL_DIFFUSE,  luz_roja_difusa);
	   glLightfv(GL_LIGHT0, GL_SPECULAR, luz_roja_especular);
	   break;
  case 2 : glLightf(GL_LIGHT0, GL_CONSTANT_ATTENUATION,  0.0);
	   glLightf(GL_LIGHT0, GL_LINEAR_ATTENUATION,    1.0);
	   glLightf(GL_LIGHT0, GL_QUADRATIC_ATTENUATION, 0.0);
	   break;
  case 3 : glLightfv(GL_LIGHT0, GL_POSITION, luz_posicion_alta);
	   break;
  }

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
  glShadeModel  (GL_FLAT);
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
  iluminacion();
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
