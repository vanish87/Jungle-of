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
       // player.butterfly_->SetRange(ofVec3f(300, 240, 0), ofVec3f(-300, 20, 0));
        
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
        
        Flower mushroom2;
		mushroom2.loadModel("Environment/shroom_alpha.obj");
<<<<<<< HEAD
		mushroom2.setPosition(400,0,11);
        mushroom2.SetMaxScale(0.05);
=======
		mushroom2.setPosition(200, 200, 60);
>>>>>>> unfinished codes
		mushroom2.setRotation(0,180,1,0,0);
		mushroom2.Enable(true);
		mushrooms_.push_back(mushroom2);
        
        Flower mushroom3;
		mushroom3.loadModel("Environment/shroom_alpha.obj");
		mushroom3.setPosition(430,0,11);
		mushroom3.SetMaxScale(0.05);
		mushroom3.setRotation(0,180,1,0,0);
		mushroom3.Enable(true);
		mushrooms_.push_back(mushroom3);
       
        Flower mushroom4;
		mushroom4.loadModel("Environment/shroom_alpha.obj");
		mushroom4.setPosition(500,0,11);
		mushroom4.SetMaxScale(0.05);
        mushroom4.setRotation(0,180,1,0,0);
		mushroom4.Enable(true);
		mushrooms_.push_back(mushroom4);
        
        Flower mushroom5;
		mushroom5.loadModel("Environment/shroom_alpha.obj");
		mushroom5.setPosition(550,0,11);
        mushroom3.SetMaxScale(0.05);
		mushroom5.setRotation(0,180,1,0,0);
		mushroom5.Enable(true);
		mushrooms_.push_back(mushroom5);
       
        Flower mushroom6;
		mushroom6.loadModel("Environment/shroom_alpha.obj");
		mushroom6.setPosition(600,0,11);
        mushroom3.SetMaxScale(0.05);
		mushroom6.setRotation(0,180,1,0,0);
		mushroom6.Enable(true);
		mushrooms_.push_back(mushroom6);
        
        Flower mushroom7;
		mushroom7.loadModel("Environment/shroom_alpha.obj");
		mushroom7.setPosition(700,0,11);
		mushroom7.setRotation(0,180,1,0,0);
		mushroom7.Enable(true);
		mushrooms_.push_back(mushroom7);
        
        Flower mushroom8;
		mushroom8.loadModel("Environment/shroom_alpha.obj");
		mushroom8.setPosition(750,0,11);
        mushroom8.SetMaxScale(0.01);
		mushroom8.setRotation(0,180,1,0,0);
		mushroom8.Enable(true);
		mushrooms_.push_back(mushroom8);
        
        Flower mushroom9;
		mushroom9.loadModel("Environment/shroom_alpha.obj");
		mushroom9.setPosition(800,0,11);
        mushroom9.SetMaxScale(0.01);
		mushroom9.setRotation(0,180,1,0,0);
		mushroom9.Enable(true);
		mushrooms_.push_back(mushroom9);
        
        Flower mushroom10;
		mushroom10.loadModel("Environment/shroom_alpha.obj");
		mushroom10.setPosition(830,0,11);
        mushroom10.SetMaxScale(0.01);
		mushroom10.setRotation(0,180,1,0,0);
		mushroom10.Enable(true);
		mushrooms_.push_back(mushroom10);
        
        //// Flower Placing
        
        //17
        Flower mushroom;
		mushroom.loadModel("Environment/flower_alpha.obj");
        //112 110 -5
		mushroom.setPosition(112, 119, -5);
        //default value of max scaling
        //call this fun to set different size of mushroom
        //if not called, default value is 0.008
		mushroom.SetMaxScale(0.008);
		mushroom.setRotation(0,180,1,0,0);
		mushroom.setRotation(1,90,0,1,0);
		mushroom.Enable(false);
		mushrooms_.push_back(mushroom);
        
        Flower mushroom19;
		mushroom19.loadModel("Environment/flower_alpha.obj");
        //55 167 0
		mushroom19.setPosition(55, 176, 0);
        //default value of max scaling
        //call this fun to set different size of mushroom
        //if not called, default value is 0.008
		mushroom19.SetMaxScale(0.008);
		mushroom19.setRotation(0,180,1,0,0);
		mushroom19.setRotation(1,90,0,1,0);
		mushroom19.Enable(false);
		mushrooms_.push_back(mushroom19);
        
        Flower mushroom20;
		mushroom20.loadModel("Environment/flower_alpha.obj");
        //92 189 -3
		mushroom20.setPosition(92, 198, -3);
        //default value of max scaling
        //call this fun to set different size of mushroom
        //if not called, default value is 0.008
		mushroom20.SetMaxScale(0.008);
		mushroom20.setRotation(0,180,1,0,0);
		mushroom20.setRotation(1,90,0,1,0);
		mushroom20.Enable(false);
		mushrooms_.push_back(mushroom20);
        
        Flower mushroom21;
		mushroom21.loadModel("Environment/flower_alpha.obj");
        //130 191 1
        //0.02
		mushroom21.setPosition(130, 203, -2);
        //default value of max scaling
        //call this fun to set different size of mushroom
        //if not called, default value is 0.008
		mushroom21.SetMaxScale(0.02);
		mushroom21.setRotation(0,180,1,0,0);
		mushroom21.setRotation(1,90,0,1,0);
		mushroom21.Enable(false);
		mushrooms_.push_back(mushroom21);
        
        Flower mushroom22;
		mushroom22.loadModel("Environment/flower_alpha.obj");
        //174 186 -4
		mushroom22.setPosition(174, 195, -4);
        //default value of max scaling
        //call this fun to set different size of mushroom
        //if not called, default value is 0.008
		mushroom22.SetMaxScale(0.008);
		mushroom22.setRotation(0,180,1,0,0);
		mushroom22.setRotation(1,90,0,1,0);
		mushroom22.Enable(false);
		mushrooms_.push_back(mushroom22);
        
        Flower mushroom23;
		mushroom23.loadModel("Environment/flower_alpha.obj");
        //-203 126 7
		mushroom23.setPosition(-203, 135, 7);
        //default value of max scaling
        //call this fun to set different size of mushroom
        //if not called, default value is 0.008
		mushroom23.SetMaxScale(0.008);
		mushroom23.setRotation(0,180,1,0,0);
		mushroom23.setRotation(1,90,0,1,0);
		mushroom23.Enable(false);
		mushrooms_.push_back(mushroom23);
        
        Flower mushroom24;
		mushroom24.loadModel("Environment/flower_alpha.obj");
        //-98 130 3
		mushroom24.setPosition(-98, 139, 3);
        //default value of max scaling
        //call this fun to set different size of mushroom
        //if not called, default value is 0.008
		mushroom24.SetMaxScale(0.008);
		mushroom24.setRotation(0,180,1,0,0);
		mushroom24.setRotation(1,90,0,1,0);
		mushroom24.Enable(false);
		mushrooms_.push_back(mushroom24);
        
        Flower mushroom25;
		mushroom25.loadModel("Environment/flower_alpha.obj");
        //-168 185 -5
        //0.022
		mushroom25.setPosition(-168, 194, -5);
        //default value of max scaling
        //call this fun to set different size of mushroom
        //if not called, default value is 0.008
		mushroom25.SetMaxScale(0.022);
		mushroom25.setRotation(0,180,1,0,0);
		mushroom25.setRotation(1,90,0,1,0);
		mushroom25.Enable(false);
		mushrooms_.push_back(mushroom25);
        
        Flower mushroom26;
		mushroom26.loadModel("Environment/flower_alpha.obj");
        //-98 201 -6
		mushroom26.setPosition(-98, 210, -6);
        //default value of max scaling
        //call this fun to set different size of mushroom
        //if not called, default value is 0.008
		mushroom26.SetMaxScale(0.008);
		mushroom26.setRotation(0,180,1,0,0);
		mushroom26.setRotation(1,90,0,1,0);
		mushroom26.Enable(false);
		mushrooms_.push_back(mushroom26);
        
        Flower mushroom27;
		mushroom27.loadModel("Environment/flower_alpha.obj");
        //
		mushroom27.setPosition(-48, 214, -4);
        //default value of max scaling
        //call this fun to set different size of mushroom
        //if not called, default value is 0.008
		mushroom27.SetMaxScale(0.008);
		mushroom27.setRotation(0,180,1,0,0);
		mushroom27.setRotation(1,90,0,1,0);
		mushroom27.Enable(false);
		mushrooms_.push_back(mushroom27);
    
        Flower mushroom28;
		mushroom28.loadModel("Environment/flower_alpha.obj");
		mushroom28.setPosition(-199, 143, 3);
        //default value of max scaling
        //call this fun to set different size of mushroom
        //if not called, default value is 0.008
		mushroom28.SetMaxScale(0.008);
		mushroom28.setRotation(0,180,1,0,0);
		mushroom28.setRotation(1,90,0,1,0);
		mushroom28.Enable(false);
		mushrooms_.push_back(mushroom28);
        
        circle_.loadImage("Environment/glowing-circle-2.png");
        
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
        

		camera.enableOrtho();
        ofEnableAlphaBlending();
		camera.begin();
        
        ofEnableLighting();
        light_.enable();
        

        
		//draw static scene
		this->GetParent()->Draw();
		glEnable(GL_DEPTH_TEST);
		//draw mushrooms
        
        ofSetColor(255,0,0);
        ofSphere(1280,720,0,50);
		ofPushMatrix();
       // for(int i =0; i < mushrooms_.size(); ++i)
        {
            if(mushrooms_[0].Enabled())
                mushrooms_[0].Draw();
        }
		ofPopMatrix();
		//draw butterfly
		//butterfly.drawFaces();
        
        ofDrawAxis(100);
        glDisable(GL_DEPTH_TEST);
        light_.disable();


		camera.end();
		ofDisableAlphaBlending();

        
        ofDisableLighting();
        ofEnableAlphaBlending();
        
        
		ofVec3f pos = mushrooms_[0].getPosition();
		ofVec3f ss_pos = mushrooms_[0].GetScreenPos(pos, player.GetCamera());
        
		circle_.draw(pos.x,720-pos.y, 200, 200);
        
		player.wind_.Draw();
        
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
