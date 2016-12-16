//
// Created by tag on 16/12/16.
//

#pragma once

#include <vector>
#include "sailboat.h"
#include "buoy.h"

class World {
public:
    World(int sailboat,int buoy);

private:
    std::vector<Sailboat> vec_sailboat;
    std::vector<Buoy> vec_buoy;
};
