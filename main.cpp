#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <unistd.h>

#include "world.h"
#include "config.h"
//#include "serverToBuoys.h"

double dt = DT;

int boucle(){



    return EXIT_SUCCESS;
}

int main(int argc, char *argv[])
{
    printf("SIMULATION STARTED\n");

    // Objects creation
    World env = World(4,5);
    env.initialize();
    while (boucle()==EXIT_SUCCESS)
    {

        // Server init
        //ServerToBuoys();
//        GraphInterface(ADRESS,PORT)
        //listen TODO

        //Fait avancer la simulation
        env.clock();

        //Formate les donnes par JSON TODO

        //Envoie les infos par la socket TODO

        //Temps interne
        env.simuTime += dt;
        usleep(500);
        printf("\ntime : %f \n",env.simuTime);
    }

    return 0;
}





