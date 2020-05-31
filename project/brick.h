#ifndef BRICK_H
#define BRICK_H
#include "game_object.h"




class brick : public game_object{
    protected: 
        int hp;
    public:
        inline int get_hp(){return hp;}
        inline void set_hp(int HP){hp=HP;}
        inline bool hit (int dmg){hp-=dmg; return (hp>0);}
            
};
#endif /* BRICK_H */

