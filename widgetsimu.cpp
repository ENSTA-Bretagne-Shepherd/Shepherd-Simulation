#include "widgetsimu.h"
#include "sailboat.h"
#include "stdio.h"

#include <GL/gl.h>
#include <GL/glu.h>

extern double dt;



WidgetSimu::WidgetSimu()
{   Zoom=0.5;    zCam=1000;   xCam=-1100;
    deltag=0;    deltavmax=0.3;
    
    cx=0;cy=0;
}


void WidgetSimu::Start()
{   if (dt==0)  dt=0.02; else dt=0;
}

void WidgetSimu::Clock()
{   
	DrawMer();	
	
	sailboat1.cx = cx+100;
	sailboat1.cy = cy+100;
	sailboat2.cx = cx-100;
	sailboat2.cy = cy+100;
	sailboat3.cx = cx+100;
	sailboat3.cy = cy-100;
	sailboat4.cx = cx-100;
	sailboat4.cy = cy-100;
	sailboat1.Clock();
	sailboat2.Clock();
	sailboat3.Clock();
	sailboat4.Clock();
    DrawSailboat(sailboat1);
    DrawSailboat(sailboat2);
    DrawSailboat(sailboat3);
    DrawSailboat(sailboat4);
    
}


/************************/
/*   dessin de la scène */
/************************/

void WidgetSimu::initializeGL()
{
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_NORMALIZE);
    glClearColor(0.9,0.9,1,1);  //arrière plan
            static const GLfloat lightPos[4] = { 5.0f, 5.0f, 10.0f, 1.0f };
            glLightfv(GL_LIGHT0, GL_POSITION, lightPos);
            glEnable(GL_LIGHTING);
            xCam=-90; yCam=0;  zCam=20;
            glEnable(GL_COLOR_MATERIAL);
}

void WidgetSimu::paintGL()
{
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glLoadIdentity();
        glTranslated(0.0,-2.0, -40.0);
        glRotated(xCam, 1.0, 0.0, 0.0);
        glRotated(yCam, 0.0, 1.0, 0.0);
        glRotated(zCam, 0.0, 0.0, 1.0);
        glScalef( Zoom, Zoom, Zoom);
        glPushMatrix();
          DrawMer();
          DrawBouees();
        glPopMatrix();
        DrawSailboat(sailboat1);
        DrawSailboat(sailboat2);
        DrawSailboat(sailboat3);
        DrawSailboat(sailboat4);
}



void WidgetSimu::resizeGL(int width, int height)
{
    int side = width; if(height<side)side=height;
    glViewport((width - side) / 2, (height - side) / 2, side, side);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum(-1.0, +1.0, -1.0, 1.0, 5.0, 60.0);
    glMatrixMode(GL_MODELVIEW);
}


void WidgetSimu::DrawMer()
{       glBegin(GL_POLYGON);
           glColor3f(0.5,0.5,1);
           glVertex3f(-100000,-100000,0);
           glVertex3f(100000,-100000,0);
           glVertex3f(100000,100000,0);
           glVertex3f(-100000,100000,0);
        glEnd();
}

void WidgetSimu::DrawBouees()
{   for (int k=1;k<3;k++)
    {  glTranslatef(10,0, 0);
       glColor3f(1, 0.0, 0.0);
       GLUquadricObj* q=gluNewQuadric();
       gluQuadricDrawStyle(q,GLU_FILL);
       gluSphere(q,1.0,10,10);
    }
}



void WidgetSimu::DrawSailboat(sailboat const&boat)

{
	//*
	glPushMatrix();
	glBegin(GL_LINE_LOOP);  //ligne à suivre
			float ax=boat.cx+50*cos(0*2*M_PI/3);
    		float ay=boat.cy+50*sin(0*2*M_PI/3);
    		float bx=boat.cx+50*cos(1*2*M_PI/3);
    		float by=boat.cy+50*sin(1*2*M_PI/3);
    		float dx=boat.cx+50*cos(2*2*M_PI/3);
    		float dy=boat.cy+50*sin(2*2*M_PI/3);
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

                    glRotatef((boat.psi+0.5*M_PI)*180.0/M_PI,0.0,0.0,1.0);
                    glBegin(GL_LINES);  //Fleche vent
                            double a=1;
                            glColor3f(0.7,0.1,0);             glVertex3f(3,14,13);
                            glVertex3f(3,14-a,13);            glVertex3f(3,14-a,13);
                            glVertex3f(3,14-a,14);            glVertex3f(3,14-a,14);
                            glVertex3f(3,12.5-a,12.5);        glVertex3f(3,12.5-a,12.5);
                            glVertex3f(3,14-a,11);            glVertex3f(3,14-a,11);
                            glVertex3f(3,14-a,12);            glVertex3f(3,14-a,12);
                            glVertex3f(3,14,12);              glVertex3f(3,14,12);
                            glVertex3f(3,14,13);
                    glEnd();


        glPopMatrix();
        glRotatef(boat.theta*180.0/M_PI,0.0,0.0,1.0);
        glPushMatrix();
        glRotatef(boat.phi*180.0f/M_PI,1,0,0);

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

                                                //--------------------------- faces latérales ---------------------------------------------------------------------
                                                glTranslatef(-0.01,0,0);
                                                glBegin(GL_POLYGON); //faces latérales droite
                                                    glColor3f(0,1,0);
                                                    glVertex3f(-1,-1.5,0);       glVertex3f(-1, -1.9, 0.5);
                                                    glVertex3f(-1,-2,1.0);       glVertex3f(3,-2,1.0);
                                                    glVertex3f(3, -1.9, 0.5);    glVertex3f(3,-1.5,0);
                                                    glVertex3f(-1,-1.5,0);
                                                glEnd();
                                                glBegin(GL_POLYGON); //faces latérales gauche
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
                                                // ------------------------ face arrière -----------------------------------------------
                                                glTranslatef(-0.01,0,0);
                                                glBegin(GL_POLYGON); //face arrière
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
                GLUquadricObj*q1=gluNewQuadric();  //mât
                gluQuadricOrientation(q1, GLU_OUTSIDE);
                gluQuadricTexture(q1, GL_TRUE);
                gluCylinder(q1,0.08,0.08,14, 10,10);
                gluDeleteQuadric(q1);
                glDisable(GL_TEXTURE_2D);

                glColor3f(1,1,0);
                float a=-atan(sailboat1.fv/500);  // courbure de la voile
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
