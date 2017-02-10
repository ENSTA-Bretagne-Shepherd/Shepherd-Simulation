#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <unistd.h>
#include <sstream>
#include <signal.h>
#include <cstring>

#include "world.h"
#include "config.h"
#include "unity-api/unityapi.h"
//#include "serverToBuoys.h"

#include "networktools.h"

double dt = DT;

void sig_handler(int signo);


char message[1024];

bool running_opengl = false;
bool running_unity  = false;

int main(int argc, char *argv[])
{
    printf("SIMULATION STARTED\n");
    
    if (signal(SIGINT, sig_handler) == SIG_ERR)
  		printf("\ncan't catch SIGINT\n");

    // Objects creation
    World env = World(4,5);
    env.initialize();

	// TODO dont kill the process when unity is unreachable
    //DisplayAPI display("localhost", 13000);
    
    // initialisation du socket si le port est donné au lancement du programme
    if (argc >= 3) {
        if(argv[1][0] == 'o'){
            running_opengl = true;
            init_connection(argv[2]);
        }
        if(argv[1][0] == 'u')
        {
            running_unity = true;
            init_unity_connection(argv[2], 13000);
        }
    }

    while (1)
    {

        // Server init
        //ServerToBuoys();
//        GraphInterface(ADRESS,PORT)
        //listen TODO

        //Fait avancer la simulation
        env.clock();

        // Send to Unity
        if(running_unity){
            for (int i = 0; i < env.vec_sailboat.size(); ++i)
            {
                std::ostringstream nameStream;
                nameStream << "Auv" << i;
                sendSailBoatState(nameStream.str(), env.vec_sailboat[i].x, env.vec_sailboat[i].y, env.vec_sailboat[i].theta*180/M_PI, env.vec_sailboat[i].deltav*180/M_PI);
            }

            for (int i = 0; i < env.vec_buoy.size(); ++i)
            {
                std::ostringstream nameStream;
                nameStream << "Buoy" << i;
                sendBuoyState(nameStream.str(), env.vec_buoy[i].x, env.vec_buoy[i].y, env.vec_buoy[i].z);
            }
        }

        //Envoie les infos par la socket si l'on a défini le port
        if (running_opengl) {
        	char *output = message;
        	((Sailboat0*)output)[0] = env.vec_sailboat[0];
        	((Sailboat0*)output)[1] = env.vec_sailboat[1];
        	((Sailboat0*)output)[2] = env.vec_sailboat[2];
        	((Sailboat0*)output)[3] = env.vec_sailboat[3];
        
        	output = (char*)(((Sailboat0*)message) + 4);
        
         	((Buoy0*)output)[0] =env.vec_buoy[0];
        	((Buoy0*)output)[1] =env.vec_buoy[1];
        	((Buoy0*)output)[2] =env.vec_buoy[2];
        	((Buoy0*)output)[3] =env.vec_buoy[3];
        	((Buoy0*)output)[4] =env.vec_buoy[4];
         	char *buffer = wait_connection(message, 5*sizeof(Buoy0) + 4*sizeof(Sailboat0));
    	}

        //Temps interne
        env.simuTime += dt;
        usleep(30000);
        printf("\ntime : %f \n",env.simuTime);
    }
    

    return 0;
}


void sig_handler(int signo)
{
  if (signo == SIGINT){
    	printf("received SIGINT\n");
    	close_connection();
        if(running_unity){
            close_unity_connection();
        }
    	exit(0);
    }
}





