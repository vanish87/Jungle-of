#include "GamingScene6.h"
#include "JungleApp.h"

namespace Jungle
{
	GamingScene6::GamingScene6(void)
	{
	}


	GamingScene6::~GamingScene6(void)
	{
	}

	void GamingScene6::Steup()
	{
		w_ = ofGetWindowWidth();
		h_ = ofGetWindowHeight();
		x_ = ofGetWindowPositionX();
		y_ = ofGetWindowPositionY();
		
		hand_pos_.set(200,200,0);
		hand_vel_.set(0,0,0);
		hand_radius_ = 50;
		max_hand_radius_ = 70;
		hand_mass_ = 1;

		moving_time_ = 0;
		moving_ = false;
		track_moving_ = false;
		interval_ = false;
		interval_time_ = 0;

		butterfly_pos_.set(350, 350,0);
		butterfly_vel_.set(0, 0, 0);
		butterfly_radius_ = 50;
		butterfly_mass_ = 1;	

		ofEnableLighting();

		main_camera_.setPosition(0,12,51);
		main_camera_.lookAt(ofVec3f(0,0,0));
		

		ofBackground(0);
		ofSetFrameRate(60);
		ofSetVerticalSync(true);

		ofViewport(x_, y_, w_, h_, false);
	}

	void GamingScene6::Update()
	{
		if(pre_hand_pos_ - hand_pos_ == ofVec3f(0,0,0))
		{
			hand_radius_ +=0.3;
		}
		else
		{
			hand_radius_ -= 1;
		}

		hand_radius_ = ofClamp(hand_radius_, 50, max_hand_radius_);
		if (hand_radius_ == max_hand_radius_ && !interval_)
		{
			track_moving_ = true;
			start_pos_ = hand_pos_;
		}

		butterfly_force_ = ofVec3f(0,0,0);
		if (track_moving_)
		{
			moving_time_ +=ofGetLastFrameTime();

			if(moving_time_ > 0.5)
			{
				hand_vel_ = hand_pos_ - start_pos_;
				vlength =hand_vel_.length();
				if( vlength > 150)
				{
					butterfly_force_ += hand_vel_.getNormalized() * 10;
					cout<<"apply force"<<butterfly_force_.x<<" "<<butterfly_force_.y<<endl;
					interval_ = true;
				}
				moving_time_ = 0;
				track_moving_ = false;
			}
		}

		if(interval_)
		{
			interval_time_+=ofGetLastFrameTime();
			if(interval_time_ > 1)
				interval_ = false;
		}

		ofVec3f acc = butterfly_force_ / butterfly_mass_;
		butterfly_vel_ += acc;
		if(butterfly_vel_ != ofVec3f(0,0,0))
		{
			butterfly_vel_ += -butterfly_vel_.getNormalized() *0.1;
			if(butterfly_vel_.x < 0.1 && butterfly_vel_.x > -0.1)
				butterfly_vel_.x = 0;
			if (butterfly_vel_.y < 0.1 && butterfly_vel_.y > -0.1)
				butterfly_vel_.y = 0;
		}
		butterfly_pos_ +=butterfly_vel_;

		butterfly_pos_.x = ofClamp(butterfly_pos_.x, x_, w_);
		butterfly_pos_.y = ofClamp(butterfly_pos_.y, y_, h_);

		pre_hand_pos_ = hand_pos_;

		//update static scene
		this->GetParent()->Update();
	}

	void GamingScene6::Draw()
	{

		//ofSetColor(255, 255, 255);		
		main_camera_.begin();
		ofPushMatrix();
		//draw static scene
		this->GetParent()->Draw();
		ofPopMatrix();

		ofDrawAxis(100);       
		main_camera_.end();

// 		ofPushMatrix();
// 		ofTranslate(hand_pos_.x, hand_pos_.y, hand_pos_.z);
// 		if (hand_radius_ == max_hand_radius_)
// 		{
// 			ofSetColor(255,0,0,255);
// 		}
// 		ofSphere(0, 0, 0, hand_radius_);
// 		ofPopMatrix();
// 
// 
// 		ofPushMatrix();
// 		ofTranslate(butterfly_pos_.x, butterfly_pos_.y, butterfly_pos_.z);
// 		ofSetColor(255, 255, 255);		
// 		ofSphere(0, 0, 0, butterfly_radius_);
// 		ofPopMatrix();

		if(Jungle::KINECT_ENABLE)
		{
			glPushMatrix();
			ofTranslate(0, h_ - 0.3*h_);
			ofScale(0.4, 0.4);
			JungleApp::KinectInstance().debugDraw();
			glPopMatrix();
		}  
        
        
        
//         ofSetColor(255,255,255,255);
//         ofDrawBitmapString("moving_time_ "+ ofToString(moving_time_), 20, 20);
//         ofDrawBitmapString("v length "+ ofToString(vlength), 20, 40);
// 		//ofDrawBitmapString("f "+ ofToString(butterfly_force_.x) + " "+ ofToString(butterfly_force_.y), 20, 80);
//         ofDrawBitmapString("vel "+ ofToString(butterfly_vel_.x) + " "+ ofToString(butterfly_vel_.y), 20, 80);
        //ofDrawBitmapString("particle num "+ ofToString(NUM_PARTICLE), 20, 80);
               
	}

	void GamingScene6::keyPressed( int key )
	{
		//this->GetParent()->keyPressed(key);

		ofVec3f pos = main_camera_.getPosition();
        
        
		switch (key)
		{
		case 's':
			pos.z--;
			break;
		case 'w': 
			pos.z++;
			break;	
		case 'q':
			pos.y++;
			break;
		case 'z':
			pos.y--;
			break;
		case 'a':
			pos.x--;
			break;
		case 'd':
			pos.x++;
			break;
		case 'e':  
			break;
		case 'c':
			break;
		case 'y':
			break;
		case 'h':
			break;
		case 'g':
			break;
		case 'j':
			break;
        case 'f':     
			break;		
        case 'v':     
			break;
		case 'o':     
			break;
		case 'p':     
			break;
		case 'm':     
			break;
		case 'n':     
			break;
		case 't':     
			break;
		case 'r':     
			break;

		default:
			break;
		}

		main_camera_.setPosition(pos);
	}

	void GamingScene6::mouseMoved( int x, int y )
	{           
		hand_pos_.x = x;
		hand_pos_.y = y;
	}

	void GamingScene6::windowResized( int w, int h )
	{
        w_ = w;
        h_ = h;
	}

	void GamingScene6::inPose( ofxUser & user )
	{
		cout<<ofGetElapsedTimef()<<"Pose---"<<user.pose<<endl;
		
	}

	void GamingScene6::inGesture( ofxUser & user )
	{
		cout<<ofGetElapsedTimef()<<"Gesture---"<<user.gesture<<endl;		
	}

	void GamingScene6::userIn( ofxUser & user )
	{
	}

	void GamingScene6::userMove( ofxUser & user )
	{
	}

	void GamingScene6::userOut( ofxUser & user )
	{
	}

}
