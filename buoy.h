#ifndef Buoy_H
#define Buoy_H

#include <math.h>

/**
 * Classe Buoy : la bouee
 */
class Buoy
{
    public:
        double x;//!State variables
        double y;//!State variables
        double z;//!State variables

        double beta;//!Parameter for Lorentz
        double sigma;//!Parameter for Lorentz
        double rho;//!Parameter for Lorentz
        double k;//!Parameter for Lorentz

        int n;//!Id de la bouee

        double u;
        double Xdot[3];

        /**
         * Equations cinematiques pour les attracteurs de Lorentz
         */
        void lorenz(void);

        /**
         * Equations cinematiques simple pour une oscillation verticale
         */
        void sinLine(void);
        void pendulum(void);
        void stateEq(void);

        /**
         * Setter for the command ub
         * @param ub
         */
        void setCommand(double ub);

        /**
         *
         * @return
         */
        int getNumber(void);
        double* getPos(void);
        void Clock(void);
        Buoy(int nb, double xb, double yb, double zb, double ub);

    inline Buoy (){x=0;y=0;z=-10;Xdot[0]=0;Xdot[1]=0;Xdot[2]=0;}
        //~Buoy();
 };

#endif // Buoy_H
