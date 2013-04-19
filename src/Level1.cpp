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
        
		Player& player = JungleApp::PlayerInstance();
        //set up mushrooms
        //set up space limits
        player.butterfly_->SetRange(ofVec3f(300, 500, 0), ofVec3f(-300, 20, 0));
        
        light_.setAmbientColor(ofFloatColor(0.8, 0.8, 0.8));
        light_.setDiffuseColor(ofFloatColor(1 ,1 ,1));
        light_.setPointLight();
        light_.setPosition(20, 100, 40);
        ofQuaternion q;
        q.makeRotate(-45, 1, 0, 0);
        light_.setOrientation(q);
        
        
        ofEnableLighting();
        light_.enable();
        ofBackground(255);
        
        
        sounds[0].loadSound("audio/trigger1.mp3");
		sounds[1].loadSound("audio/trigger2.mp3");
		sounds[2].loadSound("audio/trigger3.mp3");
		sounds[3].loadSound("audio/trigger4.mp3");
        
        
		Flower mushroom;
		mushroom.loadModel("shroom.obj");
		mushroom.setPosition(-4, 12, 15);
		mushroom.setScale(0,0, 0);
		mushroom.setRotation(0,180,1,0,0);
		mushroom.Enable(false);
		mushrooms_.push_back(mushroom);
        
        
		w_ = ofGetWindowWidth();
		h_ = ofGetWindowHeight();
		x_ = ofGetWindowPositionX();
		y_ = ofGetWindowPositionY();
	}

	void Level1::Update()
	{	
		Player& player = JungleApp::PlayerInstance();
		player.Update();
        
		ButterFly& butterfly = player.GetButterfly();
        
        
		//get butterfly's pos
		//if collision
        for(int i =0; i < mushrooms_.size(); ++i)
        {
            ofVec3f bt_pos = ofVec3f(butterfly.butterfly_pos_.x, butterfly.butterfly_pos_.y,0);
            ofVec3f mh_pos = ofVec3f(mushrooms_[i].getPosition().x, mushrooms_[i].getPosition().y, 0);
            if((bt_pos - mh_pos).length() < 8.2)
                //triggering mushrooms
            {
                if(!mushrooms_[i].Enabled())
                {
                
                    mushrooms_[i].Enable(true);
                    int index = ofRandom(0,4);
                    //cout<<index<<endl;
                    if (!sounds[index].getIsPlaying())
                    {
                        sounds[index].play();
                    }
                }
            }
        }
		//if finished
		//change to next level

		//update static scene
		this->GetParent()->Update();
	}

	void Level1::Draw()
	{

		Player& player = JungleApp::PlayerInstance();
		ButterFly& butterfly = player.GetButterfly();

		ofCamera camera = player.GetCamera();

		ofEnableAlphaBlending();
		camera.begin();
        light_.enable();
        
		//draw static scene
		this->GetParent()->Draw();
		glEnable(GL_DEPTH_TEST);
		//draw mushrooms

		ofPushMatrix();
		if(mushrooms_[0].Enabled())
			mushrooms_[0].Draw();
		ofPopMatrix();
		//draw butterfly
		butterfly.drawFaces();
        
        //ofDrawAxis(100);
        glDisable(GL_DEPTH_TEST);
        light_.disable();
		camera.end();
		ofDisableAlphaBlending();

        
		ofPushMatrix();
        ofVec3f hand_pos_ = player.GetHandPos();
        

		//ofTranslate(hand_pos_.x, hand_pos_.y, hand_pos_.z);
 		if (player.hand_radius_ == player.max_hand_radius_)
 		{
            //ofSetColor(255, 0, 0);
 		}
        else
        {
           // ofSetColor(255, 255, 255);
        }
        ofDisableLighting();
        ofEnableAlphaBlending();
		player.wind_.Draw();
        ofDisableAlphaBlending();
		//ofSphere(0, 0, 0, player.hand_radius_);
		ofPopMatrix();

		ofPushMatrix();
		ofSetColor(255,0,0);
		if(player.path_.size() > 1)
		for(vector<pair<ofVec3f,float> >::iterator it = player.path_.begin(); it!= player.path_.end()- 1; ++it)
		{
			ofLine(ofPoint(it->first.x, it->first.y), ofPoint((it+1)->first.x, (it+1)->first.y));
		}

// 		ofPoint p;
// 		ofPoint pp;
// 		for(int i=0; i < 50; ++i)
// 		{
// 			float t = i/50.0f;
// 			p = player.crspline_.GetPos(player.test_[2], player.test_[2], player.test_[3], player.test_[3], t);
// 			ofLine(pp, p);
// 			pp = p;
// 		}

		ofPopMatrix();

		/*ofVec3f butter_pos = butterfly.getPosition();
		ofPushMatrix();
		ofTranslate(butter_pos.x, butter_pos.y, butter_pos.z);
		ofSetColor(255, 0, 0);		
		ofSphere(0, 0, 0, 50);
		ofPopMatrix();*/

        ofSetColor(255, 255, 255);
		if(Jungle::KINECT_ENABLE)
		{
			glPushMatrix();
			ofTranslate(0, h_ - 0.3*h_);
			ofScale(0.4, 0.4);
			JungleApp::KinectInstance().debugDraw();
			glPopMatrix();
		}

		ofVec3f bt_pos = ofVec3f(butterfly.butterfly_pos_.x, butterfly.butterfly_pos_.y,0);
		ofVec3f mh_pos = ofVec3f(mushrooms_[0].getPosition().x, mushrooms_[0].getPosition().y, 0);
        
		ofSetColor(255, 255, 255,255);
		ofDrawBitmapString("moving_time_ "+ ofToString(player.moving_time_), 20, 20);
		ofDrawBitmapString("v length "+ ofToString((bt_pos - mh_pos).length()), 20, 40);
		ofDrawBitmapString("scale "+ ofToString(mushrooms_[0].getScale().x), 20, 60);
		
		ofDrawBitmapString("pre "+ ofToString(player.pre_hand_pos_.x) + " "+ ofToString(player.pre_hand_pos_.y), 20, 80);
		ofDrawBitmapString("hand "+ ofToString(hand_pos_.x) + " "+ ofToString(hand_pos_.x), 20, 100);

		ofDrawBitmapString("path size  "+ ofToString(player.path_.size()), 20, 120);
		ofDrawBitmapString("but pos "+ ofToString(player.butterfly_->getPosition().x) + " "+ ofToString(player.butterfly_->getPosition().y)+ " "+ ofToString(player.butterfly_->getPosition().z), 20, 140);
		ofDrawBitmapString("mush pos "+ ofToString(mushrooms_[0].getPosition().x) + " "+ ofToString(mushrooms_[0].getPosition().y)+ " "+ ofToString(mushrooms_[0].getPosition().z), 20, 160);

	}

	void Level1::keyPressed( int key )
	{
        Player& player = JungleApp::PlayerInstance();

        ofVec3f pos = mushrooms_[0].getPosition();
		ofVec3f scale = mushrooms_[0].getScale();

        
        //this->GetParent()->keyPressed(key);
		switch (key)
		{
            case 's':
                pos.z+=1;
                break;
            case 'w':
                pos.z-=1;
                break;
            case 'q':
                pos.y+=1;
                break;
            case 'z':
                pos.y-=1;
                break;
            case 'a':
                pos.x-=1;
                break;
            case 'd':
                pos.x+=1;
                break;
            case 'e':
                scale+=0.001;
                mushrooms_[0].setScale(scale.x, scale.y,scale.z);
                break;
            case 'c':
                scale-=0.001;
                mushrooms_[0].setScale(scale.x, scale.y,scale.z);
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
        
		mushrooms_[0].setPosition(pos.x, pos.y, pos.z);
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
