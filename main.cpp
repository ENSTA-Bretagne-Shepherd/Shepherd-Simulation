#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <unistd.h>
#include <sstream>

#include "world.h"
#include "config.h"
#include "unity-api/unityapi.h"
//#include "serverToBuoys.h"

#include "networktools.h"

double dt = DT;

int boucle(){



    return EXIT_SUCCESS;
}

char message[1024];

int main(int argc, char *argv[])
{
    printf("SIMULATION STARTED\n");

    // Objects creation
    World env = World(4,5);
    env.initialize();

	// TODO dont kill the process when unity is unreachable
    //DisplayAPI display("localhost", 13000);
    
    // initialisation du socket si le port est donné au lancement du programme
    if (argc >= 2) {    
         init_connection(argv[1]);
    }

    while (boucle()==EXIT_SUCCESS)
    {

        // Server init
        //ServerToBuoys();
//        GraphInterface(ADRESS,PORT)
        //listen TODO

        //Fait avancer la simulation
        env.clock();

        // Send to Unity
        /*
        for (int i = 0; i < env.vec_sailboat.size(); ++i)
        {
            std::ostringstream nameStream;
            nameStream << "Auv" << i;
            display.sendSailBoatState(nameStream.str(), env.vec_sailboat[i].x, env.vec_sailboat[i].y, env.vec_sailboat[i].theta);
        }
        //*/

        //Formate les donnes par JSON TODO

        //Envoie les infos par la socket si l'on a défini le port
        if (argc >= 2) {
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
        usleep(50000);
        printf("\ntime : %f \n",env.simuTime);
    }

    return 0;
}





