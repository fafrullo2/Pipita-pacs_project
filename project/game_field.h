

#ifndef GAME_FIELD_H
#define GAME_FIELD_H
#include "bar.h"
#include "ball.h"
#include "brick.h"

#include <map>
#include <unordered_map>





class game_field {
private:
    std::unordered_map<int, game_object*> elems;
    std::map<float, std::pair<float, int>> bricks_map; 
    
    int ball_ID;
    int bar_ID;
    float low_bound;
    float high_bound;
    float l_bound;
    float r_bound;
    
    inline void consider_ID(ball* b){ball_ID=b->get_ID();}
    inline void consider_ID(bar* b){bar_ID=b->get_ID();}
    inline void consider_ID(game_object* b){}
public:
    game_object* get_element(int ID);
    void add_element(game_object* obj);
};
#endif /* GAME_FIELD_H */