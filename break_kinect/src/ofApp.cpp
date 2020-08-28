#include "ofApp.h"
#include<thread>
#include<chrono>

//--------------------------------------------------------------
void ofApp::setup(){
    field =new game_field();
    camera.setCameraTiltAngle(0);
    camera.init();
    camera.open();
    camera.setDepthClipping(1000, 1150);
    ofBackground(0,0,0);
    ofSetVerticalSync(true);
}

//--------------------------------------------------------------
void ofApp::update(){
    std::chrono::steady_clock::time_point before, after;
    before=std::chrono::steady_clock::now();
    camera.update();
    if(setup__var){}//do nothing during setup
    else if(field->lives()>0 && field->bricks_alive() && !setup__var ){ //game phase cycle
        if(update_cycle==true){
            update_cycle=false;
            double xpos=0, ypos=0, depth=0;
            long int counter=0;
            
            for(int x=0; x<camera.getWidth();x=x+10){
                for (int y=0;y<camera.getHeight(); y=y+10){
                   depth=camera.getDistanceAt(x,y);
                    if(depth>=1000 && depth<= 1150){
                        xpos+=x;
                        ypos+=y;
                        counter++;
                    }
                }
            } 
            xpos=xpos/counter;
            ypos=ypos/counter;
            if(xpos>(camera.getWidth()/2 + camera.getWidth()/10))
                field->check_bound_l();
            if(xpos<(camera.getWidth()/2 - camera.getWidth()/10))
                field->check_bound_r();
            if(ypos>(camera.getHeight()/2 + camera.getHeight()/10))
                field->check_bound_d();
            if(ypos<(camera.getHeight()/2 - camera.getHeight()/10))
                field->check_bound_u();

        }
    else{
        field->move_ball();
        update_cycle=true;
        
        }  
          
    }
        
    else{                                   //endgame phase
        endgame=true;
        if( play_again && chose){
            delete field;
            field= new game_field();
            endgame=false;
            setup__var=false;
            play_again=false;
            chose=false;
        }
        else if(chose && !play_again) {
            delete field;
            camera.close();
            ofBaseApp::exit();
            ofExit();
        }
        return;
    }
    after=std::chrono::steady_clock::now();
    if(std::chrono::duration_cast<std::chrono::milliseconds>(after-before)<std::chrono::milliseconds(20))
        std::this_thread::sleep_for(std::chrono::milliseconds(20)-std::chrono::duration_cast<std::chrono::milliseconds>(after-before));

}

//--------------------------------------------------------------
void ofApp::draw(){
    
    if(setup__var){ //setup phase 
        camera.drawDepth(200, 0, 640, 480);    
        field->draw_setup();
    }
    else if(!setup__var && !endgame){ //game phase
        
        field->draw();
    }
    else if(endgame){       //endgame phase
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