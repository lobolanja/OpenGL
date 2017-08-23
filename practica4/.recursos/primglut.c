/* -------------------------------------------------------------------------*/
/* Primitivas geométricas, C. Rebollo                                       */
/* -------------------------------------------------------------------------*/


#include <GL/glut.h>
#include <stdio.h>

#define anchoVentana     512  /* ancho de la ventana */
#define altoVentana      512  /* alto de la ventana */
#define posicionVentanaX  50  /* pos. X de la esquina sup-izq de la ventana */
#define posicionVentanaY  50  /* pos. Y de la esquina sup-izq de la ventana */
#define alambre 1
#define solido 2

int modo= solido;

/* Función que establece la proyección -------------------------------------*/
void proyeccion (void) {

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho (-1.2, 1.2, -1.2, 1.2, -1.2, 1.2);
}

/* Rutina asociada a eventos de ventana ------------------------------------*/
void eventoVentana (GLsizei ancho, GLsizei alto) {
  
  glViewport (0, 0, ancho, alto);
  proyeccion();
}

/* Rutina de dibujo de la escena -------------------------------------------*/
void Dibuja () {

  glClearColor (.95f, .95f, .95f, 0.0f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  glMatrixMode (GL_MODELVIEW);
  glLoadIdentity ();
  gluLookAt (0,0,0, -3,-3,-3, 0,1,0);
  glScalef (0.2,0.2,0.2);

  switch (modo) { 
  case alambre:
    glColor3f (1.0, 0.0, 0.0); 
    glutWireTorus(1.0,5.0,10.0,30.0);
    glColor3f (0.0, 1.0, 0.0); 
    glutWireSphere(5.0,30.0,30.0);
    glColor3f (0.0, 0.0, 1.0); 
    glutWireCone(5.0,8.0,10.0,10.0);
    break;
  case solido:
    glColor3f (1.0, 0.0, 0.0); 
    glutSolidTorus(1.0,5.0,10.0,30.0);
    glColor3f (0.0, 1.0, 0.0); 
    glutSolidSphere(5.0,30.0,30.0);
    glColor3f (0.0, 0.0, 1.0); 
    glutSolidCone(5.0,8.0,10.0,10.0);
  break;
  }

  glutSwapBuffers();
}

/* Rutina asociada a eventos de teclado ------------------------------------*/
void eventoTeclado (unsigned char tecla, int x, int y) {

  switch (tecla) {
  case  27: exit (0); break;
  case 'x': modo= solido; break;
  case 'z': modo= alambre; break;
  }
  glutPostRedisplay();
}

/* Opciones sobre la visualización de la escena ----------------------------*/
void opcionesVisualizacion (void) {

  glDepthFunc   (GL_LEQUAL);
  glEnable      (GL_DEPTH_TEST);
  printf( " z - Alámbrico\n");
  printf( " x - Sólido \n");
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

