//**************************************************************************
// Proyecto IG 
//
// Juan Carlos Chaves Puertas
//
// GPL
//**************************************************************************
#include <iostream>
#include "stdlib.h"
#include "stdio.h" 
#include <GL/glut.h>
#include <ctype.h>
#include <vector>
#include <vertex.h>
#include "file_ply_stl.h"
#include <math.h>
#include <unistd.h>
#include <unistd.h>
#include "ovni.cc"
#include "luces.cc"
#include "camaras.cc"

// Colores ansi para la consola
#define BLACK    "\033[0m"
#define RED      "\033[31m"
#define GREEN    "\033[32m"
#define YELLOW   "\033[33m"
#define BLUE     "\033[34m"
#define MAGENTA  "\033[35m"
#define CYAN     "\033[36m"
#define WHITE    "\033[37m"

#define hormiga 0
#define busto 1
#define coche 2
using namespace std;
/*variables para las camaras*/
camaras camara;
bool planta, moverRaton,moverTeclado,perfil;
int modo;
int posCamaraX=0;
int posCamaraY=0;
int posCamaraZ=0;
//tamaño del bufer para seleccionar objetos...
const int BUFFER_SIZE=512;
/* variable que contiene la informancion del aspecto de la ventana*/
double aspecto;
/*bool indicadores de la tecla se mantiene pulsada.*/
bool pz,pZ,px,pX,pc,pC,pd,pD,pu,ph,pj,pk;
/*variables para distintos modos*/
bool ajedrez,parar_animacion,iluminati;
int modelo=0;
int luz_activa=0;
bool cola=false;
bool ply,revolucionado,jerarquico,otros,seleccionables; 
//variables para la interactividad del raton...
bool primario,secundario,central,modo_seleccion=true;
int anteriorX,anteriorY;
int actualX,actualY;
//texturas para el tablero de ajedrez
textura *madera = new textura("text-madera.jpg");
textura *cuadros = new textura("escaques4x4.jpg");
//variables para el modelo jerarquico
double velocidad_animacion; 
ovni ovni1;
//variables de objetos de la clase dibujo
dibujo *TABLERO;
dibujo *CUBO;
dibujo *TETRAEDRO;
vector<dibujo*> dibujos;
vector<dibujo*> plys;
vector<dibujo*> perfiles;
vector<dibujo*> lata;
vector<dibujo*> seleccion;

/******************************************************************/
// tamaño de los ejes
const int AXIS_SIZE=5000;
// variables que controlan la ventana y la transformacion de perspectiva
GLfloat Window_width,
	Window_height,
	Front_plane,
	Back_plane;
// variables que determninan la posicion y tamaño de la ventana X
int UI_window_pos_x=50,UI_window_pos_y=50,UI_window_width=500,UI_window_height=500;
//variables luz
GLfloat light_ambient[] = { 0.75, 0.75, 0.75, 1.0 };
GLfloat light_diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
GLfloat light_specular[] = { 1.0, 1.0, 1.0, 1.0 };
GLfloat light_position[] = { 0.0, 0.0, 1.0, 0.0 };

void clear_window()
{
glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
}
//**************************************************************************
// Funcion para definir la transformación de proyeccion 
//***************************************************************************

void change_projection()
{ 
glMatrixMode(GL_PROJECTION);
glLoadIdentity();
// formato(x_minimo,x_maximo, y_minimo, y_maximo,Front_plane, plano_traser)
//  Front_plane>0  Back_plane>PlanoDelantero)
glFrustum(-Window_width,Window_width,-Window_height,Window_height,Front_plane,Back_plane);
}

//**************************************************************************
// Funcion para definir la transformación de vista (posicionar la camara)
//***************************************************************************
GLfloat Observer_distance=50;
GLfloat Observer_angle_x=45;
GLfloat Observer_angle_y=45;

void change_observer()
{
// posicion del observador
glMatrixMode(GL_MODELVIEW);
glLoadIdentity();
glTranslatef(posCamaraX,0,-Observer_distance); 

glRotatef(Observer_angle_x,1,0,0);
glRotatef(Observer_angle_y,0,1,0); 
} 
//VARIABLE QUE CREA UN OBJETO PARA LAS FUNCIONES DE LAS LUCES
luces luz;

