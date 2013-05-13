#include "Level1.h"
#include "JungleApp.h"
#include "ofGraphics.h"
#include "Utility.h"

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
        
        light_.setAmbientColor(ofFloatColor(1, 0, 0));
        light_.setDiffuseColor(ofFloatColor(1 ,1 ,1));
        light_.setSpecularColor(ofFloatColor(0,0,0));
 
        light_.setDirectional();
        light_.setPosition(1024, 768, 0);

        ofEnableLighting();
        light_.enable();
        ofBackground(255);

        
        max_leaf_ = 0;
		angle_ = 90;

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
        JungleApp::SceneManagerInstance().Reset();
        //JungleApp::SceneManagerInstance().Reset();
        
        stage_color_ = JungleApp::SceneManagerInstance().GetStageColor();
        //light_color_ = stage_color[1];
//        
//        cout<<(int)light_color_[0].r<<" "<<
//        (int)light_color_[0].g<<" "<<
//        (int)light_color_[0].b<<" "<<
//        (int)light_color_[0].a<<endl;
            
       SceneType &scene = JungleApp::SceneManagerInstance().GetDynamicObj();
	   light_.setDiffuseColor(stage_color_[0][1]);
	   light_.setAmbientColor(stage_color_[0][1]);
	   current_stage_ = TREE;
       for (unsigned int i =0; i < 5; ++i)
       {
		   time_.push_back(0.0f);
       }

        
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
        
		ofQuaternion q;
		q.makeRotate(angle_, 1, 0, 0);
		light_.setOrientation(q);

        unsigned int fruit_count = 0;
        unsigned int cloud_count = 0;
        vector<unsigned short> light_index = JungleApp::SceneManagerInstance().GetLightingIndex();
		SceneType &scene = JungleApp::SceneManagerInstance().GetDynamicObj();
		SceneManager& scene_mag_ = JungleApp::SceneManagerInstance();		

		StaticScene* static_scene = static_cast<StaticScene*>(this->GetParent());

		max_leaf_ = scene_mag_.GetTriggeringCount(Group::LEAF);

		for(SceneType::iterator it = scene.begin(); it!= scene.end(); ++it)
		{
			if(Jungle::KINECT_ENABLE)
				it->Update(player.l_hand_pos_,player.r_hand_pos_);
			else
				it->Update(player.r_hand_pos_, ofVec3f(0,0,0));

			it->Update(ofGetLastFrameTime());
			
		}

		//update static scene
		this->GetParent()->Update();

		switch (current_stage_)
		{
		case Jungle::Level1::TREE:
            light_.setDiffuseColor(stage_color_[0][1]);
            light_.setAmbientColor(stage_color_[0][1]);
            static_scene->SetBackgroundStart(stage_color_[0][0]);
			if(scene_mag_.GetTriggeringCount(Group::TREE) > 4)
			{
				JungleApp::SceneManagerInstance().Enable(Group::LEAF,true);
				current_stage_ = LEAF;
			}
			break;
		case Jungle::Level1::LEAF:
			//tree->leaf
			time_[0] +=ofGetLastFrameTime();
			if(time_[0] < 1)
			{
				ofColor lcolor = light_.getDiffuseColor();
				ofColor color = Lerp(stage_color_[0][1], stage_color_[1][1], time_[0]);

				ofColor bcolor = Lerp(stage_color_[0][0], stage_color_[1][0], time_[0]);
				static_scene->SetBackgroundStart(bcolor);

				light_.setDiffuseColor(color);
				light_.setAmbientColor(color);
			}
			else
				time_[0] = 1;

			//fruit->leaf
			time_[1] -=ofGetLastFrameTime();
			if(time_[1] > 0)
			{
				ofColor lcolor = light_.getDiffuseColor();
				ofColor color = Lerp(stage_color_[1][1], stage_color_[2][1], time_[1]);

				ofColor bcolor = Lerp(stage_color_[1][0], stage_color_[2][0], time_[1]);
				static_scene->SetBackgroundStart(bcolor);

				light_.setDiffuseColor(color);
				light_.setAmbientColor(color);
			}
			else				
				time_[1] = 0;

			if( scene_mag_.GetTriggeringCount(Group::LEAF) > 80)
			{
				JungleApp::SceneManagerInstance().Enable(Group::FRUIT,true);
				current_stage_ = FRUIT;
			}
			break;
		case Jungle::Level1::FRUIT:
			//leaf->fruit
			time_[1] +=ofGetLastFrameTime();
			if(time_[1] < 1)
			{
				ofColor lcolor = light_.getDiffuseColor();
				ofColor color = Lerp(stage_color_[1][1], stage_color_[2][1], time_[1]);

				ofColor bcolor = Lerp(stage_color_[1][0], stage_color_[2][0], time_[1]);
				static_scene->SetBackgroundStart(bcolor);

				light_.setDiffuseColor(color);
				light_.setAmbientColor(color);
			}
			else
				time_[1] = 1;

			//mushroom->fruit
			time_[2] -=ofGetLastFrameTime();
			if(time_[2] > 0)
			{
				ofColor lcolor = light_.getDiffuseColor();
				ofColor color = Lerp(stage_color_[2][1], stage_color_[3][1], time_[2]);

				ofColor bcolor = Lerp(stage_color_[2][0], stage_color_[3][0], time_[2]);
				static_scene->SetBackgroundStart(bcolor);

				light_.setDiffuseColor(color);
				light_.setAmbientColor(color);
			}
			else				
				time_[2] = 0;

			if( scene_mag_.GetTriggeringCount(Group::FRUIT) > 4)
			{
				current_stage_ = MUSHROOM;
				JungleApp::SceneManagerInstance().Enable(Group::MUSHROOM,true);
				JungleApp::SceneManagerInstance().Enable(Group::CLOUD,  true);
			}
			else
			{
				JungleApp::SceneManagerInstance().Enable(Group::MUSHROOM,false);
				if( scene_mag_.GetTriggeringCount(Group::LEAF) < 80 && time_[2] == 0)
				{
					JungleApp::SceneManagerInstance().Enable(Group::FRUIT,false);
					current_stage_ = LEAF;
				}
			}
			break;
		case Jungle::Level1::CLOUD:
			break;
		case Jungle::Level1::MUSHROOM:
			time_[2] +=ofGetLastFrameTime();
			if(time_[2] < 1)
			{
				ofColor lcolor = light_.getDiffuseColor();
				ofColor color = Lerp(stage_color_[2][1], stage_color_[3][1], time_[2]);

				ofColor bcolor = Lerp(stage_color_[2][0], stage_color_[3][0], time_[2]);
				static_scene->SetBackgroundStart(bcolor);

				light_.setDiffuseColor(color);
				light_.setAmbientColor(color);
			}
			else
				time_[2] = 1;

			if( scene_mag_.GetTriggeringCount(Group::FRUIT) < 4)
			{
				current_stage_ = FRUIT;
				JungleApp::SceneManagerInstance().Enable(Group::MUSHROOM,false);
			}
			break;
		default:
			break;
		}



