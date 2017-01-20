//
// Created by tag on 16/12/16.
//

#include "world.h"
#include "sailboat.h"
#include "buoy.h"
#include "config.h"

World::World(int sailboat, int buoy) {

    // Boat creation
    for (int i = 0; i < BOAT_NUMBER; ++i) {
        const double x = 0;
        const double y = 0;
        vec_sailboat.push_back(Sailboat(i+1,x,y));
    }

    // Buoy creation
    for (int i = 0; i < BUOY_NUMBER; ++i) {
        //vec_buoy.push_back(Buoy(

        //));
        double x = 10;
        double y = 7.40;
        double z = 0;
        const double u = 0;
        vec_buoy.push_back(Buoy(i+1,x,y,z,u));
    }
}

void World::initialize()
{
    const double tabSailX[] = X_BOAT_TARGET;
    const double tabSailY[] = Y_BOAT_TARGET;

    for (int i = 0; i < vec_sailboat.size(); ++i) {
        vec_sailboat[i].setTargetTriangle(tabSailX[i],tabSailY[i]);
    }
}

void World::clock()
{
    for (auto &&sailboat : vec_sailboat) {
        sailboat.clock();
    }

    for (auto &&buoy : vec_buoy) {
        buoy.clock();
    }
}
