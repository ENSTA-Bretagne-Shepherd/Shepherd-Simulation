#include "affichage.h"
#include "stdio.h"

#include <GL/gl.h>
#include <GL/glu.h>

#include "config.h"

extern double dt;





/************************/
/*   dessin de la sc�ne */
/************************/




void DrawMer()
{   

	glEnable(GL_BLEND);
	glDisable(GL_DEPTH_TEST);
	int k,j;
	
		
	glBegin(GL_POLYGON);
       glColor4f(0.1,0.1,0.5,0.5);
       glVertex3f(-100000,-100000,-2000);
       glVertex3f(100000,-100000,-2000);
       glVertex3f(100000,100000,-2000);
       glVertex3f(-100000,100000,-2000);
    glEnd();
    
    
    glBegin(GL_LINES);
    glColor4f(0,0,0,0.5);
    for(k=-10;k<10;k++){
        glVertex3f(k*1000,10000,-1999);
        glVertex3f(k*1000,-10000,-1999);
           		
         glVertex3f(10000,k*1000,-1999);
        glVertex3f(-10000,k*1000,-1999);        
    }
    glEnd();
    
    
    glBegin(GL_POLYGON);
       glColor4f(0.1,0.1,0.5,0.5);
       glVertex3f(-100000,-100000,0);
       glVertex3f(100000,-100000,0);
       glVertex3f(100000,100000,0);
       glVertex3f(-100000,100000,0);
    glEnd();
    
    
        
    glBegin(GL_LINES);
	glColor4f(0,0,0,1);
	for(k=-10;k<10;k++){
           	
        glVertex3f(k*1000,10000,1);
        glVertex3f(k*1000,-10000,1);
           		
        glVertex3f(10000,k*1000,1);
        glVertex3f(-10000,k*1000,1); 
    }
    glEnd();
       
    glEnable(GL_DEPTH_TEST);
	glDisable(GL_BLEND);
}


void DrawBouees(Buoy0 const&boue){   
    	glPushMatrix();
    	
    	glTranslatef(boue.x,boue.y, boue.z);
        glColor3f(1, 0.0, 0.0);
        GLUquadricObj* q=gluNewQuadric();
        gluQuadricDrawStyle(q,GLU_FILL);
        gluSphere(q,1.0,10,10);
        
        glPopMatrix();
}

void DrawCourant(){

	int k,j,i;
	double u,v;
	glColor3f(1,0,0);
	
	glBegin(GL_LINES);
	
	for(k=-50;k<50;k++){
			for(j=-50;j<50;j++){
				double x=20*j;
				double y=20*k;
				double z=-100;
				
				double Xi[] = {150,100,-100,-100};
    			double Yi[] = {100,-100,150,-100};
    			
    			double phi[] = {10,-10,10,-10};
    			double Ri = 100;
				u=v=0;
    			for (int i=0;i<4;i++)
    			{
        			double d2 = (x-Xi[i])*(x-Xi[i])+(y-Yi[i])*(y-Yi[i]);

        			u   += phi[i]*2*y*(y-Yi[i])*exp(-1*d2/(Ri*Ri))/(Ri*Ri);
        			v   -= phi[i]*2*x*(x-Xi[i])*exp(-1*d2/(Ri*Ri))/(Ri*Ri);
        		}
	
				glVertex3d(x,y,z);
           		glVertex3d(x+u, y+v, z);
           	}
		
	}
    glEnd(); 
}

