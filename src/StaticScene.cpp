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
		tree_.loadModel("Environment/Tree_Last.obj");
		tree_.setPosition(690 , -200, 0);
		tree_.setScale(2,2,2);
		tree_.setRotation(0, 180, 0, 0, 1);
		tree_.Enable(true);
        
        ///
        
        tree1_.loadModel("Environment/Tree_1.obj");
		tree1_.setPosition(155 , -200, -30);
		tree1_.setScale(1,1,1);
		tree1_.setRotation(0, 180, 0, 0, 1);
		tree1_.Enable(true);
        
        tree2_.loadModel("Environment/Tree_2.obj");
		tree2_.setPosition(450 , -200, -30);
		tree2_.setScale(1,1.24,1);
		tree2_.setRotation(0, 180, 0, 0, 1);
		tree2_.Enable(true);
        
        tree3_.loadModel("Environment/Tree_3.obj");
		tree3_.setPosition(691 , -170, -30);
		tree3_.setScale(1,1.1,1);
		tree3_.setRotation(0, 180, 0, 0, 1);
		tree3_.Enable(true);
        
        tree4_.loadModel("Environment/Tree_4.obj");
		tree4_.setPosition(941 , -200, -30);
		tree4_.setScale(1,1.24,1);
		tree4_.setRotation(0, 180, 0, 0, 1);
		tree4_.Enable(true);
        
        tree5_.loadModel("Environment/Tree_5.obj");
		tree5_.setPosition(1116 , -190, -30);
		tree5_.setScale(0.87,0.87,0.87);
		tree5_.setRotation(0, 180, 0, 0, 1);
		tree5_.Enable(true);
    
        ////
        
        bg_1_.loadModel("Environment/mountain2.obj");
		bg_1_.setPosition(600,-115,-270);
		bg_1_.setScale(2,2,2);
		bg_1_.setRotation(0, 180, 0, 0, 1);
        bg_1_.setRotation(1, 180, 0, 1, 0);
		bg_1_.Enable(true);
        
        ground_1_.loadModel("Environment/ground_1.obj");
		ground_1_.setPosition(300,-20,0);
		ground_1_.setScale(0.3,0.3,0.3);
		ground_1_.setRotation(0, 180, 0, 0, 1);
        ground_1_.setRotation(1, 180, 0, 1, 0);
		ground_1_.Enable(true);
        
        ground_2_.loadModel("Environment/ground_2.obj");
		ground_2_.setPosition(700,-20,-40);
		ground_2_.setScale(0.3,0.3,0.3);
		ground_2_.setRotation(0, 180, 0, 0, 1);
        ground_2_.setRotation(1, 180, 0, 1, 0);
		ground_2_.Enable(true);
        
        ground_3_.loadModel("Environment/ground_3.obj");
		ground_3_.setPosition(1000,-20,0);
		ground_3_.setScale(0.3,0.3,0.3);
		ground_3_.setRotation(0, 180, 0, 0, 1);
        ground_3_.setRotation(1, 180, 0, 1, 0);
		ground_3_.Enable(true);
        
        
        model_ = &tree_;
        
        ground_1_.AddToScene();
        ground_2_.AddToScene();
        ground_3_.AddToScene();

        bg_1_.AddToScene();
		//tree_.AddToScene();
        tree1_.AddToScene();
        tree2_.AddToScene();
        tree3_.AddToScene();
        tree4_.AddToScene();
        tree5_.AddToScene();
        
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
