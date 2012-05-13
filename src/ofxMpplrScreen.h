//
//  ofxMpplrScreen.h
//  ofxMpplrExample
//
//  Created by maxillacult on 12/01/20.
//  Copyright (c) 2012 maxillacult. All rights reserved.
//
#pragma once
#include "ofMain.h"
#include "ofxXmlSettings.h"
#include <deque>

#define PHASE_POINT 0x01
//#define PHASE_JOINT 0x02
#define PHASE_PLATE 0x03
#define PHASE_RECTM 0X04
#define PHASE_MAGNE 0x05
#define PHASE_NOEDIT 0x06

#define SUB_POINT_MAKE 0x00
#define SUB_POINT_MOVE 0x01

#define SUB_TRIANGLE_MOVE 0X00

#define SUB_MAGNET_MAKE 0x00
#define SUB_MAGNET_MOVE 0x01

#define PANEL_TEX	0x00
#define PANEL_VER	0x01
#define PANEL_NONE	0x02

struct Triangle{
	GLfloat point[6];
};

class ofxMpplrScreen{
public:
	
	//Setup params and call frame buffer allocation
	void setup(int width,int height);
	
	//Call ofFbo's begin() & end()
	void Begin();
	void End();
	
	//Draw transformed image.
	void draw(float x,float y,float width,float height);
	//Draw rect Image
	void drawBuffer(float x,float y,float width,float height);
	//Draw OutPutImage
  void drawOutPut(float x,float y,float width,float height);
  
	//Other sub functions
	void LoadXML(int num);
	void SaveXML(int num);
	void makeTriangles(Triangle tri);

	//Mouse & Key Events
	void mousePressed(ofMouseEventArgs& mouse);
	void mouseDragged(ofMouseEventArgs& mouse);
	void mouseMoved(ofMouseEventArgs& mouse);
	void mouseReleased(ofMouseEventArgs& mouse);
	void keyPressed(ofKeyEventArgs  &key);
	void keyReleased(ofKeyEventArgs &key);
	
  int getInMouseX();
  int getInMouseY();
  bool getInMousePressed();
  
	int Edit_phase;
	int edit_Panel;
	int Sub_phase;
	int loaden;
	bool bFix;
	bool bDebug;
  bool bCanEdit;
	
protected:
	//deques can use param pct of screen width/height 0.0f~1.0f
	int active_point[2];
	int active_triangle;
	int active_magnet;
	int active_magnev;
	int ph;
	float win_x,win_y,win_w,win_h;
	float ver_x,ver_y,ver_w,ver_h;
	int mx,my;
  int _mouseX;
  int _mouseY;
  bool _mousePressed;
	
	Triangle Stock;
	deque <Triangle*> Texcoord;
	deque <Triangle*> Vertexes;
	deque <ofPoint> magnets;
	deque <ofPoint> magnetv;
	ofFbo buffer;
};