#ifndef sailboat_H
#define sailboat_H

#include <math.h>


class sailboat
{    public:
            double x,y,theta,v,omega,phi,phiPoint; // state variables
            double beta, Jz, rg, rv, alphag, alphav, alphaf, alphatheta, l,m, Jx; //parameters
            double a,psi;  //wind
            double fg,fv,gamma,deltav,deltag,deltavmax;  //link variables
            double eta;//viscosité
            double hv; // hauteur de centre de poussée

            int q;
            double cx,cy;// centre du triangle
            int iseg;// numero du segment

            void Clock();
            void Controller();
            explicit sailboat();
        ~sailboat();
 };

#endif // sailboat_H
