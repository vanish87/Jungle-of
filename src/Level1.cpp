#include "Level1.h"
#include "Level2.h"
#include "JungleApp.h"

namespace Jungle
{
	Level1::Level1( void )
		//not use right now
		:wind_("config.xml")
	{
		
	}

	Level1::~Level1( void )
	{

	}

	void Level1::Steup()
	{
        
        trigger1.loadSound("trigger1.mp3");
//        trigger2.loadSound("trigger2.mp3");
        
		w_ = ofGetWindowWidth();
		h_ = ofGetWindowHeight();
		x_ = ofGetWindowPositionX();
		y_ = ofGetWindowPositionY();
		stage_.loadModel("Jungle_alpha_2.obj");
		stage_pos_.set(2,-42,9);
		stage_.setPosition(stage_pos_.x,stage_pos_.y,stage_pos_.z);
		//16,-42,-1
		//0.12
		stage_.setScale(0.05,0.05,0.05);
		stage_.setRotation(0, 180, 0, 0, 1);


		butterfly_.loadModel("Yellow_Butterfly_1.dae");
		butterfly_pos_ = ofVec3f(2,3.5, 10.7);
		butterfly_mass_ = 18000;//2500
		butterfly_acc_.set(0, 0, 0);

		butterfly_.setPosition(butterfly_pos_.x,butterfly_pos_.y,butterfly_pos_.z);
		butterfly_.setRotation(0, 150, 1, 0, 0); 
		butterfly_.setScale(0.003,0.003,0.003);


		//2 ,2.7, 10.3
		//
		Flower mushroom;
		mushroom.loadModel("shroom_6.dae");
		mushroom.setRotation(0,180,1,0,0);
		mushroom.setScale(0.000001, 0.000001, 0.000001);
		mushroom.setPosition(0.6, 2.35, 10);
		mushrooms_.push_back(mushroom);   

		Flower mushroom1;
		mushroom1.loadModel("shroom_6.dae");
		mushroom1.setRotation(0,180,1,0,0);
		mushroom1.setScale(0.000001, 0.000001, 0.000001);
		mushroom1.setPosition( 1.2, 2.35, 10);
		mushrooms_.push_back(mushroom1); 

		Flower mushroom2;
		mushroom2.loadModel("shroom_6.dae");
		mushroom2.setRotation(0,180,1,0,0);
		mushroom2.setScale(0.000001, 0.000001, 0.000001);
		mushroom2.setPosition( 2, 2.35, 10.3);
		mushrooms_.push_back(mushroom2);    

		Flower mushroom3;
		mushroom3.loadModel("shroom_6.dae");
		mushroom3.setRotation(0,180,1,0,0);
		mushroom3.setScale(0.000001, 0.000001, 0.000001);
		mushroom3.setPosition( 1.6, 2.36, 10.5);
		mushrooms_.push_back(mushroom3);    

		Flower flower;
		flower.loadModel("pre-Geranium.obj");
		flower.setRotation(0,90,1,0,0);
		flower.setScale(0.0005, 0.0005, 0.0005);
		flower.setPosition(-0.6, 9.4, 7.6);
		flowers_.push_back(flower);  

		Flower flower1;
		flower1.loadModel("pre-Geranium.obj");
		flower1.setRotation(0,90,1,0,0);
		flower1.setScale(0.0005, 0.0005, 0.0005);
		flower1.setPosition( 0.1, 9.3, 8.1);
		flowers_.push_back(flower1); 

		Flower flower2;
		flower2.loadModel("pre-Geranium.obj");
		flower2.setRotation(0,90,1,0,0);
		flower2.setScale(0.0005, 0.0005, 0.0005);
		flower2.setPosition(2.0, 9.03, 9.4);
		flowers_.push_back(flower2);    

		Flower flower3;
		flower3.loadModel("pre-Geranium.obj");
		flower3.setRotation(0,90,1,0,0);
		flower3.setScale(0.0005, 0.0005, 0.0005);
		flower3.setPosition( 1.5, 8.8, 9.3);
		flowers_.push_back(flower3);  
		
		//TODO: move it to butterfly class
		animation_time_ = 0;

		wind_.Init();
		two_hands_ = true;
		move_to_next_lev_ = false;
		level1_finished_ = false;
		level2_start_.set(1, 9, 10);
		moving_time_ = 0;

		clampX_.set(-5 , 5, 0);
		clampY_.set(2.7, 5, 0);

		light_.setDirectional();
		light_.setOrientation(ofVec3f(-32,-47,25));
		light_.setAmbientColor(ofFloatColor(0.5,0.5,0.5));
		light_.enable();

		camera_pos_ = ofVec3f(2, 3.5, 11.5);
		main_camera_.setFarClip(10000);
		main_camera_.setNearClip(0.1);
		main_camera_.setPosition(camera_pos_);
		main_camera_.lookAt(butterfly_pos_);

		ofBackground(0);
		ofSetFrameRate(60);
		ofSetVerticalSync(true);
		ofEnableBlendMode(OF_BLENDMODE_ALPHA);

		ofViewport(x_, y_, w_, h_, false);
		
		//b_pos_.set(300,300,0);
	}

