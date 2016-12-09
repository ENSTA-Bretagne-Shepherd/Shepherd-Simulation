#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <SDL/SDL.h>
#include <math.h>
#include <GL/gl.h>
#include <GL/glu.h>

#include "sailboat.h"
#include "widgetsimu.h"


#define LARGEUR_FENETRE 900
#define HAUTEUR_FENETRE 700
#define DELAY_FRAME 30


/** biblihotèques :
	SDLmain
	SDL
	GLU
	GL

compilation: 
g++ *.cpp -lSDLmain -lSDL -lGLU -lGL
**/
double dt = 0.2;


int boucle(SDL_Event* event);


int main(int argc, char *argv[])
{
    int k;
    SDL_Event event;



    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER);
    SDL_WM_SetCaption("graphisme", NULL);

    SDL_SetVideoMode(LARGEUR_FENETRE, HAUTEUR_FENETRE, 32, SDL_OPENGL);


    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();
    gluPerspective(70,(double)LARGEUR_FENETRE/HAUTEUR_FENETRE,1,1000);    
    glEnable(GL_DEPTH_TEST);

    
    WidgetSimu s;
    s.initializeGL();


    k=0;

    Uint32 temps = SDL_GetTicks()-50;
    Uint32 tempspasse;
    int a1=0,a2=0;

    while (boucle(&event))
    {
        glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

        glMatrixMode( GL_MODELVIEW );
        glLoadIdentity();

        gluLookAt(-40,-40,300,0,0,0,0,0,1);
        //glTranslated(0,0,2);
        glPushMatrix();

        if(event.button.x!=0 && event.button.y!=0){a1=event.button.x;a2=event.button.y;}
        glRotated(a1*0.5,0,1,0);
        glRotated(a2*0.5,1,0,0);
        
        
        
        //glPushMatrix();s.DrawBouees();glPopMatrix();
        
        s.Clock();
        
        
        glPopMatrix();   

        tempspasse = temps - SDL_GetTicks() + DELAY_FRAME;
        if (tempspasse < 10000)SDL_Delay(tempspasse);
        temps = SDL_GetTicks();


        glFlush();// mise à jour de l'écran
        SDL_GL_SwapBuffers();
    }//*/


    return 0;
}

int boucle(SDL_Event* event){
    int continuer=1;
    while (SDL_PollEvent(event)){
    switch ((*event).type)
        {
        case SDL_QUIT:
            continuer = 0;break;
        case SDL_KEYDOWN: /* Si appui d'une touche */
            switch ((*event).key.keysym.sym)
                {
                case SDLK_ESCAPE: /* Appui sur la touche Echap, on arrête le programme */
                    continuer = 0;break;
                default: ;
                }
            break;
        default: ;
        }
    }
    return continuer;
}




