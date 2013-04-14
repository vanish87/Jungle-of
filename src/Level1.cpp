#include "Level1.h"
#include "Level2.h"
#include "JungleApp.h"
#include "ofGraphics.h"

namespace Jungle
{
	Level1::Level1( void )
	{
		
	}

	Level1::~Level1( void )
	{

	}

	void Level1::Steup()
	{
        //set up mushrooms
        ofBackground(0);
	}

	void Level1::Update()
	{	
		Player& player = JungleApp::PlayerInstance();
		player.Update();
		//get butterfly's pos
		//if collision
		//triggering mushrooms
		//if finished
		//change to next level

		//update static scene
		this->GetParent()->Update();
	}

	void Level1::Draw()
	{

		Player& player = JungleApp::PlayerInstance();
		ButterFly butterfly = player.GetButterfly();

		ofCamera camera = player.GetCamera();

		//camera.begin();

		//draw static scene
		//this->GetParent()->Draw();
		//draw mushrooms

		//draw butterfly
		//butterfly.drawFaces();

		//camera.end();

		ofVec3f hand_pos_ = player.GetHandPos();
		ofPushMatrix();
		ofTranslate(hand_pos_.x, hand_pos_.y, hand_pos_.z);
 		if (player.hand_radius_ == player.max_hand_radius_)
 		{
 			ofSetColor(0,255,0,255);
 		}
		ofSphere(0, 0, 0, player.hand_radius_);
		ofPopMatrix();

		ofVec3f butter_pos = butterfly.getPosition();
		ofPushMatrix();
		ofTranslate(butter_pos.x, butter_pos.y, butter_pos.z);
		ofSetColor(255, 0, 0);		
		ofSphere(0, 0, 0, 50);
		ofPopMatrix();

		ofSetColor(255, 255, 255);	
		ofDrawBitmapString("moving_time_ "+ ofToString(player.moving_time_), 20, 20);
		ofDrawBitmapString("v length "+ ofToString(player.vlength), 20, 40);
		ofDrawBitmapString("hand_radius_ "+ ofToString(player.hand_radius_), 20, 60);
		
		ofDrawBitmapString("pre "+ ofToString(player.pre_hand_pos_.x) + " "+ ofToString(player.pre_hand_pos_.y), 20, 80);
		ofDrawBitmapString("hand "+ ofToString(hand_pos_.x) + " "+ ofToString(hand_pos_.x), 20, 100);

	}

	void Level1::keyPressed( int key )
	{

	}

	void Level1::mouseMoved( int x, int y )
	{
		//hand_pos_.set(x,y,0);
		//wind_.Enable(true, hand_pos_);
		Player& player = JungleApp::PlayerInstance();
		player.SetHandPos(ofVec3f(x, y, 0));
	}

	void Level1::windowResized( int w, int h )
	{

	}

	void Level1::inPose( ofxUser & user )
	{

	}

	void Level1::inGesture( ofxUser & user )
	{

	}

	void Level1::userIn( ofxUser & user )
	{

	}

	void Level1::userMove( ofxUser & user )
	{

	}

	void Level1::userOut( ofxUser & user )
	{

	}

}
