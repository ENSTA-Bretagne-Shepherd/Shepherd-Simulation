#ifndef WIDGETSIMU_H
#define WIDGETSIMU_H

#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <sys/types.h>
#include <sys/timeb.h>
#include <string.h>

#include "sailboat.h"
#include "buoy.h"

class WidgetSimu
{
public:
    WidgetSimu();


public:
   void Start();
   void Clock();

    void initializeGL();
    void paintGL();
    void resizeGL(int width, int height);

    void DrawMer();
    void DrawBouees();
    void DrawSailboat(Sailboat const&boat);
    int xCam,yCam,zCam;
    float Zoom;

    Sailboat sailboat1;
    Sailboat sailboat2;
    Sailboat sailboat3;
    Sailboat sailboat4;
    
    Buoy bouees[50];
    int nbbouees;
    
    double cx,cy;
    
    
    
    double deltavmax;
    double deltag;
};

#endif // WIDGETSIMU_H
