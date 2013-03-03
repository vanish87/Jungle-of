#include "GamingScene2.h"
#include "JungleApp.h"

namespace Jungle
{
	GamingScene2::GamingScene2(void)
	{
	}


	GamingScene2::~GamingScene2(void)
	{
	}

	void GamingScene2::Steup()
	{
		w_ = ofGetWindowWidth();
		h_ = ofGetWindowHeight();
		x_ = ofGetWindowPositionX();
		y_ = ofGetWindowPositionY();
		stage_.loadModel("stage_04.dae");
		stage_.setPosition(0, 0, 0);

		stage_.setRotation(2, 180, 0, 0, 1);
		stage_.setScale(0.1,0.1,0.1);

		shadow_.loadModel("shadow.dae");
		shadow_.setPosition(0,1,0);
		shadow_.setScale(0.01,0.0001,0.01);
		
		bird_enable_ = false;
		if(bird_enable_)
		{
			bird_.loadModel("smooth_birdy.dae");
			bird_.setPosition(0,1,0);
			bird_.setScale(0.01,0.01,0.01);
		}

		hand_.loadImage("hand.png");
		tree_button_1_.loadImage("button_interface_notpressed_02.png");
		tree_button_pos_1_ = ofPoint(w_*7/8, 0);
		button_1_time_= 0;

		tree_button_2_.loadImage("button_interface_notpressed_02.png");
		tree_button_pos_2_ = ofPoint(w_*7/8, h_ * 1/5);
		button_2_time_ = 0;

		loading_.loadImage("hourglass_placeholder_02.gif");
		loading_pos_ = ofPoint(-1,-1);


		light_.setPosition(0, 50, 50);
        //light_.setSpotlight();
        //light_.setSpotlightCutOff(30);
        
		light_.enable();
        //light_.

		main_camera_.setPosition(ofVec3f(0, 10, 50));
        look_at_ = ofVec3f(0,0,0);
		main_camera_.lookAt(look_at_);

		ofBackground(0);
		ofSetFrameRate(60);
		ofSetVerticalSync(true);
        glShadeModel(GL_SMOOTH);
        ofEnableBlendMode(OF_BLENDMODE_ALPHA);

		ofViewport(x_, y_, w_, h_, false);
	}

