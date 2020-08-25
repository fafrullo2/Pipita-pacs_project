#ifndef PAINTER_H
#define PAINTER_H
#include "game_elems.h"
#include "ofMain.h"
    class painter{
    public:
        //void prepare_for_update();
        void draw(){};
        void draw(brick* elem, float coord_x, float coord_y);
        void draw(ball* elem, float coord_x, float coord_y);
        void draw(bar* elem, float coord_x, float coord_y);
        void prepare_for_update(){ofClear(0,0,0);}
        void setup_draw();
        void endgame_draw();
        void draw_gamefield(int lives);
    }
    ;

#endif