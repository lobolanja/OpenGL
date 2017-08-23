/* -------------------------------------------------------------------------*/
/* Primitivas geométricas, C. Rebollo                                       */
/* -------------------------------------------------------------------------*/


#include <GL/glut.h>
#include <stdio.h>

#define anchoVentana     512  /* ancho de la ventana */
#define altoVentana      512  /* alto de la ventana */
#define posicionVentanaX  50  /* pos. X de la esquina sup-izq de la ventana */
#define posicionVentanaY  50  /* pos. Y de la esquina sup-izq de la ventana */

char c = 'a';

/* Función que establece la proyección -------------------------------------*/
void proyeccion (void) {

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluOrtho2D (-0.2, 1.2, -0.2, 1.2);
}

/* Rutina asociada a eventos de ventana ------------------------------------*/
void eventoVentana (GLsizei ancho, GLsizei alto) {
  
  glViewport (0, 0, ancho, alto);
  proyeccion();
}

/* Rutina de dibujo de la escena -------------------------------------------*/
void Dibuja () {

  glClearColor (.95f, .95f, .95f, 0.0f);
  glClear(GL_COLOR_BUFFER_BIT );

  glMatrixMode (GL_MODELVIEW);
  glLoadIdentity ();
  glColor3f ( 0.8, 0.0, 0.5); 

  switch  (c)
  { 
	
	//FIGURAS ALAMBRICAS
	case 'a':
 		glTranslatef(0.5,0.5,0.0);
		glutWireSphere ( 0.3, 20, 20);
		break;
	case 's':
		glTranslatef(0.5,0.5,0.0);
		glutWireCube ( 0.5);
		break;

	case 'd':
		glTranslatef(0.5,0.5,0.0);
		glutWireTorus (0.1, 0.2, 20, 20);
		break;

	case 'f':
		glTranslatef(0.5,0.5,0.0);
		glScalef (0.4,0.4,0.4);
		glRotatef (-46.0, 1,0,0);
		glutWireIcosahedron ( );
		break;

	case 'g':
		glTranslatef(0.5,0.5,0.0);
		glScalef (0.4,0.4,0.4);
		glRotatef (-10.0, 1,0,0);
		glutWireOctahedron ( );
		break;
	case 'h':
		glTranslatef(0.5,0.5,0.0);
		glScalef (0.5,0.5,0.5);
		glRotatef (-20.0, 0,1,0);
		glutWireTetrahedron ();
		break;
	case 'j':
		glTranslatef(0.5,0.5,0.0);
		glScalef (0.2,0.2,0.2);
		glRotatef (-30.0, 1,0,0);
		glutWireDodecahedron ();
		break;
	case 'k':
		glTranslatef(0.5,0.2,0.0);
		glRotatef (-70.0, 1,0,0);
		glutWireCone ( 0.3, 0.8, 20, 20);
		break;
	case 'l':
		glTranslatef(0.5,0.5,0.0);
		glutWireTeapot (0.35);
		break;

	//FIGURAS SOLIDAS
	case 'A': 
 		glTranslatef(0.5,0.5,0.0);
		glutSolidSphere ( 0.3, 20, 20);
		break;
	case 'S':
		glTranslatef(0.5,0.5,0.0);
		glutSolidCube ( 0.5);
		break;

	case 'D':
		glTranslatef(0.5,0.5,0.0);
		glutSolidTorus (0.1, 0.2, 20, 20);
		break;

	case 'F':
		glTranslatef(0.5,0.5,0.0);
		glScalef (0.4,0.4,0.4);
		glRotatef (-46.0, 1,0,0);
		glutSolidIcosahedron ( );
		break;

	case 'G':
		glTranslatef(0.5,0.5,0.0);
		glScalef (0.4,0.4,0.4);
		glRotatef (-10.0, 1,0,0);
		glutSolidOctahedron ( );
		break;
	case 'H':
		glTranslatef(0.5,0.5,0.0);
		glScalef (0.5,0.5,0.5);
		glRotatef (-20.0, 0,1,0);
		glutSolidTetrahedron ();
		break;
	case 'J':
		glTranslatef(0.5,0.5,0.0);
		glScalef (0.2,0.2,0.2);
		glRotatef (-30.0, 1,0,0);
		glutSolidDodecahedron ();
		break;
	case 'K':
		glTranslatef(0.5,0.2,0.0);
		glRotatef (-70.0, 1,0,0);
		glutSolidCone ( 0.3, 0.8, 20, 20);
		break;
	case 'L':
		glTranslatef(0.5,0.5,0.0);
		glutSolidTeapot (0.35);
		break;

	default:
	  break;
  }
  glutSwapBuffers();
}

/* Rutina asociada a eventos de teclado ------------------------------------*/
void eventoTeclado (unsigned char tecla, int x, int y) {

  switch (tecla) {
  case  27: exit (0); break;
  case 'a':  c='a'; Dibuja(); break;
  case 's':  c='s'; Dibuja(); break;
  case 'd':  c='d'; Dibuja(); break;
  case 'f':  c='f'; Dibuja(); break;
  case 'g':  c='g'; Dibuja(); break;
  case 'h':  c='h'; Dibuja(); break;
  case 'j':  c='j'; Dibuja(); break;
  case 'k':  c='k'; Dibuja(); break;
  case 'l':  c='l'; Dibuja(); break;

  case 'A':  c='A'; Dibuja(); break;
  case 'S':  c='S'; Dibuja(); break;
  case 'D':  c='D'; Dibuja(); break;
  case 'F':  c='F'; Dibuja(); break;
  case 'G':  c='G'; Dibuja(); break;
  case 'H':  c='H'; Dibuja(); break;
  case 'J':  c='J'; Dibuja(); break;
  case 'K':  c='K'; Dibuja(); break;
  case 'L':  c='L'; Dibuja(); break;
  }
}

/* Opciones sobre la visualización de la escena ----------------------------*/
void opcionesVisualizacion (void) {

  printf( " a - Esfera alambrica      A - Esfera solida \n");
  printf( " s - Cubo alambrico        S - Cubo solido \n");
  printf( " d - Toroide alambrico     D - Toroide solido \n");
  printf( " f - Icosaedro alambrico   F - Icosaedro solido \n");
  printf( " g - Octaedro alambrico    G - Octaedro solido \n");
  printf( " h - Tetraaedro alambrico  H - Tetraedro solido \n");
  printf( " j - Dodecaedro alambrico  J - Dodecaedro solido \n");
  printf( " k - Cono alambrico        K - Cono solido \n");
  printf( " l - Tetera alambrica      L - Tetera solida \n");
}

/* Establece las funciones que atienden los distintos eventos --------------*/
void  asociaEventos (void) {

  glutReshapeFunc  (eventoVentana);
  glutKeyboardFunc (eventoTeclado);
}

/* Abre la ventana de la aplicación ----------------------------------------*/
void abreVentana (int numParametros, char **listaParametros) {

  glutInit               (&numParametros, listaParametros);
  glutInitDisplayMode    (GLUT_DOUBLE | GLUT_RGB );
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

