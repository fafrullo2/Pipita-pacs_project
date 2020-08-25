#include "ofApp.h"
#include<thread>
#include<chrono>

//--------------------------------------------------------------
void ofApp::setup(){
    field =new game_field();
    camera.setCameraTiltAngle(0);
    camera.init();
    camera.open();
    camera.setDepthClipping(500, 650);
    ofBackground(0,0,0);
}

//--------------------------------------------------------------
void ofApp::update(){
    camera.update();
    if(setup__var){}
    else if(field->lives()>0 && field->bricks_alive() && !setup__var ){
        update_cycle++;
        if(update_cycle==5){
            update_cycle=0;
            float xpos=0, ypos=0, depth=0;
            int counter=0;
            
            for(int x=0; x<camera.getWidth();x=x+3){
                for (int y=0;y<camera.getHeight(); y=y+3){
                    depth=camera.getDistanceAt(x,y);
                    if(depth>=500 && depth<= 650){
                        xpos+=x;
                        ypos+=y;
                        counter++;
                    }
                }
            } 
            xpos=xpos/counter;
            ypos=ypos/counter;
            //ofDrawCircle(xpos+300, 500-ypos, 6);
            camera.drawDepth(300, 0);
            if(xpos>(camera.getWidth()/2 + camera.getWidth()/10))
                field->check_bound_l();
            if(xpos<(camera.getWidth()/2 - camera.getWidth()/10))
                field->check_bound_r();
            if(ypos>(camera.getHeight()/2 + camera.getHeight()/10))
                field->check_bound_d();
            if(ypos<(camera.getHeight()/2 - camera.getHeight()/10))
                field->check_bound_u();
        }
    field->move_ball();    
    }
        
    else{
        endgame=true;
        if( play_again && chose){
            delete field;
            field= new game_field();
        }
        else if(chose) {
        delete field;
        camera.close();
        ofExit();
        }
        return;
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    if(setup__var){
        camera.drawDepth(200, 0, 640, 480);    
        field->draw_setup();
    }
    else if(!setup__var && !endgame){
        
        field->draw();
    }
    else if(endgame){
        field->draw_endgame();
    }
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    switch (key){
        case OF_KEY_UP:
            if(setup__var){
                alpha++;
                if(alpha>=30){
                    alpha=30;
                    }
                camera.setCameraTiltAngle(alpha);
            }
            if(endgame){
                play_again=true;
                chose=true;
                setup__var=true;
            }
            break;
        case OF_KEY_DOWN:
            if(setup__var){
                alpha--;
                if(alpha<=-30){
                    alpha=-30;
                }   
                camera.setCameraTiltAngle(alpha);
            }
            if(endgame){
                play_again=false;
                chose=true;
            }
            break;
        case OF_KEY_RIGHT:
            setup__var=false;
            break;
    }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}