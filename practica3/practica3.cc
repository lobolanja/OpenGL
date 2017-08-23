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
#include "dibujo.cc"
#include <unistd.h>
using namespace std;

bool pz,pZ,px,pX,pc,pC,pd,pD,pu,ph,pj,pk;
bool ajedrez,parar_animacion;
int modelo=0;



bool ply,revolucionado,jerarquico,otros,
	aterrizar; 
double velocidad_animacion;
struct ovni{ 
	double torreta_x,torreta_y,torreta_z;
	double x,y,z;
	int maximos_movimientos=200;
	int n_movimientos=0;
	int grados_z_ovni = 0,grados_x_ovni=0;
	bool rotando_z=false, rotando_x=false;
	double velocidad_animacion,velocidad_torreta=1,mov_torreta=0,velocidad_cuerpo=1, mov_cuerpo=0 ,velocidad_patas=1, mov_patas=0,
	mov_x=0,velocidad_x=1;
	vector<dibujo*> perfiles;
	dibujo *torreta,*cuerpo,*cristal;
	bool alante, atras;
	double giro_y_cuerpo; //en grados
	double grados_pata;
	ovni(int x1=0, int y1=10, int z1=0){
		x=x1;	y=y1;	z=z1;
		torreta_x=0;	torreta_y=0;	torreta_z=0;
		grados_pata=-30;
		giro_y_cuerpo = 0;
		velocidad_animacion = 0.2;
		crea_cuerpo();
		crea_torreta();
	}

	void revolucionar(dibujo* perfil){
		perfil->revolucion();
	}
	void crea_cuerpo(){
		cuerpo = new dibujo("ovni.ply");
		cristal = new dibujo("cristal.ply");
		revolucionar(cuerpo);
		revolucionar(cristal);
	}
	
	void crea_torreta(){
		torreta = new dibujo("torreta.ply");
		revolucionar(torreta);
	}
	
	void mover_torreta(double velocidad = 1){
		if(torreta_y <= 2 && torreta_y >= 0){
			torreta_y = torreta_y + velocidad*0.2;
			if (torreta_y > 2)
				torreta_y = 2;
			if (torreta_y < 0)
				torreta_y = 0;	
		
		}
	}
	void esferas(int cuantas=6,float x=-14, float y=-2, float z=0){
				
		glEnable(GL_BLEND);
					glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
					glColor4f(1.0,1.0,0.0,0.5);
		
		glPushMatrix();
			for(int k=0;k<cuantas; k++){
				glPushMatrix();
					glRotatef((360/cuantas)*k,0,1,0);
					glTranslatef (x, y, z);
					glutSolidSphere (1.5, 15, 15);
				
				glPopMatrix();
		}
		glDisable(GL_BLEND);
		

	}
	void desplegar_patas(int velocidad){
		 
		if((grados_pata+(360*velocidad/40))>-30 && (grados_pata+(360*velocidad/30))<100){
			grados_pata += 360*velocidad/30;
		}	
	}
	void draw_patas(double x1=8, double y1=-2.5, double z1=0){
	glPushMatrix();
		for(int k=0;k<3; k++){
			glPushMatrix();
				glRotatef((360/3)*k,0,1,0);
				glTranslatef (x1, y1, z1);
				glColor3f(0,0,0);
				glutSolidSphere (0.75, 15, 15);
				
			glPopMatrix();
		}
		for(int k=0;k<3; k++){
			glPushMatrix();
				
				glRotatef((360/3)*k,0,1,0);
				glTranslatef (x1, y1, -z1);
				glRotatef(grados_pata,1,0,0);
				glColor3f(0,0,0);
				
				glutSolidCone (0.75,5, 15, 15);
				
			glPopMatrix();
		}
		
	}
	void aterrizando(){
		if(y<15){
			aterrizar=true;

		}
		else{
			aterrizar=false;
			
		}
		//~ if (tamanio_pata>=1 && tamanio_pata<=5){
		//~ tamanio_pata = 50/y;// el 5 es para cuadrar el crecimiento de la pata con el aterrizaje ya k la razon en unidades es de 1/5;
	}	
	
