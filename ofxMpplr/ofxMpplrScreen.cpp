//
//  ofxMpplrScreen.cpp
//  ofxMpplrExample
//
//  Created by maxillacult on 12/01/20.
//  Copyright (c) 2012 maxillacult. All rights reserved.
//

#include "ofxMpplrScreen.h"

void ofxMpplrScreen::setup(int width, int height){
	buffer.allocate(width, height,GL_RGBA,1);
	buffer.begin();
	glClearColor(0, 0, 0, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	buffer.end();
	ofRegisterMouseEvents(this);
	ofRegisterKeyEvents(this);
	ph = 0;
	Edit_phase = PHASE_POINT;
	Sub_phase = 0x00;
	active_triangle = -1;
	active_point[0] = -1;
	active_point[1] = -1;
	bFix = true;
	edit_Panel = PANEL_TEX;
	loaden = -1;
}

void ofxMpplrScreen::Begin(){
	buffer.begin();
}

void ofxMpplrScreen::End(){
	buffer.end();
}

void ofxMpplrScreen::makeTriangles(Triangle tri){
	Triangle* t = new Triangle;
	Triangle* t2= new Triangle;
	t->point[0] = tri.point[0];
	t->point[1] = tri.point[1];
	t->point[2] = tri.point[2];
	t->point[3] = tri.point[3];
	t->point[4] = tri.point[4];
	t->point[5] = tri.point[5];
	t2->point[0] = tri.point[0];
	t2->point[1] = tri.point[1];
	t2->point[2] = tri.point[2];
	t2->point[3] = tri.point[3];
	t2->point[4] = tri.point[4];
	t2->point[5] = tri.point[5];
	Texcoord.push_back(t);
	Vertexes.push_back(t2);
}

void ofxMpplrScreen::draw(float x,float y,float width,float height){
	ver_x = x;
	ver_y = y;
	ver_w = width;
	ver_h = height;
	string message = "";
	
	glPushMatrix();
	glTranslatef(x, y, 0.0f);
	buffer.getTextureReference().bind();
	glBegin(GL_TRIANGLES);
	for (int i = 0;i < Vertexes.size();i++){
		glTexCoord2f(Texcoord[i]->point[0]*width,
					 Texcoord[i]->point[1]*height);
		glVertex2f(Vertexes[i]->point[0]*width, 
				   Vertexes[i]->point[1]*height);
		glTexCoord2f(Texcoord[i]->point[2]*width,
					 Texcoord[i]->point[3]*height);
		glVertex2f(Vertexes[i]->point[2]*width, 
				   Vertexes[i]->point[3]*height);
		glTexCoord2f(Texcoord[i]->point[4]*width,
					 Texcoord[i]->point[5]*height);
		glVertex2f(Vertexes[i]->point[4]*width, 
				   Vertexes[i]->point[5]*height);
	}
	glEnd();
	buffer.getTextureReference().unbind();
	glPopMatrix();
	
	if (bDebug){
		glPushMatrix();
		glTranslatef(x, y, 0.0f);
		
		ofSetColor(255, 255, 255,128);
		for (int i = 0;i < width;i+=40){
			ofLine(i, 0, i, height);
		}
		for (int i = 0;i < height;i+=40){
			ofLine(0, i, width, i);
		}
		
		for (int i = 0;i < Texcoord.size();i++){
			ofSetColor(255, 0, 0, 50);
			if (i == active_triangle) ofSetColor(0, 0, 255, 50);
			glBegin(GL_TRIANGLES);
			glVertex2f(Vertexes[i]->point[0]*width, 
					   Vertexes[i]->point[1]*height);
			glVertex2f(Vertexes[i]->point[2]*width, 
					   Vertexes[i]->point[3]*height);
			glVertex2f(Vertexes[i]->point[4]*width, 
					   Vertexes[i]->point[5]*height);
			glEnd();
			
			ofSetHexColor(0xFFFFFF);
			glBegin(GL_LINE_LOOP);
			glVertex2f(Vertexes[i]->point[0]*width, 
					   Vertexes[i]->point[1]*height);
			glVertex2f(Vertexes[i]->point[2]*width, 
					   Vertexes[i]->point[3]*height);
			glVertex2f(Vertexes[i]->point[4]*width, 
					   Vertexes[i]->point[5]*height);
			glEnd();
		}
		
		if (edit_Panel == PANEL_VER){
			if (Edit_phase == PHASE_POINT){
				message = "-- Move point";
				for (int i = 0;i < Vertexes.size();i++){
					for (int j = 0;j < 3;j++){
						if (ofDist(Vertexes[i]->point[j*2  ]*width, 
								   Vertexes[i]->point[j*2+1]*height, 
								   ofGetMouseX()-x, ofGetMouseY()-y) < 10){
							Sub_phase = SUB_POINT_MOVE;
							ofSetHexColor(0xFF0000);
							ofNoFill();
							ofCircle(Vertexes[i]->point[j*2  ]*width, 
									 Vertexes[i]->point[j*2+1]*height,8);
							ofFill();
						}
					}
				}
			}else if (Edit_phase == PHASE_PLATE){
				message = "-- Move Panel";
				Sub_phase = SUB_TRIANGLE_MOVE;
			}else if (Edit_phase == PHASE_RECTM){
				message = "-- Edit Only Source Panel";
			}else if (Edit_phase == PHASE_MAGNE){
				message = "-- Make magnet";
				Sub_phase = SUB_MAGNET_MAKE;
				for (int i = 0;i < magnetv.size();i++){
					ofSetHexColor(0xFFFFFF);
					ofNoFill();
					ofCircle(magnetv[i].x*width, magnetv[i].y*height, 5);
					ofFill();
					ofSetColor(50,50,255,128);
					ofCircle(magnetv[i].x*width, magnetv[i].y*height, 4);
					
					if (i == active_magnev){
						ofSetColor(255, 255, 0);
						ofNoFill();
						ofCircle(magnetv[i].x*width, 
								 magnetv[i].y*height,10);
						ofFill();
					}
					
					if (ofDist(magnetv[i].x*width, 
							   magnetv[i].y*height, 
							   ofGetMouseX()-x, ofGetMouseY()-y) < 10){
						Sub_phase = SUB_MAGNET_MOVE;
						message = "-- Move magnet";
						ofSetHexColor(0xaa33FF);
						ofNoFill();
						ofCircle(magnetv[i].x*width, 
								 magnetv[i].y*height,8);
						ofFill();
					}
				}
			}
		}else{
			ofSetColor(0, 0, 0,100);
			ofRect(0, 0, width, height);
		}
		ofNoFill();
		ofSetHexColor(0xFFFFFF);
		ofRect(0,0,width,height);
		ofFill();
		glPopMatrix();
		ofSetHexColor(0xFFFFFF);
		ofDrawBitmapString(message, ofGetMouseX()+12, ofGetMouseY()+4);
	}

}

void ofxMpplrScreen::drawBuffer(float x, float y, float width, float height){
	static bool bRectReady = false;
	static ofPoint rect_top;
	win_x = x;
	win_y = y;
	win_w = width;
	win_h = height;
	ofSetHexColor(0xFFFFFF);
	buffer.draw(x, y,width,height);
	if (bDebug){
		glPushMatrix();
		glTranslatef(x, y, 0.0f);
		for (int i = 0;i < Texcoord.size();i++){
			ofSetColor(255, 0, 0, 50);
			if (i == active_triangle) ofSetColor(0, 0, 255, 50);
			glBegin(GL_TRIANGLES);
			glVertex2f(Texcoord[i]->point[0]*width, 
					   Texcoord[i]->point[1]*height);
			glVertex2f(Texcoord[i]->point[2]*width, 
					   Texcoord[i]->point[3]*height);
			glVertex2f(Texcoord[i]->point[4]*width, 
					   Texcoord[i]->point[5]*height);
			glEnd();
			
			ofSetHexColor(0xFFFFFF);
			glBegin(GL_LINE_LOOP);
			glVertex2f(Texcoord[i]->point[0]*width, 
					   Texcoord[i]->point[1]*height);
			glVertex2f(Texcoord[i]->point[2]*width, 
					   Texcoord[i]->point[3]*height);
			glVertex2f(Texcoord[i]->point[4]*width, 
					   Texcoord[i]->point[5]*height);
			glEnd();			
		}		
		
		ofSetHexColor(0xFFFFFF);
		for (int i = 0;i < ph;i++){
			ofCircle(Stock.point[i*2  ]*width, 
					 Stock.point[i*2+1]*height,3);
		}
		glBegin(GL_LINE_LOOP);
		for (int i = 0;i < ph;i++){
			glVertex2f(Stock.point[i*2  ]*width, 
					   Stock.point[i*2+1]*height);
		}
		glEnd();
		glPopMatrix();
		
		string message = "";
		if (edit_Panel == PANEL_TEX){
			if (Edit_phase == PHASE_POINT){
				message = "-- Make point";
				Sub_phase = SUB_POINT_MAKE;
				
				for (int i = 0;i < Texcoord.size();i++){
					for (int j = 0;j < 3;j++){
						if (ofDist(Texcoord[i]->point[j*2  ]*width, 
								   Texcoord[i]->point[j*2+1]*height, 
								   ofGetMouseX()-x, ofGetMouseY()-y) < 10){
							message = "-- Move point";
							Sub_phase = SUB_POINT_MOVE;
							ofSetHexColor(0xFF0000);
							glPushMatrix();
							glTranslatef(x, y, 0);
							ofNoFill();
							ofCircle(Texcoord[i]->point[j*2  ]*width, 
									 Texcoord[i]->point[j*2+1]*height,8);
							ofFill();
							glPopMatrix();
						}
					}
				}
			}
			else if (Edit_phase == PHASE_PLATE)
			{
				message = "-- Move Panel";
				Sub_phase = SUB_TRIANGLE_MOVE;
				
			}
			else if(Edit_phase == PHASE_RECTM)
			{
				message = "-- Make Rectangle";
				if (ofGetMousePressed() && !bRectReady){
					if ((win_x < ofGetMouseX())&&(ofGetMouseX() < win_x+win_w)&&
						(win_y < ofGetMouseY())&&(ofGetMouseY() < win_y+win_h)){
						bRectReady = true;
						rect_top = ofPoint(ofGetMouseX(),ofGetMouseY());
					}
				}
				if (!ofGetMousePressed() && bRectReady){
					bRectReady = false;
					Triangle t,t2;
					t.point[0] = MAX(MIN(1.0f,(rect_top.x - x) / width),0);
					t.point[1] = MAX(MIN(1.0f,(rect_top.y - y) / height),0);
					t.point[2] = MAX(MIN(1.0f,(rect_top.x - x) / width),0);
					t.point[3] = MAX(MIN(1.0f,(ofGetMouseY() - y) / height),0);
					t.point[4] = MAX(MIN(1.0f,(ofGetMouseX() - x) / width),0);
					t.point[5] = MAX(MIN(1.0f,(rect_top.y - y) / height),0);
					
					t2.point[0] = t.point[4];
					t2.point[1] = t.point[5];
					t2.point[2] = t.point[2];
					t2.point[3] = t.point[3];
					t2.point[4] = MAX(MIN(1.0f,(ofGetMouseX() - x) / width),0);
					t2.point[5] = MAX(MIN(1.0f,(ofGetMouseY() - y) / height),0);
					makeTriangles(t);
					makeTriangles(t2);
				}
				if (ofGetMousePressed()&&(bRectReady)){
					ofSetHexColor(0xFFFFFF);
					ofNoFill();
					ofRect(rect_top.x - x, rect_top.y - y, ofGetMouseX() - rect_top.x, ofGetMouseY() - rect_top.y);
					ofFill();
				}
			}
			else if (Edit_phase == PHASE_MAGNE){
				message = "-- Make Magnet";
				Sub_phase = SUB_MAGNET_MAKE;
				for (int i = 0;i < magnets.size();i++){
					ofSetHexColor(0xFFFFFF);
					ofNoFill();
					ofCircle(magnets[i].x*width, magnets[i].y*height, 5);
					ofFill();
					ofSetColor(50,50,255,128);
					ofCircle(magnets[i].x*width, magnets[i].y*height, 4);
					
					if (i == active_magnet){
						ofSetColor(255, 255, 0);
						ofNoFill();
						ofCircle(magnets[i].x*width, 
								 magnets[i].y*height,10);
						ofFill();
					}
					
					if (ofDist(magnets[i].x*width, 
								magnets[i].y*height, 
								ofGetMouseX()-x, ofGetMouseY()-y) < 10){
						message = "-- Move Magnet";
						Sub_phase = SUB_MAGNET_MOVE;
						ofSetHexColor(0xaa33FF);
						glPushMatrix();
						glTranslatef(x, y, 0);
						ofNoFill();
						ofCircle(magnets[i].x*width, 
								 magnets[i].y*height,8);
						ofFill();
						glPopMatrix();
					}
				}

			}
			
			ofSetHexColor(0xFFFFFF);
			ofDrawBitmapString(message, ofGetMouseX()+12, ofGetMouseY()+4);
		}else{
			ofSetColor(0, 0, 0,100);
			ofRect(0, 0, width, height);
		}
	}

	
	ofNoFill();
	ofSetHexColor(0xFFFFFF);
	ofRect(x, y, width, height);
	ofFill();
}

void ofxMpplrScreen::mousePressed(ofMouseEventArgs &mouse){
	if (!bDebug) return;
	if (edit_Panel == PANEL_TEX){
		if (Edit_phase == PHASE_POINT){
			if (Sub_phase == SUB_POINT_MAKE){
				Stock.point[ph*2  ] = MAX(MIN(1.0f,(mouse.x - win_x) / win_w),0.0f);
				Stock.point[ph*2+1] = MAX(MIN(1.0f,(mouse.y - win_y) / win_h),0.0f);
				ph++;
				if (ph == 3){
					ph = 0;
					makeTriangles(Stock);
					Stock.point[0] = 0.0f;
					Stock.point[1] = 0.0f;
					Stock.point[2] = 0.0f;
					Stock.point[3] = 0.0f;
					Stock.point[4] = 0.0f;
					Stock.point[5] = 0.0f;
				}
			}else if(Sub_phase == SUB_POINT_MOVE){
				
			}
		}else if (Edit_phase == PHASE_PLATE){
			active_triangle = -1;
			float x1,x2,x3,x4,y1,y2,y3,y4;
			for (int i = 0;i < Texcoord.size();i++){
				x1 = Texcoord[i]->point[0];
				y1 = Texcoord[i]->point[1];
				x2 = Texcoord[i]->point[2];
				y2 = Texcoord[i]->point[3];
				x3 = Texcoord[i]->point[4];
				y3 = Texcoord[i]->point[5];
				x4 = (ofGetMouseX() - win_x) / win_w;
				y4 = (ofGetMouseY() - win_y) / win_h;
				
				if ((x4*(y1-y2)+x1*(y2-y4)+x2*(y4-y1) > 0) &&
					(x4*(y2-y3)+x2*(y3-y4)+x3*(y4-y2) > 0) &&
					(x4*(y3-y1)+x3*(y1-y4)+x1*(y4-y3) > 0)){
					active_triangle = i;
				}
				if ((x4*(y1-y2)+x1*(y2-y4)+x2*(y4-y1) < 0) &&
					(x4*(y2-y3)+x2*(y3-y4)+x3*(y4-y2) < 0) &&
					(x4*(y3-y1)+x3*(y1-y4)+x1*(y4-y3) < 0)){
					active_triangle = i;
				}
			}
		}else if (Edit_phase == PHASE_MAGNE){
			if (Sub_phase == SUB_MAGNET_MAKE){
				ofPoint p;
				p.x = (mouse.x - win_x) / win_w;
				p.y = (mouse.y - win_y) / win_h;
				magnets.push_back(p);
				active_magnet = magnets.size()-1;
				for (int i = 0;i < Texcoord.size();i++){
					for (int j = 0;j < 3;j++){
						if (ofDist(Texcoord[i]->point[j*2  ]*win_w, 
								   Texcoord[i]->point[j*2+1]*win_h, 
								   mouse.x-win_x, mouse.y-win_y) < 10){
							Texcoord[i]->point[j*2  ] = p.x;
							Texcoord[i]->point[j*2+1] = p.y;

						}
					}
				}
			}else if (Sub_phase == SUB_MAGNET_MOVE){
				for (int i = 0;i < magnets.size();i++){
					if (ofDist(magnets[i].x*win_w, 
							   magnets[i].y*win_h, 
							   mouse.x-win_x, mouse.y-win_y) < 10){
						active_magnet = i;
					}
				}
			}
		}

		
	}else if(edit_Panel == PANEL_VER){
		if (Edit_phase == PHASE_PLATE){
			active_triangle = -1;
			float x1,x2,x3,x4,y1,y2,y3,y4;
			for (int i = 0;i < Vertexes.size();i++){
				x1 = Vertexes[i]->point[0];
				y1 = Vertexes[i]->point[1];
				x2 = Vertexes[i]->point[2];
				y2 = Vertexes[i]->point[3];
				x3 = Vertexes[i]->point[4];
				y3 = Vertexes[i]->point[5];
				x4 = (ofGetMouseX() - ver_x) / ver_w;
				y4 = (ofGetMouseY() - ver_y) / ver_h;
				
				if ((x4*(y1-y2)+x1*(y2-y4)+x2*(y4-y1) > 0) &&
					(x4*(y2-y3)+x2*(y3-y4)+x3*(y4-y2) > 0) &&
					(x4*(y3-y1)+x3*(y1-y4)+x1*(y4-y3) > 0)){
					active_triangle = i;
				}
				if ((x4*(y1-y2)+x1*(y2-y4)+x2*(y4-y1) < 0) &&
					(x4*(y2-y3)+x2*(y3-y4)+x3*(y4-y2) < 0) &&
					(x4*(y3-y1)+x3*(y1-y4)+x1*(y4-y3) < 0)){
					active_triangle = i;
				}
			}
		}
		if (Edit_phase == PHASE_MAGNE){
			if (Sub_phase == SUB_MAGNET_MAKE){
				ofPoint p;
				p.x = (mouse.x - ver_x) / ver_w;
				p.y = (mouse.y - ver_y) / ver_h;
				magnetv.push_back(p);
				active_magnev = magnetv.size()-1;
				for (int i = 0;i < Vertexes.size();i++){
					for (int j = 0;j < 3;j++){
						if (ofDist(Vertexes[i]->point[j*2  ]*ver_w, 
								   Vertexes[i]->point[j*2+1]*ver_h, 
								   mouse.x-ver_x, mouse.y-ver_y) < 10){
							Vertexes[i]->point[j*2  ] = p.x;
							Vertexes[i]->point[j*2+1] = p.y;
						}
					}
				}
			}else if (Sub_phase == SUB_MAGNET_MOVE){
				for (int i = 0;i < magnetv.size();i++){
					if (ofDist(magnetv[i].x*ver_w, 
							   magnetv[i].y*ver_h, 
							   mouse.x-ver_x, mouse.y-ver_y) < 10){
						active_magnev = i;
					}
				}
			}
		}

	}
	mx = mouse.x;
	my = mouse.y;
}

void ofxMpplrScreen::mouseDragged(ofMouseEventArgs &mouse){
		if (!bDebug) return;
	if (edit_Panel == PANEL_TEX){
		if (Edit_phase == PHASE_POINT){
			if (Sub_phase == SUB_POINT_MOVE){
				for (int i = 0;i < Texcoord.size();i++){
					for (int j = 0;j < 3;j++){
						if (ofDist(Texcoord[i]->point[j*2  ]*win_w, 
								   Texcoord[i]->point[j*2+1]*win_h, 
								   ofGetMouseX()-win_x, ofGetMouseY()-win_y) < 10){
							if ((active_point[0] == -1)&&(active_point[1] == -1)){
								active_point[0] = i;
								active_point[1] = j;
							}
						}
					}
				}
				if ((active_point[0] > -1)&&(active_point[1] > -1)){
					Texcoord[active_point[0]]->point[active_point[1]*2  ] = MAX(MIN(1.0f,(mouse.x - win_x) / win_w),0.0f);
					Texcoord[active_point[0]]->point[active_point[1]*2+1] = MAX(MIN(1.0f,(mouse.y - win_y) / win_h),0.0f);
					if (bFix){
						Vertexes[active_point[0]]->point[active_point[1]*2  ] = MAX(MIN(1.0f,(mouse.x - win_x) / win_w),0.0f);
						Vertexes[active_point[0]]->point[active_point[1]*2+1] = MAX(MIN(1.0f,(mouse.y - win_y) / win_h),0.0f);
					}
				}
			}
		}else if (Edit_phase == PHASE_PLATE){
			if (Sub_phase == SUB_TRIANGLE_MOVE){

				if (active_triangle != -1){
					Texcoord[active_triangle]->point[0] += (mouse.x - mx) / win_w;
					Texcoord[active_triangle]->point[1] += (mouse.y - my) / win_h;
					Texcoord[active_triangle]->point[2] += (mouse.x - mx) / win_w;
					Texcoord[active_triangle]->point[3] += (mouse.y - my) / win_h;
					Texcoord[active_triangle]->point[4] += (mouse.x - mx) / win_w;
					Texcoord[active_triangle]->point[5] += (mouse.y - my) / win_h;
					for (int i = 0;i < 6;i++){
						Texcoord[active_triangle]->point[i] = MAX(MIN(1.0f,Texcoord[active_triangle]->point[i]),0.0f);
					}
					if (bFix){
						Vertexes[active_triangle]->point[0] = Texcoord[active_triangle]->point[0];
						Vertexes[active_triangle]->point[1] = Texcoord[active_triangle]->point[1];
						Vertexes[active_triangle]->point[2] = Texcoord[active_triangle]->point[2];
						Vertexes[active_triangle]->point[3] = Texcoord[active_triangle]->point[3];
						Vertexes[active_triangle]->point[4] = Texcoord[active_triangle]->point[4];
						Vertexes[active_triangle]->point[5] = Texcoord[active_triangle]->point[5];
					}
				}
			}
		}else if (Edit_phase == PHASE_MAGNE){
			if ((active_magnet < magnets.size())&&(active_magnet > -1)&&(Sub_phase == SUB_MAGNET_MOVE)){
				magnets[active_magnet].x += (mouse.x - mx) / win_w;
				magnets[active_magnet].y += (mouse.y - my) / win_h;
				
				for (int i = 0;i < Texcoord.size();i++){
					for (int j = 0;j < 3;j++){
						if (ofDist(Texcoord[i]->point[j*2  ]*win_w, 
								   Texcoord[i]->point[j*2+1]*win_h, 
								   mouse.x-win_x, mouse.y-win_y) < 20){
							Texcoord[i]->point[j*2  ] = magnets[active_magnet].x;
							Texcoord[i]->point[j*2+1] = magnets[active_magnet].y;
							if (bFix){
								Vertexes[i]->point[j*2  ] = magnets[active_magnet].x;
								Vertexes[i]->point[j*2+1] = magnets[active_magnet].y;
							}
						}
					}
				}
			}
		}
		

	}else if(edit_Panel == PANEL_VER){
		if (Edit_phase == PHASE_POINT){
			if (Sub_phase == SUB_POINT_MOVE){
				for (int i = 0;i < Vertexes.size();i++){
					for (int j = 0;j < 3;j++){
						if (ofDist(Vertexes[i]->point[j*2  ]*ver_w, 
								   Vertexes[i]->point[j*2+1]*ver_h, 
								   ofGetMouseX()-ver_x, ofGetMouseY()-ver_y) < 10){
							if ((active_point[0] == -1)&&(active_point[1] == -1)){
								active_point[0] = i;
								active_point[1] = j;
							}
						}
					}
				}
				if ((active_point[0] > -1)&&(active_point[1] > -1)){
					Vertexes[active_point[0]]->point[active_point[1]*2  ] = MAX(MIN(1.0f,(mouse.x - ver_x) / ver_w),0.0f);
					Vertexes[active_point[0]]->point[active_point[1]*2+1] = MAX(MIN(1.0f,(mouse.y - ver_y) / ver_h),0.0f);
				}
			}
		}
		if (Edit_phase == PHASE_PLATE){
			if (Sub_phase == SUB_TRIANGLE_MOVE){
				if (active_triangle != -1){
					Vertexes[active_triangle]->point[0] += (mouse.x - mx) / ver_w;
					Vertexes[active_triangle]->point[1] += (mouse.y - my) / ver_h;
					Vertexes[active_triangle]->point[2] += (mouse.x - mx) / ver_w;
					Vertexes[active_triangle]->point[3] += (mouse.y - my) / ver_h;
					Vertexes[active_triangle]->point[4] += (mouse.x - mx) / ver_w;
					Vertexes[active_triangle]->point[5] += (mouse.y - my) / ver_h;
					for (int i = 0;i < 6;i++){
						Vertexes[active_triangle]->point[i] = MAX(MIN(1.0f,Vertexes[active_triangle]->point[i]),0.0f);
					}
				}
			}
		}
		if (Edit_phase == PHASE_MAGNE){
			if ((active_magnev < magnetv.size())&&(active_magnev > -1)&&(Sub_phase == SUB_MAGNET_MOVE)){
				magnetv[active_magnev].x += (mouse.x - mx) / ver_w;
				magnetv[active_magnev].y += (mouse.y - my) / ver_h;
				
				for (int i = 0;i < Vertexes.size();i++){
					for (int j = 0;j < 3;j++){
						if (ofDist(Vertexes[i]->point[j*2  ]*ver_w, 
								   Vertexes[i]->point[j*2+1]*ver_h, 
								   mouse.x-ver_x, mouse.y-ver_y) < 20){
							Vertexes[i]->point[j*2  ] = magnetv[active_magnev].x;
							Vertexes[i]->point[j*2+1] = magnetv[active_magnev].y;
						}
					}
				}
			}
		}


	}
	mx = mouse.x;
	my = mouse.y;
}

void ofxMpplrScreen::mouseMoved(ofMouseEventArgs &mouse){
	if ((win_x < mouse.x)&&(mouse.x < win_x+win_w)&&
		(win_y < mouse.y)&&(mouse.y < win_y+win_h)) edit_Panel = PANEL_TEX;
	else if ((ver_x < mouse.x)&&(mouse.x < ver_x+ver_w)&&
			 (ver_y < mouse.y)&&(mouse.y < ver_y+ver_h)) edit_Panel = PANEL_VER;
	else 
		edit_Panel = PANEL_NONE;

}

void ofxMpplrScreen::mouseReleased(ofMouseEventArgs &mouse){
	active_point[0] = -1;
	active_point[1] = -1;
}

void ofxMpplrScreen::keyPressed(ofKeyEventArgs &key){
	if (key.key == 's') SaveXML(1);
	if (key.key == 'l') LoadXML(1);
	if (Edit_phase == PHASE_POINT){
		if ((Sub_phase == SUB_POINT_MAKE)&&(ph > 0)&&(key.key == 127)){
			ph = 0;
		}
	}
	if (Edit_phase == PHASE_PLATE){
		if ((active_triangle != -1)&&(key.key == 127)){
			Texcoord.erase(Texcoord.begin()+active_triangle);
			Vertexes.erase(Vertexes.begin()+active_triangle);
			active_triangle = -1;
		}
	}
	if (Edit_phase == PHASE_MAGNE){
		if (edit_Panel == PANEL_TEX){
			if ((active_magnet != -1)&&(key.key == 127)){
				magnets.erase(magnets.begin()+active_magnet);
			}			
		}else if (edit_Panel == PANEL_VER){
			if ((active_magnev != -1)&&(key.key == 127)){
				magnetv.erase(magnetv.begin()+active_magnev);
			}
		}
	}
}

void ofxMpplrScreen::keyReleased(ofKeyEventArgs &key){
	
}

void ofxMpplrScreen::LoadXML(int num){
	if (num > 10) return;
	//Max 10 Presets(preset0.xml ~ preset9.xml)
	ofxXmlSettings xml;
	if (!xml.loadFile("preset"+ofToString(num)+".xml")) return;
	loaden = num;
	Texcoord.clear();
	Vertexes.clear();
	magnets.clear();
	magnetv.clear();
	
	int numVerts;
	xml.pushTag("TEX");
	numVerts = xml.getNumTags("PT");
	for (int i = 0;i < numVerts;i+=3){
		Triangle* t = new Triangle();
		t->point[0] = xml.getValue("PT:X", 0.0,i);
		t->point[1] = xml.getValue("PT:Y", 0.0,i);
		t->point[2] = xml.getValue("PT:X", 0.0,i+1);
		t->point[3] = xml.getValue("PT:Y", 0.0,i+1);
		t->point[4] = xml.getValue("PT:X", 0.0,i+2);
		t->point[5] = xml.getValue("PT:Y", 0.0,i+2);
		Texcoord.push_back(t);
	}
	xml.popTag();
	xml.pushTag("VER");
	for (int i = 0;i < numVerts;i+=3){
		Triangle* t = new Triangle();
		t->point[0] = xml.getValue("PT:X", 0.0,i  );
		t->point[1] = xml.getValue("PT:Y", 0.0,i  );
		t->point[2] = xml.getValue("PT:X", 0.0,i+1);
		t->point[3] = xml.getValue("PT:Y", 0.0,i+1);
		t->point[4] = xml.getValue("PT:X", 0.0,i+2);
		t->point[5] = xml.getValue("PT:Y", 0.0,i+2);
		Vertexes.push_back(t);
	}
	xml.popTag();
	
	xml.pushTag("MAGS");
	int numMags = xml.getNumTags("PT");
	if (numMags > 0){
		for (int i = 0;i < numMags;i++){
			ofPoint m;
			m.x = xml.getValue("PT:X", 0.0,i);
			m.y = xml.getValue("PT:Y", 0.0,i);
			magnets.push_back(m);
		}
	}
	xml.popTag();
	xml.pushTag("MAGV");
	int numMagv = xml.getNumTags("PT");
	if (numMagv > 0){
		for (int i = 0;i < numMagv;i++){
			ofPoint m;
			m.x = xml.getValue("PT:X", 0.0,i);
			m.y = xml.getValue("PT:Y", 0.0,i);
			magnetv.push_back(m);
		}
	}
	xml.popTag();
	
}

void ofxMpplrScreen::SaveXML(int num){
	if (num > 10) return;
	loaden = num;
	ofxXmlSettings xml;
	xml.addTag("TEX");
	xml.addTag("VER");
	xml.addTag("MAGS");
	xml.addTag("MAGV");
	
	xml.pushTag("TEX");
	int tagNum;
	for (int i = 0;i < Texcoord.size();i++){
		tagNum = xml.addTag("PT");
		xml.setValue("PT:X", (double)Texcoord[i]->point[0] , tagNum);
		xml.setValue("PT:Y", (double)Texcoord[i]->point[1] , tagNum);
		
		tagNum = xml.addTag("PT");
		xml.setValue("PT:X", (double)Texcoord[i]->point[2] , tagNum);
		xml.setValue("PT:Y", (double)Texcoord[i]->point[3] , tagNum);
		
		tagNum = xml.addTag("PT");
		xml.setValue("PT:X", (double)Texcoord[i]->point[4] , tagNum);
		xml.setValue("PT:Y", (double)Texcoord[i]->point[5] , tagNum);
	}
	xml.popTag();
	
	xml.pushTag("VER");
	for (int i = 0;i < Vertexes.size();i++){
		tagNum = xml.addTag("PT");
		xml.setValue("PT:X", (double)Vertexes[i]->point[0] , tagNum);
		xml.setValue("PT:Y", (double)Vertexes[i]->point[1] , tagNum);
		
		tagNum = xml.addTag("PT");
		xml.setValue("PT:X", (double)Vertexes[i]->point[2] , tagNum);
		xml.setValue("PT:Y", (double)Vertexes[i]->point[3] , tagNum);
		
		tagNum = xml.addTag("PT");
		xml.setValue("PT:X", (double)Vertexes[i]->point[4] , tagNum);
		xml.setValue("PT:Y", (double)Vertexes[i]->point[5] , tagNum);
	}
	xml.popTag();
	
	xml.pushTag("MAGS");
	for (int i = 0;i < magnets.size();i++){
		tagNum = xml.addTag("PT");
		xml.setValue("PT:X", (double)magnets[i].x , tagNum);
		xml.setValue("PT:Y", (double)magnets[i].y , tagNum);
	}
	xml.popTag();
	
	xml.pushTag("MAGV");
	for (int i = 0;i < magnetv.size();i++){
		tagNum = xml.addTag("PT");
		xml.setValue("PT:X", (double)magnetv[i].x , tagNum);
		xml.setValue("PT:Y", (double)magnetv[i].y , tagNum);
	}
	xml.popTag();
	xml.saveFile("preset"+ofToString(num)+".xml");
}