#ifndef BAR_H
    #define BAR_H


#include "game_object.h"


class bar : public game_object{
    protected:
        float length;
        float angle;
    public:
        inline float get_length(){return length;}
        inline float get_angle(){return angle;}
        
        inline void set_length(float value){length=value;}
        inline void set_angle(float value){angle=value;}
};

#endif /* BAR_H */