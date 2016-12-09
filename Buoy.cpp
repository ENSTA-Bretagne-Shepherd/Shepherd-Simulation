#include "sailboat.h"



#include <GL/gl.h>
#include <GL/glu.h>
extern double dt;


class Buoy 
{
    Buoy* b;
    public:
        void Lorenz(void);
        void Pendulum(void);
        void StateEq(void);
        void SetCommand(double ub);
        int GetNumber(void);
        double* GetPos(void);
        void Clock(void);
        Buoy(int nb, double xb, double yb, double zb, double ub);

    private:
        int n;
        double x;
        double y;
        double z;
        double u;
        double* Xdot;
};




Buoy::Buoy(int nb, double xb, double yb, double zb, double ub)
{    
    n = nb;
    x = xb;
    y = yb;
    z = zb;
    u = ub;
}



void Buoy::Lorenz(void)
{
    double sigma = 10.0; 
    double beta = 8.0/3.0; 
    double rho = 24.3;
    double k = 1.0;
    Xdot[0] = sigma*(y-x);
    Xdot[1] = x*(rho-z)-y;
    Xdot[2] = k*(x-y-beta*z)+u;
    
}


void Buoy::Pendulum(void)
{
    Xdot[0] = y;
    Xdot[1] = -sin(x);
    Xdot[2] = u;
}

void Buoy::StateEq(void)
{
    Xdot[0] = sin(0.001*(y+0.9*z));
    Xdot[1] = -sin(0.001*(x+z));
    Xdot[2] = u;
    
}


void Buoy::SetCommand(double ub)
{
    u = ub;
}



int Buoy::GetNumber(void)
{
    return n;
}


double* Buoy::GetPos(void)
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
    Lorenz();
    x = x+dt*Xdot[0];
    y = y+dt*Xdot[1];
    z = z+dt*Xdot[2];
    
}

