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
		stage_.loadModel("stage_1.dae");
		//stage_.setPosition(0, 0, 0);

		stage_.setRotation(1, 180, 1, 0, 0);
		stage_.setScale(0.1,0.1,0.1);

		shadow_.loadModel("shadow.dae");
		shadow_.setPosition(0,1,0);
		shadow_.setScale(0.01,0.0001,0.01);
		
		bird_enable_ = true;
		if(bird_enable_)
		{
			bird_.loadModel("smooth_birdy.dae");
			bird_.setPosition(0,1,0);
			bird_.setScale(0.01,0.01,0.01);
		}

		light_.setPosition(0, 50, 0);
		light_.enable();

		main_camera_.setPosition(ofVec3f(0, 10, 50));
		main_camera_.lookAt(ofVec3f(0,0,0));

		ofBackground(0);
		ofSetFrameRate(60);
		ofSetVerticalSync(true);

		ofViewport(x_, y_, w_, h_, false);
	}

	void GamingScene2::Update()
	{
		ofxUser* user = JungleApp::KinectInstance().users;
		for(int i =0; i< 8; ++i)
		{
			if(user[i].isActive)
			{
				Bones bone = user[i].bonesPoints;
				ofVec3f torsor_pos = bone.torso;
				torsor_pos.x = ofMap(torsor_pos.x , 0, 640, -50, 50, true);
				torsor_pos.z = ofMap(torsor_pos.z , 1000, 6000, 0, 100, true);
				shadow_pos_ = torsor_pos;
				//cout<<shadow_pos_.x<<" "<<shadow_pos_.y<<" "<<shadow_pos_.z<<"\r";
				shadow_.setPosition(shadow_pos_.x, 1, shadow_pos_.z);

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
			}
		}
	}

	void GamingScene2::Draw()
	{

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
			ofTranslate(0, h_ - 0.4*h_);
			ofScale(0.4, 0.4);
			JungleApp::KinectInstance().debugDraw();
			glPopMatrix();
		}
	}

	void GamingScene2::keyPressed( int key )
	{

		ofVec3f pos = main_camera_.getPosition();

		shadow_pos_= shadow_.getPosition();
		switch (key)
		{
		case 's':
			pos.z--;
			main_camera_.setPosition(pos);
			break;
		case 'w':
			pos.y++;
			main_camera_.setPosition(pos);
			main_camera_.lookAt(ofVec3f(0,0,0));
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
			tree_pos.y = 1;
			tree_pos.z = ofMap(torsor_pos.z , 1000, 6000, 0, 100, true);
			if(trees_.size() == 0)
			{
				ofxAssimpModelLoader new_tree;
				new_tree.loadModel("tree.dae");
				new_tree.setPosition(tree_pos.x ,tree_pos.y ,tree_pos.z);
				new_tree.setScale(0.01,0.01,0.01);
				trees_.push_back(new_tree);
				cout<<"ADD new tree"<<endl;
			}
			else
			{
				bool can_add = true;
				for(int i =0; i < trees_.size(); ++i)
				{
					if(ofDistSquared(tree_pos.x, tree_pos.z, trees_[i].getPosition().x, trees_[i].getPosition().z) < 25)
					{
						can_add = false;
					}
				}
				if(can_add)
				{
					ofxAssimpModelLoader new_tree;
					new_tree.loadModel("tree.dae");
					new_tree.setPosition(tree_pos.x ,tree_pos.y ,tree_pos.z);
					new_tree.setScale(0.01,0.01,0.01);
					trees_.push_back(new_tree);
					cout<<"ADD new tree"<<endl;
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
