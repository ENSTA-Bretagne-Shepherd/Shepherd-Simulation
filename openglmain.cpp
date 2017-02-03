#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <SDL/SDL.h>
#include <math.h>
#include <GL/gl.h>
#include <GL/glu.h>


#include "affichage.h"
#include "client.h"


#define LARGEUR_FENETRE 900
#define HAUTEUR_FENETRE 700
#define DELAY_FRAME 30

#define BOAT_NUMBER 4
#define BUOY_NUMBER 5

// include pour les sockets
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>

#include <vector>
#include <algorithm>




int boucle(SDL_Event* event);

char reponse[1024];

int appui = 0;
int appui2 = 0;


int main(int argc, char *argv[])
{
//    printf("SIMULATION STARTED\n");

    int k;
    SDL_Event event;
    
    if (argc < 3) {
         printf("nombre d'argument insuffisant: hote et port demandé\n");
         return 0;
    }



    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER);
    SDL_WM_SetCaption("graphisme", NULL);

    SDL_SetVideoMode(LARGEUR_FENETRE, HAUTEUR_FENETRE, 32, SDL_OPENGL);


    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();
    gluPerspective(70,(double)LARGEUR_FENETRE/HAUTEUR_FENETRE,1,1000);    
    glEnable(GL_DEPTH_TEST);
    
    
    //glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	
	//glDisable(GL_BLEND);
	
	std::vector<Sailboat0> vec_sailboat;
	std::vector<Buoy0> vec_buoy;
	std::vector<Flow> vec_flow;
	
	for (int i = 0; i < BOAT_NUMBER; ++i) {
        vec_sailboat.push_back(Sailboat0());
    }
    for (int i = 0; i < BUOY_NUMBER; ++i) {
        vec_buoy.push_back(Buoy0());
    }

    
    
    

    k=0;

    Uint32 temps = SDL_GetTicks()-50;
    Uint32 tempspasse;
    int a1=0,a2=0,b1=0,b2=0;
    
    int c1=0,c2=0,d1=0,d2=0;

    while (boucle(&event))
    {
        glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

        glMatrixMode( GL_MODELVIEW );
        glLoadIdentity();

        gluLookAt(-60,0,300,0,0,0,0,0,1);
        
        
        glPushMatrix();
        if(!appui2){b1 = event.button.x - a1; b2 = event.button.y - a2 ;}
        
        if(appui2){a1=event.button.x-b1; a2=event.button.y-b2;}
        
        if(!appui){d1 = event.button.x - c1; d2 = event.button.y - c2 ;}
        
        if(appui){c1=event.button.x-d1; c2=event.button.y-d2;}
        
        glTranslatef( -c2*0.5, -c1*0.5,0);
        
        if(a1 != 0 || a2 != 0){
        	float coef = sqrt(a1*a1 + a2*a2);
        	glRotatef(coef*0.3, a1/coef, -a2/coef,0);
        }
        //glRotated(a2*0.5,1,0,0);         
        
        DrawMer();
        for_each(vec_sailboat.begin(), vec_sailboat.end(), DrawSailboat);
    	for_each(vec_buoy.begin(), vec_buoy.end(), DrawBouees);
    	glBegin(GL_QUADS);
    		for_each(vec_flow.begin(), vec_flow.end(), DrawCourant);    
    	glEnd();   
        
        glPopMatrix();
        
        char * buffer = connect(argv[2], argv[1], "recu", 4);
        
        vec_sailboat[0] = ((Sailboat0*)buffer)[0];
        vec_sailboat[1] = ((Sailboat0*)buffer)[1];
        vec_sailboat[2] = ((Sailboat0*)buffer)[2];
        vec_sailboat[3] = ((Sailboat0*)buffer)[3];
        
        buffer = (char*)(((Sailboat0*)buffer) + 4);
        
        vec_buoy[0] = ((Buoy0*)buffer)[0];
        vec_buoy[1] = ((Buoy0*)buffer)[1];
        vec_buoy[2] = ((Buoy0*)buffer)[2];
        vec_buoy[3] = ((Buoy0*)buffer)[3];
        vec_buoy[4] = ((Buoy0*)buffer)[4];
        
   
		/*
        //Temps externe
        tempspasse = temps - SDL_GetTicks() + DELAY_FRAME;
        if (tempspasse < 10000)SDL_Delay(tempspasse);
        temps = SDL_GetTicks();
        //*/


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
        case SDL_MOUSEBUTTONDOWN:
        	if(event->button.button == SDL_BUTTON_LEFT)
				appui = 1;
			else if(event->button.button == SDL_BUTTON_RIGHT)
				appui2 = 1;
			
			break;
		case SDL_MOUSEBUTTONUP:
            if(event->button.button == SDL_BUTTON_LEFT)
				appui = 0;
			else if(event->button.button == SDL_BUTTON_RIGHT)
				appui2 = 0;
			break;
        default: ;
        }
    }
    return continuer;
}




