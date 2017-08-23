/* -------------------------------------------------------------------------*/
/* Focos de luz, R. Mollá                                                   */
/* -------------------------------------------------------------------------*/


#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>

#define anchoVentana     512  /* ancho de la ventana */
#define altoVentana      512  /* alto de la ventana */
#define posicionVentanaX  50  /* pos. X de la esquina sup-izq de la ventana */
#define posicionVentanaY  50  /* pos. Y de la esquina sup-izq de la ventana */

#define INCREMENTO_LUZ 0.01

enum DIMENSION {X, Y, Z, MAX_DIMENSION};
enum TIPO_LUZ {AMBIENTE, DIFUSA, ESPECULAR, MAX_TIPO_LUZ};
enum COMPONENTE_LUZ {R, G, B, A, MAX_COMPONENTE_LUZ};

/*Tamaño del cilindro*/
#define RadioBase 10.0
#define RadioSup   5.0
#define Altura    20.0
#define Cortes    25

#define ESFERA 2
#define CILINDRO 1

GLfloat  RGBAf[MAX_TIPO_LUZ][MAX_COMPONENTE_LUZ] = {	{ 0.2, 0.3, 0.4, 0.0},  /*Se determina la luz ambiente*/
														{ 1.0, 1.0, 1.0, 0.0},  /*Se determina la luz difusa*/
														{ 0.5, 0.5, 0.5, 0.0}},  /*Se determina la luz especular*/
		 Posicion[] = {-20.0, 20.0, 20.0, 1.0}, /*Se determina la posicion de la luz 0*/
		 Direccion[MAX_DIMENSION] = {0.0, 0.0, 0.0},
		 Especular [MAX_COMPONENTE_LUZ] = { 1.0, 1.0, 1.0, 1.0 },	/*Color especular*/
		 Brillo [] = { 100.0 };	/*Brillo de la superficie de un objeto*/

enum TIPO_LUZ Luz;

/* Función que establece la proyección -------------------------------------*/
void proyeccion (void) {

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(70.0, 1.33, 1.0, 1000.0);			
  gluLookAt(20.0, 20.0, 30.0, /*Desde donde mira la cámara*/
	  		 0.0, 0.0, 0.0,   /*Hacia donde mira la cámara*/
			 0.0, 0.0, 1.0);  /*Verticalidad  de la cámara*/

  glMatrixMode(GL_MODELVIEW);
}

/* Rutina asociada a eventos de ventana ------------------------------------*/
void eventoVentana (GLsizei Ancho, GLsizei Alto) {
  
  glViewport (0, 0, Ancho, Alto);
  proyeccion();
}

/* Rutina de dibujo de la escena -------------------------------------------*/
void Dibuja (void) {

  glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
  glLoadIdentity ();

  /*Comienza el dibujo del cilindro*/
  glTranslatef(-12.5, 0.0, 0.0);	/*Se traslada y rota el objeto */
  glRotatef(45, 1.0, 0.0, 0.0);
  glRotatef(45, 0.0, 1.0, 0.0);
  glRotatef(45, 0.0, 0.0, 1.0);
  
  glColor3f (0.0, 0.0, 1.0);
   /*Dibuja el cilindro*/
  glCallList(CILINDRO);

  /*Comienza el dibujo del nuevo cilindro*/
  glLoadIdentity ();

  glTranslatef(12.5, 0.0, 0.0);	/*Se traslada y rota el objeto */
  glColor3f (0.0, 1.0, 0.0); 
  /*Dibuja la esfera*/
  glTranslatef(12.5, 0.0, 0.0);	/*Se crea y traslada un nuevo cilindro copia del anterior*/
  glCallList(CILINDRO);

  glColor3f (1.0, 0.0, 0.0); 
  /*Dibuja la esfera*/
  glTranslatef(-12.5, 0.0, 0.0);	/*Se traslada la esfera otras 12.5 uds.*/
  glCallList(ESFERA);

  /*Fuerza a vaciar el buffer de dibujo*/
  glFlush();

  glutSwapBuffers();
}

