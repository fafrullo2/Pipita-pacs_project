#ifndef BALL_H
#define BALL_H
#include "game_object.h"





class ball:public game_object{
    protected:
        float velX;
        float velY;
        float speed_mult;
    public:
        inline float get_velX(){return velX;}
        inline float get_velY(){return velY;}
        inline float get_speed_mult(){return speed_mult;}
        
        inline void set_velX(float value){velX=value;}
        inline void set_velY(float value){velY=value;}
        inline void set_speed_mult(float value){speed_mult=value;}
        
        inline void move(){posX+=(velX*speed_mult); posY+=(velY*speed_mult);}
        void bounce(float angle);
            
};
#endif /* BALL_H */
