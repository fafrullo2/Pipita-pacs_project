#include "painter.h"
//scale factor = 3
int scale=15;
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
    ofDrawBitmapString("Lives: ",400,20);
    switch(lives){
        case 1:
            ofDrawBitmapString("1",450,20);
        break;
        case 2:
            ofDrawBitmapString("2 ",450,20);
        break;
        case 3:
            ofDrawBitmapString("3",450,20);
        break;
    }     
    ofDrawLine(30, y_offset, 30, y_offset-30*scale );
    ofDrawLine(30+20*scale, y_offset, 30+20*scale, y_offset-30*scale );
    ofDrawLine(30, y_offset-30*scale, 30+20*scale, y_offset-30*scale);
    ofSetColor(255, 0, 0);
    ofDrawLine(30, y_offset, 30+20*scale, y_offset);
    ofDrawBitmapString("Lives: ",400,20);ofDrawBitmapString("Blue bricks still have 3 lives \nGreen bricks have 2 lives \nRed bricks are down to their last life ",400,70);

}


void painter::setup_draw(){ //setup phase
    ofSetColor(255, 255, 255);
    ofDrawBitmapString("Use Up and Down keys on your keyboard \nto set the kinect angle.\nIn the game you will move the bar left \nand right by moving your hand left or right.\nMove your hand up to rotate the bar anti-clockwise,\ndown to rotate it clockwise.\nDon't let the ball hit the red line!\nPress Right when you are ready to start\nNote that the Kinect will only track \nobjects between 1m and 1.15m, so position\nyourself at a distance such that only your hand are \nvisible on screen.", 0, 10);
    ofSetColor(0,255,0);
    ofDrawLine(200,192 , 840,192 );
    ofDrawLine(200,288 , 840,288 );
    ofDrawLine(456,0, 456, 480 );
    ofDrawLine(584,0, 584, 480 );
    ofSetColor(0,0,255);
}
void painter::endgame_draw(bool victory){ //endgame phase 
    if(victory){
        ofSetColor(0, 0, 255);
        ofDrawBitmapString("You won!!!", 50, 10);
    }
    else{
        ofSetColor(255, 0, 0);
        ofDrawBitmapString("You have no more lives :(", 50, 10);
    }
    ofSetColor(255, 255, 255);
    ofDrawBitmapString("Use the Up Key to play again, \n or use the down key to exit", 0, 70);

}


void painter::draw(brick* elem, float coord_x, float coord_y){ //draw a brick

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


void painter::draw(ball* elem, float coord_x, float coord_y){ //draw the ball
    ofSetColor(255,255,255);
    ofDrawCircle((coord_x)*scale+x_offset, y_offset-(coord_y)*scale, (elem->get_radius()-0) *scale);
    return;
}

void painter::draw(bar* elem, float coord_x, float coord_y){ //draw the bar
    ofSetColor(255, 255, 255);
    ofDrawLine((coord_x-elem->x())*scale+x_offset,y_offset-(coord_y-elem->y())*scale, (coord_x+elem->x())*scale+x_offset,y_offset-(coord_y+elem->y())*scale);
    return;
}