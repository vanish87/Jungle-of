#include "Level1.h"
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
		w_ = ofGetWindowWidth();
		h_ = ofGetWindowHeight();
		x_ = ofGetWindowPositionX();
		y_ = ofGetWindowPositionY();
		stage_.loadModel("Jungle_alpha_2.obj");
		stage_pos_.set(2,-42,9);
		stage_.setPosition(stage_pos_.x,stage_pos_.y,stage_pos_.z);
		//16,-42,-1
		//0.12
		stage_.setScale(0.04,0.04,0.04);
		stage_.setRotation(0, 180, 0, 0, 1);


		butterfly_.loadModel("Yellow_Butterfly_1.dae");
		butterfly_pos_ = ofVec3f(2,3.5, 10);

		butterfly_.setPosition(butterfly_pos_.x,butterfly_pos_.y,butterfly_pos_.z);
		butterfly_.setRotation(0, 150, 1, 0, 0); 
		butterfly_.setScale(0.005,0.005,0.005);
		
		//TODO: move it to butterfly class
		animation_time_ = 0;

		wind_.Init();
		two_hands_ = true;

		light_.setDirectional();
		light_.setOrientation(ofVec3f(-32,-47,25));
		light_.setAmbientColor(ofFloatColor(0.5,0.5,0.5));
		light_.enable();

		camera_pos_ = ofVec3f(2, 3.5, 12);
		main_camera_.setFarClip(10000);
		main_camera_.setNearClip(1);
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
					}
				}
				else
				{
					hand_pos_.x = ofMap(r_hand_pos.x , 0, 640, 0, w_, true);
					hand_pos_.y = ofMap(r_hand_pos.y , 0, 480, 0, h_, true);
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

		ofMatrix4x4 mvp_mat_ = main_camera_.getModelViewProjectionMatrix();
		butterfly_pos_ss_= butterfly_pos_ * mvp_mat_ ;
		ofPoint screen_pos;
		screen_pos.set(butterfly_pos_ss_.x * w_/2 + (x_/2 + w_/2), h_ - (butterfly_pos_ss_.y * h_/2 + (y_/2 + h_/2)));

		butterfly_pos_ss_.set(screen_pos.x, screen_pos.y);

 		butterfly_pos_+= wind_.butterfly_force_ * 0.0001;
		butterfly_pos_.x = ofClamp(butterfly_pos_.x, -5, 5);
		butterfly_pos_.y = ofClamp(butterfly_pos_.y,  2.7, 5);

		butterfly_.setPosition(butterfly_pos_.x, butterfly_pos_.y, butterfly_pos_.z); 
		ofVec3f delta = butterfly_pos_ - camera_pos_;

		main_camera_.lookAt(butterfly_pos_);
		camera_pos_.x += delta.x/10;
		camera_pos_.y += delta.y/10;
		main_camera_.setPosition(camera_pos_);
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

		ofSetColor(255, 255, 255);	
		butterfly_.drawFaces();

// 		for(int i = 0; i < 4; i++)
// 		{
// 			//if(flowers_[i].flower_collided_ )
// 			flowers_[i].Draw();            
// 		}
// 		ofPushMatrix();
// 		ofTranslate(sphere_pos_.x, sphere_pos_.y, sphere_pos_.z);
// 		ofSphere(sphere_radius_);
// 		glPopMatrix();
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
		//ofDrawBitmapString("birds pos "+ ofToString(bird_pos_.x) + " "+ ofToString(bird_pos_.y) + " "+ ofToString(bird_pos_.z), 20, 40);

	}

	void Level1::keyPressed( int key )
	{

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
