/* -------------------------------------------------------------------------*/
/* Sombreado constante y suave, J. Lluch                                    */
/* -------------------------------------------------------------------------*/


#include <GL/glut.h>
#include <stdio.h>

#define anchoVentana     512  /* ancho de la ventana */
#define altoVentana      512  /* alto de la ventana */
#define posicionVentanaX  50  /* pos. X de la esquina sup-izq de la ventana */
#define posicionVentanaY  50  /* pos. Y de la esquina sup-izq de la ventana */

double aspecto;   /* relación ancho/alto de la ventana */
int    modo=1;    /* a 1 GL_FLAT habilitado, a 0 GL_SMOOTH habilitado */

/* Función que establece la proyección -------------------------------------*/
void proyeccion (void) {

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(-2.0, 2.0, -2.0, 2.0, -2.0, 2.0);
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
  case 32: 
    modo=!modo;
    if (modo) glShadeModel(GL_FLAT); 
    else glShadeModel(GL_SMOOTH); 
    break;
  case  27: exit (0); break;
  case 'q': exit (0); break;
  case 'Q': exit (0); break;
  }
  glutPostRedisplay();
}

/* Rutina de dibujo de la escena -------------------------------------------*/
void Dibuja (void) {

  glClearColor(1.0f,1.0f,1.0f,1.0f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  
  /* Dibujo de una esfera de radio 1.0 */
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  glutSolidSphere(1.0, 16, 16);
  glFlush (); 
}

/* Define los materiales ---------------------------------------------------*/
void material (void) {

  GLfloat difusa[]=    {0.7f, 0.7f, 0.7f, 1.0f};
  GLfloat especular[]= {0.2f, 0.2f, 0.2f, 1.0f};
  GLfloat brillo[]=    {50.0f};

  glMaterialfv (GL_FRONT, GL_AMBIENT_AND_DIFFUSE, difusa);
  glMaterialfv (GL_FRONT, GL_SPECULAR, especular);
  glMaterialfv (GL_FRONT, GL_SHININESS, brillo);

  glColorMaterial (GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
  glEnable (GL_COLOR_MATERIAL);
}

/* Define las fuentes de luz -----------------------------------------------*/
void iluminacion() {
  GLfloat posicion[]=  {10.0f, 10.0f, 10.0f, 1.0f};
  GLfloat difusa[]=    {0.7f, 0.7f,  0.7f, 1.0f};
  GLfloat especular[]= {0.2f, 0.2f,  0.2f, 1.0f};
  GLfloat ambiente[]=  {0.2f, 0.2f,  0.2f, 1.0f};

  glLightModelfv (GL_LIGHT_MODEL_AMBIENT, ambiente);

  glLightfv (GL_LIGHT0, GL_POSITION, posicion);
  glLightfv (GL_LIGHT0, GL_DIFFUSE,  difusa);
  glLightfv (GL_LIGHT0, GL_SPECULAR, especular);

  glEnable  (GL_LIGHTING);
  glEnable  (GL_LIGHT0);
}

/* Opciones sobre la visualización de la escena ----------------------------*/
void opcionesVisualizacion (void) {
   
  glDepthFunc(GL_LEQUAL);
  glEnable(GL_DEPTH_TEST);

  glShadeModel(GL_FLAT);
  printf ("Presiona la barra para habilitar sombreado CONSTANTE/SUAVE\n");
}

/* Establece las funciones que atienden los distintos eventos --------------*/
void  asociaEventos (void) {

  glutReshapeFunc  (eventoVentana);
  glutKeyboardFunc (eventoTeclado);
}

/* Abre la ventana de la aplicación ----------------------------------------*/
void abreVentana (int numParametros, char **listaParametros) {

  glutInit               (&numParametros, listaParametros);
  glutInitDisplayMode    (GLUT_SINGLE | GLUT_RGB);
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
  
  /* define las fuentes de luz */
  iluminacion();

  /* define los materiales */
  material ();

  /* bucle a la espera de eventos */
  glutMainLoop();
}