//**************************************************************************
// Funcion que dibuja los ejes utilizando la primitiva grafica de lineas
//***************************************************************************
void draw_axis(){
	glBegin(GL_LINES);
		// eje X, color rojo
		glColor3f(1,0,0);
		glVertex3f(-AXIS_SIZE,0,0);
		glVertex3f(AXIS_SIZE,0,0);
		// eje Y, color verde
		glColor3f(0,1,0);
		glVertex3f(0,-AXIS_SIZE,0);
		glVertex3f(0,AXIS_SIZE,0);
		// eje Z, color azul
		glColor3f(0,0,1);
		glVertex3f(0,0,-AXIS_SIZE);
		glVertex3f(0,0,AXIS_SIZE);
	glEnd();
	glBegin(GL_POINTS);
		glColor3f(0,0,0);
		glVertex3f(5,0,0);
		glVertex3f(-5,0,0);
		glVertex3f(0,5,0);
		glVertex3f(0,-5,0);
		glVertex3f(0,0,5);
		glVertex3f(0,0,-5);
}


//**************************************************************************
// Funcion que dibuja una luz que definio el profesor
//***************************************************************************
void draw_light(){
	glLightfv (GL_LIGHT0, GL_AMBIENT, light_ambient);
	glLightfv (GL_LIGHT0, GL_DIFFUSE, light_diffuse);
	glLightfv (GL_LIGHT0, GL_SPECULAR, light_specular);
	glLightfv (GL_LIGHT0, GL_POSITION, light_position);


}
//**************************************************************************
//sin relevancia para la practica
//***************************************************************************
void cambia_objeto(bool sube){
	if(sube){
		if(ply){
			if (modelo < plys.size()-1){modelo++;}
			else{modelo = 0;}
		}	
		if(revolucionado){
			if (modelo < perfiles.size()-1){modelo++;}
			else{modelo = 0;}
		}
		if(otros){
			if (modelo < dibujos.size()-1){modelo++;}
			else{modelo = 0;}
		}
	}	
	else{
		if(ply){
			if (modelo < plys.size()-1){modelo--;}
			else{modelo = plys.size()-1;}
		}	
		if(revolucionado){
			if (modelo < 0){modelo--;}
			else{modelo = perfiles.size()-1;}
		}
		if(otros){
			if (modelo < 0){modelo--;}
			else{modelo = dibujos.size()-1;}
		}
	}	
}
/****************************************
 * 
 * CAMARAS /* Funcións que establecen la proyección 
 *
 ****************************************/
void proyeccionPerspectivaTeclado (void) {
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(30.0, aspecto, 1.0f, 10000.0f); 
}
void proyeccionPerspectivaRaton (void) {
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(30.0, aspecto, 1.0f, 10000.0f); 
  glMatrixMode(GL_MODELVIEW);
  gluLookAt(0,2,10,0,2,0,0,1,0);
}

/* Función que establece la proyección paralela */
void proyeccionParalela (void) {
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(-10.5f*aspecto, 10.5f*aspecto, -10.5f, 10.5f, 1.0f, 10000.0f); 
}
void proyeccionParalelaPerfil (void) {
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(-10.5f*aspecto, 10.5f*aspecto, -10.5f, 10.5f, 1.0f, 10000.0f); 
}

/* Rutina asociada a eventos de ventana ------------------------------------*/
void eventoVentana (GLsizei ancho, GLsizei alto) {
	glViewport (0, 0, ancho, alto);
	aspecto= (GLdouble) (ancho)/alto;
	proyeccionPerspectivaTeclado();
}
void draw_practica5_names(){
	glMatrixMode(GL_MODELVIEW);
            glInitNames();
            glPushName(0);
                    glPushMatrix();
						glLoadName(1);
						glTranslatef(-5,0,5);glScalef(0.3,0.3,0.3);seleccion[0]->draw_objects_suave_rojo_metalico();
						glPopMatrix();
						
						glPushMatrix();
						glLoadName(2);
						glTranslatef(5,0,5);glScalef(0.5,0.5,0.5);seleccion[1]->draw_objects_suave_rojo_metalico();
						glPopMatrix();
						
						glPushMatrix();
						glLoadName(3);
						glTranslatef(-5,0,-5);glScalef(0.5,0.5,0.5);seleccion[2]->draw_objects_suave_rojo_metalico();
						glPopMatrix();
						
						glPushMatrix();
						glLoadName(4);
						glTranslatef(5,0,-5);glScalef(0.5,0.5,0.5);seleccion[3]->draw_objects_suave_rojo_metalico();
						glPopMatrix();
                    glPopMatrix();
                
            
            glPopName();
}