// 		if( scene_mag_.GetTriggeringCount(Group::LEAF) > 80)
// 		{
// 			time_[1] +=ofGetLastFrameTime();
// 			if(time_[1] < 1)
// 			{
// 				ofColor lcolor = light_.getDiffuseColor();
// 				ofColor color;
// 				color.r = ofLerp(stage_color_[1][1].r, stage_color_[2][1].r, time_[1]);
// 				color.g = ofLerp(stage_color_[1][1].g, stage_color_[2][1].g, time_[1]);
// 				color.b = ofLerp(stage_color_[1][1].b, stage_color_[2][1].b, time_[1]);
// 				light_.setDiffuseColor(color);
// 				light_.setAmbientColor(color);
// 			}
// 			else
// 				time_[1] = 1;
// 			JungleApp::SceneManagerInstance().Enable(Group::FRUIT,true);
// 		}	
// 		else
// 		{
// 			time_[1] -=ofGetLastFrameTime();
// 			if(time_[1] > 0)
// 			{
// 				ofColor lcolor = light_.getDiffuseColor();
// 				ofColor color;
// 				color.r = ofLerp(stage_color_[1][1].r, stage_color_[2][1].r, time_[1]);
// 				color.g = ofLerp(stage_color_[1][1].g, stage_color_[2][1].g, time_[1]);
// 				color.b = ofLerp(stage_color_[1][1].b, stage_color_[2][1].b, time_[1]);
// 				light_.setDiffuseColor(color);
// 				light_.setAmbientColor(color);
// 			}
// 			else
// 				time_[1] = 0;
// 			JungleApp::SceneManagerInstance().Enable(Group::FRUIT,false);
// 		}
// 
// 		if( scene_mag_.GetTriggeringCount(Group::FRUIT) > 4)
// 		{
// 			time_[2] +=ofGetLastFrameTime();
// 			if(time_[2] < 1)
// 			{
// 				ofColor lcolor = light_.getDiffuseColor();
// 				ofColor color;
// 				color.r = ofLerp(stage_color_[2][1].r, stage_color_[3][1].r, time_[2]);
// 				color.g = ofLerp(stage_color_[2][1].g, stage_color_[3][1].g, time_[2]);
// 				color.b = ofLerp(stage_color_[2][1].b, stage_color_[3][1].b, time_[2]);
// 				light_.setDiffuseColor(color);
// 				light_.setAmbientColor(color);
// 			}
// 			else
// 				time_[2] = 1;
// 			JungleApp::SceneManagerInstance().Enable(Group::MUSHROOM,true);
// 		}
// 		else
// 		{
// 			time_[2] -=ofGetLastFrameTime();
// 			if(time_[2] > 0)
// 			{
// 				ofColor lcolor = light_.getDiffuseColor();
// 				ofColor color;
// 				color.r = ofLerp(stage_color_[2][1].r, stage_color_[3][1].r, time_[2]);
// 				color.g = ofLerp(stage_color_[2][1].g, stage_color_[3][1].g, time_[2]);
// 				color.b = ofLerp(stage_color_[2][1].b, stage_color_[3][1].b, time_[2]);
// 				light_.setDiffuseColor(color);
// 				light_.setAmbientColor(color);
// 			}
// 			else
// 				time_[2] = 0;
// 			JungleApp::SceneManagerInstance().Enable(Group::MUSHROOM,false);
// 		}
// 
// 		if( scene_mag_.GetTriggeringCount(Group::FRUIT) > 4)
// 		{
// 
// 			JungleApp::SceneManagerInstance().Enable(Group::CLOUD,true);
// 		}
// 		else
// 		{
// 			JungleApp::SceneManagerInstance().Enable(Group::CLOUD,false);
// 		}
	}

	void Level1::Draw()
	{

		Player& player = JungleApp::PlayerInstance();

		ofCamera camera = player.GetCamera();

        ofEnableAlphaBlending();
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE);
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
			ofDrawBitmapString("angle  "+ ofToString(angle_), 20, 40);
			ofDrawBitmapString("time_[1] "+ ofToString(time_[1]), 20, 60);

			ofDrawBitmapString("stage "+ ofToString(current_stage_), 20, 80);
			ofDrawBitmapString("Mouse pos " + ofToString(ofGetMouseX())+ " " +ofToString(h_ - ofGetMouseY()), 20, 100);
			//ofDrawBitmapString("hand "+ ofToString(bt_pos.x) + " "+ ofToString(bt_pos.y), 20, 100);
		}
		//ofDrawBitmapString("mush pos "+ ofToString(mushrooms_[index_].getPosition().x) + " "+ ofToString(mushrooms_[index_].getPosition().y)+ " "+ ofToString(mushrooms_[index_].getPosition().z), 20, 160);

	}

	void Level1::keyPressed( int key )
	{
        Player& player = JungleApp::PlayerInstance();
        
        int index = 0;
        index_ = index;
        ofVec3f pos;// = mushrooms_[index].getPosition();
		ofVec3f scale;// = mushrooms_[index].getScale();
        
        ofVec3f cam_pos=player.player_camera_.getPosition();
        
        ofQuaternion q;

        //static scene
        //this->GetParent()->keyPressed(key);
        //return;
		switch (key)
		{
            case 's':
                angle_+=1;
                break;
            case 'w':
                angle_-=1;
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
    
        q.makeRotate(angle_, 1, 0, 0);
        //light_.setPosition(500, angle_, 0);
        light_.setOrientation(q);
        //player.player_camera_.setPosition(cam_pos);
		//mushrooms_[index].setPosition(pos.x, pos.y, pos.z);
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


		JungleApp::SceneManagerInstance().Reset();
		light_.setDiffuseColor(stage_color_[0][1]);
		light_.setAmbientColor(stage_color_[0][1]);
		current_stage_ = TREE;
	}

}
