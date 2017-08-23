//**************************************************************************
// Práctica 1
//
// Domingo Martin Perandres 2013-2016
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

#include "dibujo.cc"
using namespace std;

bool ajedrez;
int modelo=0;
struct ovni{ 
	vector<dibujo*> perfiles;
	bool revolu = false;// cambiar en el inicializador+++++
	void aniadir_perfiles(dibujo* aniade){
		perfiles.push_back(aniade);
	}
	void revolucionar(){
		if(!revolu){
			for(int i = 0; i < perfiles.size(); i++){
				perfiles[i]->revolucion();
			}
			revolu = true;
		}
	}
	void esferas(int cuantas=6,float x=-14, float y=-2, float z=0){
				
					
				glTranslatef (x, y, z);
				glColor3f(0,0,0);
				glutSolidSphere (1.5, 15, 15);
				glLoadIdentity();
		for(int k=0;k<cuantas-1; k++){
				x = x*(cos((2*M_PI/(cuantas)))) +z*(sin((2*M_PI/(cuantas))));
				z = -x*(sin((2*M_PI/(cuantas)))) + z*(cos((2*M_PI/(cuantas))));
				cout << "esfera x " << x << endl;
				cout << "esfera z " << z << endl;
				//~ aux_ver.push_back({(vertices[k][0]*(cos((2*M_PI/(puntos_rev-1))*i))+vertices[k][2]*(sin((2*M_PI/(puntos_rev-1))*i))),
					 //~ vertices[k][1],
					 //~ ((-vertices[k][0]*(sin((2*M_PI/(puntos_rev-1))*i))+vertices[k][2]*(cos((2*M_PI/(puntos_rev-1))*i))))});
				//~ 
				//~ 
			
				
				
				glTranslatef (x, y, z);
				glColor3f(0,0,0);
				glutSolidSphere (1.5, 15, 15);
				glLoadIdentity();
		}
			//~ 
		

	}
	void draw_ovni(bool ajedrez = false){
		revolucionar();

		for(int i = 0; i < perfiles.size(); i++){
			perfiles[i]->draw_objects(ajedrez);
		}
		
		esferas();
	}
	
};
ovni ovni1;

struct valvula{
	
	valvula(){
		
	}
	void draw_valvula(bool ajedrez = false){
		//glPushMatrix();
		glPushMatrix();
		glTranslatef(0,-5,0);
		glScalef(1,10,1);
		glutSolidCube(1);//cuerpo
		glPopMatrix();
		
		//~ glPushMatrix();
		//~ glTranslatef(0,-3.5,0);
		//~ glScalef(0.3,7,0.3);
		//~ glRotatef(45,0,1,0);
		//~ glutSolidCube(1);//cuerpo
		//~ glPopMatrix();
		
		        
	}
};

valvula valvula1;
//vector<_vertex3f> puntillo;
//vector<GLint> puntillo;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*******************ESTRUCTURA DIBUJO********************************/




////////////////////////////////////////////////////////////////////////////////////////////////////////
/******************************************************************/

dibujo *CUBO;
dibujo *TETRAEDRO;
static vector<dibujo*> dibujos;



/******************************************************************/



// tamaño de los ejes
const int AXIS_SIZE=5000;

// variables que definen la posicion de la camara en coordenadas polares
GLfloat Observer_distance;
GLfloat Observer_angle_x;
GLfloat Observer_angle_y;

// variables que controlan la ventana y la transformacion de perspectiva
GLfloat Window_width,Window_height,Front_plane,Back_plane;

// variables que determninan la posicion y tamaño de la ventana X
int UI_window_pos_x=50,UI_window_pos_y=50,UI_window_width=500,UI_window_height=500;

//variables luz

GLfloat light_ambient[] = { 0.75, 0.75, 0.75, 1.0 };
GLfloat light_diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
GLfloat light_specular[] = { 1.0, 1.0, 1.0, 1.0 };
GLfloat light_position[] = { 0.0, 0.0, 1.0, 0.0 };
//**************************************************************************
//
//***************************************************************************

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

