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

		// Mushroom Placement        
        title_.loadImage("/UI/title-screen-3.png");
        
		//
		//z axis
		//              all glowing circle
		//                      |
		//--------------(-7)----0---------------500
		//               ^						 ^
		//				 |				         |
		//			    tree			     camera pos

		//left bottom corner is X:0,     Y:0
		//right up cornor is    X: 1280, Y:720
        
        // MUSHROOMS PLACEMENT 
        
        Flower mushroom1;
		mushroom1.loadModel("Environment/shroom_alpha.obj");
		mushroom1.setPosition(30,-10,0);
		mushroom1.setRotation(0,180,1,0,0);
        mushroom1.SetMaxScale(0.05);
		mushroom1.SetScaleSpeed(0.001);
        mushroom1.staying_time_ = 8;
        mushroom1.holding_time_ = 1;
		mushroom1.SetCircleSize(200);
		mushroom1.Enable(true);
		mushrooms_.push_back(mushroom1);
        
        Flower mushroom2;
		mushroom2.loadModel("Environment/shroom_alpha.obj");
		mushroom2.setPosition(250,-10,0);
		mushroom2.setRotation(0,180,1,0,0);
        mushroom2.SetMaxScale(0.05);
		mushroom2.SetScaleSpeed(0.001);
        mushroom2.staying_time_ = 8;
        mushroom2.holding_time_ = 1;
		mushroom2.SetCircleSize(200);
		mushroom2.Enable(true);
		mushrooms_.push_back(mushroom2);
        
        Flower mushroom3;
		mushroom3.loadModel("Environment/shroom_alpha.obj");
		mushroom3.setPosition(350,-10,0);
		mushroom3.setRotation(0,180,1,0,0);
        mushroom3.SetMaxScale(0.08);
		mushroom3.SetScaleSpeed(0.001);
        mushroom3.staying_time_ = 8;
        mushroom3.holding_time_ = 1;
		mushroom3.SetCircleSize(200);
		mushroom3.Enable(false);
		mushrooms_.push_back(mushroom3);
        
        Flower mushroom4;
		mushroom4.loadModel("Environment/shroom_alpha.obj");
		mushroom4.setPosition(300,-10,0);
		mushroom4.setRotation(0,180,1,0,0);
        mushroom4.SetMaxScale(0.05);
		mushroom4.SetScaleSpeed(0.001);
        mushroom4.staying_time_ = 8;
        mushroom4.holding_time_ = 1;
		mushroom4.SetCircleSize(200);
		mushroom4.Enable(false);
		mushrooms_.push_back(mushroom4);
        
        Flower mushroom5;
		mushroom5.loadModel("Environment/shroom_alpha.obj");
		mushroom5.setPosition(250,-10,0);
		mushroom5.setRotation(0,180,1,0,0);
        mushroom5.SetMaxScale(0.05);
		mushroom5.SetScaleSpeed(0.001);
        mushroom5.staying_time_ = 8;
        mushroom5.holding_time_ = 1;
		mushroom5.SetCircleSize(200);
		mushroom5.Enable(false);
		mushrooms_.push_back(mushroom5);
        
        Flower mushroom6;
		mushroom6.loadModel("Environment/shroom_alpha.obj");
		mushroom6.setPosition(430,-10,0);
		mushroom6.setRotation(0,180,1,0,0);
        mushroom6.SetMaxScale(0.08);
		mushroom6.SetScaleSpeed(0.001);
        mushroom6.staying_time_ = 8;
        mushroom6.holding_time_ = 1;
		mushroom6.SetCircleSize(200);
		mushroom6.Enable(false);
		mushrooms_.push_back(mushroom6);
        
        Flower mushroom7;
		mushroom7.loadModel("Environment/shroom_alpha.obj");
		mushroom7.setPosition(450,-10,0);
		mushroom7.setRotation(0,180,1,0,0);
        mushroom7.SetMaxScale(0.05);
		mushroom7.SetScaleSpeed(0.001);
        mushroom7.staying_time_ = 8;
        mushroom7.holding_time_ = 1;
		mushroom7.SetCircleSize(200);
		mushroom7.Enable(false);
		mushrooms_.push_back(mushroom7);
        
        Flower mushroom8;
		mushroom8.loadModel("Environment/shroom_alpha.obj");
		mushroom8.setPosition(650,-10,0);
		mushroom8.setRotation(0,180,1,0,0);
        mushroom8.SetMaxScale(0.06);
		mushroom8.SetScaleSpeed(0.001);
        mushroom8.staying_time_ = 8;
        mushroom8.holding_time_ = 1;
		mushroom8.SetCircleSize(200);
		mushroom8.Enable(false);
		mushrooms_.push_back(mushroom8);
        
        Flower mushroom9;
		mushroom9.loadModel("Environment/shroom_alpha.obj");
		mushroom9.setPosition(850,-10,0);
		mushroom9.setRotation(0,180,1,0,0);
        mushroom9.SetMaxScale(0.05);
		mushroom9.SetScaleSpeed(0.001);
        mushroom9.staying_time_ = 8;
        mushroom9.holding_time_ = 1;
		mushroom9.SetCircleSize(200);
		mushroom9.Enable(false);
		mushrooms_.push_back(mushroom9);
        
        Flower mushroom10;
		mushroom10.loadModel("Environment/shroom_alpha.obj");
		mushroom10.setPosition(1000,-10,0);
		mushroom10.setRotation(0,180,1,0,0);
        mushroom10.SetMaxScale(0.04);
		mushroom10.SetScaleSpeed(0.001);
        mushroom10.staying_time_ = 8;
        mushroom10.holding_time_ = 1;
		mushroom10.SetCircleSize(200);
		mushroom10.Enable(false);
		mushrooms_.push_back(mushroom10);
        
        Flower mushroom11;
		mushroom11.loadModel("Environment/shroom_alpha.obj");
		mushroom11.setPosition(1100,-10,0);
		mushroom11.setRotation(0,180,1,0,0);
        mushroom11.SetMaxScale(0.05);
		mushroom11.SetScaleSpeed(0.001);
        mushroom11.staying_time_ = 8;
        mushroom11.holding_time_ = 1;
		mushroom11.SetCircleSize(200);
		mushroom11.Enable(false);
		mushrooms_.push_back(mushroom11);
        
        Flower mushroom12;
		mushroom12.loadModel("Environment/shroom_alpha.obj");
		mushroom12.setPosition(1200,-10,0);
		mushroom12.setRotation(0,180,1,0,0);
        mushroom12.SetMaxScale(0.05);
		mushroom12.SetScaleSpeed(0.001);
        mushroom12.staying_time_ = 8;
        mushroom12.holding_time_ = 1;
		mushroom12.SetCircleSize(200);
		mushroom12.Enable(false);
		mushrooms_.push_back(mushroom2);
        
        Flower mushroom13;
		mushroom13.loadModel("Environment/shroom_alpha.obj");
		mushroom13.setPosition(1250,-10,0);
		mushroom13.setRotation(0,180,1,0,0);
        mushroom13.SetMaxScale(0.05);
		mushroom13.SetScaleSpeed(0.001);
        mushroom13.staying_time_ = 8;
        mushroom13.holding_time_ = 1;
		mushroom13.SetCircleSize(200);
		mushroom13.Enable(false);
		mushrooms_.push_back(mushroom2);
        
        Flower mushroom14;
		mushroom14.loadModel("Environment/shroom_alpha.obj");
		mushroom14.setPosition(1300,-10,0);
		mushroom14.setRotation(0,180,1,0,0);
        mushroom14.SetMaxScale(0.05);
		mushroom14.SetScaleSpeed(0.001);
        mushroom14.staying_time_ = 8;
        mushroom14.holding_time_ = 1;
		mushroom14.SetCircleSize(200);
		mushroom14.Enable(false);
		mushrooms_.push_back(mushroom14);
        
        ///LEAves
        
        //// FIRST TREE FROM LEFT 
        
        Leaf_Time = 15; // how long the leaves are visible before disappearing again
        //create variable for hovering time aka holding_time
        
        Flower leaf1;
		leaf1.loadModel("Environment/Leaf.obj");
		leaf1.setPosition(1,202,06);
		leaf1.setRotation(0,180,1,0,0);
        leaf1.SetMaxScale(0.1);
		leaf1.SetScaleSpeed(0.01);
        leaf1.staying_time_ = Leaf_Time;
        leaf1.holding_time_ = 1;
		leaf1.SetCircleSize(200);
        leaf1.SetCircleColor(ofColor(255,0,0,255));
		leaf1.Enable(false);
		mushrooms_.push_back(leaf1);
 
        Flower leaf2;
		leaf2.loadModel("Environment/Leaf.obj");
		leaf2.setPosition(103,402,40);
		leaf2.setRotation(0,180,1,0,0);
        leaf2.SetMaxScale(0.1);
		leaf2.SetScaleSpeed(0.01);
        leaf2.staying_time_ = Leaf_Time;
        leaf2.holding_time_ = 1;
		leaf2.SetCircleSize(200);
        leaf2.SetCircleColor(ofColor(255,0,0,255));
		leaf2.Enable(false);
		mushrooms_.push_back(leaf2);
        
        Flower leaf3;
		leaf3.loadModel("Environment/Leaf.obj");
		leaf3.setPosition(155,474,4);
		leaf3.setRotation(0,180,1,0,0);
        leaf3.SetMaxScale(0.1);
		leaf3.SetScaleSpeed(0.01);
        leaf3.staying_time_ = Leaf_Time;
        leaf3.holding_time_ = 1;
		leaf3.SetCircleSize(200);
        leaf3.SetCircleColor(ofColor(255,0,0,255));
		leaf3.Enable(false);
		mushrooms_.push_back(leaf3);
       
        Flower leaf4;
		leaf4.loadModel("Environment/Leaf.obj");
		leaf4.setPosition(279,380,19);
		leaf4.setRotation(0,180,1,0,0);
        leaf4.SetMaxScale(0.15);
		leaf4.SetScaleSpeed(0.01);
        leaf4.staying_time_ = Leaf_Time;
        leaf4.holding_time_ = 1;
		leaf4.SetCircleSize(200);
        leaf4.SetCircleColor(ofColor(255,0,0,255));
		leaf4.Enable(false);
		mushrooms_.push_back(leaf4);
        
        Flower leaf5;
		leaf5.loadModel("Environment/Leaf.obj");
		leaf5.setPosition(48,193,5);
		leaf5.setRotation(0,180,1,0,0);
        leaf5.SetMaxScale(0.1);
		leaf5.SetScaleSpeed(0.01);
        leaf5.staying_time_ = Leaf_Time;
        leaf5.holding_time_ = 1;
		leaf5.SetCircleSize(200);
        leaf5.SetCircleColor(ofColor(255,0,0,255));
		leaf5.Enable(false);
		mushrooms_.push_back(leaf5);
        
        Flower leaf6;
		leaf6.loadModel("Environment/Leaf.obj");
		leaf6.setPosition(220,240,-8);
		leaf6.setRotation(0,180,1,0,0);
        leaf6.SetMaxScale(0.15);
		leaf6.SetScaleSpeed(0.01);
        leaf6.staying_time_ = Leaf_Time;
        leaf6.holding_time_ = 1;
		leaf6.SetCircleSize(200);
        leaf6.SetCircleColor(ofColor(255,0,0,255));
		leaf6.Enable(false);
		mushrooms_.push_back(leaf6);
        
        Flower leaf7;
		leaf7.loadModel("Environment/Leaf.obj");
		leaf7.setPosition(312,275,-1);
		leaf7.setRotation(0,180,1,0,0);
        leaf7.SetMaxScale(0.10);
		leaf7.SetScaleSpeed(0.01);
        leaf7.staying_time_ = Leaf_Time;
        leaf7.holding_time_ = 1;
		leaf7.SetCircleSize(200);
        leaf7.SetCircleColor(ofColor(255,0,0,255));
		leaf7.Enable(false);
		mushrooms_.push_back(leaf7);
        
        Flower leaf8;
		leaf8.loadModel("Environment/Leaf.obj");
		leaf8.setPosition(9, 295, -25);
		leaf8.setRotation(0,180,1,0,0);
        leaf8.SetMaxScale(0.15);
		leaf8.SetScaleSpeed(0.01);
        leaf8.staying_time_ = Leaf_Time;
        leaf8.holding_time_ = 1;
		leaf8.SetCircleSize(200);
        leaf8.SetCircleColor(ofColor(255,0,0,255));
		leaf8.Enable(false);
		mushrooms_.push_back(leaf8);
        
        Flower leaf9;
		leaf9.loadModel("Environment/Leaf.obj");
		leaf9.setPosition(80,270,-20);
		leaf9.setRotation(0,180,1,0,0);
        leaf9.SetMaxScale(0.1);
		leaf9.SetScaleSpeed(0.01);
        leaf9.staying_time_ = Leaf_Time;
        leaf9.holding_time_ = 1;
		leaf9.SetCircleSize(200);
        leaf9.SetCircleColor(ofColor(255,0,0,255));
		leaf9.Enable(false);
		mushrooms_.push_back(leaf9);
        
        Flower leaf10;
		leaf10.loadModel("Environment/Leaf.obj");
		leaf10.setPosition(158,233,-20);
		leaf10.setRotation(0,180,1,0,0);
        leaf10.SetMaxScale(0.1);
		leaf10.SetScaleSpeed(0.01);
        leaf10.staying_time_ = Leaf_Time;
        leaf10.holding_time_ = 1;
		leaf10.SetCircleSize(200);
        leaf10.SetCircleColor(ofColor(255,0,0,255));
		leaf10.Enable(false);
		mushrooms_.push_back(leaf10);
        
        Flower leaf11;
		leaf11.loadModel("Environment/Leaf.obj");
		leaf11.setPosition(121,150, 9);
		leaf11.setRotation(0,180,1,0,0);
        leaf11.SetMaxScale(0.15);
		leaf11.SetScaleSpeed(0.01);
        leaf11.staying_time_ = Leaf_Time;
        leaf11.holding_time_ = 1;
		leaf11.SetCircleSize(200);
        leaf11.SetCircleColor(ofColor(255,0,0,255));
		leaf11.Enable(false);
		mushrooms_.push_back(leaf11);
        
        Flower leaf12;
		leaf12.loadModel("Environment/Leaf.obj");
		leaf12.setPosition(157,320,-15);
		leaf12.setRotation(0,180,1,0,0);
        leaf12.SetMaxScale(0.15);
		leaf12.SetScaleSpeed(0.01);
        leaf12.staying_time_ = Leaf_Time;
        leaf12.holding_time_ = 1;
		leaf12.SetCircleSize(200);
        leaf12.SetCircleColor(ofColor(255,0,0,255));
		leaf12.Enable(false);
		mushrooms_.push_back(leaf12);
        
       
        // SECOND TREE FROM LEFT
        
        
        
        ///
        
        
		//circle_.loadImage("Environment/glowing-circle-2.png");
		w_ = ofGetWindowWidth();
		h_ = ofGetWindowHeight();
		x_ = ofGetWindowPositionX();
		y_ = ofGetWindowPositionY();
	}

	void Level1::Update()
	{	
		Player& player = JungleApp::PlayerInstance();
		player.Update();
        
        
		//get butterfly's pos
		//if collision
        for(int i =0; i < mushrooms_.size(); ++i)
        {
            ofVec3f bt_pos = player.hand_pos_;
			bt_pos.y = h_-bt_pos.y;
            ofVec3f mh_pos = ofVec3f(mushrooms_[i].getPosition().x, mushrooms_[i].getPosition().y, 0);
            if((bt_pos - mh_pos).length() < 70)
                //triggering mushrooms
            {
                if(!mushrooms_[i].Enabled())
                {
                    
                    
                    
                    int index = ofRandom(0,4);
                    //cout<<index<<endl;
                    if (!sounds[index].getIsPlaying())
                    {
                        sounds[index].play();
                    }
                }
                mushrooms_[i].Enable(true);
            }
            else
            {
                mushrooms_[i].Enable(false);
            }
            mushrooms_[i].Update(ofGetLastFrameTime());
        }
		//if finished
		//change to next level

		//update static scene
		this->GetParent()->Update();
	}

	void Level1::Draw()
	{

		Player& player = JungleApp::PlayerInstance();

		ofCamera camera = player.GetCamera();

        ofEnableAlphaBlending();
		camera.begin();        
        ofEnableLighting();
        light_.enable();         
		//draw static scene
		this->GetParent()->Draw();
		glEnable(GL_DEPTH_TEST);
		//draw mushrooms        
		ofPushMatrix();
        for(int i =0; i < mushrooms_.size(); ++i)
        {
			mushrooms_[i].Draw();
        }
		ofPopMatrix();

        glDisable(GL_DEPTH_TEST);
        light_.disable();

		camera.end();
		ofDisableAlphaBlending();

        
        ofDisableLighting();
        ofEnableAlphaBlending();              
		player.wind_.Draw();
        
		ofPushMatrix();
        ofVec3f hand_pos_ = player.GetHandPos();

        ofDisableLighting();
        ofEnableAlphaBlending();
		player.wind_.Draw();
        ofSetColor(255, 255, 255);
        if(!player.detected_)
            title_.draw(ofPoint(0,0), w_, h_);
        ofDisableAlphaBlending();

		ofPopMatrix();

        ofSetColor(255, 255, 255);
		if(Jungle::KINECT_ENABLE && !player.detected_)
		{
			glPushMatrix();
			ofTranslate(0, h_ - 0.3*h_);
			ofScale(0.4, 0.4);
			//JungleApp::KinectInstance().debugDraw();
			glPopMatrix();
		}

		ofVec3f bt_pos = player.hand_pos_;
		bt_pos.y = h_- bt_pos.y;
		ofVec3f mh_pos = ofVec3f(mushrooms_[0].getPosition().x, mushrooms_[0].getPosition().y, 0);
        
		ofSetColor(255, 255, 255,255);
		ofDrawBitmapString("angle "+ ofToString(player.wind_.emitter_.angle), 20, 20);
		ofDrawBitmapString("v length "+ ofToString((bt_pos - mh_pos).length()), 20, 40);
		ofDrawBitmapString("scale "+ ofToString(mushrooms_[index_].getScale().x), 20, 60);
		
		ofDrawBitmapString("pre "+ ofToString(player.pre_hand_pos_.x) + " "+ ofToString(player.pre_hand_pos_.y), 20, 80);
		ofDrawBitmapString("hand "+ ofToString(bt_pos.x) + " "+ ofToString(bt_pos.y), 20, 100);

		ofDrawBitmapString("mush pos "+ ofToString(mushrooms_[index_].getPosition().x) + " "+ ofToString(mushrooms_[index_].getPosition().y)+ " "+ ofToString(mushrooms_[index_].getPosition().z), 20, 160);

	}

	void Level1::keyPressed( int key )
	{
        Player& player = JungleApp::PlayerInstance();
        
        int index = 0;
        index_ = index;
        ofVec3f pos = mushrooms_[index].getPosition();
		ofVec3f scale = mushrooms_[index].getScale();
        
        ofVec3f cam_pos=player.player_camera_.getPosition();

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
                cam_pos.x--;
                break;
                
            case 'i':
                cam_pos.y++;
                break;
                
            case 'k':
                cam_pos.y--;
                break;
                
            case 'l':
                cam_pos.x++;
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
        
        player.player_camera_.setPosition(cam_pos);
		mushrooms_[index].setPosition(pos.x, pos.y, pos.z);
	}

	void Level1::mouseMoved( int x, int y )
	{
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
	}

}
