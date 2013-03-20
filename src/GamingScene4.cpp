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

		sphere_.loadModel("flower_1.dae");
		sphere_.setScale(0.003,0.003,0.003);
		sphere_pos_ = ofVec3f(3, 14, -2);
		sphere_.setPosition(sphere_pos_.x, sphere_pos_.y, sphere_pos_.z);
		sphere_radius_ = 3.0f;
		sphere_collided_ = false;

		shadow_.loadModel("shadow.dae");
		shadow_.setPosition(0,0,0);
		shadow_.setScale(0.01,0.0001,0.01);
		//shadow_.setRotation(0, 180, 0, 0, 1);

		bird_.loadModel("Yellow_Butterfly_1.dae");
		bird_pos_ = ofVec3f(2,3.5,5);
		bird_.setPosition(bird_pos_.x,bird_pos_.y,bird_pos_.z);
		bird_.setScale(0.05,0.05,0.05);
		bird_rot_.set(0, 0, 0);
		animation_time_= 0;
        bird_rotation_ = 0;
        bird_.disableNormals();

		right_wind_.loadImage("Right_Medium_Wind.png");
		right_wind_.rotate90(1);
		rw_pos_.set(10, 10, 0);
		rw_enabled_ = false;

		left_wind_start_ = false;
		right_wind_start_ = false;

		light_.setAmbientColor(ofFloatColor(0.2,0.2,0.2));
        light_.setDiffuseColor(ofFloatColor(0.3,0.3,0.3));
        light_.setSpecularColor(ofFloatColor(0.3,0.3,0.3));
        light_.setPosition(0, 100, 0);
        ofSetSmoothLighting(true);
        light_.enable();
        
		main_camera_.setPosition(ofVec3f(2, 3.5, 12));
		virtual_looking_obj_.setGlobalPosition(ofVec3f(2,3.5,0));
		main_camera_.lookAt(virtual_looking_obj_.getGlobalPosition());
		camera_orbit_para_ = ofVec3f(0,0,15);
		main_camera_.orbit(camera_orbit_para_.x,camera_orbit_para_.y, camera_orbit_para_.z,virtual_looking_obj_);
        
        if ( !emitter_.loadFromXml( "circles.pex" ) )
        {
            ofLog( OF_LOG_ERROR, "testApp::setup() - failed to load emitter config" );
        }

		particle_scale_ =1;

		gesture_timer_ = 0;

		ofBackground(0);
		ofSetFrameRate(60);
		ofSetVerticalSync(true);
		//ofShadeModel(GL_SMOOTH);
		ofEnableBlendMode(OF_BLENDMODE_ALPHA);

		ofViewport(x_, y_, w_, h_, false);
	}

	void GamingScene4::Update()
	{
        emitter_.update();
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

				ofVec3f hand_pos = bone.right_hand;
				pre_hand_pos_ = hand_pos_;
				hand_pos_.x = ofMap(hand_pos.x , 0, 640, 0, w_, true);
				hand_pos_.y = ofMap(hand_pos.y , 0, 480, 0, h_, true);
				//cout<<shadow_pos_.x<<" "<<shadow_pos_.y<<" "<<shadow_pos_.z<<"\r";
				
			}
		}
				
		//bird_pos_ = ofVec3f(shadow_pos_.x, bird_pos_.y, shadow_pos_.z);
		ofVec3f vo_pos = virtual_looking_obj_.getGlobalPosition();
		ofVec3f camera_pos = main_camera_.getPosition();

/*
		ofVec3f dir = (camera_pos - vo_pos).normalize();
		dir *= camera_orbit_para_.z * 0.4;
		bird_pos_.y = dir.y + vo_pos.y;*/


