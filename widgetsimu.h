#ifndef WIDGETSIMU_H
#define WIDGETSIMU_H

#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <sys/types.h>
#include <sys/timeb.h>
#include <string.h>

#include "sailboat.h"

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
    void DrawSailboat(sailboat const&boat);
    int xCam,yCam,zCam;
    float Zoom;

    sailboat sailboat1;
    sailboat sailboat2;
    sailboat sailboat3;
    sailboat sailboat4;
    double cx,cy;
    
    
    
    double deltavmax;
    double deltag;
};

#endif // WIDGETSIMU_H
