#include <iostream>
#include "stdlib.h"
#include "stdio.h"
#include <GL/glut.h>
#include <ctype.h>
#include <vector>
#include <vertex.h>
#include "file_ply_stl.h"
#include "jpg_imagen.hpp"
#include "jpg_jinclude.h"

/**************************************************
 * estructura que permite asignar texturas a un objeto
 * 
 ****************************************************/

struct textura{
	
unsigned tamx,tamy;
unsigned char * texels;
  
	textura(char * nombre_archivo){
		jpg::Imagen * pimg = new jpg::Imagen(nombre_archivo);
		tamx = pimg->tamX(); // num. columnas (unsigned)
		tamy = pimg->tamY(); // num. filas (unsigned)
		texels = pimg->leerPixels(); // puntero texels (unsigned char * )
	}
	
	void static initialize_texturas(){
	    //Pegado sobre el polígono
	    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);
	    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);
	
	    //Filtros
	    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
	
	    glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_DECAL);// GL_MODULATE para que la iluminacion haga efecto.
	
	    //Activamos las texturas
	    glEnable(GL_TEXTURE_2D);
	}
};

/*******************************
 * 
 * ESTRUCTURA que contiene los datos de un modelo 3D
 * 
 *******************************/
struct dibujo{
	
	int const static lados_revolucion=50;
	int n_vertices;
	int n_caras;
	int aux_n_vertices;
	int aux_n_caras;
	GLfloat vertice_aux[3];// Para pasar vectores a las funciones que requieren que sean del tipo GLfloat
	textura * texturilla;// para asignar una tectura a un objeto
	int R, G, B; 
	
	vector<_vertex3f> vertices;//contiene los vertices del objeto3D
	vector<_vertex3f> normales_vertices;//contiene la normal de cada vertice con mismo indice
	vector<_vertex3f> aux_ver;  // para facilitar las copias y las transformaciones.
	
	vector<_vertex3i> caras;//contiene los trios de vertices que componen una cara
	vector<_vertex3f> normales_caras;//contiene la normal de cara cara, siendo esta la media de las normales de cada vertice que compone dicha cara.
	vector<_vertex3i> aux_car;  // para facilitar las copias y las transformaciones.
	
	vector<_vertex2f> text; //contiene las coordenadas de textura de cada vertice.
	