	void GamingScene2::Update()
	{
        //light_.setOrientation(shadow_pos_);
		ofxUser* user = JungleApp::KinectInstance().users;
		for(int i =0; i< MAX_USERS; ++i)
		{
			if(user[i].isActive&& user[i].bones)
			{
				Bones bone = user[i].bonesPoints;
				ofVec3f torsor_pos = bone.torso;
				torsor_pos.x = ofMap(torsor_pos.x , 0, 640, -50, 50, true);
				torsor_pos.z = ofMap(torsor_pos.z , 1000, 6000, 0, 100, true);
				shadow_pos_ = torsor_pos;
				//cout<<shadow_pos_.x<<" "<<shadow_pos_.y<<" "<<shadow_pos_.z<<"\r";
				shadow_.setPosition(shadow_pos_.x, 0, shadow_pos_.z);

				if(bird_enable_)
				{
					bird_.setPosition(shadow_pos_.x, 3, shadow_pos_.z);
					ofVec3f hand_pos = bone.right_hand;
					hand_pos.x = ofMap(hand_pos.x , 0, 640, -50, 50, true);
					hand_pos.y = ofMap(hand_pos.y , 0, 480, -50, 50, true);
					hand_pos.z = ofMap(hand_pos.z , 1000, 6000, 0, 100, true);

					ofVec3f elbow_pos = bone.right_elbow;
					elbow_pos.x = ofMap(elbow_pos.x , 0, 640, -50, 50, true);
					elbow_pos.y = ofMap(elbow_pos.y , 0, 480, -50, 50, true);
					elbow_pos.z = ofMap(elbow_pos.z , 1000, 6000, 0, 100, true);

					hand_pos = hand_pos - elbow_pos;
					const aiScene* scene= bird_.getAssimpScene();
					const aiAnimation* mAnim = scene->mAnimations[1];

					// calculate the transformations for each animation channel
					for( unsigned int a = 0; a < mAnim->mNumChannels; a++)
					{
						const aiNodeAnim* channel = mAnim->mChannels[a];

						aiNode* targetNode = scene->mRootNode->FindNode(channel->mNodeName);

						targetNode->mTransformation.a4 = -hand_pos.x;
						targetNode->mTransformation.b4 = hand_pos.y;
						targetNode->mTransformation.c4 = hand_pos.z;
					}

					bird_.updateAnimation(0);

					hand_pos = bone.left_hand;
					hand_pos.x = ofMap(hand_pos.x , 0, 640, -50, 50, true);
					hand_pos.y = ofMap(hand_pos.y , 0, 480, -50, 50, true);
					hand_pos.z = ofMap(hand_pos.z , 1000, 6000, 0, 100, true);

					elbow_pos = bone.left_elbow;
					elbow_pos.x = ofMap(elbow_pos.x , 0, 640, -50, 50, true);
					elbow_pos.y = ofMap(elbow_pos.y , 0, 480, -50, 50, true);
					elbow_pos.z = ofMap(elbow_pos.z , 1000, 6000, 0, 100, true);

					hand_pos = hand_pos - elbow_pos;

					mAnim = scene->mAnimations[0];

					// calculate the transformations for each animation channel
					for( unsigned int a = 0; a < mAnim->mNumChannels; a++)
					{
						const aiNodeAnim* channel = mAnim->mChannels[a];

						aiNode* targetNode = scene->mRootNode->FindNode(channel->mNodeName);

						targetNode->mTransformation.a4 = -hand_pos.x;
						targetNode->mTransformation.b4 = hand_pos.y;
						targetNode->mTransformation.c4 = hand_pos.z;
					}

					bird_.updateAnimation(1);
				}

				ofVec3f lh_pos = bone.right_hand;
				hand_pos_.x = ofMap(lh_pos.x , 160, 480, 0, 1280-80, true);
				hand_pos_.y = ofMap(lh_pos.y , 120, 360, 0, 720-80, true);

			}
		}

		ofRectangle hand_rec = ofRectangle(hand_pos_.x,hand_pos_.y, 80,80);
		ofRectangle button_1_rec = ofRectangle(tree_button_pos_1_.x,tree_button_pos_1_.y, 150,150);
		ofRectangle button_2_rec = ofRectangle(tree_button_pos_2_.x,tree_button_pos_2_.y, 150,150);

		if(hand_rec.intersects(button_1_rec))			
		{

			tree_button_2_.loadImage("button_interface_notpressed_02.png");
			button_1_time_ += ofGetLastFrameTime();
			loading_pos_ = tree_button_pos_1_;
			loading_pos_ += 30;
			if(button_1_time_ > 2.0f)
			{
				button_1_time_ = 0;
				loading_pos_.x= -1;
				tree_button_1_.loadImage("button_interface_pressed_01.png");
				cout<<"Inter with 1"<<endl;
			}
		}
		else
		{
			button_1_time_ = 0;
			loading_pos_.x= -1;
			tree_button_1_.loadImage("button_interface_notpressed_02.png");
			if(hand_rec.intersects(button_2_rec))
			{
				button_2_time_ += ofGetLastFrameTime();
				loading_pos_ = tree_button_pos_2_;
				loading_pos_ += 30;
				if(button_2_time_ > 2.0f)
				{
					button_2_time_ = 0;
					loading_pos_.x= -1;
					tree_button_2_.loadImage("button_interface_pressed_01.png");
					cout<<"Inter with 2"<<endl;
				}
			}
			else
			{
				button_2_time_ = 0;
				loading_pos_.x= -1;
				tree_button_2_.loadImage("button_interface_notpressed_02.png");
			}
		}
	}

	void GamingScene2::Draw()
	{
		ofEnableBlendMode(OF_BLENDMODE_ALPHA);
        ofSetColor(255, 255, 255);
		main_camera_.begin();
		glPushMatrix();
		glEnable(GL_DEPTH_TEST);
		stage_.drawFaces();
		shadow_.drawFaces();
		for(int i =0; i < trees_.size(); ++i)
			trees_[i].drawFaces();
		if(bird_enable_)
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

		//draw GUI
		tree_button_1_.draw(tree_button_pos_1_.x, tree_button_pos_1_.y, 0, 150, 150);
		tree_button_2_.draw(tree_button_pos_2_.x, tree_button_pos_2_.y, 0, 150, 150);
		
		hand_.draw(hand_pos_.x,hand_pos_.y, 0 ,80,80);
		if(loading_pos_.x >=0)
		{
			loading_.draw(loading_pos_.x, loading_pos_.y, 50, 50);
		}
	}

