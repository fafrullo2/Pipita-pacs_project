

#ifndef MAP_WRAPPER_H
#define MAP_WRAPPER_H
#include <map>
#include <mutex>
#include <utility>
#include <vector>


class map_wrapper{
private:
    std::multimap<float, std::vector<std::pair<float, int>>> map;
    std::mutex mtx;
public:
    void insert(float Y, float X, int ID);
    int get_by_coord(float Y, float X);
    void delete_elem(float Y, float X);    
};


#endif /* MAP_WRAPPER_H */