void draw_practica4(){
		glPushMatrix();
		glScalef(5,5,5);
			for(int i = 0; i < lata.size()-1; i++){
				if (i == 1){
					lata[i]->draw_objects_suave_rojo_metalico();
				}
				else if(i==0){
					glPushMatrix();
					glTranslatef(0,0.01,0);
						lata[i]->draw_objects_suave_gris_metalico();
					glPopMatrix(); 
				} 
				else{ 
					lata[i]->draw_objects_suave_gris_metalico();
				}
			}
	glPopMatrix();	  
	glPushMatrix();
		glTranslatef(5,1.4,5);
			lata[lata.size()-1]->draw_objects_suave_blanco();
	glPopMatrix(); 
	glPushMatrix();
		glTranslatef(0,1.4,5); 
			lata[lata.size()-1]->draw_textura_revolucion();
	glPopMatrix();
	glPushMatrix();
		glTranslatef(-5,1.4,5);
			lata[lata.size()-1]->draw_objects_suave_negro(); 
	glPopMatrix();
	glPushMatrix();
		glTranslatef(5,0,0);
		glScalef(5,5,5);
			//TABLERO->draw_textura_cubo();
	glPopMatrix();
	glPushMatrix();
		glEnable(GL_TEXTURE_2D);
		glTexImage2D(GL_TEXTURE_2D,0,3,madera->tamx, madera->tamy,
			0,GL_RGB,GL_UNSIGNED_BYTE,madera->texels);
		glPolygonMode (GL_FRONT, GL_FILL);
  

  glShadeModel  (GL_SMOOTH);
  glDepthFunc   (GL_LEQUAL);
  glEnable      (GL_DEPTH_TEST);
  glEnable      (GL_NORMALIZE);
  //hay que darle un material a la textura sino no se pinta
lata[1]->material();
   glClearColor(1, 1, 1, 1.0);
        glBegin(GL_QUADS);
            glTexCoord2f(0.0f, 0.0f);
            glVertex3f(-10.0f, 0.0f, 10);

			glTexCoord2f(1.0f, 0.0f);
			glVertex3f(10.0f, 0.0f, 10);

			glTexCoord2f(1.0f, 1.0f);
			glVertex3f(10.0f, 0.0f, -10.0f);

			glTexCoord2f(0.0f, 1.0f);
			glVertex3f(-10.0f, 0.0f,-10.0f);
		glEnd();
		glPopMatrix();
		
		glPushMatrix();
		glEnable(GL_TEXTURE_2D);
		glTexImage2D(GL_TEXTURE_2D,0,3,cuadros->tamx, cuadros->tamy,
0,GL_RGB,GL_UNSIGNED_BYTE,cuadros->texels);
		glPolygonMode (GL_FRONT, GL_FILL);
  glShadeModel  (GL_SMOOTH);
  glDepthFunc   (GL_LEQUAL);
  glEnable      (GL_DEPTH_TEST);
  glEnable      (GL_NORMALIZE);

   glClearColor(1, 1, 1, 1.0);
        glBegin(GL_QUADS);
            glTexCoord2f(0.0f, 0.0f);
            glVertex3f(-8.0f, 0.001f, 8);

			glTexCoord2f(2.0f, 0.0f);
			glVertex3f(8.0f, 0.001f, 8);

			glTexCoord2f(2.0f, 2.0f);
			glVertex3f(8.0f, 0.001f, -8.0f);

			glTexCoord2f(0.0f, 2.0f);
			glVertex3f(-8.0f, 0.001f,-8.0f);
		glEnd();
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);
}
//***************************************************************************
// Funcion selección al hacer click
//IMPÔRTANTE
//***************************************************************************

