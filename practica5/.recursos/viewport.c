/* -------------------------------------------------------------------------*/
/* glViewport.c                                                             */
/* Julio 2002                                                               */
/* R Moll�			                                                        */
/* -------------------------------------------------------------------------*/


#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>

#define anchoVentana     512  /* ancho de la ventana */
#define altoVentana      512  /* alto de la ventana */
#define posicionVentanaX  50  /* pos. X de la esquina sup-izq de la ventana */
#define posicionVentanaY  50  /* pos. Y de la esquina sup-izq de la ventana */

/*Especificaci�n del ViewPort*/
#define TOTAL_PARAMS_VIEWPORT 4
enum ATRIB_VIEWPORT {VP_X, VP_Y, VP_ANCHURA, VP_ALTURA};

enum DIMENSION {ANCHURA, ALTURA};
enum DIMENSION Dimension = ANCHURA;

GLint ViewPort[TOTAL_PARAMS_VIEWPORT];

/* Funci�n que establece la proyecci�n -------------------------------------*/
void proyeccion (void) {

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluOrtho2D (-0.2, 1.2, -0.2, 1.2);
}

/* Rutina asociada a eventos de ventana ------------------------------------*/
void eventoVentana (GLsizei Ancho, GLsizei Alto) {
  
  ViewPort[VP_ANCHURA] = Ancho;	/*Esta asignaci�n redundante es porque cuando se reajusta 
								  la ventana el nuevo tama�o debe almacenarse para el cambio 
								  de viewport*/
  ViewPort[VP_ALTURA] = Alto;

  glViewport (ViewPort[VP_X], ViewPort[VP_Y], ViewPort[VP_ANCHURA], ViewPort[VP_ALTURA]);
  proyeccion();
}

/* Rutina de dibujo de la escena -------------------------------------------*/
void Dibuja (void) {

  glClearColor (.95f, .95f, .95f, 0.0f);
  glClear (GL_COLOR_BUFFER_BIT);

  glMatrixMode (GL_MODELVIEW);
  glLoadIdentity ();

  glBegin(GL_LINE_STRIP);		/* Cuerpo de la casa*/
    glColor3f (0.0, 0.0, 1.0);  /* color azul */
    glVertex2f (0.1, 0.0);      /* l�nea base casa*/  
    glVertex2f (0.9, 0.0);      
    glVertex2f (0.9, 0.5);		/* l�nea lado derecho*/  
	glVertex2f (0.1, 0.5);		/* l�nea borde superior*/
	glVertex2f (0.1, 0.0);		/* l�nea lado izquierdo*/
  glEnd();

  glBegin(GL_LINE_STRIP);		/* Chimenea*/
    glColor3f (0.0, 0.0, 0.0);  /* color negro */
    glVertex2f (0.25, 0.7);      /* l�nea izquierda*/
    glVertex2f (0.25, 0.9);
    glVertex2f (0.35, 0.9);      /* l�nea superior*/
    glVertex2f (0.35, 0.8);      /* l�nea derecha*/
  glEnd();

  glBegin(GL_LINE_STRIP);		/* Techo de la casa*/
    glColor3f (1.0, 0.5, 0.5);  /* color amarronado */
    glVertex2f (0.0, 0.4);      /* l�nea techo izquierdo*/
    glVertex2f (0.5, 1.0);
    glVertex2f (1.0, 0.4);      /* l�nea techo derecho*/
  glEnd();

  glutSwapBuffers();
}

/* Rutina asociada a eventos de teclado ------------------------------------*/
void eventoTeclado (unsigned char tecla, int x, int y) {

  switch (tecla) {
  case 27: 
	  exit (0); break;

  case 'w':
  case 'W':
	  Dimension = ANCHURA;
	  break;	//Width

  case 'h':
  case 'H':
	  Dimension = ALTURA;
	  break;	//Heigth

  case '+':
	  if (Dimension == ANCHURA)
	     glViewport (ViewPort[VP_X], ViewPort[VP_Y], ++ViewPort[VP_ANCHURA], ViewPort[VP_ALTURA]);
	  else glViewport (ViewPort[VP_X], ViewPort[VP_Y], ViewPort[VP_ANCHURA], ++ViewPort[VP_ALTURA]);
	  Dibuja();
	  break;

  case '-':
	  if (Dimension == ANCHURA)
		   glViewport (ViewPort[VP_X], ViewPort[VP_Y], --ViewPort[VP_ANCHURA], ViewPort[VP_ALTURA]);
	  else glViewport (ViewPort[VP_X], ViewPort[VP_Y], ViewPort[VP_ANCHURA], --ViewPort[VP_ALTURA]);
	  Dibuja();
	  break;

  case '8': 
	  glViewport (ViewPort[VP_X], ++ViewPort[VP_Y], ViewPort[VP_ANCHURA], ViewPort[VP_ALTURA]);
	  Dibuja();
	  break;
  case '2': 
	  glViewport (ViewPort[VP_X], --ViewPort[VP_Y], ViewPort[VP_ANCHURA], ViewPort[VP_ALTURA]);
	  Dibuja();
	  break;
  case '6': 
	  glViewport (++ViewPort[VP_X], ViewPort[VP_Y], ViewPort[VP_ANCHURA], ViewPort[VP_ALTURA]);
	  Dibuja();
	  break;
  case '4': 
	  glViewport (--ViewPort[VP_X], ViewPort[VP_Y], ViewPort[VP_ANCHURA], ViewPort[VP_ALTURA]);
	  Dibuja();
	  break;
  }
}

/* Opciones sobre la visualizaci�n de la escena ----------------------------*/
void opcionesVisualizacion (void) {

  glLineWidth(10.0f);

  /*Gesti�n de ViewPort*/
  glGetIntegerv( GL_VIEWPORT, ViewPort);

}

/* Establece las funciones que atienden los distintos eventos --------------*/
void  asociaEventos (void) {

  glutReshapeFunc  (eventoVentana);
  glutKeyboardFunc (eventoTeclado);
}

/* Abre la ventana de la aplicaci�n ----------------------------------------*/
void abreVentana (int numParametros, char **listaParametros) {

  glutInit               (&numParametros, listaParametros);
  glutInitDisplayMode    (GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
  glutInitWindowSize     (anchoVentana, altoVentana);
  glutInitWindowPosition (posicionVentanaX, posicionVentanaY);
  glutCreateWindow       (listaParametros[0]);
  glutDisplayFunc        (Dibuja);
}

/* Programa principal ------------------------------------------------------*/
void main (int numParametros, char **listaParametros) {

  /* crea la ventana de la aplicaci�n*/
  abreVentana (numParametros, listaParametros);

  /* asocia funciones a eventos de ventana, teclado o rat�n*/
  asociaEventos ();              

  /* establece opciones sobre la visualizaci�n de la escena */
  opcionesVisualizacion();

  /* bucle a la espera de eventos */
  glutMainLoop();
}

