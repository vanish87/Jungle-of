#include "GamingScene4.h"
#include "JungleApp.h"

namespace Jungle
{
	GamingScene4::GamingScene4(void)
	{
	}


	GamingScene4::~GamingScene4(void)
	{
	}

	void GamingScene4::Steup()
	{
		w_ = ofGetWindowWidth();
		h_ = ofGetWindowHeight();
		x_ = ofGetWindowPositionX();
		y_ = ofGetWindowPositionY();
		stage_.loadModel("Tree_Stage_Smooth.dae");
		tree_rotation_ = 0;
		stage_.setPosition(0, -139, 0);        
		stage_.setScale(0.5,0.5,0.5);
		stage_.setRotation(0, 180, 0, 0, 1);
		stage_.setRotation(1, -90, 0, 1, 0);
		background_.loadModel("background.dae");
		background_.setPosition(18, -70, -10);        
		background_.setScale(1 , 0.3 ,0.5);
		background_.setRotation(0, 180, 0, 0, 1);
		background_.setRotation(1, -90, 0, 1, 0);
		background_.disableMaterials();
		background_.disableNormals();

		sphere_.loadModel("sphere.dae");
		sphere_.setScale(0.003,0.003,0.003);
		sphere_pos_ = ofVec3f(3, 13, -2);
		sphere_.setPosition(sphere_pos_.x, sphere_pos_.y, sphere_pos_.z);
		sphere_radius_ = 2.0f;
		sphere_collided_ = false;
		//sphere_.setRotation(1, -90, 0, 1, 0);

		shadow_.loadModel("shadow.dae");
		shadow_.setPosition(0,0,0);
		shadow_.setScale(0.01,0.0001,0.01);
		//shadow_.setRotation(0, 180, 0, 0, 1);

		bird_.loadModel("smooth_birdy.dae");
		bird_pos_ = ofVec3f(2,3.5,5);
		bird_.setPosition(bird_pos_.x,bird_pos_.y,bird_pos_.z);
		bird_.setScale(0.003,0.003,0.003);
		bird_rot_.set(0, 0, 0);
		animation_time_= 0;

		right_wind_.loadImage("Right_Medium_Wind.png");
		right_wind_.rotate90(1);
		rw_pos_.set(10, 10, 0);
		rw_enabled_ = false;

		light_.enable();

		main_camera_.setPosition(ofVec3f(2, 3.5, 12));
		virtual_looking_obj_.setGlobalPosition(ofVec3f(2,3.5,0));
		main_camera_.lookAt(virtual_looking_obj_.getGlobalPosition());
		camera_orbit_para_ = ofVec3f(0,0,15);
		main_camera_.orbit(camera_orbit_para_.x,camera_orbit_para_.y, camera_orbit_para_.z,virtual_looking_obj_);


		ofBackground(0);
		ofSetFrameRate(60);
		ofSetVerticalSync(true);
		glShadeModel(GL_SMOOTH);
		ofEnableBlendMode(OF_BLENDMODE_ALPHA);

		ofViewport(x_, y_, w_, h_, false);
	}

