#include "game_field.h"
#include <utility>
#include <unistd.h>
void game_field::add_element(game_object* obj){
   
}
void game_field::add_element(ball* b){
    resource_lock.lock();
    elems.insert(std::pair<int, game_object*>(b->get_ID(), b));
    resource_lock.unlock();
    ball_ID=b->get_ID();
}


void game_field::add_element(bar* b){
    resource_lock.lock();
    elems.insert(std::pair<int, game_object*>(b->get_ID(), b));
    resource_lock.unlock();
    bar_ID=b->get_ID();
}


void game_field::add_element(brick* b){
    resource_lock.lock();
    elems.insert(std::pair<int, game_object*>(b->get_ID(), b));
    bricks_map.insert(b->getY(), b->getX(), b->get_ID());
    resource_lock.unlock();
}

void game_field::model_thread(){
    while (true){
        if (bricks_map.empty() || lives==0)
            return;
        while(message_queue.is_empty())
            usleep(1000);
        while(!message_queue.is_empty())
            apply_to_model(message_queue.pop());
    }
}

void game_field::apply_to_model(message msg){
    int aux=msg.get_type();
    bar* b=elems.at(bar_ID);
    if(aux==1)
       b->set_pos(msg.get_param(0), msg.get_param(1)); 
    else if(aux==2)
       b->set_length(msg.get_param(0)); 
    else if(aux==3)
        b->set_angle(msg.get_param(0));
    //TODO:push message to view
}

float game_field::check_for_impact(float X, float Y){}