	/*********************************
	 * Constructor que recibe 2 vectores
	 * el primero contiene los vertices
	 * el segundo contiene las caras
	 *********************************/
	dibujo(vector<_vertex3f> ver, vector<_vertex3i> car){
		n_vertices=ver.size();
		n_caras = car.size();

		rellena_matrices(ver, car);
		calculaNormalesCaras();
	}
	/*********************************
	 * Constructor que recibe el nombre de un archivo ply
	 *********************************/
	dibujo(char * nombre_archivo){
		vector<float> vector_vertices ;
		vector<int> vector_caras;

		_file_ply ply;
		ply.open(nombre_archivo);
		ply.read(vector_vertices, vector_caras);

		for (int j = 0; j < vector_vertices.size(); j+=3){			
			_vertex3f vert;
			vert.x = vector_vertices[j] ;
			vert.y = vector_vertices[j+1] ;
			vert.z = vector_vertices[j+2] ;

			vertices.push_back(vert);
		}
		for (int j = 0; j < vector_caras.size(); j+=3){
			_vertex3i triangulo;
			triangulo._0 = vector_caras[j] ;
			triangulo._1 = vector_caras[j+1] ;
			triangulo._2 = vector_caras[j+2] ;

			caras.push_back(triangulo);
		}
		
		calculaNormalesCaras();
}
/*********************************
 * funcion que se encarga de asignar una textura al objeto3D
 ********************************/
void settexturilla(char * jpg){
	texturilla = new textura(jpg);
}
/*********************************
 * constructor que recibe un archivo ply y una textura
 ********************************/
dibujo(char * nombre_archivo,char * jpg){
		vector<float> vector_vertices ;
		vector<int> vector_caras;
		texturilla = new textura(jpg);
		_file_ply ply;
		ply.open(nombre_archivo);
		ply.read(vector_vertices, vector_caras);

		for (int j = 0; j < vector_vertices.size(); j+=3){	   //	
			_vertex3f vert;                                    //
			vert.x = vector_vertices[j] ;                      //
			vert.y = vector_vertices[j+1] ;
			vert.z = vector_vertices[j+2] ;

			vertices.push_back(vert);
		}
		for (int j = 0; j < vector_caras.size(); j+=3){
			_vertex3i triangulo;
			triangulo._0 = vector_caras[j] ;
			triangulo._1 = vector_caras[j+1] ;
			triangulo._2 = vector_caras[j+2] ;

			caras.push_back(triangulo);
		}
		calculaNormalesCaras();
}
void SetColor( int r, int g, int b){
	R=r;
	G=g;
	B=b;
}

void rellena_matrices(vector<_vertex3f> ver, vector<_vertex3i> car){
		//creacion de la matriz de vertices		
			for (int i = 0; i<n_vertices;i++){
				vertices.push_back(ver[i]);
			}
		//creacion de la matriz de caras
			for (int i = 0; i<n_caras;i++){
				caras.push_back(car[i]);
			}
	}
	



/*********************************************************************
 * MATERIALES
 * ESPECIFICACION DE MATERIALES
 ********************************************************************/	
void material() {

  GLfloat color_ambiente[]   = {1, 0.5, 0.5, 1};
  GLfloat color_difuso[]     = {0.5, 0.5, 0.5, 0.5};
  GLfloat color_especular[]  = {0.5, 0.5, 0.5, 0.5};
  GLfloat brillo_especular[] = {5.0};

  glMaterialfv(GL_FRONT, GL_AMBIENT,   color_ambiente);
  glMaterialfv(GL_FRONT, GL_DIFFUSE,   color_difuso);
  glMaterialfv(GL_FRONT, GL_SPECULAR,  color_especular);
  glMaterialfv(GL_FRONT, GL_SHININESS, brillo_especular);
}
void material_negro_specular() {

  GLfloat color_ambiente[]   = {0, 0, 0, 1};
  GLfloat color_difuso[]     = {0.5, 0.5, 0.5, 0.1};
  GLfloat color_especular[]  = {1, 1, 1, 1};
  GLfloat brillo_especular[] = {10.0};

  glMaterialfv(GL_FRONT, GL_AMBIENT,   color_ambiente);
  glMaterialfv(GL_FRONT, GL_DIFFUSE,   color_difuso);
  glMaterialfv(GL_FRONT, GL_SPECULAR,  color_especular);
  glMaterialfv(GL_FRONT, GL_SHININESS, brillo_especular);
}
void material_blanco_difuso() {

  GLfloat color_ambiente[]   = {0.5, 0.5,0.5, 1};
  GLfloat color_difuso[]     = {0.9,0.9,0.9,1};
  GLfloat color_especular[]  = {0,0,0};
  GLfloat brillo_especular[] = {0};

  glMaterialfv(GL_FRONT, GL_AMBIENT,   color_ambiente);
  glMaterialfv(GL_FRONT, GL_DIFFUSE,   color_difuso);
  glMaterialfv(GL_FRONT, GL_SPECULAR,  color_especular);
  glMaterialfv(GL_FRONT, GL_SHININESS, brillo_especular);
}
void material_rojo_specular() {

  GLfloat color_ambiente[]   = {1, 0,0, 1};
  GLfloat color_difuso[]     = {1, 0,0, 1};
  GLfloat color_especular[]  = {1, 1,1, 1};
  GLfloat brillo_especular[] = {10};

  glMaterialfv(GL_FRONT, GL_AMBIENT,   color_ambiente);
  glMaterialfv(GL_FRONT, GL_DIFFUSE,   color_difuso);
  glMaterialfv(GL_FRONT, GL_SPECULAR,  color_especular);
  glMaterialfv(GL_FRONT, GL_SHININESS, brillo_especular);
}
void material_gris_specular() {

  GLfloat color_ambiente[]   = {0.5, 0.5,0.5, 1};
  GLfloat color_difuso[]     = {0.5, 0.5,0.5, 1};
  GLfloat color_especular[]  = {1, 1,1, 1};
  GLfloat brillo_especular[] = {10};

  glMaterialfv(GL_FRONT, GL_AMBIENT,   color_ambiente);
  glMaterialfv(GL_FRONT, GL_DIFFUSE,   color_difuso);
  glMaterialfv(GL_FRONT, GL_SPECULAR,  color_especular);
  glMaterialfv(GL_FRONT, GL_SHININESS, brillo_especular);
}

/***********************************
 * NORMALES para la iluminacion
 **********************************/	
void calculaNormalesVertices(){
		_vertex3f ceros(0.0,0.0,0.0);
		for(int i=0; i<vertices.size();i++){
			normales_vertices.push_back(ceros);
		}
		
		for (int i = 0; i < caras.size();i++){
			int aux1=caras[i][0];
			int aux2=caras[i][1];
			int aux3=caras[i][2];
			
			normales_vertices[aux1]+=normales_caras[i];
			normales_vertices[aux2]+=normales_caras[i];
			normales_vertices[aux3]+=normales_caras[i];
			
		}
		for(int i=0;i<normales_vertices.size();i++){
			normales_vertices[i].normalize();
		}
	}
	
void calculaNormalesCaras(){
	_vertex3f vector1;
	_vertex3f vector2;
	
	for (int i = 0; i < caras.size();i++){
		vector1 = (vertices[caras[i][0]] - vertices[caras[i][1]]);
		vector2 = (vertices[caras[i][0]] - vertices[caras[i][2]]);
		vector2 = vector1.cross_product(vector2);
		vector2.normalize();
		normales_caras.push_back(vector2);
	}
	calculaNormalesVertices();
}
	

	
void revolucion(int puntos_ini=0, int puntos_rev=lados_revolucion){
	// creamos los vertices por revolucion (y nos faltara introducir el primer y el ul"timo punto que se colocan en el eje y.
	for(int k=0;k<vertices.size();k++){
		for (int i = 0; i<=puntos_rev-1;i++){
			_vertex2f vert;
			vert.x = i/(puntos_rev-1);
			if(text.size()==0){
				vert.y =0  ;
			}else{
				vert.y = k/(vertices.size()-1);//text[text.size()-1].y 
			}	
			text.push_back(vert);
			aux_ver.push_back({(vertices[k][0]*(cos((2*M_PI/(puntos_rev-1))*i))+vertices[k][2]*(sin((2*M_PI/(puntos_rev-1))*i))),
				 vertices[k][1],
				 ((-vertices[k][0]*(sin((2*M_PI/(puntos_rev-1))*i))+vertices[k][2]*(cos((2*M_PI/(puntos_rev-1))*i))))});	
		}
		
	}

	for (int i = 0; i<(vertices.size())-1 ; i++){		
		for(int j=0;j<puntos_rev-1;j++){
			aux_car.push_back({j+i*puntos_rev,j+1+(1+i)*puntos_rev,j+(i+1)*puntos_rev});
			aux_car.push_back({j+i*puntos_rev,j+1+(i*puntos_rev),j+1+((1+i)*puntos_rev)});
		}
	}
	//TAPAS
	aux_ver.push_back({0,aux_ver[0].y,0});
	aux_ver.push_back({0,aux_ver[aux_ver.size()-2].y,0});
	for(int i = 0; i<puntos_rev-1 ; i++){
		aux_car.push_back({aux_ver.size()-2, i, i+1});
	}
	for(int i = 1; i<puntos_rev ; i++){
		aux_car.push_back({aux_ver.size()-1, (puntos_rev*vertices.size())-i, (puntos_rev*vertices.size())-(i+1)});
	}
	vertices=aux_ver;
	caras=aux_car;
	
	n_vertices=vertices.size();
	n_caras=caras.size();
	normales_caras.clear();
	normales_vertices.clear();
	calculaNormalesCaras();	
}

//PINTAR EL OBJETO DEL COLOR PASADO CON setcolor()
void draw_objects_color(double trans_x=0,double trans_y=0,double trans_z=0){
	glColor3f(R,G,B);
	glPointSize(4);
	glPushMatrix();
		glTranslatef( trans_x, trans_y, trans_z );
		glBegin(GL_TRIANGLES);
			for (int i=0;i<caras.size();i++){
				for(int j=0;j<3;j++){
				vertice_aux[0]=vertices[caras[i][j]][0];
				vertice_aux[1]=vertices[caras[i][j]][1];
				vertice_aux[2]=vertices[caras[i][j]][2];
				glVertex3fv(vertice_aux);
				}
			}		
		glEnd();
	glPopMatrix();	
}

void draw_objects(bool ajedrez=false, double trans_x=0,double trans_y=0,double trans_z=0){
	glColor3f(148,0,128);
	glPointSize(4);
	glPushMatrix();
		glTranslatef( trans_x, trans_y, trans_z );
		glBegin(GL_TRIANGLES);	
			for (int i=0;i<caras.size();i++){
				if (ajedrez){
					if (i%2 ==0){glColor3ub(0,255,0);}
					else{glColor3ub(148,0,128);}
				}
				for(int j=0;j<3;j++){
				vertice_aux[0]=vertices[caras[i][j]][0];
				vertice_aux[1]=vertices[caras[i][j]][1];
				vertice_aux[2]=vertices[caras[i][j]][2];
				glVertex3fv(vertice_aux);
				}
			}
		glEnd();
	glPopMatrix();	
}
//FUNCION PARA PONER LA TEXTURA A UN OBJETO REVOLUCIONADO, SIN TERMINAR
void draw_textura_revolucion(bool ajedrez=false, double trans_x=0,double trans_y=0,double trans_z=0){
	glEnable(GL_TEXTURE_2D);
	glTexImage2D(GL_TEXTURE_2D,0,3,texturilla->tamx, texturilla->tamy,
0,GL_RGB,GL_UNSIGNED_BYTE,texturilla->texels);
	  glPolygonMode (GL_FRONT, GL_FILL);
  glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE) ;

