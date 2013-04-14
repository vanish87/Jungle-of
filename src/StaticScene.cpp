#include "StaticScene.h"
#include "JungleApp.h"

namespace Jungle
{
	StaticScene::StaticScene(void)
	{
	}


	StaticScene::~StaticScene(void)
	{
	}

	void StaticScene::Steup()
	{
		w_ = ofGetWindowWidth();
		h_ = ofGetWindowHeight();
		x_ = ofGetWindowPositionX();
		y_ = ofGetWindowPositionY();
		
		tree_.loadModel("jungle_9.obj");
		//0,-46, 0
		tree_.setPosition(0,-46,0);
		tree_.setScale(1,1,1);
		tree_.setRotation(0, 180, 0, 0, 1);
		tree_.Enable(true);
		tree_.AddToScene();

	}

	void StaticScene::Update()
	{
		JungleApp::SceneManagerInstance().Update();
	}

	void StaticScene::Draw()
	{
        ofEnableAlphaBlending();
		ofSetColor(255, 255, 255);		
		//glEnable(GL_DEPTH_TEST);

		ofPushMatrix();				
		JungleApp::SceneManagerInstance().Draw();
		ofPopMatrix();

		//glDisable(GL_DEPTH_TEST);

		ofSetColor(255, 255, 255);	
		if(Jungle::KINECT_ENABLE)
		{
			glPushMatrix();
			ofTranslate(0, h_ - 0.3*h_);
			ofScale(0.4, 0.4);
			JungleApp::KinectInstance().debugDraw();
			glPopMatrix();
		}  
               
	}

	void StaticScene::keyPressed( int key )
	{        
        ofVec3f pos = tree_.getPosition();
		ofVec3f scale = tree_.getScale();
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
			scale+=0.1;
			tree_.setScale(scale.x, scale.y,scale.z);
			break;
		case 'c':
			scale-=0.1;
			tree_.setScale(scale.x, scale.y,scale.z);
			break;
		case 'y':
			break;
		case 'h':
			break;
		case 'g':
			break;
		case 'j':
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

		tree_.setPosition(pos.x, pos.y, pos.z);
	}

	void StaticScene::mouseMoved( int x, int y )
	{           
	}

	void StaticScene::windowResized( int w, int h )
	{
        w_ = w;
        h_ = h;
	}

	void StaticScene::inPose( ofxUser & user )
	{
		cout<<ofGetElapsedTimef()<<"Pose---"<<user.pose<<endl;
		
	}

	void StaticScene::inGesture( ofxUser & user )
	{
		cout<<ofGetElapsedTimef()<<"Gesture---"<<user.gesture<<endl;		
	}

	void StaticScene::userIn( ofxUser & user )
	{
	}

	void StaticScene::userMove( ofxUser & user )
	{
	}

	void StaticScene::userOut( ofxUser & user )
	{
	}

}