	void Level1::Update()
	{
		ofxUser* user = JungleApp::KinectInstance().users;
		for(int i =0; i< MAX_USERS; ++i)
		{
			if(user[i].isActive&& user[i].bones)
			{
				Bones bone = user[i].bonesPoints;
				ofVec3f torsor_pos = bone.torso;
				torsor_pos.x = ofMap(torsor_pos.x , 
					MIN_KINECT_AREA.x, MAX_KINECT_AREA.x, MIN_PLAY_AREA.x, MAX_PLAY_AREA.x, true);
				torsor_pos.z = ofMap(torsor_pos.z ,
					MIN_KINECT_AREA.z, MAX_KINECT_AREA.z, MIN_PLAY_AREA.z, MAX_PLAY_AREA.z, true);



				ofVec3f l_hand_pos = bone.left_hand;
				ofVec3f r_hand_pos = bone.right_hand;
				ofVec3f hand_pos = l_hand_pos - r_hand_pos;

				pre_hand_pos_ = hand_pos_;


				if(two_hands_)
				{
					if(hand_pos.length() < 100)
					{
						hand_pos_.x = ofMap((l_hand_pos.x+ r_hand_pos.x)/2 , 0, 640, 0, w_, true);
						hand_pos_.y = ofMap((l_hand_pos.y+ r_hand_pos.y)/2  , 0, 480, 0, h_, true);

						wind_.Enable(true, hand_pos_);	
					}
				}
				else
				{
					hand_pos_.x = ofMap(r_hand_pos.x , 0, 640, 0, w_, true);
					hand_pos_.y = ofMap(r_hand_pos.y , 0, 480, 0, h_, true);


					wind_.Enable(true, hand_pos_);	
				}

				//cout<<shadow_pos_.x<<" "<<shadow_pos_.y<<" "<<shadow_pos_.z<<"\r";

			}
		}		


		wind_.Update(hand_pos_);

		animation_time_ += ofGetLastFrameTime()/24.0f;
		if( animation_time_ > 14.0f/360.0f )
		{
			animation_time_ = 0;
		}
		butterfly_.setAnimation(0);        
		butterfly_.setNormalizedTime(animation_time_);

		butterfly_acc_ += wind_.butterfly_force_ / butterfly_mass_;
		if(-0.00001 <= butterfly_acc_.x && butterfly_acc_.x <= 0.00001)
			butterfly_acc_.x = 0;
		if(-0.00001 <= butterfly_acc_.y && butterfly_acc_.y <= 0.00001)
			butterfly_acc_.y = 0;
		if(butterfly_acc_.x > 0)
			butterfly_acc_.x -= 0.001;
		else
		{
			if(butterfly_acc_.x < 0)
				butterfly_acc_.x += 0.001;
		}
		if(butterfly_acc_.y > 0)
			butterfly_acc_.y -= 0.001;
		else
		{
			if(butterfly_acc_.y < 0)
				butterfly_acc_.y += 0.001;
		}
//		cout<<butterfly_acc_.x<<" "<<butterfly_acc_.y<<"\r";
 		butterfly_pos_+= butterfly_acc_;

		butterfly_pos_.x = ofClamp(butterfly_pos_.x, clampX_.x, clampX_.y);
		butterfly_pos_.y = ofClamp(butterfly_pos_.y, clampY_.x, clampY_.y);
	

		butterfly_.setPosition(butterfly_pos_.x, butterfly_pos_.y, butterfly_pos_.z); 
		ofVec3f delta = butterfly_pos_ - camera_pos_;

		main_camera_.lookAt(butterfly_pos_);
		camera_pos_.x += delta.x/10;
		camera_pos_.y += delta.y/10;
		main_camera_.setPosition(camera_pos_);

		for(int i =0; i < 4; i++)
		{
			ofVec3f m_pos = mushrooms_[i].getPosition();
			m_pos.z = 0;
			ofVec3f b_pos = butterfly_pos_;
			b_pos.z = 0;
            if(0 == i)
                cout<<m_pos.distance(b_pos)<<"\r";
			if(m_pos.distance(b_pos) < 0.4 &&!mushrooms_[i].flower_collided_)
			{
				//mushrooms_[i].color_.set(255, 0, 0);
				mushrooms_[i].flower_collided_ = true;
                
				//playing triggering sound here
               // if(!trigger.getIsPlaying())
					trigger1.play();
			}
			if(level1_finished_)
			{
				ofVec3f f_pos = flowers_[i].getPosition();
				f_pos.z = 0;
				ofVec3f b_pos = butterfly_pos_;
				b_pos.z = 0;
				
				if(f_pos.distance(b_pos) < 0.1 &&!flowers_[i].flower_collided_)
				{

					//mushrooms_[i].color_.set(255, 0, 0);
					flowers_[i].flower_collided_ = true;

					//playing triggering sound here
					// if(!trigger.getIsPlaying())
					//trigger.play();
				}
			}
		}

		ofVec3f hand_delta =  hand_pos_- pre_hand_pos_;

		//cout<<delta.x<<" "<<delta.y<<" "<<delta.z<<endl;
		if(hand_delta.x == 0 && hand_delta.y == 0)
		{
			wind_.AddParticle(hand_pos_);
		}

		if(!level1_finished_)
		for(int i =0; i < 4; i++)
		{
			if (!mushrooms_[i].flower_collided_) 
			{
				move_to_next_lev_ = false;
				break;
			}
			move_to_next_lev_ = true;
		}

		if(move_to_next_lev_)
		{
			level1_finished_ = true;
			clampY_.y = 2.7 + level2_start_.y;
			moving_time_ +=0.001;
			ofVec3f cur_pos;
			//ofVec3f(2,3.5, 10.7);
			cur_pos.x = ofLerp(2, level2_start_.x, moving_time_);
			cur_pos.y = ofLerp(3.5, level2_start_.y, moving_time_);
			cur_pos.z = 10.7;
			butterfly_pos_ = cur_pos;
			if(moving_time_ > 1)
				move_to_next_lev_ = false;
			//TODO: use config class to store all general parameters
			//Level2 level2;
			//JungleApp::StateManagerInstance().ChangeState(&level2, SOP_PUSH);
		}


		pre_hand_pos_ = hand_pos_;
	}

