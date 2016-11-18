#include "sailboat.h"


#include <GL/gl.h>
#include <GL/glu.h>
extern double dt;


sailboat::sailboat()
{   x=0.0; y=0.0; theta =-3.0; v = 1; omega = 0.0;  phi = 0.5; phiPoint = 0;
    Jx = 3000.0; Jz = 10000.0; // moments d'inertie
    beta=0.1;  rg=2.0;  alphatheta=6000;  m=300.0;
    alphaf=1.0;  rv=1.0;  alphag=2000.0; l=1.0;  alphav=1000.0;
    a=2;
    psi=M_PI;  //vent
    eta = 16000;     hv = 4.00;  //Roulis
    ax=-1000;ay=-2000,bx=1000;by=2000;   //line with wind
    //ax=-1000;ay=0,bx=1000;by=0;   //line against wind
    q=1;
}

sailboat::~sailboat()
{
}

double sign(double a)
{if (a>0) return 1; else return -1;};

void sailboat::Controller()   //voir www.ensta-bretagne.fr/jaulin/polyrobots.pdf
{   double r=10;
    double zeta=M_PI/4;
    double e=((bx-ax)*(y-ay)-(x-ax)*(by-ay))/hypot(ax-bx,ay-by);
    if (fabs(e)>r) q=0;  //The robot is now free from its closed-hauled mode
    double phi=atan2(by-ay,bx-ax);
    double thetabar=phi-0.5*atan(e/r);
    if ((q==0)&((cos(psi-thetabar)+cos(zeta)<0)|((fabs(e)<r)&(cos(psi-phi)+cos(zeta)<0)))) q=sign(e);
    if (q!=0)  thetabar=M_PI+psi-zeta*q;
    double dtheta=theta-thetabar;
    deltag=(1/M_PI)*(atan(tan(0.5*dtheta)));
    deltavmax=0.5*M_PI*(0.5*(cos(psi-thetabar)+1));
    //qDebug()<<"q="<<q<<",   e="<<e;
}




void sailboat::Clock()  // The model is described in "L. Jaulin Mod�lisation et commande d'un bateau � voile, CIFA2004, Douz (Tunisie)"
{   Controller();
    double xw_ap=a*cos(psi-theta)-v;
    double yw_ap=a*sin(psi-theta);
    double psi_ap=atan2(yw_ap,xw_ap);   //Apparent wind
    double a_ap=sqrt(xw_ap*xw_ap+yw_ap*yw_ap);
    gamma=cos(psi_ap)+cos(deltavmax);
    if (gamma<0) {deltav=M_PI+psi_ap;} //voile en drapeau
    else  if (sin(-psi_ap)>0) deltav=deltavmax;   else deltav=-deltavmax;
    fg = alphag*v*sin(deltag);
    fv = alphav*a_ap*sin(deltav-psi_ap);
    x += (v*cos(theta)+beta*a*cos(psi))*dt;
    y += (v*sin(theta)+beta*a*sin(psi))*dt;
    theta += omega*dt;
    omega += (1/Jz)*((l-rv*cos(deltav))*fv-rg*cos(deltag)*fg-alphatheta*omega*v)*dt;
    v     += (1/m)*(sin(deltav)*fv-sin(deltag)*fg-alphaf*v*v)*dt;
    phiPoint += (-phiPoint+fv*hv*cos(deltav)*cos(phi)/Jx - 10000*9.81*sin(phi)/Jx)*dt ;
    phi += phiPoint * dt;
}