	void GamingScene2::keyPressed( int key )
	{

		ofVec3f pos = main_camera_.getPosition();

		shadow_pos_= shadow_.getPosition();
		switch (key)
		{
            case 's':
                pos.z++;
                main_camera_.setPosition(pos);                
                main_camera_.lookAt(look_at_);
                break;
            case 'w':
                pos.z--;
                main_camera_.setPosition(pos);
                main_camera_.lookAt(look_at_);
                break;	
            case 'q':
                pos.y++;
                main_camera_.setPosition(pos);                
                main_camera_.lookAt(look_at_);
                break;
            case 'z':
                pos.y--;
                main_camera_.setPosition(pos);
                main_camera_.lookAt(look_at_);
                break;
            case 'a':
                pos.x--;
                main_camera_.setPosition(pos);                
                main_camera_.lookAt(look_at_);
                break;
            case 'd':
                pos.x++;
                main_camera_.setPosition(pos);
                main_camera_.lookAt(look_at_);
                break;
            case 'e':
                look_at_.y++;
                main_camera_.setPosition(pos);                
                main_camera_.lookAt(look_at_);
                break;
            case 'c':
                look_at_.y--;
                main_camera_.setPosition(pos);
                main_camera_.lookAt(look_at_);
                break;
		case 'y':
			shadow_pos_ . z--;
			shadow_.setPosition(shadow_pos_.x, shadow_pos_.y, shadow_pos_.z);
			break;
		case 'h':

			shadow_pos_ . z++;
			shadow_.setPosition(shadow_pos_.x, shadow_pos_.y, shadow_pos_.z);
			break;
		case 'g':

			shadow_pos_ . x--;
			shadow_.setPosition(shadow_pos_.x, shadow_pos_.y, shadow_pos_.z);
			break;
		case 'j':

			shadow_pos_ . x++;
			shadow_.setPosition(shadow_pos_.x, shadow_pos_.y, shadow_pos_.z);
			break;
		default:
			break;
		}
	}

	void GamingScene2::keyReleased( int key )
	{
	}

	void GamingScene2::inPose( ofxUser & user )
	{
		cout << "INPOSE : " ;
		cout<<user.pose<<endl;
		if(user.pose == "TREE")
		{
			Bones bone = user.bonesPoints;
			ofVec3f torsor_pos = bone.torso;
			ofVec3f tree_pos;
			tree_pos.x = ofMap(torsor_pos.x , 0, 640, -50, 50, true);
			tree_pos.y = -3;
			tree_pos.z = ofMap(torsor_pos.z , 1000, 6000, 0, 100, true);
			if(trees_.size() == 0)
			{
				ofxAssimpModelLoader new_tree;
				new_tree.loadModel("Abstratc_tree.dae");
				new_tree.setPosition(tree_pos.x ,tree_pos.y ,tree_pos.z);
                new_tree.setRotation(1, 90, 0, 1, 0);
                new_tree.setRotation(2, 180, 0, 0, 1);
				new_tree.setScale(0.01,0.01,0.01);
				trees_.push_back(new_tree);
				
                //cout<<"ADD new tree"<<tree_pos.x<<" "<<tree_pos.y <<" "<<tree_pos.z<<endl;
			}
			else
			{
				bool can_add = true;
				for(int i =0; i < trees_.size(); ++i)
				{
					if(ofDistSquared(tree_pos.x, tree_pos.z, trees_[i].getPosition().x, trees_[i].getPosition().z) < 16)
					{
						can_add = false;
					}
				}
				if(can_add && user.velF < 10.0f)
				{
					ofxAssimpModelLoader new_tree;
					new_tree.loadModel("Abstratc_tree.dae");
					new_tree.setPosition(tree_pos.x ,tree_pos.y ,tree_pos.z);
                    
                    new_tree.setRotation(1, 90, 0, 1, 0);
                    new_tree.setRotation(2, 180, 0, 0, 1);                    
                    new_tree.setScale(0.01,0.01,0.01);
					trees_.push_back(new_tree);
					//cout<<"ADD new tree"<<tree_pos.x<<" "<<tree_pos.y <<" "<<tree_pos.z<<endl;
				}

			}
		}
	}

	void GamingScene2::inGesture( ofxUser & user )
	{
	}

	void GamingScene2::userIn( ofxUser & user )
	{
	}

	void GamingScene2::userMove( ofxUser & user )
	{
	}

	void GamingScene2::userOut( ofxUser & user )
	{
	}

}
