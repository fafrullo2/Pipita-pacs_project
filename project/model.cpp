#include "model.h"
#include <chrono>
#include <thread>

void model::model_thread(){
    while (true){
        if(lives==0){
           //send message to view, attend return ok from control and close everything 
        }
        if(brick_count==0){
           //send win message, wait for ok and close everything 
        }
        if(!message_queue.is_empty()){
            while(!message_queue.is_empty()){
                model::analyze_msg(message_queue.pop());
            }
        }
        model::ball_control();
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
    }
    return;
}


void model::analyze_msg(message msg){
    //if update on bar
    model::bar_update(msg);
    //push message to view and return
    //else execute whatever needed
}
void model::ball_control(){
    ball_.move();
    //if impact set new position to point of impact and bounce
    //if fallen out of field lives--
}