	void GamingScene4::Update()
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
				shadow_pos_ = torsor_pos;
				//cout<<shadow_pos_.x<<" "<<shadow_pos_.y<<" "<<shadow_pos_.z<<"\r";
				
			}
		}
				
		//bird_pos_ = ofVec3f(shadow_pos_.x, bird_pos_.y, shadow_pos_.z);
		ofVec3f vo_pos = virtual_looking_obj_.getGlobalPosition();
		ofVec3f camera_pos = main_camera_.getPosition();

		ofVec3f dir = (camera_pos - vo_pos).normalize();
		dir *= camera_orbit_para_.z * 0.4;
		bird_pos_.y = dir.y + vo_pos.y;


		//with 2 x cood shift
		if(bird_pos_.x > 5+2)
			tree_rotation_--;
		else
			if(bird_pos_.x < -5+2)
				tree_rotation_++;


		//cout<<bird_pos_.x<<" "<<bird_pos_.y<<" "<<bird_pos_.z<<endl;


		//cout<<bird_pos_.x<<" "<<bird_pos_.y<<" "<<bird_pos_.z<<endl;
		//cout<<sphere_pos_.x<<" "<<sphere_pos_.y<<" "<<sphere_pos_.z<<endl;
		
		ofVec3f world_pos = sphere_pos_;
		world_pos.rotate(tree_rotation_, ofVec3f(0, 1, 0));
		float dis = bird_pos_.distance(world_pos);
		if(dis < sphere_radius_)
			sphere_collided_ = true;
		else
			sphere_collided_ = false;
		ofPopMatrix();
		
		
		main_camera_.orbit(camera_orbit_para_.x,camera_orbit_para_.y, camera_orbit_para_.z,virtual_looking_obj_);


		animation_time_ += ofGetLastFrameTime();
		if( animation_time_ >= 1.0 ){
			animation_time_ = 0.0;
		}
		bird_.setAnimation(0);
		bird_.setNormalizedTime(animation_time_);

		bird_.setAnimation(1);
		bird_.setNormalizedTime(animation_time_);
		
		if(rw_enabled_)
		{			
			bird_.setRotation(0, bird_rot_.z, 0, 0 ,1); 
			bird_pos_ +=ofVec3f(-1* bird_rot_.z * 0.005,-1.5* bird_rot_.z * 0.005,0);
			if(bird_rot_.z < 0) 
			{
				bird_rot_.z+=2;
			}
			else
				if(bird_rot_.z > 0)
				{
					bird_rot_.z-=2;
				}
				else
				{

					rw_enabled_ = false;
				}
		}

		shadow_.setPosition(shadow_pos_.x, 0, shadow_pos_.z);
		bird_.setPosition(bird_pos_.x, bird_pos_.y, bird_pos_.z);
	}

	void GamingScene4::Draw()
	{
		ofEnableBlendMode(OF_BLENDMODE_ALPHA);
		ofSetColor(255, 255, 255);		
		main_camera_.begin();
		glPushMatrix();
		glEnable(GL_DEPTH_TEST);
		
		background_.drawFaces();

		ofPushMatrix();
		ofRotateY(tree_rotation_);
		stage_.drawFaces();
		if(sphere_collided_)
			ofSetColor(0, 255, 0);
		sphere_.drawFaces();
		ofPopMatrix();

		ofSetColor(255, 255, 255);	
		shadow_.drawFaces();
		bird_.drawFaces();
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

		ofSetColor(255, 255, 255);	
		if(rw_enabled_)
			right_wind_.draw(rw_pos_.x, rw_pos_.y, 0 , 360,213);
	}

	void GamingScene4::keyPressed( int key )
	{
		ofVec3f pos = main_camera_.getPosition();
		ofVec3f vo_pos = virtual_looking_obj_.getGlobalPosition();
		shadow_pos_= shadow_.getPosition();
		switch (key)
		{
		case 's':
			//                 pos.z++;
			//                 main_camera_.setPosition(pos);                
			//                 main_camera_.lookAt(look_at_);
			//main_camera_.dolly(1);
			if(camera_orbit_para_.y > -90)
				camera_orbit_para_.y--;
			break;
		case 'w':
			//                 pos.z--;
			//                 main_camera_.setPosition(pos);
			//                 main_camera_.lookAt(look_at_);
			//main_camera_.dolly(-1);
			if(camera_orbit_para_.y < 90)
				camera_orbit_para_.y++;
			break;	
		case 'q':
			pos.y++;
			//look_at_.y++;
			main_camera_.setPosition(pos);                
			//main_camera_.lookAt(look_at_);
			break;
		case 'z':
			pos.y--;
			//look_at_.y--;
			main_camera_.setPosition(pos);
			//main_camera_.lookAt(look_at_);
			break;
		case 'a':
			//                 pos.x--;
			//                 main_camera_.setPosition(pos);                
			//                 main_camera_.lookAt(look_at_);
			//main_camera_.truck(-1);
			//camera_orbit_para_.x--;
			bird_pos_.x++;
			break;
		case 'd':
			//                 pos.x++;
			//                 main_camera_.setPosition(pos);
			//                 main_camera_.lookAt(look_at_);
			//main_camera_.truck(1);
			//camera_orbit_para_.x++;
			bird_pos_.x--;
			break;
		case 'e':
			//look_at_.y++;
			main_camera_.setPosition(pos);                
			//main_camera_.lookAt(look_at_);
			break;
		//case 'c':
			// look_at_.y--;
			//main_camera_.setPosition(pos);
			//main_camera_.lookAt(look_at_);
			//break;
		case 'y':
			shadow_pos_ . z--;
			//shadow_.setPosition(shadow_pos_.x, shadow_pos_.y, shadow_pos_.z);

			break;
		case 'h':

			shadow_pos_ . z++;
			//shadow_.setPosition(shadow_pos_.x, shadow_pos_.y, shadow_pos_.z);
			//vo_pos.y--;
			//virtual_looking_obj_.setGlobalPosition(vo_pos);
			break;
		case 'g':

			shadow_pos_ . x--;
			//shadow_.setPosition(shadow_pos_.x, shadow_pos_.y, shadow_pos_.z);
			break;
		case 'j':

			shadow_pos_ . x++;
			//shadow_.setPosition(shadow_pos_.x, shadow_pos_.y, shadow_pos_.z);
			break;
		case 'v':     
			//bird_pos_.y+=bird_speed_;
			rw_enabled_ = true;
			bird_rot_.z-=60;
			break;
		case 'c':     
			//bird_pos_.y+=bird_speed_;
			rw_enabled_ = true;
			bird_rot_.z+=60;
			break;
		case 'o':     
			tree_rotation_++;
			break;
		case 'p':     
			tree_rotation_--;
			break;
		case 'm':     
			vo_pos.y++;
			virtual_looking_obj_.setGlobalPosition(vo_pos);
			break;
		case 'n':     
			vo_pos.y--;
			virtual_looking_obj_.setGlobalPosition(vo_pos);
			break;
		default:
			break;
		}
	}

	void GamingScene4::mouseMoved( int x, int y )
	{
	}

	void GamingScene4::windowResized( int w, int h )
	{
	}

	void GamingScene4::inPose( ofxUser & user )
	{
	}

	void GamingScene4::inGesture( ofxUser & user )
	{
		cout<<ofGetElapsedTimef()<<"---"<<user.gesture<<endl;
		if(user.gesture == "LeftWind")
		{
			rw_enabled_ = true;
			bird_rot_.z-=60;
		}
	}

	void GamingScene4::userIn( ofxUser & user )
	{
	}

	void GamingScene4::userMove( ofxUser & user )
	{
	}

	void GamingScene4::userOut( ofxUser & user )
	{
	}

}
