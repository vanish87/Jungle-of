#include "GamingScene5.h"
#include "JungleApp.h"

namespace Jungle
{
    static int NUM_PARTICLE = 250;
    static const int MAX_PARTICLE = 300;
    static const int MIN_PARTICLE = 200;
	GamingScene5::GamingScene5(void)
	{
	}


	GamingScene5::~GamingScene5(void)
	{
	}

	void GamingScene5::Steup()
	{
		w_ = ofGetWindowWidth();
		h_ = ofGetWindowHeight();
		x_ = ofGetWindowPositionX();
		y_ = ofGetWindowPositionY();
		stage_.loadModel("Tree_Stage_Smooth.dae");
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


		bird_.loadModel("Yellow_Butterfly_1.dae");
		bird_pos_ = ofVec3f(2,3.5,5);
		bird_.setPosition(bird_pos_.x,bird_pos_.y,bird_pos_.z);
		bird_.setRotation(0, 150, 1, 0, 0); 
		bird_.setScale(0.03,0.03,0.03);
		bird_rot_.set(0, 0, 0);
		animation_time_= 0;

		sphere_pos_.set(bird_pos_.x + 2, bird_pos_.y, bird_pos_.z);
		sphere_radius_ = 70;
		in_sphere_ = false;
		need_move_= false;

		light_.setAmbientColor(ofFloatColor(0.2,0.2,0.2));
        light_.setDiffuseColor(ofFloatColor(0.3,0.3,0.3));
        light_.setSpecularColor(ofFloatColor(0.3,0.3,0.3));
        light_.setPosition(0, 100, 0);
        ofSetSmoothLighting(true);
        light_.enable();
        
		camera_pos_ = ofVec3f(2, 3.5, 12);
		main_camera_.setPosition(camera_pos_);
		main_camera_.lookAt(bird_pos_);
        
        for (int i = 0; i < NUM_PARTICLE; ++i)
        {
            WindParticle particle;
            wind_.push_back(particle);
        }
        


		ofBackground(0);
		ofSetFrameRate(60);
		ofSetVerticalSync(true);
		ofEnableBlendMode(OF_BLENDMODE_ALPHA);

		ofViewport(x_, y_, w_, h_, false);
	}

	void GamingScene5::Update()
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