  glShadeModel  (GL_SMOOTH);
  glDepthFunc   (GL_LEQUAL);
  glEnable      (GL_DEPTH_TEST);
  glEnable      (GL_NORMALIZE);

   glClearColor(1, 1, 1, 1.0);
	glPushMatrix();
	glTranslatef( trans_x, trans_y, trans_z );
	material();
	glBegin(GL_TRIANGLES);
	int texx,texy;
		for (int i=0;i<caras.size();i++){
			for(int j=0;j<3;j++){
			vertice_aux[0]=normales_vertices[caras[i][j]][0];
			vertice_aux[1]=normales_vertices[caras[i][j]][1];
			vertice_aux[2]=normales_vertices[caras[i][j]][2];
			glNormal3fv(vertice_aux);
			
			glTexCoord2f(0,0);
			vertice_aux[0]=vertices[caras[i][j]][0];
			vertice_aux[1]=vertices[caras[i][j]][1];
			vertice_aux[2]=vertices[caras[i][j]][2];
			glVertex3fv(vertice_aux);
			}
		}
		
		glEnd();
		glDisable(GL_TEXTURE_2D);
	glPopMatrix();	
}
/**************************************
 * 
 * SUAVIZADO PLANO
 * 
 *************************************/
void draw_objects_plano(bool ajedrez=false, double trans_x=0,double trans_y=0,double trans_z=0){
	glPushMatrix();
		glTranslatef( trans_x, trans_y, trans_z );
		glShadeModel  (GL_FLAT);//plano
		glBegin(GL_TRIANGLES);
			for (int i=0;i<caras.size();i++){
				vertice_aux[0]=normales_caras[i][0];
				vertice_aux[1]=normales_caras[i][1];
				vertice_aux[2]=normales_caras[i][2];
				glNormal3fv(vertice_aux);
				for(int j=0;j<3;j++){
					
					vertice_aux[0]=vertices[caras[i][j]][0];
					vertice_aux[1]=vertices[caras[i][j]][1];
					vertice_aux[2]=vertices[caras[i][j]][2];
					glVertex3fv(vertice_aux);
				}
			}
		glEnd();
	glPopMatrix();	
}
/*************************************************
 * 
 * SUAVIZADO SUAVE
 * 
 *************************************************/
