#include "map_wrapper.h"
#include <unistd.h>

void map_wrapper::insert(float Y, float X, int ID){
    while(!mtx.try_lock())
        usleep(1000);
    //
    mtx.unlock();
}
    
int map_wrapper::get_by_coord(float Y, float X){
    while(!mtx.try_lock())
        usleep(1000);
    std::iterator<std::pair<float, int>> aux;
    aux=map.find(Y);
    if (aux==map.end())
        return -1;
    //
    
}
    
void map_wrapper::delete_elem(float Y, float X){
    //
}