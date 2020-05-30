#include "game_field.h"
#include <utility>
void game_field::add_element(game_object* obj){
    elems.insert(std::pair<float, game_object*>(obj->get_ID(), obj));
    consider_ID(obj);
}

