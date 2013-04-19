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
		
		tree_.loadModel("Enviro_Beta_3.obj");
		//0,-46, 0
		tree_.setPosition(0,-46,0);
		tree_.setScale(1,1,1);
		tree_.setRotation(0, 180, 0, 0, 1);
		tree_.Enable(true);
        
        bg_1_.loadModel("BG_1.obj");
		//0,-46, 0
		bg_1_.setPosition(0,-10,-70);
		bg_1_.setScale(1,1,1);
		bg_1_.setRotation(0, 180, 0, 0, 1);
        bg_1_.setRotation(1, 180, 0, 1, 0);
		bg_1_.Enable(true);
        
        bg_2_.loadModel("BG_2.obj");
		//0,-46, 0
		bg_2_.setPosition(0,-10,-135);
		bg_2_.setScale(1,1,1);
		bg_2_.setRotation(0, 180, 0, 0, 1);        
        bg_2_.setRotation(1, 180, 0, 1, 0);
		bg_2_.Enable(true);
        
        bg_3_.loadModel("BG_3.obj");
		//0,-46, 0
		bg_3_.setPosition(0,-15,-215);
		bg_3_.setScale(1,1,1);
		bg_3_.setRotation(0, 180, 0, 0, 1);        
        bg_3_.setRotation(1, 180, 0, 1, 0);
		bg_3_.Enable(true);
        
        ground_.loadModel("ground.obj");
		//0,-46, 0
		ground_.setPosition(0,18,0);
		ground_.setScale(1,1,1);
		ground_.setRotation(0, 180, 0, 0, 1);
		ground_.Enable(true);
        
        model_ = &tree_;
        
		ground_.AddToScene();
		bg_3_.AddToScene();
		bg_2_.AddToScene();
		bg_1_.AddToScene();
		tree_.AddToScene();
		
		atmo.loadSound("audio/jungle-atmos-2.mp3");
		atmo.setLoop(true);
        
		atmo.play();
        
        

	}

	void StaticScene::Update()
	{
		JungleApp::SceneManagerInstance().Update();
        
        
	}

	void StaticScene::Draw()
	{
		ofSetColor(255, 255, 255);		
		glEnable(GL_DEPTH_TEST);

		ofPushMatrix();				
		JungleApp::SceneManagerInstance().Draw();
		ofPopMatrix();

		glDisable(GL_DEPTH_TEST);


               
	}

	void StaticScene::keyPressed( int key )
	{        
       

		ofVec3f pos = model_->getPosition();
		ofVec3f scale = tree_.getScale();
		switch (key)
		{
		case 's':
			pos.z+=5;
			break;
		case 'w': 
			pos.z-=5;
			break;	
		case 'q':
			pos.y+=5;
			break;
		case 'z':
			pos.y-=5;
			break;
		case 'a':
			pos.x-=5;
			break;
		case 'd':
			pos.x+=5;
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
        case '5':   
			pos = ground_.getPosition();
			model_ = &ground_;
			break;		
        case '4':  
			pos = tree_.getPosition();
			model_ = &tree_;
			break;
		case '3':     
			pos = bg_3_.getPosition();
			model_ = &bg_3_;
			break;
		case '2':   
			pos = bg_2_.getPosition();
			model_ = &bg_2_;
			break;
		case '1':     
			pos = bg_1_.getPosition();
			model_ = &bg_1_;
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

		if(model_ !=0)
		{
			model_->setPosition(pos.x, pos.y, pos.z);
		}
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
