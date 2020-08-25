#pragma once

#include "ofMain.h"
#include "game_field.h"
#include "ofxKinect.h"





class ofApp : public ofBaseApp{
	public:
		void setup();
		void update();
		void draw();
		
		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y);
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
	private:
		game_field* field;
		ofxKinect camera;
		int update_cycle=0; //one every five ticks
		bool setup__var=true, endgame=false, chose=false, play_again=false;
		float alpha=0;
};
