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
        
        max_leaf_ = 0;

		// Mushroom Placement        
        title_.loadImage("UI/title-screen-3.png");
        
        index_=0;
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
 
        
        if(!JungleApp::SceneManagerInstance().LoadScene("SceneConfig.xml"))
            cout<<"Cannot Load Scene"<<endl;
			//throw exception("Cannot Load Scene");;
       JungleApp::SceneManagerInstance().Enable(Group::TREE,true);
        
        
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
        
        max_leaf_ = 0;
        unsigned int fruit_count = 0;
		SceneType &scene = JungleApp::SceneManagerInstance().GetDynamicObj();
		for(SceneType::iterator it = scene.begin(); it!= scene.end(); ++it)
		{
			if(Jungle::KINECT_ENABLE)
				it->Update(player.l_hand_pos_,player.r_hand_pos_);
			else
				it->Update(player.r_hand_pos_, ofVec3f(0,0,0));

			it->Update(ofGetLastFrameTime());
			if(it->GetType() == Group::TREE)
            {
				if(it->GetTriggeringCount() > 4)
				{
					JungleApp::SceneManagerInstance().Enable(Group::LEAF,true);
				}
                else
                {
                    JungleApp::SceneManagerInstance().Enable(Group::LEAF,false);
                }
            }
            if(it->GetType() == Group::LEAF)
            {
                max_leaf_ += it->GetTriggeringCount();
                //cout<<max_leaf_<<endl;
                if( max_leaf_ > 130)
				{
                    JungleApp::SceneManagerInstance().Enable(Group::FRUIT,true);
                }
                else
                {
                    JungleApp::SceneManagerInstance().Enable(Group::FRUIT,false);
                }
            }
            if(it->GetType() == Group::FRUIT)
            {
                fruit_count += it->GetTriggeringCount();
                //cout<<max_leaf_<<endl;
                if( fruit_count > 4)
				{
                    JungleApp::SceneManagerInstance().Enable(Group::MUSHROOM,true);
                }
                else
                {
                    JungleApp::SceneManagerInstance().Enable(Group::MUSHROOM,false);
                }
            }
		}

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
		SceneType &scene = JungleApp::SceneManagerInstance().GetDynamicObj();
		for(SceneType::iterator it = scene.begin(); it!= scene.end(); ++it)
		{
            it->Draw();
		}
		ofPopMatrix();

        glDisable(GL_DEPTH_TEST);
        light_.disable();

		camera.end();
		ofDisableAlphaBlending();

        
        ofDisableLighting();
        ofEnableAlphaBlending();   
        
		ofPushMatrix();
        ofDisableLighting();
        ofEnableAlphaBlending();
		player.wind_.Draw();
        ofSetColor(255, 255, 255);
        if(!player.detected_)
            title_.draw(ofPoint(0,0), ofGetScreenWidth(), ofGetScreenHeight());
        ofDisableAlphaBlending();

		ofPopMatrix();

        ofSetColor(255, 255, 255);
		if(Jungle::KINECT_ENABLE && JUNGLE_DEBUG)
		{
			glPushMatrix();
			ofTranslate(0, h_ - 0.3*h_);
			ofScale(0.4, 0.4);
			JungleApp::KinectInstance().debugDraw();
			glPopMatrix();
		}

		//ofVec3f mh_pos = ofVec3f(mushrooms_[0].getPosition().x, mushrooms_[0].getPosition().y, 0);
        
		if(JUNGLE_DEBUG)
		{
			ofSetColor(255, 255, 255,255);
			ofDrawBitmapString("leaf num "+ ofToString(max_leaf_), 20, 20);
			//ofDrawBitmapString("v length "+ ofToString((bt_pos - mh_pos).length()), 20, 40);
			//ofDrawBitmapString("scale "+ ofToString(mushrooms_[index_].getScale().x), 20, 60);
			
			ofDrawBitmapString("Mouse pos " + ofToString(ofGetMouseX())+ " " +ofToString(h_ - ofGetMouseY()), 20, 40);
			//ofDrawBitmapString("pre "+ ofToString(player.pre_hand_pos_.x) + " "+ ofToString(player.pre_hand_pos_.y), 20, 80);
			//ofDrawBitmapString("hand "+ ofToString(bt_pos.x) + " "+ ofToString(bt_pos.y), 20, 100);
		}
		//ofDrawBitmapString("mush pos "+ ofToString(mushrooms_[index_].getPosition().x) + " "+ ofToString(mushrooms_[index_].getPosition().y)+ " "+ ofToString(mushrooms_[index_].getPosition().z), 20, 160);

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
