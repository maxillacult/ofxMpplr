#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
	ofEnableBlendMode(OF_BLENDMODE_ALPHA);
	ofSetFrameRate(60);
	ofSetVerticalSync(true);
	
	//ofxMpplr Initialize
	buf.setup(640, 480);
	con.setup(&buf);
	buf.LoadXML(0);
}

//--------------------------------------------------------------
void testApp::update(){
}

//--------------------------------------------------------------
void testApp::draw(){
	
	//You can draw anything between Begin(); and End();
	buf.Begin();
	glClearColor(0, 0, 0, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	ofSetHexColor(0xFF0000);
	for (int i = 0;i < 480;i+=30){
		ofRect(0, ofGetFrameNum()%30+i, 640, 10);
	}
	buf.End();
	
	
	ofSetHexColor(0xFFFFFF);
	ofBackground(0, 0, 0);

	//Sub Display out
	buf.draw(1440,0, 640, 480);
	
	//Monitor out
	buf.draw(640, 0, 640, 480);
	
	//Source out
	buf.drawBuffer(0, 0, 640, 480);
	
	//draw ofxMpplrController
	con.draw(50, 500);
	
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){
	if (key == 'f') ofToggleFullscreen();
}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){ 

}