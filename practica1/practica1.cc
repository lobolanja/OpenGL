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

using namespace std;



//vector<_vertex3f> puntillo;
//vector<GLint> puntillo;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*******************ESTRUCTURA DIBUJO********************************/
struct dibujo{
	int n_vertices;
	int n_caras;
	int aux_n_vertices;
	int aux_n_caras;
	
	GLfloat **vertices;
	GLfloat **aux_ver; // para facilitar las copias y las transformaciones.
	
	GLint **caras;
	GLint **aux_car;  // para facilitar las copias y las transformaciones.
	
	dibujo(int n_v, int n_c, GLfloat ver[][3], GLint car[][3]){
		n_vertices=n_v;
		n_caras = n_c;
		reserva_matrices();
		rellena_matrices(ver, car);
	}
	void reserva_matrices(bool aux=false){
		if(!aux){
		//reserva de la matriz de vertices
		vertices=new GLfloat*[n_vertices];
			for (int i = 0; i<n_vertices;i++){
				vertices[i]= new GLfloat[3];
			}
		//reserva de la matriz de caras
		caras=new GLint*[n_caras];
			for (int i = 0; i<n_caras;i++)
				caras[i]= new GLint[3];
		}
		else{
			
		aux_ver=new GLfloat*[aux_n_vertices];
			for (int i = 0; i<aux_n_vertices;i++){
				aux_ver[i]= new GLfloat[3];
			}
		
		aux_car=new GLint*[aux_n_caras];
			for (int i = 0; i<aux_n_caras;i++)
				aux_car[i]= new GLint[3];
			
		}
	}

	
	void rellena_matrices(GLfloat ver[][3], GLint car[][3]){
		//creacion de la matriz de vertices
			for (int i = 0; i<n_vertices;i++){
				for (int j=0; j<3;j++){
					vertices[i][j]=ver[i][j];
				}
			}
		//creacion de la matriz de caras
		for (int i = 0; i<n_caras;i++){
				for (int j=0; j<3;j++){
					caras[i][j]=car[i][j];
				}
			}
		}
	void revolucion(int puntos_ini, int puntos_rev=50){
		//if(plano){...meter lo siguiente}
		aux_n_vertices = ((puntos_rev*(puntos_ini-2))+2);
		aux_n_caras = ((((puntos_ini-2)*puntos_rev)+(2*puntos_rev)));
		reserva_matrices(true);
		cout << aux_n_vertices << aux_n_caras << endl;
		cout<< "empezamos revolucion" << endl;
		// creamos los vertices por revolucion (y nos faltara introducir el primer y el ultimo punto que se colocan en el eje y.
		for(int k=1;k<n_vertices-1;k++){
			for (int i = 0; i<=puntos_rev;i++){
				
					aux_ver[i+((k-1)*puntos_rev)][0]=((vertices[k][0]*(cos((2*M_PI/(puntos_rev))*i))+vertices[k][2]*(sin((2*M_PI/(puntos_rev))*i))));
					aux_ver[i+((k-1)*puntos_rev)][1]=vertices[k][1];
					aux_ver[i+((k-1)*puntos_rev)][2]=((-vertices[k][0]*(sin((2*M_PI/(puntos_rev))*i))+vertices[k][2]*(cos((2*M_PI/(puntos_rev))*i))));
				//cout <<i+(k-1)*puntos_rev << "   " << aux_ver[i+((k-1)*puntos_rev)][0]<< "   " << aux_ver[i+((k-1)*puntos_rev)][1] << "   " << aux_ver[i+((k-1)*puntos_rev)][2] << endl;
			}
			
			cout << "puff" << endl;
		}
		cout << "salimos del primer for" << aux_n_caras<< endl;
		//creamos las caras por revolucion
	
			for (int i = 0; i<n_vertices-2; i++){
				int z =0;
				for(int j=0;j<puntos_rev;j++){
					
					cout << i*puntos_rev+z << "     "<< j+i*puntos_rev << "  " << j+1+(1+i)*puntos_rev << "  " << j+(i+1)*puntos_rev<< endl;
					aux_car[i*puntos_rev+z ][0]=j+i*puntos_rev;
					aux_car[i*puntos_rev+z ][1]=j+1+(1+i)*puntos_rev;
					aux_car[i*puntos_rev+z ][2]=j+(i+1)*puntos_rev;
					
					cout << i*puntos_rev+z+1  << "     "<< j+i*puntos_rev << "  " << j+1+(i*puntos_rev) << "  " << j+1+((1+i)*puntos_rev) << endl;
					aux_car[i*puntos_rev+1+z][0]=j+i*puntos_rev;
					aux_car[i*puntos_rev+1+z][1]=j+1+(i*puntos_rev);
					aux_car[i*puntos_rev+1+z][2]=j+1+((1+i)*puntos_rev);
					z=z+2;
				}
			}
			vertices=aux_ver;
			caras=aux_car;
			n_vertices=aux_n_vertices;
			n_caras=200;//aux_n_caras;
			
		}
		
		
		
		
		
};


////////////////////////////////////////////////////////////////////////////////////////////////////////
/******************************************************************/

dibujo *CUBO;
dibujo *TETRAEDRO;
vector<dibujo*> dibujos;
bool ajedrez;
int modelo=0;


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

void draw_objects()
{



glColor3f(148,0,128);
glPointSize(4);

glBegin(GL_TRIANGLES);
		for (int i=0;i<dibujos[modelo]->n_caras;i++){
			if (ajedrez){if (i%2 ==0){glColor3f(0,255,0);}
				else{glColor3f(148,0,128);}}
			for(int j=0;j<3;j++){
			glVertex3fv((GLfloat *) dibujos[modelo]->vertices[dibujos[modelo]->caras[i][j]]);
			}
		}
		
		glEnd();
	
}


//**************************************************************************
//
//***************************************************************************

void draw_scene(void)
{

clear_window();
change_observer();
draw_axis();
draw_objects();
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
		case '+':modelo++;break;
		case '-':modelo--;break;
		case 'q':exit(0);break;
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
Back_plane=1000;

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
	GLfloat Cubo[9][3]= {{4,4,-4},{4,-4,-4},{4,4,4},{4,-4,4},{-4,4,4},{-4,-4,4},{-4,4,-4},{-4,-4,-4}};
	GLint Caras_cubo[12][3]={{0,1,2},{1,2,3},{4,2,3},{3,4,5},{6,5,4},{6,5,7},{0,2,4},{4,6,0},{6,7,0},{7,1,0},{1,3,5},{5,7,1}};
	
	// datos del tetraedro... mas adelante automatizar entrada con archivos ply o revolucion.
	GLfloat tetraedro[4][3]= {{0, 0, 3},{0, 1.88561799, 0.6666666},{-1.63299399, -0.931281, -0.6666666},{1.63299399, -0.931281, -0.6666666}};
	GLint Caras_tetraedro[4][3]={{0,1,2},{1,2,3},{0,1,3},{2,0,3}};


//probar revolucion?????? WTF

GLfloat SI[4][3]={{0,0,0},{4,0,0},{4,8,0},{0,8,0}};
GLint caras_SI[1][3]={{0,1,2}};	
	
	dibujos.push_back(new dibujo(9,12,Cubo,Caras_cubo));
	dibujos.push_back(new dibujo(4,4,tetraedro,Caras_tetraedro));
	dibujos.push_back(new dibujo(4,1,SI,caras_SI));
// se llama a la inicialización de glut
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
