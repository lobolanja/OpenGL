/* -------------------------------------------------------------------------*/
/* Niebla,  R. Mollá                                                        */
/* -------------------------------------------------------------------------*/


#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>

#define anchoVentana     512  /* ancho de la ventana */
#define altoVentana      512  /* alto de la ventana */
#define posicionVentanaX  50  /* pos. X de la esquina sup-izq de la ventana */
#define posicionVentanaY  50  /* pos. Y de la esquina sup-izq de la ventana */

#define INCREMENTO_DENSIDAD_NIEBLA 0.01
#define INCREMENTO_DISTANCIA_NIEBLA 1.0

enum DIMENSION {X, Y, Z, MAX_DIMENSION};
enum TIPO_LUZ {AMBIENTE, DIFUSA, ESPECULAR, MAX_TIPO_LUZ};
enum COMPONENTE_LUZ {R, G, B, A, MAX_COMPONENTE_LUZ};
enum OPCIONES_NIEBLA {DENSIDAD, PPIO, FIN, MAX_OPCIONES_NIEBLA};

/*Tamaño del cilindro*/
#define RadioBase 10.0
#define RadioSup   5.0
#define Altura    20.0
#define Cortes    25

#define ESFERA 2
#define TOROIDE 1

GLfloat  RGBAf[MAX_TIPO_LUZ][MAX_COMPONENTE_LUZ] = {	{ 0.2, 0.3, 0.4, 0.0},  /*Se determina la Niebla ambiente*/
									{ 1.0, 1.0, 1.0, 0.0},  /*Se determina la Niebla difusa*/
									{ 0.5, 0.5, 0.5, 0.0}},  /*Se determina la Niebla especular*/
		 Direccion[MAX_DIMENSION] = {0.0, 0.0, 0.0},
		 ColorFondo[MAX_COMPONENTE_LUZ] = {.95f, .95f, .95f, 0.0f},
		 Especular [MAX_COMPONENTE_LUZ] = { 1.0, 1.0, 1.0, 1.0 },	/*Color especular*/
		 Brillo [] = { 100.0 },	/*Brillo de la superficie de un objeto*/
		 Posicion[] = {20.0, 20.0, 20.0, 1.0}, /*Se determina la posicion de la luz 0*/
		 Niebla[MAX_OPCIONES_NIEBLA] = {0.5, 0.0, 10.0};	/*Densidad, ppio y fin de niebla*/

enum OPCIONES_NIEBLA OpcionesNiebla = DENSIDAD;

