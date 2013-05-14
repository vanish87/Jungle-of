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
                
        bg_1_.loadModel("Environment/mountain.obj");
		bg_1_.setPosition(648,-20,-500);
		bg_1_.setScale(2,2,2);
		bg_1_.setRotation(0, 180, 0, 0, 1);
        bg_1_.setRotation(1, 180, 0, 1, 0);
		bg_1_.Enable(true);
        
        ground_1_.loadModel("Environment/front.obj");

		ground_1_.setPosition(680,-24,200);
		ground_1_.setScale(2,2,2);
		ground_1_.setRotation(0, 180, 0, 0, 1);
        ground_1_.setRotation(1, 180, 0, 1, 0);
		ground_1_.Enable(true);
        
        ground_2_.loadModel("Environment/second.obj");
		ground_2_.setPosition(680,-24,0);
		ground_2_.setScale(2,2,2);
		ground_2_.setRotation(0, 180, 0, 0, 1);
        ground_2_.setRotation(1, 180, 0, 1, 0);
		ground_2_.Enable(true);
        
        ground_3_.loadModel("Environment/back.obj");
		ground_3_.setPosition(680,-24,-50);
		ground_3_.setScale(2,2,2);
        ground_3_.setRotation(0, 180, 0, 0, 1);
        ground_3_.setRotation(1, 180, 0, 1, 0);
		ground_3_.Enable(true);
        
        model_ = &tree_;
    

        bg_1_.AddToScene();
        
        back_color_start_ = ofColor(255,255,255);
        back_color_end_ = ofColor((255,255,255));
   
        ground_3_.AddToScene();
        ground_2_.AddToScene();
        ground_1_.AddToScene();
        
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
        ofBackgroundGradient(back_color_start_, back_color_end_,OF_GRADIENT_LINEAR);
		//ofBackgroundGradient(ofColor(230,0,0),ofColor(14,28,54), OF_GRADIENT_LINEAR);

		glEnable(GL_DEPTH_TEST);

		ofPushMatrix();				
		JungleApp::SceneManagerInstance().Draw();
		ofPopMatrix();

		glDisable(GL_DEPTH_TEST);
               
	}

	void StaticScene::keyPressed( int key )
	{        
       
		ofVec3f pos; //= model_->getPosition();
		ofVec3f scale; //= model_->getScale();
		switch (key)
		{
		case '1':
			pos.z+=5;
			break;
		case '2':
			pos.z-=5;
			break;	
		case '3':
			pos.y+=5;
			break;
		case '4':
			pos.y-=5;
			break;
		case '5':
			pos.x-=5;
			break;
		case '6':
			pos.x+=5;
			break;
		case '7':
			scale+=0.1;
			model_->setScale(scale.x, scale.y,scale.z);
			break;
		case '8':
			scale-=0.1;
			model_->setScale(scale.x, scale.y,scale.z);
			break;
		case '9':
			break;
		case 'q':
			break;
		case 'w':
			break;
		case 'e':
			break;
        case 'r':
            pos = ground_.getPosition();
            model_ = &bg_4_;
            back_color_start_.set(0, 255, 0);
            break;
        case 't':
			pos = ground_.getPosition();
			model_ = &ground_;
			break;		
        case 'y':
			pos = tree_.getPosition();
			model_ = &tree_;
			break;
		case 'u':
			pos = bg_3_.getPosition();
			model_ = &bg_3_;
			break;
		case 'i':
			pos = bg_2_.getPosition();
			model_ = &bg_2_;
			break;
		case 'o':
			pos = bg_1_.getPosition();
			model_ = &bg_1_;
			break;
        case 'p':
            pos = rocks_.getPosition();
            model_ = &rocks_;
            break;
		case 'a':
                pos = ground_.getPosition();
                model_ = &bg_4_;
                back_color_start_.set(206, 234, 235);
			break;
		case 's':
                pos = ground_.getPosition();
                model_ = &bg_4_;
                back_color_start_.set(186, 186, 186);
			break;
		case 'd':
                pos = ground_.getPosition();
                model_ = &bg_4_;
                back_color_start_.set(239, 41, 94);
			break;
		case 'f':
                pos = ground_.getPosition();
                model_ = &bg_4_;
                back_color_start_.set(14, 28, 54);
			break;
            case 'g':
                pos = ground_.getPosition();
                model_ = &bg_4_;
                back_color_start_.set(150, 33, 166);
                break;
            case 'h':
                pos = ground_.getPosition();
                model_ = &bg_4_;
                back_color_start_.set(85, 50, 133);
                break;
            case 'j':
                pos = ground_.getPosition();
                model_ = &bg_4_;
                back_color_start_.set(255, 182, 22);
                break;
            case 'k':
                pos = ground_.getPosition();
                model_ = &bg_4_;
                back_color_start_.set(242, 82, 96);
                break;
            case 'l':
                pos = ground_.getPosition();
                model_ = &bg_4_;
                back_color_start_.set(85, 50, 133);
                break;
            case ';':
                pos = ground_.getPosition();
                model_ = &bg_4_;
                back_color_start_.set(255, 182, 22);
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

	void StaticScene::SetBackgroundStart( ofColor color )
	{
		back_color_start_ = color;
	}

}