void DrawSailboat(Sailboat0 const&boat)
{
	//*
	glPushMatrix();
	glBegin(GL_LINE_LOOP);  //ligne � suivre
			glColor3f(1,1,0);
			float ax = static_cast<float>(boat.cx+TAILLE_TRIANGLE*cos(0*2*M_PI/3));
    		float ay = static_cast<float>(boat.cy+TAILLE_TRIANGLE*sin(0*2*M_PI/3));
    		float bx = static_cast<float>(boat.cx+TAILLE_TRIANGLE*cos(1*2*M_PI/3));
    		float by = static_cast<float>(boat.cy+TAILLE_TRIANGLE*sin(1*2*M_PI/3));
    		float dx = static_cast<float>(boat.cx+TAILLE_TRIANGLE*cos(2*2*M_PI/3));
    		float dy = static_cast<float>(boat.cy+TAILLE_TRIANGLE*sin(2*2*M_PI/3));
            glVertex3f(ax,ay,1);
            glVertex3f(bx,by,1);
            glVertex3f(dx,dy,1);
    glEnd();
    //*/
	
    // ***************************************
    	glTranslated(boat.x,boat.y,0.0);
		glPushMatrix();
		//printf("position :%f %f \n",sailboat1.x, sailboat1.y);
        

        // ***************************************
        //       WIND
        // ***************************************

                    glRotatef(static_cast<float>((boat.psi+0.5*M_PI)*180.0/M_PI),0.0,0.0,1.0);
                    glBegin(GL_LINES);  //Fleche vent
                            double a=1;
                            glColor3f(0.7,0.1,0);             glVertex3f(3,14,13);
                            glVertex3f(3,static_cast<float>(14-a),13);            glVertex3f(3,static_cast<float>(14-a),13);
                            glVertex3f(3,static_cast<float>(14-a),14);            glVertex3f(3,static_cast<float>(14-a),14);
                            glVertex3f(3,static_cast<float>(12.5-a),12.5);        glVertex3f(3,static_cast<float>(12.5-a),12.5);
                            glVertex3f(3,static_cast<float>(14-a),11);            glVertex3f(3,static_cast<float>(14-a),11);
                            glVertex3f(3,static_cast<float>(14-a),12);            glVertex3f(3,static_cast<float>(14-a),12);
                            glVertex3f(3,14,12);              glVertex3f(3,14,12);
                            glVertex3f(3,14,13);
                    glEnd();


        glPopMatrix();
        glRotatef(static_cast<float>(boat.theta*180.0/M_PI),0.0,0.0,1.0);
        glPushMatrix();
        glRotatef(static_cast<float>(boat.phi*180.0f/M_PI),1,0,0);

        // ***************************************
        //       COQUE
        // ***************************************

                                            {   glBegin(GL_QUADS);   //plancher
                                                   glVertex3f(-1,-1.5,0.1);        glVertex3f(3,-1.5, 0.1);
                                                   glVertex3f(3,1.5,0.1);          glVertex3f(-1,1.5,0.1);
                                                   glVertex3f(4.5,-0.75, 0.1);     glVertex3f(5.06,-0.375, 0.1);
                                                   glVertex3f(5.25,0, 0.1);        glVertex3f(5.06,0.375, 0.1);
                                                   glVertex3f(4.5,0.75, 0.1);
                                                glEnd();
                                                // ---------------------------- dessus avant ----------------------------------------------------------------------
                                                glTranslatef(0.01,0,0.01);
                                                glBegin(GL_POLYGON);  //dessus avant
                                                   glColor3f(0.8,0.2,0.2);            glVertex3f(3,-2,1.0);
                                                   glVertex3f(3.1,-1.9,1.01);         glVertex3f(3.75,-1.6, 1.01);
                                                   glVertex3f(5.0,-1,1.01);           glVertex3f(5.75,-0.5,1.01);
                                                   glVertex3f(6.0, 0, 1.01);          glVertex3f(5.75,0.5,1.01);
                                                   glVertex3f(5.0,1,1.01);            glVertex3f(3.75,1.6,1.01);
                                                   glVertex3f(3.1,1.9,1.01);          glVertex3f(3,2,1.01);
                                                glEnd();

                                                //--------------------------- faces lat�rales ---------------------------------------------------------------------
                                                glTranslatef(-0.01,0,0);
                                                glBegin(GL_POLYGON); //faces lat�rales droite
                                                    glColor3f(0,1,0);
                                                    glVertex3f(-1,-1.5,0);       glVertex3f(-1, -1.9, 0.5);
                                                    glVertex3f(-1,-2,1.0);       glVertex3f(3,-2,1.0);
                                                    glVertex3f(3, -1.9, 0.5);    glVertex3f(3,-1.5,0);
                                                    glVertex3f(-1,-1.5,0);
                                                glEnd();
                                                glBegin(GL_POLYGON); //faces lat�rales gauche
                                                    glColor3f(0,0,1);
                                                    glVertex3f(-1,1.5,0);        glVertex3f(-1, 1.9, 0.5);
                                                    glVertex3f(-1,2,1.0);        glVertex3f(3,2,1.0);
                                                    glVertex3f(3, 1.9, 0.5);     glVertex3f(3,1.5,0);
                                                    glVertex3f(-1,1.5,0);
                                                glEnd();
                                                //--------------------------- banc ----------------------------------------------------------------------------------
                                                glTranslatef(0,-0.01,0);
                                                glBegin(GL_QUADS);              //banc
                                                    glColor3f(1,1,1);
                                                    glVertex3f(-1,2,1.0);         glVertex3f(-1, 1.3, 1.0);
                                                    glVertex3f(3, 1.3, 1.0);      glVertex3f(3,2,1.0);
                                                    glVertex3f(-1, 1.3, 1.0);     glVertex3f(-1, 1.1, 4*1.0/5);
                                                    glVertex3f(3, 1.1, 4*1.0/5);  glVertex3f(3, 1.3, 1.0);
                                                    glVertex3f(-1, 1.1, 4*1.0/5); glVertex3f(-1, 0.9, 3*1.0/5);
                                                    glVertex3f(3, 0.9, 3*1.0/5);  glVertex3f(3, 1.1, 4*1.0/5);
                                                    glVertex3f(-1, 0.9, 3*1.0/5); glVertex3f(-1,0.8,0);
                                                    glVertex3f(3,0.8,0);          glVertex3f(3, 0.9, 3*1.0/5);
                                                glEnd();
                                                glTranslatef(0,0.01,0);

                                                // -------------------------------- autre banc ----------------------------------------------------------------
                                                glBegin(GL_QUADS);              //banc
                                                    glColor3f(1,1,1);
                                                    glVertex3f(-1,-2,1.0);        glVertex3f(-1, -1.3, 1.0);
                                                    glVertex3f(3, -1.3, 1.0);     glVertex3f(3,-2,1.0);
                                                    glVertex3f(-1, -1.3, 1.0);    glVertex3f(-1, -1.1, 4*1.0/5);
                                                    glVertex3f(3, -1.1, 4*1.0/5); glVertex3f(3, -1.3, 1.0);
                                                    glVertex3f(-1, -1.1, 4*1.0/5);glVertex3f(-1, -0.9, 3*1.0/5);
                                                    glVertex3f(3, -0.9, 3*1.0/5); glVertex3f(3, -1.1, 4*1.0/5);
                                                    glVertex3f(-1, -0.9, 3*1.0/5);glVertex3f(-1,-0.8,0);
                                                    glVertex3f(3,-0.8,0);         glVertex3f(3, -0.9, 3*1.0/5);
                                                glEnd();
                                                glTranslatef(0,-0.01,0);
                                                // ---------------------- face avant mat --------------------------------
                                                glBegin(GL_POLYGON); //face "avant mat"
                                                    glColor3f(0,0,1);
                                                    glNormal3f(-1,0,0);                glVertex3f(3+0,-1.5+0.4,0);
                                                    glVertex3f(3+0, -1.9+0.4, 0.5);    glVertex3f(3+0,-2+0.4,1.0);
                                                    glVertex3f(3+0,2-0.4,1.0);         glVertex3f(3+0, 1.9-0.4, 0.5);
                                                    glVertex3f(3+0,1.5-0.4,0);         glVertex3f(3+0,-1.5+0.4,0);
                                                glEnd();
                                                // ------------------------ face arri�re -----------------------------------------------
                                                glTranslatef(-0.01,0,0);
                                                glBegin(GL_POLYGON); //face arri�re
                                                    glColor3f(0.5,1,0);              glNormal3f(-1,0,0);
                                                    glVertex3f(-1,-1.5,0);           glVertex3f(-1, -1.9, 0.5);
                                                    glVertex3f(-1,-2,1.0);           glVertex3f(-1,2,1.0);
                                                    glVertex3f(-1, 1.9, 0.5);        glVertex3f(-1,1.5,0);
                                                    glVertex3f(-1,-1.5,0);
                                                glEnd();
                                                glTranslatef(0.01,-0.01,0);
                                                // ----------------------------- face avant ------------------------------------------
                                                glBegin(GL_POLYGON);
                                                   glVertex3f(3,-2,1.0);           glVertex3f(3.1,-1.7,1.0);
                                                   glVertex3f(3.75,-1.5, 1.0);     glVertex3f(5.0,-1,1.0);
                                                   glVertex3f(5.75,-0.5,1.0);      glVertex3f(6.0, 0, 1.0);
                                                   glVertex3f(5.25,0, 0);          glVertex3f(5.06,-0.375, 0);
                                                   glVertex3f(4.5,-0.75, 0);       glVertex3f(3,-1.5,0);
                                                   glVertex3f(3, -1.9, 0.5);       glVertex3f(3,-2,1.0);
                                                   glVertex3f(3,2,1.0);            glVertex3f(3.1,1.7,1.0);
                                                   glVertex3f(3.75,1.5, 1.0);      glVertex3f(5.0,1,1.0);
                                                   glVertex3f(5.75,0.5,1.0);       glVertex3f(6.0, 0, 1.0);
                                                   glVertex3f(5.25,0, 0);          glVertex3f(5.06,0.375, 0);
                                                   glVertex3f(4.5,0.75, 0);        glVertex3f(3,1.5,0);
                                                   glVertex3f(3, 1.9, 0.5);        glVertex3f(3,2,1.0);
                                                glEnd();
                                            }



        glPopMatrix();
        glPushMatrix();
             glTranslatef(-1,0,0);
             glRotatef(boat.deltag*180.0/M_PI,0,0,1);

             // ***************************************
             //       RUDDER
             // ***************************************
             {   glColor3f(0,0,1);
                 glBegin(GL_POLYGON);
                 glVertex3f(0,-0.05,1);       glVertex3f(0,-0.05,0);      glVertex3f(-0.6,-0.05,0);
                 glVertex3f(-0.3,-0.05,1);    glVertex3f(0,-0.05,1);      glVertex3f(0,0.05,1);
                 glVertex3f(0,0.05,0);        glVertex3f(-0.6,0.05,0);    glVertex3f(-0.3,0.05,1);
                 glVertex3f(0,0.05,1);
                 glVertex3f(0,-0.05,1);       glVertex3f(0,0.05,1);       glVertex3f(0,-0.05,0);
                 glVertex3f(0,0.05,0);        glVertex3f(-0.6,-0.05,0);   glVertex3f(-0.6,0.05,0);
                 glVertex3f(-0.3,-0.05,1);    glVertex3f(-0.3,0.05,1);    glVertex3f(0,-0.05,1);
                 glVertex3f(0,0.05,1);
                 glEnd();
                 glDisable(GL_TEXTURE_2D);
                 glTranslatef(-0.6,0,1);
                 glRotatef(90,0,1,0);
                 GLUquadricObj*q1=gluNewQuadric();  //barre
                 gluQuadricOrientation(q1, GLU_OUTSIDE);
                 gluQuadricTexture(q1, GL_TRUE);
                 gluCylinder(q1,0.05,0.05,3, 10,10);
                 gluDeleteQuadric(q1);
             }

        glPopMatrix();
        glPushMatrix();
            glTranslatef(5,0,0);
            glRotatef(boat.deltav*180.0/M_PI,0,0,1);

           // ***************************************
           //       SAIL
           // ***************************************

            {   glColor3f(0.9,0.9,0.9);
                GLUquadricObj*q1=gluNewQuadric();  //m�t
                gluQuadricOrientation(q1, GLU_OUTSIDE);
                gluQuadricTexture(q1, GL_TRUE);
                gluCylinder(q1,0.08,0.08,14, 10,10);
                gluDeleteQuadric(q1);
                glDisable(GL_TEXTURE_2D);

                glColor3f(1,1,0);
                float a=-atan(boat.fv/500);  // courbure de la voile
                glEnable(GL_TEXTURE_2D);
                glBegin(GL_TRIANGLE_FAN);
                    glVertex3f(0,0,2);     glVertex3f(0,0,12);    glVertex3f(-1,a*1.5,10);
                    glVertex3f(-2,a*2,8);  glVertex3f(-3,a*2,6);  glVertex3f(-4,a*1.5,4);  glVertex3f(-5,0,2);
                glEnd();

                glDisable(GL_BLEND);
                glDisable(GL_TEXTURE_2D);
                glTranslatef(0,0,2);
                glRotatef(-90,0,1,0);
                glEnable(GL_TEXTURE_2D);         //bome
                glBindTexture(GL_TEXTURE_2D,5);

                q1=gluNewQuadric();
                gluQuadricOrientation(q1, GLU_OUTSIDE);
                gluQuadricTexture(q1, GL_TRUE);
                gluCylinder(q1,0.1,0.1,5.5, 10,10);
                gluDeleteQuadric(q1);
                glDisable(GL_TEXTURE_2D);
            }
        glPopMatrix();
    glPopMatrix();
}
