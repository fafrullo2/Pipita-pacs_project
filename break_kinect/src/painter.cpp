#include "painter.h"
//scale factor = 3
int scale=10;
int x_offset=30;
int y_offset=500;
//(x->-10)* scale factor
//(y->-15)* scale factor

/*
As of th x and y of bricks (x->-10-)* scale factor, y=(15-y)*scale factor
dimensions-> *scale factor 


*/

void painter::draw_gamefield(int lives){
    ofSetColor(255, 255, 255);
    ofDrawBitmapString("Lives: ",300,0);
    for (int i=0; i<lives;i++){
        ofDrawBitmapString(" ][  ",300 +i*3,0);    
    }
    ofDrawLine(30, y_offset, 30, y_offset-30*scale );
    ofDrawLine(30+20*scale, y_offset, 30+20*scale, y_offset-30*scale );
    ofDrawLine(30, y_offset, 30+20*scale, y_offset);
    ofSetColor(255, 0, 0);
    ofDrawLine(30, y_offset-30*scale, 30+10*scale, y_offset-30*scale);
}


void painter::setup_draw(){
    ofSetColor(255, 255, 255);
    ofDrawBitmapString("Use Up and Down keys on your keyboard \nto set the kinect angle. Press Right when\n you are ready to start", 0, 10);
}
void painter::endgame_draw(){
    ofSetColor(255, 255, 255);
    ofDrawBitmapString("Use the Up Key to play again, \n or use the down key to exiit", 0, 10);

}


void painter::draw(brick* elem, float coord_x, float coord_y){

    if(elem->get_type()<=0)
        return;

    float x, y, lenght, width;
    lenght=2*scale;
    width=scale;
    x=coord_x*2 * scale + x_offset;
    y=y_offset-(30-coord_y)*scale;

   // ofRectangle to_draw((coord_x)*scale+x_offset,y_offset-(coord_y)*scale, 2*scale, scale);
    ofRectangle to_draw(x, y, lenght, width);
    switch(elem->get_type()){
        case 0:
            ofSetColor(0,0,0);
            break;
        case 1:
            ofSetColor(255,0,0);
            break;
        case 2:
            ofSetColor(0,255,0);

            break;
        case 3:
            ofSetColor(0,0, 255);
            break;
        default:
            ofSetColor(255, 0, 0);
            break;
    }
    
    ofDrawRectangle(to_draw);
}


void painter::draw(ball* elem, float coord_x, float coord_y){
    ofSetColor(255,255,255);
    ofDrawCircle((coord_x)*scale+x_offset, y_offset-(coord_y)*scale, (elem->get_radius()-0) *scale);
    return;
}

void painter::draw(bar* elem, float coord_x, float coord_y){
    ofSetColor(255, 255, 255);
    ofDrawLine((coord_x-elem->x())*scale+x_offset,y_offset-(coord_y-elem->y())*scale, (coord_x+elem->x())*scale+x_offset,y_offset-(coord_y+elem->y())*scale);
    return;
}