	void Level1::Draw()
	{
		ofEnableAlphaBlending();
		ofEnableBlendMode(OF_BLENDMODE_ALPHA);
		ofSetColor(255, 255, 255);		
		main_camera_.begin();
		glPushMatrix();
		glEnable(GL_DEPTH_TEST);

		ofPushMatrix();
		stage_.drawFaces();
		ofPopMatrix();



		for(int i = 0; i < 4; i++)
		{
			if(mushrooms_[i].flower_collided_ )
				mushrooms_[i].Draw();            
		}

		for(int i = 0; i < 4; i++)
		{
			if(flowers_[i].flower_collided_ )
				flowers_[i].Draw();            
		}
// 		ofPushMatrix();
// 		ofTranslate(sphere_pos_.x, sphere_pos_.y, sphere_pos_.z);
// 		ofSphere(sphere_radius_);
// 		glPopMatrix();
		ofSetColor(255, 255, 255);	
		butterfly_.drawFaces();
		glPopMatrix();

		glDisable(GL_DEPTH_TEST);

		main_camera_.end();

		if(Jungle::KINECT_ENABLE)
		{
			glPushMatrix();
			ofTranslate(0, h_ - 0.3*h_);
			ofScale(0.4, 0.4);
			JungleApp::KinectInstance().debugDraw();
			glPopMatrix();
		}  

		//
		ofSetColor(255, 226, 141, 20); //color particles //added alpha
		ofPushMatrix();
		wind_.Draw();
		ofPopMatrix();

		ofSetColor(255,255,255,255);
		//ofDrawBitmapString("particle num "+ ofToString(NUM_PARTICLE), 20, 20);
		ofDrawBitmapString("birds pos "+ ofToString(butterfly_pos_.x) + " "+ ofToString(butterfly_pos_.y) + " "+ ofToString(butterfly_pos_.z), 20, 40);

	}

	void Level1::keyPressed( int key )
	{
		ofVec3f pos = flowers_[2].getPosition();
		switch (key)
		{
		case 'h':     
			two_hands_ = !two_hands_;
			break;
		case 'w':
			pos.z+=0.1;
			flowers_[2].setPosition(pos.x, pos.y,pos.z);
			break;
		case 's':
			pos.z-=0.1;
			flowers_[2].setPosition(pos.x, pos.y,pos.z);
			break;
		case 'n':
			for(int i =0; i < 4; i++)
			{
				mushrooms_[i].flower_collided_ = true;
			}
			break;
		}
	}

	void Level1::mouseMoved( int x, int y )
	{
		hand_pos_.set(x,y,0);
		wind_.Enable(true, hand_pos_);		
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
