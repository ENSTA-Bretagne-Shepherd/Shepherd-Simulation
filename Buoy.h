#ifndef Buoy_H
#define Buoy_H

#include <math.h>


class Buoy
{    public:
            double x,y,z; // state variables
            double beta,sigma,rho,k; //parameters
            double xdot,ydot,zdot;  //link variables


            void Lorenz(void);
            void Pendulum(void);
            void StateEq(void);
            void SetCommand(double ub);
            int GetNumber(void);
            double* GetPos(void);
            void Clock(void);
            Buoy(int nb, double xb, double yb, double zb, double ub);
            
            //explicit Buoy ();
        //~Buoy();
 };

#endif // Buoy_H
