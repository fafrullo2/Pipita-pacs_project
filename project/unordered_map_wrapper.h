

#ifndef UNORDERED_MAP_WRAPPER_H
#define UNORDERED_MAP_WRAPPER_H
#include <mutex>
#include <unordered_map>
#include "game_object.h"

class unordered_map_wrapper{
private:
    std::unordered_map<int, game_object*> map;
    std::mutex mtx;
public:
    game_object* get_elem(int key);
    void add_element(game_object* obj);
    void delete_element(int key);
    unordered_map_wrapper();
};


#endif /* UNORDERED_MAP_WRAPPER_H */

