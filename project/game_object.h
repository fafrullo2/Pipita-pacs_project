#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H





class game_object{
protected :
    int ID;
    float posX;
    float posY;
public:
    inline int get_ID(){return ID;}
    inline void set_ID(int id){ID=id;}
    inline bool hit(int dmg){return true;}
    inline float getX(){return posX;}
    inline float getY(){return posY;}
    inline void set_pos(float X, float Y){posX=X; posY=Y;}
};

#endif /* GAME_OBJECT_H */

