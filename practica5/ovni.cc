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
 struct ovni{    
	bool aterrizar;	
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
	}
	void aumentaVelocidadX(double velocidad=0.1){
		velocidad_x+=velocidad;
	}
};
