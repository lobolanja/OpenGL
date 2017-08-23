/* -------------------------------------------------------------------------*/
/* Que trabaje!!: glutIdleFunc, glutTimer, O. Belmonte                      */
/* -------------------------------------------------------------------------*/


#include <GL/glut.h>
#include <stdio.h>

#define anchoVentana     512  /* ancho de la ventana */
#define altoVentana      512  /* alto de la ventana */
#define posicionVentanaX  50  /* pos. X de la esquina sup-izq de la ventana */
#define posicionVentanaY  50  /* pos. Y de la esquina sup-izq de la ventana */
#define BAJANDO            1  /* indica que el movimiento es ascendente */
#define SUBIENDO           2  /* indica que el movimiento es descendente */
#define g              9.81f  /* valor de la gravedad */

float h = 1.0, h0 = 1.0f, t = 0.0f;

/* Función que dibuja un cuadrado con el origen de coordenadas en su centro */
void cuadrado (void){
  float vertices[4][2] = {{-0.05f, -0.05f}, {0.05f, -0.05f}, {0.05f, 0.05f}, {-0.05f, 0.05f}};

  glBegin (GL_POLYGON);
    glVertex2fv (vertices[0]);
    glVertex2fv (vertices[1]);
    glVertex2fv (vertices[2]);
    glVertex2fv (vertices[3]);
  glEnd ();
}

/* Función que establece la proyección -------------------------------------*/
void proyeccion (void) {

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(-1.0, 1.1, -0.1, 1.1, -2.0, 2.0);
}

/* Rutina asociada a eventos de ventana ------------------------------------*/
void eventoVentana (GLsizei ancho, GLsizei alto) {
  
  glViewport (0, 0, ancho, alto);
  proyeccion();
}

/* implementa las ecuaciones del movimiento en caida libre y un rebote */
/* la misma función responde a dos contadores de tiempo distinto, SUBIENDO y BAJANDO */
void timer (int id) {
	if (id == BAJANDO) { /* discrimina lo que tiene que hacer segun el valor del identificador */
    h = h0 - (g*t*t/2.0f); /* ecuacion del movimiento */
    if (h <= 0.0f) { /* de BAJANDO se tiene que pasar a SUBIENDO */
	  t = 0.0f;
	  glutTimerFunc (60, timer, SUBIENDO);
	}
    else { /* se sigue BAJANDO */
	  t = t + 0.05f;
	  glutTimerFunc (60, timer, BAJANDO);
	}
  }
  else {
    h = -(g*t*t/2.0f) + (4.43*t); /* ecuacion del movimiento */
    if (h > h0) {
      t = 0.0f;
      glutTimerFunc (60, timer, BAJANDO); /* de SUBIENDO se tiene que pasar a BAJANDO */
	}
    else { /* se sigue SUBIENDO */
	  t = t + 0.05f;
	  glutTimerFunc (60, timer, SUBIENDO);
	}
  }
  glutPostRedisplay ();
}

/* Rutina asociada a eventos de teclado ------------------------------------*/
void eventoTeclado (unsigned char tecla, int x, int y) {

  switch (tecla) {
  case  27:
  case 'q':
  case 'Q': exit (0); break;
  }
}

/* Rutina de dibujo de la escena -------------------------------------------*/
void Dibuja (void) {
  glClear (GL_COLOR_BUFFER_BIT); /* Borramos el buffer de color */
 
  /* Transformacion de la camara */
  glMatrixMode(GL_MODELVIEW); /* Seleccionamos la matriz modelo vista */
  glLoadIdentity(); /* Cargamos la matriz unidad sobre la modelo vista */

  glPushMatrix ();
  glTranslatef (0.0f, h, 0.0f);
  cuadrado ();
  glPopMatrix ();

  glutSwapBuffers ();
}

/* Opciones sobre la visualización de la escena ----------------------------*/
void opcionesVisualizacion (void) {

  glClearColor (0.0f, 0.0f, 0.0f, 0.0f);
  glColor3f (1.0f, 1.0f, 1.0f);
}

/* Establece las funciones que atienden los distintos eventos --------------*/
void  asociaEventos (void) {

  glutReshapeFunc  (eventoVentana);
  glutKeyboardFunc (eventoTeclado);
  glutTimerFunc (50, timer, BAJANDO);
}

/* Abre la ventana de la aplicación ----------------------------------------*/
void abreVentana (int numParametros, char **listaParametros) {

  glutInit               (&numParametros, listaParametros);
  glutInitDisplayMode    (GLUT_DOUBLE | GLUT_RGB);
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