	void subeBaja(double velocidad){
	double min=7.8;
	
		if(y+velocidad*0.2>min/*esto solo para animacion por no perderlo de la pantalla*/){
			if(y>y+velocidad*0.2 && y<min*2){
				desplegar_patas(1);
			}
			else if(y<y+velocidad*0.2 && y>min*2){
				desplegar_patas(-1);
			}
		
		
			
				y+=velocidad*0.2;
			
		}
		//else{y=min;}
		
			
	}
	void translacion_x(double velocidad){
		rotando_z=true;
		if(velocidad > 0 && grados_z_ovni >= -24){
			grados_z_ovni+=-3;
			if(grados_z_ovni<=-24){
				grados_z_ovni=-24;
			}
		}
		else if(velocidad < 0 && grados_z_ovni <= 24){
			grados_z_ovni+=3;
			if(grados_z_ovni>=24){
				grados_z_ovni=24;
			}
		}
		x+=velocidad*1;

		
	}
	void translacion_z(double velocidad){
		rotando_x=true;
		if(velocidad < 0 && grados_x_ovni >= -24){
			grados_x_ovni+=-3;
			if(grados_x_ovni<=-24){
				grados_x_ovni=-24;
			}
		}
		else if(velocidad > 0 && grados_x_ovni <= 24){
			grados_x_ovni+=3;
			if(grados_x_ovni>=24){
				grados_x_ovni=24;
			}
		}
		z+=velocidad*1;

		
	}
	
	void draw_ovni(bool ajedrez1 = false){
///////
		giro_y_cuerpo += 15;
		if(!rotando_z){
			if(grados_z_ovni<0){
				grados_z_ovni++;
			}
			else if(grados_z_ovni>0){
				grados_z_ovni--;
			}
		}
		if(!rotando_x){
			if(grados_x_ovni<0){
				grados_x_ovni++;
			}
			else if(grados_x_ovni>0){
				grados_x_ovni--;
			}
		}


///////
		glPushMatrix();
			
			glTranslatef( x, y, z);
			glRotatef(grados_z_ovni,0,0,1);
			glRotatef(grados_x_ovni,1,0,0);
			glPushMatrix();
				glTranslatef(torreta_x, torreta_y, torreta_z);
				torreta->draw_objects_grises();
			glPopMatrix();
			glPushMatrix();
				
				glRotatef(giro_y_cuerpo,0,1,0);
				cuerpo->draw_objects_grises();
				cristal->draw_objects_cristal();
				esferas();
				
				
				
				
				
			glPopMatrix();
			aterrizando();
			glPushMatrix();
				if (!aterrizar){
					glRotatef(giro_y_cuerpo,0,1,0);
					
					draw_patas();
				}
				if(aterrizar){
					draw_patas();
					//no giran las patas y se escalan los conos
				}
			
			glPopMatrix();
		glPopMatrix();
		rotando_z=false;
		rotando_x=false;	
	}
	void miIdle(void){
		
		mov_cuerpo+= velocidad_cuerpo;
		mov_torreta+= velocidad_torreta;
		mov_patas+= velocidad_patas;
		mov_x+= velocidad_x;
				if(sin(mov_cuerpo*0.0174532925)>0){
						subeBaja(velocidad_cuerpo);
						
				}
				else if(sin((mov_cuerpo)*0.0174532925)<0){
						subeBaja(-velocidad_cuerpo);
						
				}
				//~ if(sin(mov_x*0.0374532925)>0){
						//~ translacion_x(velocidad_x);
				//~ }
				//~ else if(sin((mov_x)*0.0374532925)<0){
						//~ 
						//~ translacion_x(-velocidad_x);
				//~ }
				
				
				if(sin(mov_torreta*0.0174532925)>0){
						mover_torreta(velocidad_torreta);
				}
				else if(sin(mov_torreta*0.0174532925)<0){
						mover_torreta(-velocidad_torreta);
				}
				
				if(sin(mov_patas*0.0174532925)>0){
						desplegar_patas(velocidad_patas);
				}
				else if(sin((mov_patas)*0.0174532925)<0){
						desplegar_patas(-velocidad_patas);
				}
				
			
	}	
	void aumentaVelocidadTorreta(double velocidad=0.1){
		velocidad_torreta+=velocidad;
		
		
	}
	void aumentaVelocidadCuerpo(double velocidad=0.1){
		velocidad_cuerpo+=velocidad;
		
	}
	void aumentaVelocidadPatas(double velocidad=0.1){
		velocidad_patas+=velocidad;
		;
	}
	void aumentaVelocidadX(double velocidad=0.1){
		velocidad_x+=velocidad;
	}
};
ovni ovni1;

