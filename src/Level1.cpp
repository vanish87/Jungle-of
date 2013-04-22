#include "Level1.h"
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
        player.butterfly_->SetRange(ofVec3f(300, 240, 0), ofVec3f(-300, 20, 0));
        
        light_.setAmbientColor(ofFloatColor(0.5, 0.5, 0.5));
        light_.setDiffuseColor(ofFloatColor(1 ,1 ,1));
        light_.setPointLight();
        light_.setPosition(20, 100, 40);
        ofQuaternion q;
        q.makeRotate(-45, 1, 0, 0);
        light_.setOrientation(q);
        
        
        ofEnableLighting();
        light_.enable();
        ofBackground(255);
        
        
        sounds[0].loadSound("Audio/trigger1.mp3");
		sounds[1].loadSound("Audio/trigger2.mp3");
		sounds[2].loadSound("Audio/trigger3.mp3");
		sounds[3].loadSound("Audio/trigger4.mp3");
        
        
		Flower mushroom;
		mushroom.loadModel("Environment/Flower.obj");
		mushroom.setPosition(-4, 12, 29);
        //default value of max scaling
        //call this fun to set different size of mushroom
        //if not called, default value is 0.008
		mushroom.SetMaxScale(1);
		mushroom.setRotation(0,180,1,0,0);
		mushroom.Enable(true);
		mushrooms_.push_back(mushroom);
        
        Flower mushroom2;
		mushroom2.loadModel("Environment/Mushroom.obj");
		mushroom2.setPosition(15, 12, 29);
		mushroom2.setRotation(0,180,1,0,0);
		mushroom2.Enable(false);
		mushrooms_.push_back(mushroom2);
        
        Flower mushroom3;
		mushroom3.loadModel("Environment/Mushroom.obj");
		mushroom3.setPosition(17, 12, 29);
		mushroom3.SetMaxScale(0.01);
		mushroom3.setRotation(0,180,1,0,0);
		mushroom3.Enable(false);
		mushrooms_.push_back(mushroom3);
       
        Flower mushroom4;
		mushroom4.loadModel("Environment/Mushroom.obj");
		mushroom4.setPosition(26, 12, 29);
		mushroom4.setRotation(0,180,1,0,0);
		mushroom4.Enable(false);
		mushrooms_.push_back(mushroom4);

        title_.loadImage("/UI/title-screen-3.png");
        
        Flower mushroom5;
		mushroom5.loadModel("Environment/Mushroom.obj");
		mushroom5.setPosition(27, 12, 29);
        mushroom3.SetMaxScale(0.01);
		mushroom5.setRotation(0,180,1,0,0);
		mushroom5.Enable(false);
		mushrooms_.push_back(mushroom5);
       
        Flower mushroom6;
		mushroom6.loadModel("Environment/Mushroom.obj");
		mushroom6.setPosition(-79, 12, 29);
        mushroom3.SetMaxScale(0.01);
		mushroom6.setRotation(0,180,1,0,0);
		mushroom6.Enable(false);
		mushrooms_.push_back(mushroom6);
        
        Flower mushroom7;
		mushroom7.loadModel("Environment/Mushroom.obj");
		mushroom7.setPosition(-81, 12, 29);
		mushroom7.setRotation(0,180,1,0,0);
		mushroom7.Enable(false);
		mushrooms_.push_back(mushroom7);
        
        Flower mushroom8;
		mushroom8.loadModel("Environment/Mushroom.obj");
		mushroom8.setPosition(-79, 12, 29);
        mushroom8.SetMaxScale(0.01);
		mushroom8.setRotation(0,180,1,0,0);
		mushroom8.Enable(false);
		mushrooms_.push_back(mushroom8);
        
        Flower mushroom9;
		mushroom9.loadModel("Environment/Mushroom.obj");
		mushroom9.setPosition(-144, 12, 29);
        mushroom9.SetMaxScale(0.01);
		mushroom9.setRotation(0,180,1,0,0);
		mushroom9.Enable(false);
		mushrooms_.push_back(mushroom9);
        
        Flower mushroom10;
		mushroom10.loadModel("Environment/Mushroom.obj");
		mushroom10.setPosition(-140, 12, 29);
        mushroom10.SetMaxScale(0.01);
		mushroom10.setRotation(0,180,1,0,0);
		mushroom10.Enable(false);
		mushrooms_.push_back(mushroom10);
        
        Flower mushroom11;
		mushroom11.loadModel("Environment/Mushroom.obj");
		mushroom11.setPosition(82, 12, 29);
        mushroom11.SetMaxScale(0.01);
		mushroom11.setRotation(0,180,1,0,0);
		mushroom11.Enable(false);
		mushrooms_.push_back(mushroom11);
        
        Flower mushroom12;
		mushroom12.loadModel("Environment/Mushroom.obj");
		mushroom12.setPosition(92, 12, 29);
        mushroom12.SetMaxScale(0.01);
		mushroom12.setRotation(0,180,1,0,0);
		mushroom12.Enable(false);
		mushrooms_.push_back(mushroom12);
        
        
        Flower mushroom13;
		mushroom13.loadModel("Environment/Mushroom.obj");
		mushroom13.setPosition(115, 12, 29);
        mushroom13.SetMaxScale(0.01);
		mushroom13.setRotation(0,180,1,0,0);
		mushroom13.Enable(false);
		mushrooms_.push_back(mushroom13);
        
        
        Flower mushroom14;
		mushroom14.loadModel("Environment/Mushroom.obj");
		mushroom14.setPosition(120, 12, 29);
        mushroom14.SetMaxScale(0.01);
		mushroom14.setRotation(0,180,1,0,0);
		mushroom14.Enable(false);
		mushrooms_.push_back(mushroom14);
        
        
        Flower mushroom15;
		mushroom15.loadModel("Environment/Mushroom.obj");
		mushroom15.setPosition(217, 12, 29);
        mushroom15.SetMaxScale(0.01);
		mushroom15.setRotation(0,180,1,0,0);
		mushroom15.Enable(false);
		mushrooms_.push_back(mushroom15);
        
        Flower mushroom16;
		mushroom16.loadModel("Environment/Mushroom.obj");
		mushroom16.setPosition(200, 12, 29);
		mushroom16.setRotation(0,180,1,0,0);
		mushroom16.Enable(false);
		mushrooms_.push_back(mushroom16);
        
        Flower mushroom17;
		mushroom17.loadModel("Environment/Mushroom.obj");
		mushroom17.setPosition(204, 12, 29);
        mushroom17.SetMaxScale(0.01);
		mushroom17.setRotation(0,180,1,0,0);
		mushroom17.Enable(false);
		mushrooms_.push_back(mushroom17);
        
        Flower mushroom18;
		mushroom18.loadModel("Environment/Mushroom.obj");
		mushroom18.setPosition(161, 12, 29);
		mushroom18.setRotation(0,180,1,0,0);
		mushroom18.Enable(false);
		mushrooms_.push_back(mushroom18);
    
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
        for(int i =0; i < mushrooms_.size(); ++i)
        {
            if(mushrooms_[i].Enabled())
                mushrooms_[i].Draw();
        }
		ofPopMatrix();
		//draw butterfly
		butterfly.drawFaces();
        
        //ofDrawAxis(100);
        glDisable(GL_DEPTH_TEST);
        light_.disable();
        
        
        ofDisableLighting();
        ofEnableAlphaBlending();
		player.wind_.Draw();

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
        ofSetColor(255, 255, 255);
        if(!player.detected_)
            title_.draw(ofPoint(0,0), w_, h_);
        ofDisableAlphaBlending();
		//ofSphere(0, 0, 0, player.hand_radius_);
		ofPopMatrix();

		ofPushMatrix();
        ofEnableAlphaBlending();
		ofSetColor(255, 226, 141, 50);
		if(player.path_.size() > 1)
		for(vector<pair<ofVec3f,float> >::iterator it = player.path_.begin(); it!= player.path_.end()- 1; ++it)
		{
			ofLine(ofPoint(it->first.x, it->first.y), ofPoint((it+1)->first.x, (it+1)->first.y));
		}
        ofDisableAlphaBlending();
        
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
		if(Jungle::KINECT_ENABLE && !player.detected_)
		{
			glPushMatrix();
			ofTranslate(0, h_ - 0.3*h_);
			ofScale(0.4, 0.4);
			//JungleApp::KinectInstance().debugDraw();
			glPopMatrix();
		}

		ofVec3f bt_pos = ofVec3f(butterfly.butterfly_pos_.x, butterfly.butterfly_pos_.y,0);
		ofVec3f mh_pos = ofVec3f(mushrooms_[0].getPosition().x, mushrooms_[0].getPosition().y, 0);
        
		ofSetColor(255, 255, 255,255);
		ofDrawBitmapString("angle "+ ofToString(player.wind_.emitter_.angle), 20, 20);
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
        
        int index = 0;
        ofVec3f pos = mushrooms_[index].getPosition();
		ofVec3f scale = mushrooms_[index].getScale();

        //static scene
        //this->GetParent()->keyPressed(key);
        //return;
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
                mushrooms_[index].setScale(scale.x, scale.y,scale.z);
                break;
            case 'c':
                scale-=0.001;
                mushrooms_[index].setScale(scale.x, scale.y,scale.z);
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
        
		mushrooms_[index].setPosition(pos.x, pos.y, pos.z);
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
        Player& player = JungleApp::PlayerInstance();
        player.detected_ = false;
        player.path_.clear();
        player.path_.push_back(make_pair(ofVec3f(w_/2, h_/2, 0), 0));
        player.path_.push_back(make_pair(ofVec3f(w_/2, h_/2, 0), 0));
        player.path_.push_back(make_pair(ofVec3f(w_/2, h_/2, 0), 0));
	}

}