int pick(unsigned int x, unsigned int y) {
    GLuint Hits, Selection_buffer[BUFFER_SIZE]; // Objetos seleccionados y Buffer de datos
    GLint Viewport[4]; // Volumen de visión

    glSelectBuffer(BUFFER_SIZE,Selection_buffer); // Crear buffer de datos
    glRenderMode(GL_SELECT); // Cambiar al modo selección
    glGetIntegerv(GL_VIEWPORT,Viewport); // Redefinir volumen de visión

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPickMatrix(x,Viewport[3]-y,5.0,5.0,Viewport);
    
    if(moverTeclado){gluPerspective(30.0, aspecto, 1.0f, 10000.0f);} // Fijar proyección

    draw_practica5_names(); // Dibujar escena
    Hits = glRenderMode(GL_RENDER); // Guardar número de objetos seleccionados

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    if(moverTeclado ){gluPerspective(30.0, aspecto, 1.0f, 10000.0f);} // Fijar proyección

    // Analizar resultados
    int encontrado = -1; // Resultado del elemento más cercano

    if(Hits>0) { // Hay algún objeto
        unsigned int i=0; // Contador del buffer
        float z, Zmin = INFINITY; // Valor minimo actual de z

        for(unsigned int k=0; k<Hits; k++) { // Recorrer objetos seleccionados
            if(Selection_buffer[i]!=0) { // Hay nombres en la pila
                z = Selection_buffer[i+1]; // Valor de z min del objeto
                if(z<Zmin) { // Si es menor que el valor actual mínimo de z
                    encontrado = Selection_buffer[i+3]; // Índice del elemento (solo un nivel jerárquico de nombres)
                    Zmin = z; // Actualizar Zmin
                }
            }
            i += Selection_buffer[i]+3; // Nos movemos al siguiente (N+Zmin+Zmax=3)+N
        }
    }

    return encontrado;
}

void draw_scene(void){
clear_window();
change_observer();
	if(primario && moverRaton){
	 glMatrixMode(GL_PROJECTION);
		  }
	glMatrixMode (GL_MODELVIEW);	 
	draw_axis();
	if(ply){
		
		if(modelo>plys.size()-1){modelo=0;}
		plys[modelo]->draw_objects(ajedrez);
	}
	if(revolucionado){
		if(modelo>perfiles.size()-1){modelo=0;}
		perfiles[modelo]->draw_objects(ajedrez);
	}
	if(jerarquico){
		
		glPushMatrix();
			glColor3f( 0.647059,0.164706,0.164706);
			glScalef(5000,0,5000);
			glutSolidCube(1);
		glPopMatrix(); 
		for(int i = 0; i<4; i++){
			glPushMatrix();
				glColor3f(0.62352,0.372549, 0.623529);
				glRotatef((360/4)*i,0,1,0);
				glTranslatef(0,0,2500);
				glRotatef(90,1,0,0);
				glScalef(5000,0,5000);
				glutSolidCube(1);
			glPopMatrix();
		}
		ovni1.draw_ovni(ajedrez); 
	}
	if(cola){
		draw_practica4();
	}
	if(seleccionables){
		draw_practica5_names();
	}
	if(otros){
		if(modelo>dibujos.size()-1){modelo=0;}
		dibujos[modelo]->draw_objects_suave(ajedrez);
	}
glutSwapBuffers();
}
void idle(void)
{

glutPostRedisplay();
}
//***************************************************************************
// Funcion llamada cuando se produce un cambio en el tamaño de la ventana
//
// el evento manda a la funcion:
// nuevo ancho
// nuevo alto
//***************************************************************************

void change_window_size(int Ancho1,int Alto1)
{
change_projection();
glViewport(0,0,Ancho1,Alto1);
glutPostRedisplay();
}
//FUNCION PARA ANIMACION
void big_idle(int n){
	ovni1.miIdle();
	glutPostRedisplay();
	if (parar_animacion) return;
	glutTimerFunc(velocidad_animacion,big_idle,n);
	
}
void practica4(){
	glPolygonMode (GL_FRONT_AND_BACK, GL_FILL);
	modelo = 2;
	ply=false;revolucionado=false;jerarquico=false;otros = false;iluminati=true;
	cola=true, seleccionables=false;	
	textura::initialize_texturas();  
}

