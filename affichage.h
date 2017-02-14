#ifndef WIDGETSIMU_H
#define WIDGETSIMU_H

#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <sys/types.h>
#include <sys/timeb.h>
#include <string.h>

#pragma once

class Buoy0
{
    public:
        double x;//!State variables
        double y;//!State variables
        double z;//!State variables
        
        double Xdot[3];//!Vecteur de vitesse de Buoy
        
        int n;        
        
        inline Buoy0(int nb, double xb, double yb, double zb, double ub){
    		n = nb;
    		x = xb;
    		y = yb;
    		z = zb;    
		}

    inline Buoy0 (){x=0;y=0;z=-10;Xdot[0]=0;Xdot[1]=0;Xdot[2]=0;}
};
 
 
 class Sailboat0
{	
	public:
	
            double x,y,theta,phi;
            
            double fg,fv,gamma,deltav,deltag,deltavmax;  //link variables
	 		double a,psi;  //wind
            
            
            double cx,cy;// centre du triangle
};
 


void DrawMer();

void DrawMesh();

void DrawCourant();

void DrawBouees(Buoy0 const&boue);

void DrawSailboat(Sailboat0 const&boat);



#endif // WIDGETSIMU_H