void draw_objects_suave(bool ajedrez=false, double trans_x=0,double trans_y=0,double trans_z=0){
	glPolygonMode (GL_FRONT, GL_FILL);
	glShadeModel  (GL_SMOOTH);//suave
	glDepthFunc   (GL_LEQUAL);
	glEnable      (GL_DEPTH_TEST);
	glEnable      (GL_NORMALIZE);
	
	glClearColor(1, 1, 1, 1.0);// CREO recordar que esto era para poner blanco el color de fondo
	glPushMatrix();
		glTranslatef( trans_x, trans_y, trans_z );
		material();
		glBegin(GL_TRIANGLES);
			for (int i=0;i<caras.size();i++){
				for(int j=0;j<3;j++){
				vertice_aux[0]=normales_vertices[caras[i][j]][0];
				vertice_aux[1]=normales_vertices[caras[i][j]][1];
				vertice_aux[2]=normales_vertices[caras[i][j]][2];
				glNormal3fv(vertice_aux);
				
				vertice_aux[0]=vertices[caras[i][j]][0];
				vertice_aux[1]=vertices[caras[i][j]][1];
				vertice_aux[2]=vertices[caras[i][j]][2];
				glVertex3fv(vertice_aux);
				}
			}
			
		glEnd();
			
	glPopMatrix();	
}
void draw_objects_suave_negro(bool ajedrez=false, double trans_x=0,double trans_y=0,double trans_z=0){
	glPolygonMode (GL_FRONT, GL_FILL);
  

	glShadeModel  (GL_SMOOTH);
	glDepthFunc   (GL_LEQUAL);
	glEnable      (GL_DEPTH_TEST);
	glEnable      (GL_NORMALIZE);

	glClearColor(1, 1, 1, 1.0);
	glPushMatrix();
		glTranslatef( trans_x, trans_y, trans_z );
		material_negro_specular();
		glBegin(GL_TRIANGLES);
			for (int i=0;i<caras.size();i++){
			
				for(int j=0;j<3;j++){
					vertice_aux[0]=normales_vertices[caras[i][j]][0];
					vertice_aux[1]=normales_vertices[caras[i][j]][1];
					vertice_aux[2]=normales_vertices[caras[i][j]][2];
					glNormal3fv(vertice_aux);
					
					vertice_aux[0]=vertices[caras[i][j]][0];
					vertice_aux[1]=vertices[caras[i][j]][1];
					vertice_aux[2]=vertices[caras[i][j]][2];
					glVertex3fv(vertice_aux);
				}
			}
		glEnd();
glPopMatrix();	
}

