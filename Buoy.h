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
            
            inline Buoy (){x=0;y=0;z=-10;xdot=0;ydot=0;zdot=0;}
        //~Buoy();
 };

#endif // Buoy_H