/* Rutina asociada a eventos de teclado ------------------------------------*/
void eventoTeclado (unsigned char tecla, int x, int y) {

  switch (tecla) {
  case 27: 
	  exit (0); break;

  case 'a':
  case 'A':	/*Selecciona la luz ambiente*/
	  Luz = AMBIENTE;
	  break;

  case 'e':
  case 'E':	/*Selecciona la luz especular*/
	  Luz = ESPECULAR;
	  break;

  case 'd':
  case 'D':	/*Selecciona la luz difusa*/
	  Luz = DIFUSA;
	  break;

  case '+':	/*Incrementa la intensidad de la luz*/
	  switch (Luz) {
	  case AMBIENTE:
		  if (RGBAf[AMBIENTE][R] < 1.0)
		  {
			  /*Se determina la componente ambiente*/
			  RGBAf[AMBIENTE][R]+=INCREMENTO_LUZ;
			  RGBAf[AMBIENTE][G] = RGBAf[AMBIENTE][B] = RGBAf[AMBIENTE][R];
			  glLightfv(GL_LIGHT0, GL_AMBIENT, RGBAf[AMBIENTE]);
		  }
		  break;
	  case ESPECULAR:
		  if (RGBAf[ESPECULAR][R] < 1.0)
		  {
			  /*Se determina la componente especular*/
			  RGBAf[ESPECULAR][R]+=INCREMENTO_LUZ;
			  RGBAf[ESPECULAR][G] = RGBAf[ESPECULAR][B] = RGBAf[ESPECULAR][R];
			  glLightfv(GL_LIGHT0, GL_SPECULAR, RGBAf[ESPECULAR]);
		  }
		  break;
	  case DIFUSA:  
		  if (RGBAf[DIFUSA][R] < 1.0)
		  {
			  /*Se determina la componente difusa*/
			  RGBAf[DIFUSA][R]+=INCREMENTO_LUZ;
			  RGBAf[DIFUSA][G] = RGBAf[DIFUSA][B] = RGBAf[DIFUSA][R];
			  glLightfv(GL_LIGHT0, GL_DIFFUSE, RGBAf[DIFUSA]);
		  }
	  }
	  break;

  case '-': /*Decrementa la intensidad de la luz*/
	  switch (Luz) {
	  case AMBIENTE:
		  if (RGBAf[AMBIENTE][R] > 0.0)
		  {
			  /*Se determina la componente ambiente*/
			  RGBAf[AMBIENTE][R]-=INCREMENTO_LUZ;
			  RGBAf[AMBIENTE][G] = RGBAf[AMBIENTE][B] = RGBAf[AMBIENTE][R];
			  glLightfv(GL_LIGHT0, GL_AMBIENT, RGBAf[AMBIENTE]);
		  }
		  break;
	  case ESPECULAR:
		  if (RGBAf[ESPECULAR][R] > 0.0)
		  {
			  /*Se determina la componente especular*/
			  RGBAf[ESPECULAR][R]-=INCREMENTO_LUZ;
			  RGBAf[ESPECULAR][G] = RGBAf[ESPECULAR][B] = RGBAf[ESPECULAR][R];
			  glLightfv(GL_LIGHT0, GL_SPECULAR, RGBAf[ESPECULAR]);
		  }
		  break;
	  case DIFUSA:  
		  if (RGBAf[DIFUSA][R] > 0.0)
		  {
			  /*Se determina la componente difusa*/
			  RGBAf[DIFUSA][R]-=INCREMENTO_LUZ;
			  RGBAf[DIFUSA][G] = RGBAf[DIFUSA][B] = RGBAf[DIFUSA][R];
			  glLightfv(GL_LIGHT0, GL_DIFFUSE, RGBAf[DIFUSA]);
		  }
	  }
	  break;
  }
  Dibuja();
}

/* Opciones sobre la visualización de la escena ----------------------------*/
void opcionesVisualizacion (void) {

  /*Color de fondo por defecto*/
  glClearColor (.95f, .95f, .95f, 0.0f);

  /*Modelo de sombreado */
  glShadeModel(GL_SMOOTH);
  
  /*Modo de releno de los polígonos */
  glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
  
  /*Se habilita el testeo de profundidad para eliminar caras ocultas */
  glEnable(GL_DEPTH_TEST);
  
  /* Se definen las propiedades del material como el color especular, brillo,...*/
  glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, Especular);
  glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, Brillo);
  
  glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
  glEnable(GL_COLOR_MATERIAL);
		
  /*Se habilita el proceso de iluminación*/
  glEnable (GL_LIGHTING);	/*Se activa el proceso de iluminación*/
  glEnable (GL_LIGHT0);		/*Se activa la luz nº 0*/
  glLightf (GL_LIGHT0, GL_SPOT_EXPONENT, 1.0); /*La luz se concentra un poco en el centro*/
  glLighti (GL_LIGHT0, GL_SPOT_CUTOFF, 450); /*El ángulo de apertura es de 180º*/
  glLightfv(GL_LIGHT0, GL_POSITION, Posicion);
  glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, Direccion);
  glLightfv(GL_LIGHT0, GL_AMBIENT, RGBAf[AMBIENTE]);
  glLightfv(GL_LIGHT0, GL_DIFFUSE, RGBAf[DIFUSA]);
  glLightfv(GL_LIGHT0, GL_SPECULAR, RGBAf[ESPECULAR]);
}

/* Establece las funciones que atienden los distintos eventos --------------*/
void  asociaEventos (void) {

  glutReshapeFunc  (eventoVentana);
  glutKeyboardFunc (eventoTeclado);
}

/*Crea los objetos con los que trabaja el ejemplo*/
void creaObjetos () {

  GLUquadricObj *Objeto;

  Objeto = gluNewQuadric();

  glNewList(CILINDRO, GL_COMPILE);
  gluCylinder(Objeto, RadioBase, RadioSup, Altura, Cortes, Cortes);
  glEndList();

  /*Se genera la esfera*/
  glNewList(ESFERA, GL_COMPILE);
  gluSphere(Objeto, RadioBase, Cortes*2, Cortes);
  glEndList();
}

/* Abre la ventana de la aplicación ----------------------------------------*/
void abreVentana (int numParametros, char **listaParametros) {

  glutInit               (&numParametros, listaParametros);
  glutInitDisplayMode    (GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
  glutInitWindowSize     (anchoVentana, altoVentana);
  glutInitWindowPosition (posicionVentanaX, posicionVentanaY);
  glutCreateWindow       (listaParametros[0]);

  /*Se generan lOs objetos con los que se trabajará posteriormente*/
  creaObjetos();
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