void draw_objects_suave_blanco(bool ajedrez=false, double trans_x=0,double trans_y=0,double trans_z=0){	
	glPolygonMode (GL_FRONT, GL_FILL);
	glShadeModel  (GL_SMOOTH);
	glDepthFunc   (GL_LEQUAL);
	glEnable      (GL_DEPTH_TEST);
	glEnable      (GL_NORMALIZE);

	glClearColor(1, 1, 1, 1.0);
	glPushMatrix();
		glTranslatef( trans_x, trans_y, trans_z );
		material_blanco_difuso();
		glBegin(GL_TRIANGLES);
			for (int i=0;i<caras.size();i++){
				
				for(int j=0;j<3;j++){
					vertice_aux[0]=normales_vertices[caras[i][j]][0];
					vertice_aux[1]=normales_vertices[caras[i][j]][1];
					vertice_aux[2]=normales_vertices[caras[i][j]][2];
					glNormal3fv(vertice_aux);
					
					vertice_aux[0]=vertices[caras[i][j]][0];
					vertice_aux[1]=vertices[caras[i][j]][1];
					vertice_aux[2]=vertices[caras[i][j]][2];
					glVertex3fv(vertice_aux);
				}
			}
		glEnd();
		
glPopMatrix();	
}

void draw_objects_grises(double trans_x=0,double trans_y=0,double trans_z=0){
	glColor3f(0.25,0.25,0.25);
	glPointSize(4);
	bool ajedrez = true; 
	glPushMatrix();
	glTranslatef( trans_x, trans_y, trans_z );
		glBegin(GL_TRIANGLES);
			for (int i=0;i<caras.size();i++){
				if (ajedrez){
					if (i%2 ==0){glColor3f(0.75,0.75,0.75);}
					else{glColor3f(0.25,0.25,0.25);}
				}
				for(int j=0;j<3;j++){
					vertice_aux[0]=vertices[caras[i][j]][0];
					vertice_aux[1]=vertices[caras[i][j]][1];
					vertice_aux[2]=vertices[caras[i][j]][2];
					glVertex3fv(vertice_aux);
				}
			}
		glEnd();		
	glPopMatrix();	
}
void draw_objects_suave_rojo_metalico(bool ajedrez=false, double trans_x=0,double trans_y=0,double trans_z=0){
	glPolygonMode (GL_FRONT, GL_FILL);
	glShadeModel  (GL_SMOOTH);
	glDepthFunc   (GL_LEQUAL);
	glEnable      (GL_DEPTH_TEST);
	glEnable      (GL_NORMALIZE);

	glClearColor(1, 1, 1, 1.0);
	glPushMatrix();
		glTranslatef( trans_x, trans_y, trans_z );
		material_rojo_specular();
		glBegin(GL_TRIANGLES);
			for (int i=0;i<caras.size();i++){
				
				for(int j=0;j<3;j++){
					vertice_aux[0]=normales_vertices[caras[i][j]][0];
					vertice_aux[1]=normales_vertices[caras[i][j]][1];
					vertice_aux[2]=normales_vertices[caras[i][j]][2];
					glNormal3fv(vertice_aux);
					
					vertice_aux[0]=vertices[caras[i][j]][0];
					vertice_aux[1]=vertices[caras[i][j]][1];
					vertice_aux[2]=vertices[caras[i][j]][2];
					glVertex3fv(vertice_aux);
				}
			}
		glEnd();	
	glPopMatrix();	
}	
void draw_objects_suave_gris_metalico(bool ajedrez=false, double trans_x=0,double trans_y=0,double trans_z=0){
	glPolygonMode (GL_FRONT, GL_FILL);
	glShadeModel  (GL_SMOOTH);
	glDepthFunc   (GL_LEQUAL);
	glEnable      (GL_DEPTH_TEST);
	glEnable      (GL_NORMALIZE);

	glClearColor(1, 1, 1, 1.0);
	glPushMatrix();
	glTranslatef( trans_x, trans_y, trans_z );
	material_gris_specular();
	glBegin(GL_TRIANGLES);
		for (int i=0;i<caras.size();i++){	
			for(int j=0;j<3;j++){
			vertice_aux[0]=normales_vertices[caras[i][j]][0];
			vertice_aux[1]=normales_vertices[caras[i][j]][1];
			vertice_aux[2]=normales_vertices[caras[i][j]][2];
			glNormal3fv(vertice_aux);
			
			vertice_aux[0]=vertices[caras[i][j]][0];
			vertice_aux[1]=vertices[caras[i][j]][1];
			vertice_aux[2]=vertices[caras[i][j]][2];
			glVertex3fv(vertice_aux);
			}
		}
		glEnd();
glPopMatrix();	
}	

