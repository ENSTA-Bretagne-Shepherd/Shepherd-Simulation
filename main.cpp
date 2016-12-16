#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <unistd.h>

#include "world.h"
#include "config.h"

double dt = DT;
double simuTime = 0.0;


int boucle(){





    return EXIT_SUCCESS;
}

int main(int argc, char *argv[])
{
    printf("SIMULATION STARTED\n");

    // Objects creation
    World env = World(4,5);


    while (boucle()==EXIT_SUCCESS)
    {
        //Temps interne
        simuTime += dt;
        usleep(50);
    }

    return 0;
}