void practica5(){
	glPolygonMode (GL_FRONT_AND_BACK, GL_FILL);
	modelo = 2;
	ply=false;revolucionado=false;jerarquico=false;otros = false;iluminati=true;
	cola=false, seleccionables=true;

		
}
int pulsaX,pulsaY;
/* Rutina asociada a eventos de ratón */
void eventoRaton (int boton, int estado, int x, int y) {
	switch (boton) {
		  case GLUT_LEFT_BUTTON:
			if(modo_seleccion && estado == GLUT_DOWN) {
				cout << RED << "El objeto Selecionado es " << pick(x,y) <<BLACK << endl;
			}else if(estado == GLUT_DOWN && moverRaton){
			cout << "has pulsado el primario en " << x << "," << y <<  endl;
			anteriorX=x;
			anteriorY=y;

			glMatrixMode(GL_PROJECTION);
			glutSetCursor(GLUT_CURSOR_SPRAY);
			
			primario=true;}
			else if(perfil && estado == GLUT_DOWN) {
				proyeccionParalela();
				posCamaraX=0;
				Observer_distance=50;
				Observer_angle_x=90;
				Observer_angle_y=90;
				planta=true;moverTeclado=false;moverRaton=false;modo_seleccion=false;perfil=false;
			}
		  break;  
		  case GLUT_MIDDLE_BUTTON:
			cout << "has pulsado el terciario" << endl;
			central=true;
		  break;
	}
	switch (boton) {
	  case GLUT_LEFT_BUTTON:
	  if(estado == GLUT_DOWN){
		cout << "has soltado el primario en " << x << "," << y <<  endl;

		glutSetCursor(GLUT_CURSOR_RIGHT_ARROW);
		primario=false;
	  }
	  break;
	  
	  case GLUT_MIDDLE_BUTTON:
		cout << "has soltado el terciario" << endl;
		central=false;
	  break;
}

}

/* Rutina asociada a movimiento del ratón */
void eventoMovimientoRaton (int x, int y) {
	 
	  printf("pasando por (%d,%d)...\n",x,y);
if(moverRaton){
	Observer_angle_x= Observer_angle_x +anteriorY -y;
	Observer_angle_y=	Observer_angle_y +x-anteriorX;
	anteriorX=x;
	anteriorY=y;
}	
  glutPostRedisplay();
}

