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

		//no need background 
		//background is Gradient color now
		tree_.loadModel("Environment/Trees_Leaves_New_5.obj");
		tree_.setPosition(600 , -100, 0);
		tree_.setScale(2,2,2);
		tree_.setRotation(0, 180, 0, 0, 1);
		tree_.Enable(true);
        
 /*       bg_1_.loadModel("Environment/BG_1.obj");
		//0,-46, 0
		bg_1_.setPosition(300,300,0);
		bg_1_.setScale(2,2,2);
		bg_1_.setRotation(0, 180, 0, 0, 1);
        bg_1_.setRotation(1, 180, 0, 1, 0);
		bg_1_.Enable(true);
        
        bg_2_.loadModel("Environment/BG_2.obj");
		//0,-46, 0
		bg_2_.setPosition(0,-180,-240);
		bg_2_.setScale(1,0.5,0.5);
		bg_2_.setRotation(0, 180, 0, 0, 1);        
        bg_2_.setRotation(1, 180, 0, 1, 0);
		bg_2_.Enable(false);
        
        bg_3_.loadModel("Environment/BG_3.obj");
		//0,-46, 0
		bg_3_.setPosition(500,500,50);
		bg_3_.setScale(2,2,2);
		bg_3_.setRotation(0, 180, 0, 0, 1);        
        bg_3_.setRotation(1, 180, 0, 1, 0);
		bg_3_.Enable(true);
        
        ground_.loadModel("Environment/ground_new_1.obj");
		//0,-46, 0
		ground_.setPosition(90,-90, -100);
		ground_.setScale(1.5,1,1);
		ground_.setRotation(0, 180, 0, 0, 1);        
		ground_.setRotation(0, 5, 1, 0, 0);
		ground_.Enable(true);
        
        rocks_.loadModel("Environment/Rocks_new_1.obj");
		//0,-46, 0
		rocks_.setPosition(500,500,0);
		rocks_.setScale(1,1,1);
		rocks_.setRotation(0, 180, 0, 0, 1);
		rocks_.Enable(true);
        
        bush_.loadModel("Environment/Bushes_New_1.obj");
		//0,-46, 0
		bush_.setPosition(160,-110,-195);
		bush_.setScale(1,1,1);
		bush_.setRotation(0, 180, 0, 0, 1);
		bush_.Enable(true);
        */
        
        model_ = &tree_;
        
		//ground_.AddToScene();
        //rocks_.AddToScene();
		//bg_3_.AddToScene();
		//bg_2_.AddToScene();
		//bg_1_.AddToScene();
		tree_.AddToScene();
		//bush_.AddToScene();
        
		atmo.loadSound("Audio/jungle-atmos-2.mp3");
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
        //set background here
        ofBackground(14, 28, 54);
		//set background Gradient here
		ofBackgroundGradient(ofColor(105,119,120),ofColor(14,28,54), OF_GRADIENT_LINEAR);

		glEnable(GL_DEPTH_TEST);

		ofPushMatrix();				
		JungleApp::SceneManagerInstance().Draw();
		ofPopMatrix();

		glDisable(GL_DEPTH_TEST);


               
	}

	void StaticScene::keyPressed( int key )
	{        
       

		ofVec3f pos = model_->getPosition();
		ofVec3f scale = model_->getScale();
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
			model_->setScale(scale.x, scale.y,scale.z);
			break;
		case 'c':
			scale-=0.1;
			model_->setScale(scale.x, scale.y,scale.z);
			break;
		case 'y':
			break;
		case 'h':
			break;
		case 'g':
			break;
		case 'j':
			break;
        case '4':
            pos = ground_.getPosition();
            model_ = &bg_4_;
            break;
        case '5':   
			pos = ground_.getPosition();
			model_ = &ground_;
			break;		
        case '6':  
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
        case '7':
            pos = rocks_.getPosition();
            model_ = &rocks_;
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