/*
		//with 2 x cood shift
		if(bird_pos_.x > 5+2)
			tree_rotation_--;
		else
			if(bird_pos_.x < -5+2)
				tree_rotation_++;
        
        //with 2 x cood shift
		if(bird_pos_.x > 5 + 2 + 1)
			bird_pos_.x = 8;
		else
			if(bird_pos_.x < -5+2 -1)
				bird_pos_.x = -4;*/


		//cout<<bird_pos_.x<<" "<<bird_pos_.y<<" "<<bird_pos_.z<<endl;


		//cout<<bird_pos_.x<<" "<<bird_pos_.y<<" "<<bird_pos_.z<<endl;
		//cout<<sphere_pos_.x<<" "<<sphere_pos_.y<<" "<<sphere_pos_.z<<endl;
		
		/*ofVec3f world_pos = sphere_pos_;
		world_pos.rotate(tree_rotation_, ofVec3f(0, 1, 0));
		float dis = bird_pos_.distance(world_pos);
		if(dis < sphere_radius_)
			sphere_collided_ = true;*/
		ofPopMatrix();
		
		
		main_camera_.orbit(camera_orbit_para_.x,camera_orbit_para_.y, camera_orbit_para_.z,virtual_looking_obj_);


		animation_time_ += ofGetLastFrameTime()/24.0f;
		if( animation_time_ > 14.0f/360.0f ){
			animation_time_ = 0;
		}
        //bird_.getDuration(0)/192.0f;
		bird_.setAnimation(0);        
		bird_.setNormalizedTime(animation_time_);


//		bird_.setAnimation(1);
//		bird_.setNormalizedTime(animation_time_);

		
		/*if(rw_enabled_)
		{			
			bird_.setRotation(1, -bird_rot_.z, 0, 0 ,1); 
			bird_pos_ +=ofVec3f(-1* bird_rot_.z * 0.005,abs(5.5* bird_rot_.z * 0.005),0);
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
		}*/
		if(-0.01 <= bird_acc_.x && bird_acc_.x <= 0.01)
			bird_acc_.x = 0;
		if(-0.01 <= bird_acc_.y && bird_acc_.y <= 0.01)
			bird_acc_.y = 0;
        if(bird_acc_.x > 0)
            bird_acc_.x -= 0.01;
        else
        {
            if(bird_acc_.x < 0)
                bird_acc_.x += 0.01;
        }
        if(bird_acc_.y > 0)
            bird_acc_.y -= 0.01;
        else
        {
            if(bird_acc_.y < 0)
                bird_acc_.y += 0.01;
        }
		cout<<bird_acc_.x<<" "<<bird_acc_.y<<endl;
		shadow_.setPosition(shadow_pos_.x, 0, shadow_pos_.z);

		bird_pos_.x = ofClamp(bird_pos_.x, -5, 5);
		bird_pos_.y = ofClamp(bird_pos_.y,  0, 7);

		bird_pos_+=bird_acc_;
		bird_.setPosition(bird_pos_.x, bird_pos_.y, bird_pos_.z); 
        bird_.setRotation(0, 150+ bird_rotation_, 1, 0, 0); 
		sphere_.setRotation(1, -90+ tree_rotation_, 0, 1, 0);
        
        mvp_mat_ = main_camera_.getModelViewProjectionMatrix();
        bird_pos_ss_= bird_pos_ * mvp_mat_ ;
        ofPoint screen_pos;
        screen_pos.set(bird_pos_ss_.x * w_/2 + (x_/2 + w_/2), h_ - (bird_pos_ss_.y * h_/2 + (y_/2 + h_/2)));
        
        bird_pos_ss_.set(screen_pos.x, screen_pos.y);

		if(bird_acc_.x ==0 && bird_acc_.y ==0 && emitter_.particleLifespan < 12)
			emitter_.particleLifespan ++;
		else
		{
			if(emitter_.particleLifespan > 8)
				emitter_.particleLifespan--;
		}

/*		emitter_.sourcePosition.x = hand_pos_.x;
		emitter_.sourcePosition.y = hand_pos_.y;
		ofVec3f dir = ofVec3f(hand_pos_.x, hand_pos_.y, 0)- ofVec3f(pre_hand_pos_.x, pre_hand_pos_.y, 0);
		dir.normalize();
		dir.y = -dir.y;
		//dir.x = -dir.x;
		angle_ = dir.angle(ofVec3f(1,0,0));
		if(dir.y >=  0) angle_+=180;
		emitter_.angle = angle_;

		if(ofVec3f(hand_pos_.x, hand_pos_.y, 0).distance(bird_pos_ss_) < 50)
			bird_acc_+= dir/10;
 
 */
