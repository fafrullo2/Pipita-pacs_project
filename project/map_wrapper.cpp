#include "map_wrapper.h"
#include <unistd.h>

void map_wrapper::insert(float Y, float X, int ID){
    while(!mtx.try_lock())
        usleep(1000);
    std::vector<int> aux= map[(int)Y];
    aux[(int)X]=ID;
    bricks++;
    mtx.unlock();
}
    
int map_wrapper::get_by_coord(float Y, float X){
    while(!mtx.try_lock())
        usleep(1000);
    std::vector<int> aux= map[(int)Y];
    int value=aux[(int)X];
    mtx.unlock();
    return value;
}
    
void map_wrapper::delete_elem(float Y, float X){
    while(!mtx.try_lock())
        usleep(1000);
    std::vector<int> aux= map[(int)Y];
    aux[(int)X]=-1;
    bricks--;
    mtx.unlock();
}

map_wrapper::map_wrapper(){
    map=std::vector<std::vector<int>>(4, std::vector<int>(6, -1)); //wall is y=4, x=6
}

int map_wrapper::get_bricks(){
    while(!mtx.try_lock())
        usleep(1000);
    int aux=bricks;
    mtx.unlock();
    return aux;
}