//
//  ofxMpplrController.h
//  ofxMpplrExample
//
//  Created by maxillacult on 12/01/20.
//  Copyright (c) 2012 maxillacult. All rights reserved.
//


#pragma once
#include "ofMain.h"
#include "ofxMpplrScreen.h"
#include "Poco/Base64Decoder.h"
#define BUTTON_NUM 6

class ofxMpplrController{
public:
	void setup(ofxMpplrScreen* _child);
	void draw(int x,int y);
	
	void mousePressed(ofMouseEventArgs& mouse);
	void mouseDragged(ofMouseEventArgs& mouse);
	void mouseMoved(ofMouseEventArgs& mouse);
	void mouseReleased(ofMouseEventArgs& mouse);
	void keyPressed(ofKeyEventArgs  &key);
	void keyReleased(ofKeyEventArgs &key);
	
protected:
	int typeMessage;
	ofImage image;
	bool FileEnable[10];
	ofxMpplrScreen* child;
	int win_x,win_y;
};