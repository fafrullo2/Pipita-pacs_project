

#ifndef MAP_WRAPPER_H
#define MAP_WRAPPER_H
#include <mutex>
#include <vector>


class map_wrapper{
private:
    std::vector<std::vector<int>> map;
    std::mutex mtx;
    int bricks;
public:
    map_wrapper();
    void insert(float Y, float X, int ID);
    int get_by_coord(float Y, float X);
    void delete_elem(float Y, float X);
    int get_bricks();
};


#endif /* MAP_WRAPPER_H */