/* Función que establece la proyección -------------------------------------*/
void proyeccion (void) {

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(70.0, 1.33, 1.0, 1000.0);			
  gluLookAt(Posicion[X], Posicion[Y], Posicion[Z], /*Desde donde mira la cámara*/
	  		 Direccion[X], Direccion[Y], Direccion[Z],   /*Hacia donde mira la cámara*/
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
  glCallList(TOROIDE);

  /*Comienza el dibujo del nuevo cilindro*/
  glLoadIdentity ();

  glTranslatef(12.5, 0.0, 0.0);	/*Se traslada y rota el objeto */
  glColor3f (0.0, 1.0, 0.0); 
  /*Dibuja la esfera*/
  glTranslatef(12.5, 0.0, 0.0);	/*Se crea y traslada un nuevo cilindro copia del anterior*/
  glCallList(TOROIDE);

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

  case 'l':
  case 'L':	/*Incremento de niebla lineal*/
	  glFogi(GL_FOG_MODE, GL_LINEAR);
	  break;

  case 'e':
  case 'E':	/*Incremento de niebla exponencial*/
	  glFogi(GL_FOG_MODE, GL_EXP);
	  break;

  case '2':	/*Incremento de niebla exponencial al cuadrado*/
	  glFogi(GL_FOG_MODE, GL_EXP2);
	  break;

  case 'd':
  case 'D':	/*Selección de densidad de niebla*/
	  OpcionesNiebla = DENSIDAD;
	  break;

  case 'p':
  case 'P':	/*Selección de distancia mínima de arranque de niebla*/
	  OpcionesNiebla = PPIO;
	  break;

  case 'f':
  case 'F':	/*Selección de distancia máxima de arranque de niebla*/
	  OpcionesNiebla = FIN;
	  break;

  case 'n':
  case 'N':	/*Selección de densidad de niebla*/
	  glDisable(GL_FOG);
	  break;

  case 's':
  case 'S':	/*Selección de densidad de niebla*/
	  glEnable(GL_FOG);
	  break;

  case '+':	/*Incrementa la intensidad de la Niebla*/
	  switch (OpcionesNiebla) {
	  case DENSIDAD:
		  Niebla[DENSIDAD] += INCREMENTO_DENSIDAD_NIEBLA;
		  glFogf(GL_FOG_DENSITY, Niebla[DENSIDAD]);
		  break;
	  case PPIO:
		  Niebla[PPIO] += INCREMENTO_DISTANCIA_NIEBLA;
		  if (Niebla[PPIO] > Niebla[FIN])
			  Niebla[PPIO] = Niebla[FIN];

		  glFogf(GL_FOG_START, Niebla[PPIO]);
		  break;

	  case FIN:
		  Niebla[FIN] += INCREMENTO_DISTANCIA_NIEBLA;
		  glFogf(GL_FOG_END, Niebla[FIN]);
		  break;
	  }
	  break;

  case '-': /*Decrementa la intensidad de la Niebla*/
	  switch (OpcionesNiebla) {
	  case DENSIDAD:
		  if (Niebla[DENSIDAD] > INCREMENTO_DENSIDAD_NIEBLA) 
			  Niebla[DENSIDAD] -= INCREMENTO_DENSIDAD_NIEBLA;
		  else Niebla[DENSIDAD] = 0;

		  glFogf(GL_FOG_DENSITY, Niebla[DENSIDAD]);
		  break;
	  case PPIO:
		  if (Niebla[PPIO] > INCREMENTO_DISTANCIA_NIEBLA)
			  Niebla[PPIO] -= INCREMENTO_DISTANCIA_NIEBLA;
		  else Niebla[PPIO] = 0;
		  glFogf(GL_FOG_START, Niebla[PPIO]);
		  break;

	  case FIN:
		  if (Niebla[FIN] > INCREMENTO_DISTANCIA_NIEBLA)
			  Niebla[FIN] -= INCREMENTO_DISTANCIA_NIEBLA;
		  else Niebla[FIN] = 0;
		  
		  if (Niebla[FIN] < Niebla[PPIO] )
			  Niebla[FIN] = Niebla[PPIO];
		  glFogf(GL_FOG_END, Niebla[FIN]);
		  break;
	  }
	  break;
  }
  Dibuja();
}

/* Opciones sobre la visualización de la escena ----------------------------*/
void opcionesVisualizacion (void) {

  /*Color de fondo por defecto*/
  glClearColor (ColorFondo[R], ColorFondo[G], ColorFondo[B], ColorFondo[A]);
  glFogfv (GL_FOG_COLOR, ColorFondo);	/*Se iguala el color de niebla con el color de fondo para que los objetos no destaquen de forma extraña*/
  glHint(GL_FOG_HINT, GL_NICEST);	/*Para ir más rápido*/
	
  /*Modelo de sombreado */
  glShadeModel(GL_SMOOTH);
  
  /*Modo de releno de los polígonos */
  glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
  
  /*Se habilita el testeo de profundidad para eliminar caras ocultas */
  glEnable(GL_DEPTH_TEST);
  
  /*Modo de releno de los polígonos */
  glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
  
  /*Se habilita el testeo de profundidad para eliminar caras ocultas y la niebla*/
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_FOG);
  
  /* Se definen las propiedades del material como el color especular, brillo,...*/
  glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, Especular);
  glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, Brillo);
  
  glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
  glEnable(GL_COLOR_MATERIAL);
		
  /*Se habilita el proceso de iluminación*/
  glEnable (GL_LIGHTING);	/*Se activa el proceso de iluminación*/
  glEnable (GL_LIGHT0);		/*Se activa la Niebla nº 0*/
  glLightf (GL_LIGHT0, GL_SPOT_EXPONENT, 1.0); /*La Niebla se concentra un poco en el centro*/
  glLighti (GL_LIGHT0, GL_SPOT_CUTOFF, 180); /*El ángulo de apertura es de 180º*/
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

  glNewList(TOROIDE, GL_COMPILE);
  glutSolidTorus(2.5, 5, Cortes, Cortes);
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

  /* crea la ventana de la aplicación */
  abreVentana (numParametros, listaParametros);

  /* asocia funciones a eventos de ventana, teclado o ratón */
  asociaEventos ();              

  /* establece la función de dibujo de la escena */
  glutDisplayFunc        (Dibuja);

  /* establece opciones sobre la visualización de la escena */
  opcionesVisualizacion();

  /* bucle a la espera de eventos */
  glutMainLoop();
}