/*        
        cout<<mvp_mat_(0,0)<<"m "<<mvp_mat_(0, 1)<<" "<<mvp_mat_(0, 2)<<"\r";
        cout<<mvp_mat_(1,0)<<"m "<<mvp_mat_(1, 1)<<" "<<mvp_mat_(1, 2)<<"\r";
        cout<<mvp_mat_(2,0)<<"m "<<mvp_mat_(2, 1)<<" "<<mvp_mat_(2, 2)<<"\r";
        cout<<mvp_mat_(3,0)<<"m "<<mvp_mat_(3, 1)<<" "<<mvp_mat_(3, 2)<<"\r";
  
        cout<<screen_pos.x<<"n "<<screen_pos.y<<"\r";
        cout<<bird_pos_ss_.x<<" "<<bird_pos_ss_.y<<"\r";
        cout<<bird_pos_.x<<" "<<bird_pos_.y<<"\r";
*/

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
        
        ofDisableAlphaBlending();
        emitter_.draw( 0, 0 );
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
			//if(camera_orbit_para_.y > -90)
			//	camera_orbit_para_.y--;
                bird_rotation_+=3;
			break;
		case 'w':
			//                 pos.z--;
			//                 main_camera_.setPosition(pos);
			//                 main_camera_.lookAt(look_at_);
			//main_camera_.dolly(-1);
			//if(camera_orbit_para_.y < 90)
			//	camera_orbit_para_.y++;
                bird_rotation_-=3;
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
        emitter_.sourcePosition.x = x;
        emitter_.sourcePosition.y = y;
        
        ofVec3f dir = ofVec3f(x, y, 0)- ofVec3f(ofGetPreviousMouseX(), ofGetPreviousMouseY(), 0);
        dir.normalize();
        dir.y = -dir.y;
		//dir.x = -dir.x;
        angle_ = dir.angle(ofVec3f(1,0,0));
        if(dir.y >=  0) angle_+=180;
        emitter_.angle = angle_;
        
        if(ofVec3f(x, y, 0).distance(bird_pos_ss_) < 50)
            bird_acc_+= dir/10;
	}

	void GamingScene4::windowResized( int w, int h )
	{
        w_ = w;
        h_ = h;
	}

	void GamingScene4::inPose( ofxUser & user )
	{
		cout<<ofGetElapsedTimef()<<"Pose---"<<user.pose<<endl;
		if(user.pose == "LeftWindStart")
		{
			left_wind_start_ = true;
		}

		if(user.pose == "RightWindStart")
		{
			right_wind_start_ = true;
		}
	}

	void GamingScene4::inGesture( ofxUser & user )
	{
		cout<<ofGetElapsedTimef()<<"Gesture---"<<user.gesture<<endl;
		if(gesture_timer_ < 1)return;
		if(user.gesture == "LeftWind" && left_wind_start_)
		{
			rw_enabled_ = true;
			bird_rot_.z-=60;

			gesture_timer_ = 0;
			left_wind_start_ = false;
		}
        
        if(user.gesture == "RightWind" && right_wind_start_)
        {
            rw_enabled_ = true;
			bird_rot_.z+=60;

			gesture_timer_ = 0;
			right_wind_start_ = false;
        }
        
        if(user.gesture == "UpWind")
        {
            
            ofVec3f vo_pos = virtual_looking_obj_.getGlobalPosition();
            vo_pos.y--;
			virtual_looking_obj_.setGlobalPosition(vo_pos);

			gesture_timer_ = 0;
        }
         if(user.gesture == "DownWind")
         {
             
             ofVec3f vo_pos = virtual_looking_obj_.getGlobalPosition();
             vo_pos.y++;
             virtual_looking_obj_.setGlobalPosition(vo_pos);

			 gesture_timer_ = 0;
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
