/* -------------------------------------------------------------------------*/
/* Textura 2D sobre polígono, Repetición de textura, Filtrado de textura    */
/* R. Quirós                                                                */
/* -------------------------------------------------------------------------*/


#include <GL/glut.h>
#include <stdio.h>

#define anchoVentana     512  /* ancho de la ventana */
#define altoVentana      512  /* alto de la ventana */
#define posicionVentanaX  50  /* pos. X de la esquina sup-izq de la ventana */
#define posicionVentanaY  50  /* pos. Y de la esquina sup-izq de la ventana */
#define anchoTextura     256  /* ancho de la textura */
#define altoTextura      256  /* alto de la textura */
#define MODO1x1            1  /* tesela de 1x1 */
#define MODO3x3            3  /* tesela de 3x3 */

double aspecto;   /* relación ancho/alto de la ventana */
GLubyte pixels[anchoTextura][altoTextura][3];  /* Pixels de la textura */
int modo;   /* flag que define el modo de texturacion */

/* Función que establece la proyección -------------------------------------*/
void proyeccion (void) {

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(30.0, aspecto, 1.0f, 10.0f);
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
  case '1':  /* Fija el modo de texturación a tesela de 1x1 */ 
	modo = MODO1x1;
	break;
  case '3':  /* Fija el modo de texturación a tesela de 3x3 */ 
	modo = MODO3x3;
	break;
  case 's':  /* Fija el modo de repeticion de textura en S a GL_CLAMP */ 
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	break;
  case 'S':  /* Fija el modo de repeticion de textura en S a GL_REPEAT */ 
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	break;
  case 't':  /* Fija el modo de repeticion de textura en T a GL_CLAMP */ 
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	break;
  case 'T':  /* Fija el modo de repeticion de textura en T a GL_REPEAT */ 
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	break;
  case 'l':  /* Fija el filtro de textura a GL_LINEAR */ 
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	break;
  case 'n':  /* Fija el filtro de textura a GL_NEAREST */ 
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	break;
  }
  glutPostRedisplay();
}

/* Rutina de dibujo de la escena -------------------------------------------*/
void Dibuja (void) {

  glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  glMatrixMode (GL_MODELVIEW);
  glLoadIdentity();
  glTranslatef (0.0,-0.5,-5.0);

  if (modo == MODO1x1)   /* Modo tesela 1x1 */
     {
     glBegin(GL_POLYGON);
     	glTexCoord2f(0.0, 0.0);
     	glVertex3f(-1.0, 0.0, 0.0);
        glTexCoord2f(0.0, 1.0);
        glVertex3f(-1.0, 1.0, -1.0);
        glTexCoord2f(1.0, 1.0);
        glVertex3f(1.0, 1.0, -1.0);
        glTexCoord2f(1.0, 0.0);
        glVertex3f(1.0, 0.0, 0.0);
     glEnd();
     }
  else   /* Modo tesela 3x3 */
     {
     glBegin(GL_POLYGON);
        glTexCoord2f(0.0, 0.0);
        glVertex3f(-1.0, 0.0, 0.0);
        glTexCoord2f(0.0, 3.0);
        glVertex3f(-1.0, 1.0, -1.0);
        glTexCoord2f(3.0, 3.0);
        glVertex3f(1.0, 1.0, -1.0);
        glTexCoord2f(3.0, 0.0);
        glVertex3f(1.0, 0.0, 0.0);
     glEnd();
     }
  
  glutSwapBuffers ();
}

/* Definición de la textura ------------------------------------------------*/

/* Lee una imagen de textura en formato tga y la almacena en la variable    */
/* global "pixels"                                                          */

void leerTextura (char *fichero)
{
int   i, j;
char  r, g, b, c;
FILE  *tga;

  /* Apertura del fichero TGA */
  if ((tga = fopen(fichero, "rb")) == NULL)
  	printf ("Error abriendo el fichero: %s\n", fichero);
  else
  	{
	/* Lee los 18 primeros caracteres de la cabecera */
	for (j=1; j<=18; j++)
		fscanf (tga, "%c", &c);

	/* Lee la imagen */
	for (j=altoTextura-1; j>=0; j--)
		{
		for (i=0; i<anchoTextura; i++)
			{
			fscanf(tga, "%c%c%c", &b, &g, &r); 
			pixels[j][i][0] = (GLubyte)r;
			pixels[j][i][1] = (GLubyte)g;
			pixels[j][i][2] = (GLubyte)b;
			}
		}
		fclose(tga);   /* Cierre del fichero TGA */
	}
}

/* Definición de los materiales --------------------------------------------*/
void material (void) {

  /* Asignación de la imagen "pixels" como textura 2D */
  leerTextura("uji.tga");

  /* Definición de los parámetros iniciales de texturacion */  
  glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
  glTexImage2D(GL_TEXTURE_2D, 0, 3, anchoTextura, altoTextura, 
	       0, GL_RGB, GL_UNSIGNED_BYTE, pixels);
  glTexEnvf (GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
  
  /* Fijar el modo de repeticion de textura inicial a GL_CLAMP */
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);

  /* Fijar el filtro de textura inicial a GL_NEAREST */
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  glEnable(GL_TEXTURE_2D);
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

  /* Define el modo de texturación por defecto */
  modo = MODO1x1;

  /* crea la ventana de la aplicación*/
  abreVentana (numParametros, listaParametros);

  /* asocia funciones a eventos de ventana, teclado o ratón*/
  asociaEventos ();              

  /* establece la funcion de dibujo de la escena */
  glutDisplayFunc (Dibuja);

  /* define los materiales */
  material ();

  /* bucle a la espera de eventos */
  glutMainLoop();
}