//***************************************************************************
// Funcion llamada cuando se produce aprieta una tecla normal
//
// el evento manda a la funcion:
// codigo de la tecla
// posicion x del raton
// posicion y del raton
//***************************************************************************
void normal_keys(unsigned char Tecla1,int x,int y)
{
	if(pz==true)ovni1.mover_torreta();//cout << "estoy en pz" << endl;  
	else if(pZ==true)ovni1.mover_torreta(-1); 
		 
	if(px==true)ovni1.subeBaja(1); 
	else if(pX==true)ovni1.subeBaja(-1);
		
	if(pc==true)ovni1.desplegar_patas(1);
	else if(pC==true)ovni1.desplegar_patas(-1);
		
	if(pk==true)ovni1.translacion_x(1); 
	if(ph==true)ovni1.translacion_x(-1); 
	
	if(pj==true)ovni1.translacion_x(1);
	if(pu==true)ovni1.translacion_x(-1);
	
	switch (Tecla1){
		case 'l':ajedrez = false;glPolygonMode (GL_FRONT_AND_BACK, GL_LINE);break;
		
		case 'p':ajedrez = false;glPolygonMode (GL_FRONT_AND_BACK, GL_POINT);break;
		case 's':ajedrez = false;glPolygonMode (GL_FRONT_AND_BACK, GL_FILL);break;
		case 'a':ajedrez = true;glPolygonMode (GL_FRONT_AND_BACK, GL_FILL);break;
		case '1':glDisable(GL_LIGHTING);ply=true; revolucionado=false; jerarquico=false;otros = false;cola=false;iluminati=false;break;
		case '2':glDisable(GL_LIGHTING);ply=false; revolucionado=true; jerarquico=false;otros = false;iluminati=false;cola=false;break;
		case '3':glDisable(GL_LIGHTING);ply=false; revolucionado=false; jerarquico=true;otros = false;iluminati=false;cola=false;break;
		case '4':practica4();break;
		case '5':practica5();break;
		case '0':ajedrez = false;glPolygonMode (GL_FRONT_AND_BACK, GL_FILL);modelo = 2;ply=false;cola=false; revolucionado=false; jerarquico=false;otros = true;iluminati=true;luz.posicional(luz_activa);luz_activa++;if(luz_activa > 3){luz_activa=0;} break;
		case '+':cambia_objeto(true);break;
		case '-':cambia_objeto(false);break;
         //luces
        case '7':luz.posicional();glDisable(GL_LIGHT1);glDisable(GL_LIGHT2);break;
		case '8':luz.direccional();glDisable(GL_LIGHT0);glDisable(GL_LIGHT2);break;
		case '9':luz.roja();glDisable(GL_LIGHT0);glDisable(GL_LIGHT1);break;
         
         
		case 'q':exit(0);break;
		case 'i':parar_animacion=false;big_idle(1);break;
		case 'I':parar_animacion=true; break;
		case 'z':pz=true;pZ=false;ovni1.mover_torreta();break;
		case 'Z':pZ=true;pz=false;ovni1.mover_torreta(-1);break;
		case'm':ovni1.aumentaVelocidadTorreta(0.1);break;
		case'M':ovni1.aumentaVelocidadTorreta(-0.1);break;
		case 'x':px=true;pX=false;ovni1.subeBaja(1);break;
		case 'X':pX=true;px=false;ovni1.subeBaja(-1);break;
		case'b':ovni1.aumentaVelocidadCuerpo(0.1);break;
		case'B':ovni1.aumentaVelocidadCuerpo(-0.1);break;
		case 'c':pc=true;pC=false;ovni1.desplegar_patas(1);break;
		case 'C':pC=true;pc=false;ovni1.desplegar_patas(-1);break;
		case'n':ovni1.aumentaVelocidadPatas(0.1);break;
		case'N':ovni1.aumentaVelocidadPatas(-0.1);break;
		case'k':pk=true;ovni1.translacion_x(1);break;
		case'h':ph=true;ovni1.translacion_x(-1);break;
		case'u':pu=true;ovni1.translacion_z(-1);break;
		case'j':pj=true;ovni1.translacion_z(1);break;
		case'f':ovni1.aumentaVelocidadX(0.1);break;
		case'F':ovni1.aumentaVelocidadX(-0.1);break;
		case 't': luz.posicional(luz_activa);luz_activa++;if(luz_activa > 3){luz_activa=0;} break;
		
	}
glutPostRedisplay();
}

void normal_keysup(unsigned char Tecla1,int x,int y)
{
	switch (Tecla1){
		case'z':pz=false;break;
		case'Z':pZ=false;break;
		
		case'x':px=false;break;
		case'X':pX=false;break;
		
		case'c':pc=false;break;
		case'C':pC=false;break;
		
		case'd':pd=false;break;
		case'D':pD=false;break;
		
		case'k':pk=false;break;
		case'h':ph=false;break;
		case'u':pu=false;break;
		case'j':pj=false;break;
	}
glutPostRedisplay();
}
//***************************************************************************
// Funcion llamada cuando se produce aprieta una tecla especial
//
// el evento manda a la funcion:
// codigo de la tecla
// posicion x del raton
// posicion y del raton
//***************************************************************************
void special_keys(int Tecla1,int x,int y){
	if(moverTeclado){
		switch (Tecla1){
			case GLUT_KEY_LEFT:Observer_angle_y--;break;
			case GLUT_KEY_RIGHT:Observer_angle_y++;break;
			case GLUT_KEY_UP:Observer_angle_x--;break;
			case GLUT_KEY_DOWN:Observer_angle_x++;break;
			case GLUT_KEY_PAGE_UP:Observer_distance*=1.2;break;
			case GLUT_KEY_PAGE_DOWN:Observer_distance/=1.2;break;
			case GLUT_KEY_F5:proyeccionParalelaPerfil();
					posCamaraX=0;
					Observer_distance=50;
					Observer_angle_x=0;
					Observer_angle_y=90;
					planta=true;moverTeclado=false;moverRaton=false;modo_seleccion=false;perfil=true;break;
		}
	}
glutPostRedisplay();
}