//vector<_vertex3f> puntillo;
//vector<GLint> puntillo;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*******************ESTRUCTURA DIBUJO********************************/




////////////////////////////////////////////////////////////////////////////////////////////////////////
/******************************************************************/

dibujo *CUBO;
dibujo *TETRAEDRO;
vector<dibujo*> dibujos;
vector<dibujo*> plys;
vector<dibujo*> perfiles;



/******************************************************************/



// tamaño de los ejes
const int AXIS_SIZE=5000;

// variables que definen la posicion de la camara en coordenadas polares
GLfloat Observer_distance;
GLfloat Observer_angle_x;
GLfloat Observer_angle_y;

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

	}	

}


void draw_scene(void)
{

clear_window();
change_observer();
draw_axis();
draw_light();
if(ply){
	if(modelo>plys.size()-1){modelo=0;}
	plys[modelo]->draw_objects(ajedrez);
}
if(revolucionado){
	if(modelo>perfiles.size()-1){modelo=0;}
	perfiles[modelo]->draw_objects(ajedrez);
}
if(jerarquico){


	ovni1.draw_ovni(ajedrez);
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
}

if(otros){
	if(modelo>dibujos.size()-1){modelo=0;}
	dibujos[modelo]->draw_objects(ajedrez);
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



//***************************************************************************
// Funcion llamada cuando se produce aprieta una tecla normal
//
// el evento manda a la funcion:
// codigo de la tecla
// posicion x del raton
// posicion y del raton
//***************************************************************************
void big_idle(int n){
	

	ovni1.miIdle();
	glutPostRedisplay();
	
	
	if (parar_animacion) return;
	glutTimerFunc(velocidad_animacion,big_idle,n);
	

}
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
		case '1':ply=true; revolucionado=false; jerarquico=false;otros = false;break;
		case '2':ply=false; revolucionado=true; jerarquico=false;otros = false;break;
		case '3':ply=false; revolucionado=false; jerarquico=true;otros = false;break;
		case '0':ply=false; revolucionado=false; jerarquico=false;otros = true;break;
		case '+':cambia_objeto(true);break;
		case '-':cambia_objeto(false);break;

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
Front_plane=5;
Back_plane=10000;

// se inicia la posicion del observador, en el eje z
Observer_distance=2*Front_plane;
Observer_angle_x=0;
Observer_angle_y=0;

// se indica cual sera el color para limpiar la ventana	(r,v,a,al)
// blanco=(1,1,1,1) rojo=(1,0,0,1), ...
glClearColor(0,0,0,1);

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
	pz=false;
	px=false;
	pc=false;
	pd=false;
	ph=false;
	pj=false;
	pk=false;
	pu=false;
	jerarquico = true;
	velocidad_animacion=50;
	vector<_vertex3f> Cubo;
	parar_animacion=false;
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
		
	dibujos.push_back(new dibujo(Cubo,Caras_cubo));
	
	perfiles.push_back(new dibujo(rectangulo,caras_rectangulo));
		perfiles[perfiles.size()-1]->revolucion();


plys.push_back(new dibujo("ant.ply"));
plys.push_back(new dibujo("beethoven.ply"));
plys.push_back(new dibujo("big_dodge.ply"));

//~ // se llama a la inicialización de glut
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
glutKeyboardUpFunc(normal_keysup);
// asignación de la funcion llamada "tecla_Especial" al evento correspondiente
glutSpecialFunc(special_keys);

// funcion de inicialización
initialize();
//glutIdleFunc(idle);

// inicio del bucle de eventos
glutMainLoop();
return 0;
}
