//
//  ofxMpplrController.cpp
//  ofxMpplrExample
//
//  Created by maxillacult on 12/01/20.
//  Copyright (c) 2012 maxillacult. All rights reserved.
//

#include "ofxMpplrController.h"

void ofxMpplrController::setup(ofxMpplrScreen *_child){
	child = _child;
	child->bDebug = true;
	ofRegisterKeyEvents(this);
	ofRegisterMouseEvents(this);
	ofxXmlSettings xml;
	
	string uimg = "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";
	
	stringstream ss;
	ss << uimg;
	Poco::Base64Decoder b64in(ss);
	
	ofBuffer buffer;
	b64in >> buffer;
	
	image.loadImage(buffer);
	
	for (int i = 0;i < 10;i++){
		FileEnable[i] = xml.loadFile("preset"+ofToString(i)+".xml");
	}
}

void ofxMpplrController::draw(int x, int y){
	win_x = x;
	win_y = y;

	glPushMatrix();
	glTranslatef(x, y, 0);
	
	ofSetHexColor(0xFFFFFF);
	image.draw(0,0);

	ofEnableBlendMode(OF_BLENDMODE_ADD);
	ofSetHexColor(0x660000);
	if (child->Edit_phase == PHASE_POINT) ofRect(  0, 0, 40, 40);
	if (child->Edit_phase == PHASE_RECTM) ofRect( 40, 0, 40, 40);
	if (child->Edit_phase == PHASE_PLATE) ofRect( 80, 0, 40, 40);
	if (child->Edit_phase == PHASE_MAGNE) ofRect(120, 0, 40, 40);
	ofSetColor(0, 0, 255);
	if (child->bDebug) ofRect(160, 0, 39,39);
	ofSetColor(0, 0, 255);
	if (child->bFix) ofRect(200, 0, 39,39);
	for (int i = 0;i < 10;i++){
		if (FileEnable[i]){
			ofSetHexColor(0x0000aa);
			if (child->loaden == i) ofSetHexColor(0xaa00aa);
			ofFill();
			ofRect(i*20, 40, 20, 40);
			ofNoFill();				
		}
	}
	ofFill();
	ofEnableBlendMode(OF_BLENDMODE_ALPHA);
	glPopMatrix();
	string message;
	switch (typeMessage) {
		case 0:
			message = "";
			break;
		case 1:
			message = "-- Point";
			break;
		case 2:
			message = "-- Rect";
			break;
		case 3:
			message = "-- Plate";
			break;
		case 4:
			message = "-- Magnet";
			break;
		case 5:
			message = "-- Debug";
			break;
		case 6:
			message = "-- Fix";
			break;
			
		default:
			break;
	}
	if (typeMessage != 0){
		ofSetHexColor(0x000000);
		ofRect(ofGetMouseX()+10, ofGetMouseY()-6, 80, 13);		
	}
	ofSetHexColor(0xFFFFFF);
	ofDrawBitmapString(message, ofGetMouseX()+12, ofGetMouseY()+4);
}

void ofxMpplrController::mousePressed(ofMouseEventArgs &mouse){
	int touched = -1;
	if ((win_y < mouse.y)&&(mouse.y < win_y+40)){
		touched = MIN(5,MAX((mouse.x - win_x)/40,0));
	}
	switch (touched) {
		case 0:
			child->Edit_phase = PHASE_POINT;
			break;
		case 1:
			child->Edit_phase = PHASE_RECTM;
			break;
		case 2:
			child->Edit_phase = PHASE_PLATE;
			break;
		case 3:
			child->Edit_phase = PHASE_MAGNE;
			break;
		case 4:
			child->bDebug = !child->bDebug;
			break;
		case 5:
			child->bFix = !child->bFix;
			break;
		default:
			break;
	}
	if ((win_y+40 < mouse.y)&&(mouse.y < win_y+80)){
		touched = MIN(10,MAX((mouse.x - win_x)/20,0));
		if ((mouse.y - win_y - 40) < 20){
			child->LoadXML(touched);
		}
		if ((mouse.y - win_y - 40) > 20){
			child->SaveXML(touched);
			FileEnable[touched] = true;
		}
	}
}

void ofxMpplrController::mouseDragged(ofMouseEventArgs &mouse){
	
}

void ofxMpplrController::mouseMoved(ofMouseEventArgs &mouse){
	int touched = -1;
	if ((win_y < mouse.y)&&(mouse.y < win_y+40)){
		touched = MIN(5,MAX((mouse.x - win_x)/40,0));
	}
	typeMessage = touched+1;
}

void ofxMpplrController::mouseReleased(ofMouseEventArgs &mouse){
	
}

void ofxMpplrController::keyPressed(ofKeyEventArgs &key){
	if (key.key == 'z') child->Edit_phase = PHASE_POINT;
	if (key.key == 'x') child->Edit_phase = PHASE_RECTM;
	if (key.key == 'c') child->Edit_phase = PHASE_PLATE;
	if (key.key == 'v') child->Edit_phase = PHASE_MAGNE;
	if (key.key == 'b') child->bDebug = !child->bDebug;
	if (key.key == 'n') child->bFix = !child->bFix;
}

void ofxMpplrController::keyReleased(ofKeyEventArgs &key){
	
}