void draw_objects_cristal(bool ajedrez=false,double transparencia=0.5, double trans_x=0,double trans_y=0,double trans_z=0){
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glColor4f(1.0,1.0,0.0,transparencia);
	glPointSize(4);
	glPushMatrix();
glTranslatef( trans_x, trans_y, trans_z );
	glBegin(GL_TRIANGLES);
		for (int i=0;i<caras.size();i++){
			if (ajedrez){
				if (i%2 ==0){glColor3f(0,255,0);}
				else{glColor3f(148,0,128);}
			}
			for(int j=0;j<3;j++){
			vertice_aux[0]=vertices[caras[i][j]][0];
			vertice_aux[1]=vertices[caras[i][j]][1];
			vertice_aux[2]=vertices[caras[i][j]][2];
			glVertex3fv(vertice_aux);
			}
		}
		
		glEnd();
		
		glDisable(GL_BLEND);
glPopMatrix();	
}	

void draw_suavizado_plano(double trans_x=0,double trans_y=0,double trans_z=0){
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glColor3f(1.0,1.0,0.0);
	glPointSize(4);
	glPushMatrix();
	glTranslatef( trans_x, trans_y, trans_z );

	glBegin(GL_TRIANGLES);
		for (int l=0;l<caras.size();l++){

			
			for(int j=0;j<3;j++){
			vertice_aux[0]=vertices[caras[l][j]][0];
			vertice_aux[1]=vertices[caras[l][j]][1];
			vertice_aux[2]=vertices[caras[l][j]][2];
			glVertex3fv(vertice_aux);
			}
		}
		
		glEnd();
		
		glDisable(GL_BLEND);
glPopMatrix();	
}

