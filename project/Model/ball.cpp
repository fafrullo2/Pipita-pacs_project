#include "ball.h"
#include <math.h>
#include <functional>

void ball::bounce(float angle){
    float mod=sqrt(velX*velX+velY*velY);
    float original_angle=acos(velX/mod);
    float final_angle=angle+original_angle;
    velX=mod*cos(final_angle);
    velY=mod*sin(final_angle);
    return;
}