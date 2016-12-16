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
        vec_sailboat.push_back(Sailboat(

        ));
    }

    // Buoy creation
    for (int i = 0; i < BUOY_NUMBER; ++i) {
        vec_buoy.push_back(Buoy(

        ));
    }

}
