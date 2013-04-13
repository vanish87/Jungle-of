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
		stage_.loadModel("jungle_9.obj");
        stage_pos_.set(2,-42,9);
		stage_.setPosition(stage_pos_.x,stage_pos_.y,stage_pos_.z);
        //16,-42,-1
        //0.12
		stage_.setScale(0.04,0.04,0.04);
		stage_.setRotation(0, 180, 0, 0, 1);
        
        ground_.loadModel("plane_2.obj");
        ground_.setScale(0.04,0.04,0.04);
        //ground_.setPosition(stage_pos_.x,stage_pos_.y,stage_pos_.z);
        
        
		background_.loadModel("background.dae");
		background_.setPosition(18, -70, -10);        
		background_.setScale(1 , 0.3 ,0.5);
		background_.setRotation(0, 180, 0, 0, 1);
		background_.setRotation(1, -90, 0, 1, 0);
		background_.disableMaterials();
		background_.disableNormals();


		bird_.loadModel("Yellow_Butterfly_1.dae");
		bird_pos_ = ofVec3f(2,3.5, 10);
        target_pos_.set(1, 9, 10);
        move_to_next_lev_ = false;
		bird_.setPosition(bird_pos_.x,bird_pos_.y,bird_pos_.z);
		bird_.setRotation(0, 150, 1, 0, 0); 
		bird_.setScale(0.005,0.005,0.005);
		bird_rot_.set(0, 0, 0);
		animation_time_= 0;
        
        mr_.loadModel("shroom_7.dae");
        mr_.setScale(0.01, 0.01, 0.01);
        mr_.setRotation(0, 180, 0, 0, 1);
        //mr_.setPosition(2, 13.5, 0);

		sphere_pos_.set(bird_pos_.x + 2, bird_pos_.y, bird_pos_.z);
		sphere_radius_ = 100;
		in_sphere_ = false;
		need_move_= false;
        
        two_hands_ = true;
        
        for(int i = 0; i < 4; i++)
        {
            Flower flower;
            flower.loadModel("pre-Geranium.obj");
			flower.setRotation(0,90,1,0,0);
            flower.setScale(0.0005, 0.0005, 0.0005);
            flower.setPosition( i, 4 , 10);
            flowers_.push_back(flower);            
        }
        
        //-32,-47,25
        light_.setDirectional();
        light_.setOrientation(ofVec3f(-32,-47,25));
        
        
		light_.setAmbientColor(ofFloatColor(0.5,0.5,0.5));
        //light_.setDiffuseColor(ofFloatColor(0.3,0.3,0.3));
        //light_.setSpecularColor(ofFloatColor(0.3,0.3,0.3));
        //light_.setPosition(0, 100, 0);
        ofSetSmoothLighting(true);
        light_.enable();
        
		camera_pos_ = ofVec3f(2, 3.5, 12);
        main_camera_.setFarClip(10000);
        main_camera_.setNearClip(1);
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
		
		animation_time_ += ofGetLastFrameTime()/24.0f;
		if( animation_time_ > 1.0f ){
			animation_time_ = 0;
		}
		bird_.setAnimation(0);        
		bird_.setNormalizedTime(animation_time_);
        
        mr_.setAnimation(0);        
		mr_.setNormalizedTime(animation_time_);
		
		ofMatrix4x4 mvp_mat_ = main_camera_.getModelViewProjectionMatrix();
		bird_pos_ss_= bird_pos_ * mvp_mat_ ;
		ofPoint screen_pos;
		screen_pos.set(bird_pos_ss_.x * w_/2 + (x_/2 + w_/2), h_ - (bird_pos_ss_.y * h_/2 + (y_/2 + h_/2)));

		bird_pos_ss_.set(screen_pos.x, screen_pos.y);
        
        
		if(hand_pos_.distance(bird_pos_ss_) < sphere_radius_ && !in_sphere_)
		{
			ofVec3f dir = hand_pos_-pre_hand_pos_;
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
		//bird_pos_.x = ofClamp(bird_pos_.x, -5, 5);
		//bird_pos_.y = ofClamp(bird_pos_.y,  0, 7);
        for(int i =0; i < 4; i++)
        {
            if (!flowers_[i].flower_collided_) 
            {
                move_to_next_lev_ = false;
                break;
            }
            move_to_next_lev_ = true;
        }
        
        if(move_to_next_lev_)
        {
            ofVec3f delta = target_pos_ - bird_pos_;
            if(abs(delta.x) < 0.01 && abs(delta.x) < 0.01);
               // move_to_next_lev_ = false;
            else
                bird_pos_+= delta/70;
            
        }
        if(!move_to_next_lev_)
        {
            bird_pos_.x = ofClamp(bird_pos_.x, -5, 5);
            bird_pos_.y = ofClamp(bird_pos_.y,  2.7, 5);
        }
		bird_.setPosition(bird_pos_.x, bird_pos_.y, bird_pos_.z); 
        
        for(int i =0; i < 4; i++)
        {
            if(flowers_[i].getPosition().distance(bird_pos_) < 0.3)
            {
                flowers_[i].color_.set(255, 0, 0);
                flowers_[i].flower_collided_ = true;
            }
        }

		ofVec3f delta = bird_pos_ - camera_pos_;
		//cout<<delta.x<<" "<<delta.y<<" "<<delta.z<<endl;
		main_camera_.lookAt(bird_pos_);

		if(abs(delta.x) > 1.4 || abs(delta.y) > 1.4)
		{
			need_move_ = true;
		}
		else
		{
			if(abs(delta.x) < 0.01 && abs(delta.x) < 0.01)
				need_move_ = false;
		}
        need_move_=true;
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
        ofEnableAlphaBlending();
		ofSetColor(255, 255, 255);		
		main_camera_.begin();
		glPushMatrix();
		glEnable(GL_DEPTH_TEST);
		
		background_.drawFaces();

		ofPushMatrix();
		stage_.drawFaces();
        //ground_.drawFaces();
		ofPopMatrix();

		ofSetColor(255, 255, 255);	
		bird_.drawFaces();
        mr_.drawFaces();
        for(int i = 0; i < 4; i++)
        {
            //if(flowers_[i].flower_collided_ )
                flowers_[i].Draw();            
        }
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
        
        ofSetColor(255,255,255,255);
        ofDrawBitmapString("particle num "+ ofToString(NUM_PARTICLE), 20, 20);
        ofDrawBitmapString("birds pos "+ ofToString(bird_pos_.x) + " "+ ofToString(bird_pos_.y) + " "+ ofToString(bird_pos_.z), 20, 40);
        //ofDrawBitmapString("particle num "+ ofToString(NUM_PARTICLE), 20, 80);
        //ofDrawBitmapString("particle num "+ ofToString(NUM_PARTICLE), 20, 80);
               
	}

	void GamingScene5::keyPressed( int key )
	{
		ofVec3f pos = main_camera_.getPosition();
        
        ofVec3f scale = stage_.getScale();
		switch (key)
		{
		case 's':
			//                 pos.z++;
			//                 main_camera_.setPosition(pos);                
			//                 main_camera_.lookAt(look_at_);
			//main_camera_.dolly(1);
			//if(camera_orbit_para_.y > -90)
			//	camera_orbit_para_.y--;
                stage_pos_.z++;
            stage_.setPosition(stage_pos_.x,stage_pos_.y,stage_pos_.z);  
			break;
		case 'w':
			//                 pos.z--;
			//                 main_camera_.setPosition(pos);
			//                 main_camera_.lookAt(look_at_);
			//main_camera_.dolly(-1);
			//if(camera_orbit_para_.y < 90)
			//	camera_orbit_para_.y++;
                stage_pos_.z--;    
            stage_.setPosition(stage_pos_.x,stage_pos_.y,stage_pos_.z);  
			break;	
		case 'q':
			//pos.y++;
			//look_at_.y++;
			//main_camera_.setPosition(pos);                
			//main_camera_.lookAt(look_at_);
            scale+=0.01;
            stage_.setScale(scale.x, scale.y, scale.z);
			break;
		case 'z':
			//pos.y--;
			//look_at_.y--;
			//main_camera_.setPosition(pos);
			//main_camera_.lookAt(look_at_);
                
                scale-=0.01;
                stage_.setScale(scale.x, scale.y, scale.z);
			break;
		case 'a':
			//                 pos.x--;
			//                 main_camera_.setPosition(pos);                
			//                 main_camera_.lookAt(look_at_);
			//main_camera_.truck(-1);
			//camera_orbit_para_.x--;
			//bird_pos_.x++;
                stage_pos_.x++;
            stage_.setPosition(stage_pos_.x,stage_pos_.y,stage_pos_.z);  
			break;
		case 'd':
			//                 pos.x++;
			//                 main_camera_.setPosition(pos);
			//                 main_camera_.lookAt(look_at_);
			//main_camera_.truck(1);
			//camera_orbit_para_.x++;
			//bird_pos_.x--;
                stage_pos_.x--;
            stage_.setPosition(stage_pos_.x,stage_pos_.y,stage_pos_.z);  
			break;
		case 'e':
			//look_at_.y++;
			//main_camera_.setPosition(pos);                
			//main_camera_.lookAt(look_at_);
                stage_pos_.y++;
            stage_.setPosition(stage_pos_.x,stage_pos_.y,stage_pos_.z);  
			break;
		case 'c':
			// look_at_.y--;
			//main_camera_.setPosition(pos);
			//main_camera_.lookAt(look_at_);
                stage_pos_.y--;
            stage_.setPosition(stage_pos_.x,stage_pos_.y,stage_pos_.z); 
			break;
		case 'y':
			//shadow_pos_ . z--;
			//shadow_.setPosition(shadow_pos_.x, shadow_pos_.y, shadow_pos_.z);

			break;
		case 'h':

			//shadow_pos_ . z++;
			//shadow_.setPosition(shadow_pos_.x, shadow_pos_.y, shadow_pos_.z);
			//vo_pos.y--;
			//virtual_looking_obj_.setGlobalPosition(vo_pos);
                two_hands_ = !two_hands_;
			break;
		case 'g':

			//shadow_pos_ . x--;
			//shadow_.setPosition(shadow_pos_.x, shadow_pos_.y, shadow_pos_.z);
			break;
		case 'j':

			//shadow_pos_ . x++;
			//shadow_.setPosition(shadow_pos_.x, shadow_pos_.y, shadow_pos_.z);
                break;
        case 'f':     
                //bird_pos_.y+=bird_speed_;
                //rw_enabled_ = true;
                //bird_rot_.z-=60;
                bird_pos_.z--;
                break;		
        case 'v':     
                //bird_pos_.y+=bird_speed_;
                //rw_enabled_ = true;
                //bird_rot_.z-=60;
                bird_pos_.z++;
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