/* Atiende las opciones del menú desplegable -------------------------------*/
void atiendeMenu (int opcion) {

  switch (opcion) {
  case  1:	proyeccionParalela();
			posCamaraX=0;
			Observer_distance=50;
			Observer_angle_x=90;
			Observer_angle_y=90;
			planta=true;moverTeclado=false;moverRaton=false;modo_seleccion=false;perfil=false;break;
  case  2:	proyeccionPerspectivaRaton();
			planta=false;moverTeclado=false;moverRaton=true;modo_seleccion=false;perfil=false;break;
  case  3:	proyeccionPerspectivaTeclado();
			planta=false;moverTeclado=true;moverRaton=false;modo_seleccion=false;perfil=false;break;
				
  case  4: planta=false;moverTeclado=true;moverRaton=false;modo_seleccion=true;perfil=false;break;
  }
  glutPostRedisplay ();
}

/* Establece las opciones del menú desplegable -----------------------------*/
void menu (void) {
  int idMenuPrincipal, idMenucamara;
  idMenuPrincipal= glutCreateMenu (atiendeMenu);
  glutAttachMenu (GLUT_RIGHT_BUTTON);
  idMenucamara= glutCreateMenu (atiendeMenu);
  glutAddMenuEntry ("Planta ortogonal", 1);
  glutAddMenuEntry ("Camara Interactiva Raton ", 2);
  glutAddMenuEntry ("Camara interactiva teclado", 3);
  glutSetMenu (idMenuPrincipal);
  glutAddSubMenu ("Seleccion Camara", idMenucamara);

  glutAddMenuEntry ("Modo Seleccion", 4);
}


//***************************************************************************
// Funcion de incializacion
//***************************************************************************

void initialize(void)
{
// se inicalizan la ventana y los planos de corte
Window_width=5;
Window_height=5;
Front_plane=5;
Back_plane=10000;
modo_seleccion=false;
moverTeclado=true;
primario=false;secundario=false;central=false;

// se indica cual sera el color para limpiar la ventana	(r,v,a,al)
// blanco=(1,1,1,1) rojo=(1,0,0,1), ...
glClearColor(1,1,1,1);

// se habilita el z-bufer
glEnable(GL_DEPTH_TEST);
//
change_projection();
//
glViewport(0,0,UI_window_width,UI_window_height);
glutSetCursor(GLUT_CURSOR_RIGHT_ARROW);
}


//***************************************************************************
// Programa principal
//
// Se encarga de iniciar la ventana, asignar las funciones e comenzar el
// bucle de eventos
//***************************************************************************

