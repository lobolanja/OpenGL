/* -------------------------------------------------------------------------*/
/* Menús desplegables, A. López                                             */
/* -------------------------------------------------------------------------*/


#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>

#define anchoVentana     640  /* ancho de la ventana */
#define altoVentana      480  /* alto de la ventana */
#define posicionVentanaX  50  /* pos. X de la esquina sup-izq de la ventana */
#define posicionVentanaY  50  /* pos. Y de la esquina sup-izq de la ventana */
#define perspectiva       1
#define alzado            2
#define planta            3
#define perfil            4

double aspecto;   /* relación ancho/alto de la ventana */
int    modo=1;    /* tipo de proyección y vista */

/* Función que establece la proyección perspectiva -------------------------*/
void proyeccionPerspectiva (void) {

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(22.0, aspecto, 1.0, 10.0); 
}

/* Función que establece la proyección paralela ----------------------------*/
void proyeccionParalela (void) {

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(-1.5f*aspecto, 1.5f*aspecto, -1.5f, 1.5f, -2.0f, 2.0f); 
}

/* Rutina asociada a eventos de ventana ------------------------------------*/
void eventoVentana (GLsizei ancho, GLsizei alto) {
  
  glViewport (0,0,ancho, alto);
  aspecto= (GLdouble) ancho/alto;
}

/* Rutina asociada a eventos de teclado ------------------------------------*/
void eventoTeclado (unsigned char tecla, int x, int y) {

  switch (tecla) {
  case  27: exit (0); break;
  case 'q': exit (0); break;
  case 'Q': exit (0); break;
  }
}

void escena (void) {

  glPushMatrix();
  glRotatef(25.000000,0.000000,0.000000,1.000000);
  glRotatef(90.000000,1.000000,0.000000,0.000000);
  glutWireTorus(0.200000,1.000000,20.000000,20.000000);
  glPopMatrix();
  
  glPushMatrix();
  glScalef(0.500000,1.000000,0.500000);
  glutWireSphere(1.000000,20.000000,20.000000);
  glPopMatrix();
}

/* Rutina de dibujo de la escena -------------------------------------------*/
void Dibuja (void) {

  FILE *fichero;
  int ancho, alto;

  glClearColor (1,1,1,0);
  glClear (GL_COLOR_BUFFER_BIT  | GL_DEPTH_BUFFER_BIT);

  switch (modo){
  case perspectiva:
    proyeccionPerspectiva ();
    glMatrixMode (GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt (3, 3, 3, 0,0,0, 0,1,0);
    break;
  case alzado:
    proyeccionParalela ();
    glMatrixMode (GL_MODELVIEW);
    glLoadIdentity();
    break;
  case planta:
    proyeccionParalela ();
    glMatrixMode (GL_MODELVIEW);
    glLoadIdentity();
    glRotatef (90.0, 1.0, 0.0, 0.0);
    break;
   case perfil:
    proyeccionParalela ();
    glMatrixMode (GL_MODELVIEW);
    glLoadIdentity();
    glRotatef (-90.0, 0.0, 1.0, 0.0);
    break;
 }

  escena();
 
  glutSwapBuffers();
}

/* Atiende las opciones del menú desplegable -------------------------------*/
void atiendeMenu (int opcion) {

  switch (opcion) {
  case  1: modo= perspectiva; break;
  case  2: modo= alzado; break;
  case  3: modo= planta; break;
  case  4: modo= perfil; break;
  case  5: glColor3f(1.0,0.0,0.0); break;
  case  6: glColor3f(0.0,1.0,0.0); break;
  case  7: glColor3f(0.0,0.0,1.0); break;
  }
  glutPostRedisplay ();
}

/* Establece las opciones del menú desplegable -----------------------------*/
void menu (void) {

  int idMenuPrincipal, idMenuParalela, idMenuColor;

  idMenuPrincipal= glutCreateMenu (atiendeMenu);
  glutAttachMenu (GLUT_RIGHT_BUTTON);

  glutAddMenuEntry ("Vista Perspectiva", 1);

  idMenuParalela= glutCreateMenu (atiendeMenu);
  glutAddMenuEntry ("Alzado", 2);
  glutAddMenuEntry ("Planta", 3);
  glutAddMenuEntry ("Perfil", 4);
  glutSetMenu (idMenuPrincipal);
  glutAddSubMenu ("Vista Paralela", idMenuParalela);

  idMenuColor= glutCreateMenu (atiendeMenu);
  glutAddMenuEntry ("Rojo",  5);
  glutAddMenuEntry ("Verde", 6);
  glutAddMenuEntry ("Azul",  7);
  glutSetMenu (idMenuPrincipal);
  glutAddSubMenu ("Color", idMenuColor);
}

/* Opciones sobre la visualización de la escena ----------------------------*/
void opcionesVisualizacion (void) {

  glDepthFunc (GL_LEQUAL);
  glEnable    (GL_DEPTH_TEST);
  glColor3f   (1.0,0.0,0.0);
}

/* Establece las funciones que atienden los distintos eventos --------------*/
void  asociaEventos (void) {

  glutKeyboardFunc (eventoTeclado);
  glutReshapeFunc  (eventoVentana);
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

  /* establece opciones sobre la visualización de la escena */
  opcionesVisualizacion();

  /* establece el menú desplegable */
  menu ();

  /* bucle a la espera de eventos */
  glutMainLoop();
}