//
void draw_textura_cubo(bool ajedrez=false, double trans_x=0,double trans_y=0,double trans_z=0){
	glEnable(GL_TEXTURE_2D);
	glTexImage2D(GL_TEXTURE_2D,0,3,texturilla->tamx, texturilla->tamy,
0,GL_RGB,GL_UNSIGNED_BYTE,texturilla->texels);
	  glPolygonMode (GL_FRONT, GL_FILL);
  glShadeModel  (GL_SMOOTH);
  glDepthFunc   (GL_LEQUAL);
  glEnable      (GL_DEPTH_TEST);
  glEnable      (GL_NORMALIZE);

   glClearColor(1, 1, 1, 1.0);
	glPushMatrix();
	glTranslatef( trans_x, trans_y, trans_z );
	material();
	glBegin(GL_TRIANGLES);
	int texx,texy;
			vertice_aux[0]=normales_vertices[caras[0][0]][0];
			vertice_aux[1]=normales_vertices[caras[0][1]][1];
			vertice_aux[2]=normales_vertices[caras[0][2]][2];
			glNormal3fv(vertice_aux);
			
			glTexCoord2f(0,1);
			vertice_aux[0]=vertices[caras[0][0]][0];
			vertice_aux[1]=vertices[caras[0][1]][1];
			vertice_aux[2]=vertices[caras[0][2]][2];
			glVertex3fv(vertice_aux);
		
			vertice_aux[0]=normales_vertices[caras[2][0]][0];
			vertice_aux[1]=normales_vertices[caras[2][1]][1];
			vertice_aux[2]=normales_vertices[caras[2][2]][2];
			glNormal3fv(vertice_aux);
			
			glTexCoord2f(1,0);
			vertice_aux[0]=vertices[caras[2][0]][0];
			vertice_aux[1]=vertices[caras[2][1]][1];
			vertice_aux[2]=vertices[caras[2][2]][2];
			glVertex3fv(vertice_aux);
			
			vertice_aux[0]=normales_vertices[caras[1][0]][0];
			vertice_aux[1]=normales_vertices[caras[1][1]][1];
			vertice_aux[2]=normales_vertices[caras[1][2]][2];
			glNormal3fv(vertice_aux);
			
			glTexCoord2f(1,1);
			vertice_aux[0]=vertices[caras[1][0]][0];
			vertice_aux[1]=vertices[caras[1][1]][1];
			vertice_aux[2]=vertices[caras[1][2]][2];
			glVertex3fv(vertice_aux);
		
		
		glEnd();
		glDisable(GL_TEXTURE_2D);
glPopMatrix();	

}	
};