int main(int argc, char **argv)
{
		
if(true){
	pz=false;px=false;pc=false;pd=false;ph=false;pj=false;pk=false;pu=false;

	velocidad_animacion=50;
	vector<_vertex3f> Cubo;
	parar_animacion=false;
	Cubo.push_back(_vertex3f(-1,1,1));
	Cubo.push_back(_vertex3f(1,1,1));
	Cubo.push_back(_vertex3f(1,-1,1));
	Cubo.push_back(_vertex3f(-1,-1,1));
	Cubo.push_back(_vertex3f(1,1,-1));
	Cubo.push_back(_vertex3f(1,-1,-1));
	Cubo.push_back(_vertex3f(-1,1,-1));
	Cubo.push_back(_vertex3f(-1,-1,-1));
	
	
	
	vector<_vertex3i> Caras_cubo;
	Caras_cubo.push_back(_vertex3i(0,2,1));
	Caras_cubo.push_back(_vertex3i(0,3,2));
	Caras_cubo.push_back(_vertex3i(1,2,5));
	Caras_cubo.push_back(_vertex3i(1,5,4));
	Caras_cubo.push_back(_vertex3i(4,5,7));
	Caras_cubo.push_back(_vertex3i(4,7,6));
	Caras_cubo.push_back(_vertex3i(6,7,3));
	Caras_cubo.push_back(_vertex3i(6,3,0));
	Caras_cubo.push_back(_vertex3i(0,1,4));
	Caras_cubo.push_back(_vertex3i(0,4,6));
	Caras_cubo.push_back(_vertex3i(3,5,2));
	Caras_cubo.push_back(_vertex3i(3,7,5));
	


vector<_vertex3f> rectangulo;

rectangulo.push_back(_vertex3f(4,0,0));
rectangulo.push_back(_vertex3f(2,4,0));
rectangulo.push_back(_vertex3f(4,8,0));
rectangulo.push_back(_vertex3f(3,10,0));


vector<_vertex3i> caras_rectangulo;


caras_rectangulo.push_back(_vertex3i(0,1,2));
caras_rectangulo.push_back(_vertex3i(0,2,3));

	perfiles.push_back(new dibujo("perfil.ply"));
		perfiles[perfiles.size()-1]->revolucion();
		
	
	
	perfiles.push_back(new dibujo(rectangulo,caras_rectangulo));
		perfiles[perfiles.size()-1]->revolucion();


plys.push_back(new dibujo("ant.ply"));
plys.push_back(new dibujo("beethoven.ply"));
plys.push_back(new dibujo("big_dodge.ply"));

seleccion.push_back(new dibujo("ant.ply"));
seleccion.push_back(new dibujo("beethoven.ply"));
seleccion.push_back(new dibujo("big_dodge.ply"));
seleccion.push_back(new dibujo("big_dodge.ply"));
cout << RED << "el numero de objetos en seleccion es : "<< seleccion.size() <<BLACK<< endl;
	
	
dibujos.push_back(new dibujo(Cubo,Caras_cubo));

dibujos.push_back(new dibujo("ant.ply"));
dibujos.push_back(new dibujo("beethoven.ply"));
dibujos.push_back(new dibujo("big_dodge.ply"));
dibujos.push_back(new dibujo("perfil.ply"));
	dibujos[dibujos.size()-1]->revolucion();
dibujos.push_back(new dibujo(rectangulo,caras_rectangulo));
	dibujos[dibujos.size()-1]->revolucion();
dibujos.push_back(new dibujo("airplane.ply"));

lata.push_back(new dibujo("lata-psup.ply"));
	lata[lata.size()-1]->revolucion();
lata.push_back(new dibujo("lata-pcue.ply"));
	lata[lata.size()-1]->revolucion();
lata.push_back(new dibujo("lata-pinf.ply"));
	lata[lata.size()-1]->revolucion();
lata.push_back(new dibujo("perfil.ply","text-madera.jpg"));
	lata[lata.size()-1]->revolucion();
TABLERO=new dibujo(Cubo,Caras_cubo);
	TABLERO->settexturilla("text-madera.jpg");
//~ // se llama a la inicialización de glut
glutInit(&argc, argv);
cout << RED << "el numero de objetos en seleccion es : "<< seleccion.size() <<BLACK<< endl;
// se indica las caracteristicas que se desean para la visualización con OpenGL
// Las posibilidades son:
// GLUT_SIMPLE -> memoria de imagen simple
// GLUT_DOUBLE -> memoria de imagen doble
// GLUT_INDEX -> memoria de imagen con color indizado
// GLUT_RGB -> memoria de imagen con componentes rojo, verde y azul para cada pixel
// GLUT_RGBA -> memoria de imagen con componentes rojo, verde, azul y alfa para cada pixel
// GLUT_DEPTH -> memoria de profundidad o z-bufer
// GLUT_STENCIL -> memoria de estarcido
glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);

// posicion de la esquina inferior izquierdad de la ventana
glutInitWindowPosition(UI_window_pos_x,UI_window_pos_y);

// tamaño de la ventana (ancho y alto)
glutInitWindowSize(UI_window_width,UI_window_height);

// llamada para crear la ventana, indicando el titulo (no se visualiza hasta que se llama
// al bucle de eventos)
glutCreateWindow("Práctica 5  Juan Carlos Chaves Puertas");
glPolygonMode (GL_FRONT_AND_BACK, GL_POINT);
// asignación de la funcion llamada "dibujar" al evento de dibujo
glutDisplayFunc(draw_scene);
// asignación de la funcion llamada "cambiar_tamanio_ventana" al evento correspondiente
glutReshapeFunc(eventoVentana);
// eventos del raton
glutMouseFunc    (eventoRaton);
glutMotionFunc   (eventoMovimientoRaton);
// asignación de la funcion llamada "tecla_normal" al evento correspondiente
glutKeyboardFunc(normal_keys);
glutKeyboardUpFunc(normal_keysup);
// asignación de la funcion llamada "tecla_Especial" al evento correspondiente
glutSpecialFunc(special_keys);

// funcion de inicialización
normal_keys('5',0, 0);
normal_keys('7',0, 0);
initialize();
  menu ();
glutIdleFunc(idle);

// inicio del bucle de eventos
glutMainLoop();

}
return 0;
}