				ofVec3f hand_pos = bone.right_hand;
				pre_hand_pos_ = hand_pos_;
				hand_pos_.x = ofMap(hand_pos.x , 0, 640, 0, w_, true);
				hand_pos_.y = ofMap(hand_pos.y , 0, 480, 0, h_, true);
				//cout<<shadow_pos_.x<<" "<<shadow_pos_.y<<" "<<shadow_pos_.z<<"\r";
				
			}
		}			
		
		animation_time_ += ofGetLastFrameTime()/24.0f;
		if( animation_time_ > 14.0f/360.0f ){
			animation_time_ = 0;
		}
		bird_.setAnimation(0);        
		bird_.setNormalizedTime(animation_time_);
		
		ofMatrix4x4 mvp_mat_ = main_camera_.getModelViewProjectionMatrix();
		bird_pos_ss_= bird_pos_ * mvp_mat_ ;
		ofPoint screen_pos;
		screen_pos.set(bird_pos_ss_.x * w_/2 + (x_/2 + w_/2), h_ - (bird_pos_ss_.y * h_/2 + (y_/2 + h_/2)));

		bird_pos_ss_.set(screen_pos.x, screen_pos.y);
		if(hand_pos_.distance(bird_pos_ss_) < sphere_radius_ && !in_sphere_)
		{
			ofVec3f dir = ofVec3f(hand_pos_.x, hand_pos_.y, 0)- ofVec3f(ofGetPreviousMouseX(), ofGetPreviousMouseY(), 0);
			dir.normalize();
			dir.y = -dir.y;
			bird_acc_+= dir/3;
			in_sphere_ = true;
		}
		if(in_sphere_ && hand_pos_.distance(bird_pos_ss_) > sphere_radius_)
		{
			in_sphere_ =!in_sphere_;
		}

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
		//cout<<bird_acc_.x<<" "<<bird_acc_.y<<endl;



		bird_pos_+=bird_acc_/5;
		bird_pos_.x = ofClamp(bird_pos_.x, -5, 5);
		bird_pos_.y = ofClamp(bird_pos_.y,  0, 7);
		bird_.setPosition(bird_pos_.x, bird_pos_.y, bird_pos_.z); 

		ofVec3f delta = bird_pos_ - camera_pos_;
		//cout<<delta.x<<" "<<delta.y<<" "<<delta.z<<endl;
		main_camera_.lookAt(bird_pos_);

		if(abs(delta.x) > 2 || abs(delta.y) > 2)
		{
			need_move_ = true;
		}
		else
		{
			if(delta.x == 0 && delta.y == 0)
				need_move_ = false;
		}

		if(need_move_)
		{
			camera_pos_.x += delta.x/10;
			camera_pos_.y += delta.y/10;
			main_camera_.setPosition(camera_pos_);
		}
        
        ofVec3f hand_delta =  hand_pos_- pre_hand_pos_;
        
        //cout<<delta.x<<" "<<delta.y<<" "<<delta.z<<endl;
        if(hand_delta.x == 0 && hand_delta.y == 0 && NUM_PARTICLE < MAX_PARTICLE)
        {
            NUM_PARTICLE++;
            WindParticle particle(hand_pos_);
            wind_.push_back(particle);
        }
        else
        {
            if(NUM_PARTICLE > MIN_PARTICLE && ofRandomf()*10 > 3)
            {
                NUM_PARTICLE --;
                wind_.pop_back();
            }
        }
        
        for(int i = 0; i < NUM_PARTICLE; ++i)
            wind_[i].SetOrg(hand_pos_);
        

        pre_hand_pos_ = hand_pos_;

	}

	void GamingScene5::Draw()
	{
		ofEnableBlendMode(OF_BLENDMODE_ALPHA);
		ofSetColor(255, 255, 255);		
		main_camera_.begin();
		glPushMatrix();
		glEnable(GL_DEPTH_TEST);
		
		background_.drawFaces();

		ofPushMatrix();
		stage_.drawFaces();
		ofPopMatrix();

		ofSetColor(255, 255, 255);	
		bird_.drawFaces();
		ofPushMatrix();
		ofTranslate(sphere_pos_.x, sphere_pos_.y, sphere_pos_.z);
		ofSphere(sphere_radius_);
		glPopMatrix();
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
        for(int i = 0; i < NUM_PARTICLE; ++i)
        {
            //		ofSetColor(2.55*i,2.55*i,2.55*i,1);
            wind_[i].Simulate(0);
        }
        // 	ofTranslate(sphere_pos_.x, sphere_pos_.y, sphere_pos_.z);
        // 	ofSphere(20);
        ofPopMatrix();
        
        ofSetColor(0,0,0,255);
        ofDrawBitmapString("particle num "+ ofToString(NUM_PARTICLE), 20, 80);
               
	}

	void GamingScene5::keyPressed( int key )
	{
		ofVec3f pos = main_camera_.getPosition();
		switch (key)
		{
		case 's':
			//                 pos.z++;
			//                 main_camera_.setPosition(pos);                
			//                 main_camera_.lookAt(look_at_);
			//main_camera_.dolly(1);
			//if(camera_orbit_para_.y > -90)
			//	camera_orbit_para_.y--;
			break;
		case 'w':
			//                 pos.z--;
			//                 main_camera_.setPosition(pos);
			//                 main_camera_.lookAt(look_at_);
			//main_camera_.dolly(-1);
			//if(camera_orbit_para_.y < 90)
			//	camera_orbit_para_.y++;
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
			//shadow_pos_ . z--;
			//shadow_.setPosition(shadow_pos_.x, shadow_pos_.y, shadow_pos_.z);

			break;
		case 'h':

			//shadow_pos_ . z++;
			//shadow_.setPosition(shadow_pos_.x, shadow_pos_.y, shadow_pos_.z);
			//vo_pos.y--;
			//virtual_looking_obj_.setGlobalPosition(vo_pos);
			break;
		case 'g':

			//shadow_pos_ . x--;
			//shadow_.setPosition(shadow_pos_.x, shadow_pos_.y, shadow_pos_.z);
			break;
		case 'j':

			//shadow_pos_ . x++;
			//shadow_.setPosition(shadow_pos_.x, shadow_pos_.y, shadow_pos_.z);
			break;
		case 'v':     
			//bird_pos_.y+=bird_speed_;
			//rw_enabled_ = true;
			//bird_rot_.z-=60;
			break;
		case 'c':     
			//bird_pos_.y+=bird_speed_;
			//rw_enabled_ = true;
			//bird_rot_.z+=60;
			break;
		case 'o':     
			//tree_rotation_++;
			break;
		case 'p':     
			//tree_rotation_--;
			break;
		case 'm':     
			break;
		case 'n':     
			break;
		case 't':     
			bird_.SetTexture("Textures/B2BigWingDiffuse.png");
			break;
		case 'r':     
			bird_.SetTexture("Textures/Abstract_Wings.png");
			break;

		default:
			break;
		}
	}

	void GamingScene5::mouseMoved( int x, int y )
	{           
		ofVec3f delta(x-ofGetPreviousMouseX(), y-ofGetPreviousMouseY(),0);
		if(delta.x > 0)
			sphere_pos_.x +=0.1;
		else
		{
			if (delta.x<0)
			{
				sphere_pos_.x -=0.1;
			}
		}
		if(delta.y > 0)
			sphere_pos_.y -=0.1;
		else
		{
			if (delta.y<0)
			{
				sphere_pos_.y +=0.1;
			}
		}
		sphere_pos_.x = ofClamp(sphere_pos_.x, -5, 5);
		sphere_pos_.y = ofClamp(sphere_pos_.y,  0, 7);

		hand_pos_.set(x, y, 0);
//         if(ofVec3f(x, y, 0).distance(bird_pos_ss_) < 70)
// 		{
//             bird_acc_+= dir/10;
// 
// 			cout<<bird_pos_ss_.x<<" "<<bird_pos_ss_.y<<endl;
// 			cout<<" "<<x<<" "<<y<<endl;
// 		}
	}

	void GamingScene5::windowResized( int w, int h )
	{
        w_ = w;
        h_ = h;
	}

	void GamingScene5::inPose( ofxUser & user )
	{
		cout<<ofGetElapsedTimef()<<"Pose---"<<user.pose<<endl;
		
	}

	void GamingScene5::inGesture( ofxUser & user )
	{
		cout<<ofGetElapsedTimef()<<"Gesture---"<<user.gesture<<endl;		
	}

	void GamingScene5::userIn( ofxUser & user )
	{
	}

	void GamingScene5::userMove( ofxUser & user )
	{
	}

	void GamingScene5::userOut( ofxUser & user )
	{
	}

}