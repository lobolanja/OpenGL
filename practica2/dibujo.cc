#include <iostream>
#include "stdlib.h"
#include "stdio.h"
#include <GL/glut.h>
#include <ctype.h>
#include <vector>
#include <vertex.h>
#include "file_ply_stl.h"

struct dibujo{
	
	int n_vertices;
	int n_caras;
	int aux_n_vertices;
	int aux_n_caras;
	GLfloat vertice_aux[3];

	
	vector<_vertex3f > vertices;
	vector<_vertex3f > aux_ver;  // para facilitar las copias y las transformaciones.
	
	vector<_vertex3i> caras;
	vector<_vertex3i> aux_car;  // para facilitar las copias y las transformaciones.
	
	dibujo(vector<_vertex3f> ver, vector<_vertex3i> car){
		n_vertices=ver.size();
		cout << "numero de vertices" << n_vertices<< endl;
		n_caras = car.size();
		cout << "numero de caras" << n_caras<< endl;
		//verticesss.push_back({0,0,0});
		rellena_matrices(ver, car);
	}
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
}
	
	void rellena_matrices(vector<_vertex3f> ver, vector<_vertex3i> car){
		//creacion de la matriz de vertices
		
			for (int i = 0; i<n_vertices;i++){
				
				cout << "metememos vertices "  << i << endl;
				vertices.push_back(ver[i]);
				
			}
		//creacion de la matriz de caras
			for (int i = 0; i<n_caras;i++){
				
				caras.push_back(car[i]);
			}
	}
	
	
	void revolucion(int puntos_ini=0, int puntos_rev=50){
		//if(plano){...meter lo siguiente}
		cout<< "empezamos revolucion" << endl;
		// creamos los vertices por revolucion (y nos faltara introducir el primer y el ul"timo punto que se colocan en el eje y.
		for(int k=0;k<vertices.size();k++){
			for (int i = 0; i<=puntos_rev-1;i++){
				
				aux_ver.push_back({(vertices[k][0]*(cos((2*M_PI/(puntos_rev-1))*i))+vertices[k][2]*(sin((2*M_PI/(puntos_rev-1))*i))),
					 vertices[k][1],
					 ((-vertices[k][0]*(sin((2*M_PI/(puntos_rev-1))*i))+vertices[k][2]*(cos((2*M_PI/(puntos_rev-1))*i))))});
				
							}
			
		}

		for (int i = 0; i<(vertices.size())-1 ; i++){		
			for(int j=0;j<puntos_rev-1;j++){
					
				aux_car.push_back({j+i*puntos_rev,j+1+(1+i)*puntos_rev,j+(i+1)*puntos_rev});
				cout << aux_car.size() << "     "<< j+i*puntos_rev << "  " << j+1+(1+i)*puntos_rev << "  " << j+(i+1)*puntos_rev<< endl;
					
				aux_car.push_back({j+i*puntos_rev,j+1+(i*puntos_rev),j+1+((1+i)*puntos_rev)});
				cout << aux_car.size()  << "     "<< j+i*puntos_rev << "  " << j+1+(i*puntos_rev) << "  " << j+1+((1+i)*puntos_rev) << endl;
				
			}
		}
		//TAPAS
		aux_ver.push_back({0,aux_ver[0].y,0});
		aux_ver.push_back({0,aux_ver[aux_ver.size()-2].y,0});
		for(int i = 0; i<puntos_rev-1 ; i++){
			aux_car.push_back({aux_ver.size()-2, i, i+1});
		}
		for(int i = 1; i<puntos_rev ; i++){
			cout << "tapa superior; " << aux_ver.size()-1 << "    " << (puntos_rev*vertices.size())-i << "    " << (puntos_rev*vertices.size())-(i+1) << endl;
			aux_car.push_back({aux_ver.size()-1, (puntos_rev*vertices.size())-i, (puntos_rev*vertices.size())-(i+1)});
		}
		
		vertices=aux_ver;
		caras=aux_car;
		cout << "numero de vertices: " << vertices.size() << endl << "numero de caras: " << caras.size() << endl;
		n_vertices=vertices.size();
		n_caras=caras.size();
			
	}

	void barrido(){
		double vector[3];
		cout << " Introduxca la cordenada x del vector de barrido: ";
		cin >> vector[0];
		cout << endl << " Introduxca la cordenada y del vector de barrido: ";
		cin >> vector[1];
		cout << endl << " Introduxca la cordenada z del vector de barrido: ";
		cin >> vector[2];
		cout << endl;
		int vertices_ini = vertices.size();
		for(int k=0;k<vertices_ini;k++){
				cout << "metemos : " <<vertices[k][0]+vector[0] <<"    " << vertices[k][1]+vector[1] <<"    "<< vertices[k][1]+vector[2] << endl;
				vertices.push_back({vertices[k][0]+vector[0], vertices[k][1]+vector[1],vertices[k][1]+vector[2]});
				
		}
			
		
	
		for(int j=0;j < vertices_ini;j++){
					cout << "caras : " <<j <<"    "<< j+1 <<"    "<< j+vertices_ini << endl;
			aux_car.push_back({j,j+1,j+vertices_ini});
					
			aux_car.push_back({j+1,j+1+vertices_ini,j+vertices_ini});
				
		}
		caras=aux_car;
		cout << "numero de vertices: " << vertices.size() << endl << "numero de caras: " << caras.size() << endl;
		n_vertices=vertices.size();
		n_caras=caras.size();
		
	}

	void draw_objects(bool ajedrez=false){
	glColor3f(148,0,128);
	glPointSize(4);
glRotatef( M_PI/4, 0.0f, 1.0f, 0.0f );
//~ glTranslatef ( 1, 5, -5 );

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
		
	
}	
		
		
		
		
};
