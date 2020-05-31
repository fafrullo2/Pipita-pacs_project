

#ifndef GAME_FIELD_H
#define GAME_FIELD_H
#include "bar.h"
#include "ball.h"
#include "brick.h"
#include "../message_manager.h"
#include "../map_wrapper.h"

#include <mutex>






class game_field {
private:
    std::unordered_map<int, game_object*> elems;//<ID,pointer>
    map_wrapper bricks_map; //<Y<X,ID>>
    
    int ball_ID;
    int bar_ID;
    float low_bound;
    float high_bound;
    float l_bound;
    float r_bound;
    int lives;
    
    std::mutex resource_lock;
    
    message_manager message_queue;
    void apply_to_model(message msg);
    
public:
    game_object* get_element(int ID);
    void add_element(game_object* obj);
    void add_element(ball* b);
    void add_element(bar* b);
    void add_element(brick* b);
    void push_message(message msg){
        message_queue.push(msg);
    }
    
    float check_for_impact(float X, float Y);
    void  model_thread();
    
    
};
#endif /* GAME_FIELD_H */