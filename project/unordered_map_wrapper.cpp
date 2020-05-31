#include "unordered_map_wrapper.h"
#include "ball.h"
#include <unistd.h>
#include <utility>


game_object* unordered_map_wrapper::get_elem(int key){
    while(!mtx.try_lock())
        usleep(1000);
    game_object* aux=map.at(key);
    mtx.unlock();
    return aux;
}
void unordered_map_wrapper::add_element(game_object* obj){
    while(!mtx.try_lock())
        usleep(1000);
    map.insert(std::pair<int, game_object*>(obj->get_ID(), obj));
    mtx.unlock();
}

void unordered_map_wrapper::delete_element(int key){
    while(!mtx.try_lock())
        usleep(1000);
   // map.at(key)->delete();
    map.at(key)=NULL;
    mtx.unlock();
}

unordered_map_wrapper::unordered_map_wrapper(){
    map=std::unordered_map<int, game_object*>(26);
}