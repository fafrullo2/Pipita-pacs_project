#include "message_manager.h"
#include <unistd.h>


void message_manager::push(message msg){
    while(!mtx.try_lock())
        usleep(1000);
    message_queue.push(msg);
    mtx.unlock();
    return;
}


message message_manager::pop(){
    message value;
    while(!mtx.try_lock())
        usleep(1000);
    value.copy(message_queue.back());
    message_queue.pop();
    mtx.unlock();
    return value;
}
bool message_manager::is_empty(){
    while(!mtx.try_lock())
        usleep(1000);
    int value=message_queue.size();
    mtx.unlock();
    return (value==0);
}