void change_observer()
{

// posicion del observador
glMatrixMode(GL_MODELVIEW);
glLoadIdentity();
glTranslatef(0,0,-Observer_distance);
glRotatef(Observer_angle_x,1,0,0);
glRotatef(Observer_angle_y,0,1,0);
}

//**************************************************************************
// Funcion que dibuja los ejes utilizando la primitiva grafica de lineas
//***************************************************************************

void draw_axis()
{
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
}


//**************************************************************************
// Funcion que dibuja los objetos
//***************************************************************************

void draw_light(){
	glLightfv (GL_LIGHT0, GL_AMBIENT, light_ambient);
	glLightfv (GL_LIGHT0, GL_DIFFUSE, light_diffuse);
	glLightfv (GL_LIGHT0, GL_SPECULAR, light_specular);
	glLightfv (GL_LIGHT0, GL_POSITION, light_position);


}


//**************************************************************************
//
//***************************************************************************

void draw_scene(void)
{

clear_window();
change_observer();
draw_axis();
draw_light();
//ovni1.draw_ovni(ajedrez);
valvula1.draw_valvula(ajedrez);
//~ dibujos[dibujos.size()-1]->draw_objects(ajedrez);
//~ dibujos[dibujos.size()-2]->draw_objects(ajedrez);

glutSwapBuffers();
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
	switch (Tecla1){
		case 'a':ajedrez = false;glPolygonMode (GL_FRONT_AND_BACK, GL_LINE);break;
		
		case 'p':ajedrez = false;glPolygonMode (GL_FRONT_AND_BACK, GL_POINT);break;
		case 's':ajedrez = false;glPolygonMode (GL_FRONT_AND_BACK, GL_FILL);break;
		case 'c':ajedrez = true;glPolygonMode (GL_FRONT_AND_BACK, GL_FILL);break;
		case '0':modelo=0;break;
		case '1':modelo=1;break;
		case '+':if (modelo < dibujos.size()-1){modelo++;}
				else{modelo = 0;}break;
		case '-':if (modelo > 0){modelo--;}
				else{modelo = dibujos.size()-1;}break;
		case 'q':exit(0);break;
		case 'b':dibujos[modelo]->barrido();break;
		case 'r':dibujos[modelo]->revolucion(dibujos[modelo]->n_vertices);break;
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

void special_keys(int Tecla1,int x,int y)
{

switch (Tecla1){
	case GLUT_KEY_LEFT:Observer_angle_y--;break;
	case GLUT_KEY_RIGHT:Observer_angle_y++;break;
	case GLUT_KEY_UP:Observer_angle_x--;break;
	case GLUT_KEY_DOWN:Observer_angle_x++;break;
	case GLUT_KEY_PAGE_UP:Observer_distance*=1.2;break;
	case GLUT_KEY_PAGE_DOWN:Observer_distance/=1.2;break;
	}
glutPostRedisplay();
}



//***************************************************************************
// Funcion de incializacion
//***************************************************************************

void initialize(void)
{
// se inicalizan la ventana y los planos de corte
Window_width=5;
Window_height=5;
Front_plane=10;
Back_plane=10000;

// se inicia la posicion del observador, en el eje z
Observer_distance=2*Front_plane;
Observer_angle_x=0;
Observer_angle_y=0;

// se indica cual sera el color para limpiar la ventana	(r,v,a,al)
// blanco=(1,1,1,1) rojo=(1,0,0,1), ...
glClearColor(1,1,1,1);

// se habilita el z-bufer
glEnable(GL_DEPTH_TEST);
//
change_projection();
//
glViewport(0,0,UI_window_width,UI_window_height);
}


//***************************************************************************
// Programa principal
//
// Se encarga de iniciar la ventana, asignar las funciones e comenzar el
// bucle de eventos
//***************************************************************************

int main(int argc, char **argv)
{
	// datos del cubo... mas adelante automatizar entrada con archivos ply o revolucion.
	vector<_vertex3f> Cubo;

	Cubo.push_back(_vertex3f(4,4,-4));
	Cubo.push_back(_vertex3f(4,-4,-4));
	Cubo.push_back(_vertex3f(4,4,4));
	Cubo.push_back(_vertex3f(4,-4,4));
	Cubo.push_back(_vertex3f(-4,4,4));
	Cubo.push_back(_vertex3f(-4,-4,4));
	Cubo.push_back(_vertex3f(-4,4,-4));
	Cubo.push_back(_vertex3f(-4,-4,-4));
	
	
	vector<_vertex3i> Caras_cubo;
	Caras_cubo.push_back(_vertex3i(0,1,2));
	Caras_cubo.push_back(_vertex3i(1,2,3));
	Caras_cubo.push_back(_vertex3i(4,2,3));
	Caras_cubo.push_back(_vertex3i(3,4,5));
	Caras_cubo.push_back(_vertex3i(6,5,4));
	Caras_cubo.push_back(_vertex3i(6,5,7));
	Caras_cubo.push_back(_vertex3i(0,2,4));
	Caras_cubo.push_back(_vertex3i(4,6,0));
	Caras_cubo.push_back(_vertex3i(6,7,0));
	Caras_cubo.push_back(_vertex3i(7,1,0));
	Caras_cubo.push_back(_vertex3i(1,3,5));
	Caras_cubo.push_back(_vertex3i(5,7,1));
	
	cout << "y las caras..." << endl;
	// datos del tetraedro... mas adelante automatizar entrada con archivos ply o revolucion.
	//vector<_vertex3f> tetraedro = {{0, 0, 3},{0, 1.88561799, 0.6666666},{-1.63299399, -0.931281, -0.6666666},{1.63299399, -0.931281, -0.6666666}};
	//vector<_vertex3i> Caras_tetraedro={{0,1,2},{1,2,3},{0,1,3},{2,0,3}};


//probar revolucion?????? WTF
vector<_vertex3f> rectangulo;

rectangulo.push_back(_vertex3f(4,0,0));
rectangulo.push_back(_vertex3f(2,4,0));
rectangulo.push_back(_vertex3f(4,8,0));
rectangulo.push_back(_vertex3f(3,10,0));


vector<_vertex3i> caras_rectangulo;


caras_rectangulo.push_back(_vertex3i(0,1,2));
caras_rectangulo.push_back(_vertex3i(0,2,3));


	cout << "añade cubo" << endl;
	dibujos.push_back(new dibujo(Cubo,Caras_cubo));
	dibujos.push_back(new dibujo(rectangulo,caras_rectangulo));
	//dibujos.push_back(new dibujo(tetraedro,Caras_tetraedro));


dibujos.push_back(new dibujo("perfil.ply"));
dibujos.push_back(new dibujo("ant.ply"));
dibujos.push_back(new dibujo("beethoven.ply"));
dibujos.push_back(new dibujo("big_dodge.ply"));
dibujos.push_back(new dibujo("ovni.ply"));
dibujos.push_back(new dibujo("torreta.ply"));
// se llama a la inicialización de glut
dibujos[dibujos.size()-1]->revolucion(dibujos[modelo]->n_vertices);
dibujos[dibujos.size()-2]->revolucion(dibujos[modelo]->n_vertices);
ovni1.aniadir_perfiles(new dibujo("ovni.ply"));
ovni1.aniadir_perfiles(new dibujo("torreta.ply"));

glutInit(&argc, argv);

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
glutCreateWindow("Práctica 1");
glPolygonMode (GL_FRONT_AND_BACK, GL_POINT);
// asignación de la funcion llamada "dibujar" al evento de dibujo
glutDisplayFunc(draw_scene);
// asignación de la funcion llamada "cambiar_tamanio_ventana" al evento correspondiente
glutReshapeFunc(change_window_size);
// asignación de la funcion llamada "tecla_normal" al evento correspondiente
glutKeyboardFunc(normal_keys);
// asignación de la funcion llamada "tecla_Especial" al evento correspondiente
glutSpecialFunc(special_keys);

// funcion de inicialización
initialize();

// inicio del bucle de eventos
glutMainLoop();
return 0;
}
