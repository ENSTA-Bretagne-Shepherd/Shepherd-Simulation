#include "sailboat.h"
#include "buoy.h"
#include <stdio.h>

#include <GL/gl.h>
#include <GL/glu.h>

extern double dt;
extern double simuTime;

Buoy::Buoy(int nb, double xb, double yb, double zb, double ub)
{    
    n = nb;
    x = xb;
    y = yb;
    z = zb;
    u = ub;
}

void Buoy::lorenz(void)
{
    double sigma = 10.0; 
    double beta = 8.0/3.0; 
    double rho = 24.3;
    double k = 1.0;
    Xdot[0] = sigma*(y-x);
    Xdot[1] = x*(rho-z)-y;
    Xdot[2] = k*(x-y-beta*z)+u;
}

void Buoy::sinLine(void)
{
    double depth = 40; // m
    double freq = 0.05; // Hz
    double speed = 10;  // m/s
    Xdot[0] = 0;      //X
    Xdot[1] = 0;      //Y
    Xdot[2] = speed*sin(2*M_PI*simuTime*freq); //Z
}

void Buoy::pendulum(void)
{
    Xdot[0] = y;
    Xdot[1] = -sin(x);
    Xdot[2] = u;
}

void Buoy::stateEq(void)
{
    Xdot[0] = sin(0.001*(y+0.9*z));
    Xdot[1] = -sin(0.001*(x+z));
    Xdot[2] = u;
    
}


void Buoy::setCommand(double ub)
{
    u = ub;
}



int Buoy::getNumber(void)
{
    return n;
}


double* Buoy::getPos(void)
{
    double* xd = new double[4];
    xd[0] = sqrt(pow(Xdot[0],2.0)+pow(Xdot[1],2.0)+pow(Xdot[2],2.0));
    xd[1] = x;
    xd[2] = y;
    xd[3] = z;
    return xd;
}

void Buoy::Clock(void)  // The model is described in "L. Jaulin Modélisation et commande d'un bateau à voile, CIFA2004, Douz (Tunisie)"
{
    sinLine();
    x = x+dt*Xdot[0];
    y = y+dt*Xdot[1];
    z = z+dt*Xdot[2];

    printf("State : %f %f %f \n",x,y,z);
    fflush(stdout);
}

