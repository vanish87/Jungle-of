#include "GamingScene_1.h"
#include "JungleApp.h"
namespace Jungle
{
	GamingScene_1::GamingScene_1(void)
	{
	}


	GamingScene_1::~GamingScene_1(void)
	{
	}

	void GamingScene_1::Steup()
	{

		w_ = ofGetWindowWidth();
		h_ = ofGetWindowHeight();
        ofEnableAlphaBlending();
        
		giraffe_enabled_ = false;
		elephant_enabled_ = false;
		bird_enabled_ = false;
		
		light_.enable();
		//bool success = giraffe_decoder_.decode("test.gif");
		//if (success)
		//	giraffe_ = giraffe_decoder_.getFile();
        background_.loadImage("background.png");

		bird_.loadModel("smooth_birdy.dae",true);
        bird_.setPosition(w_/2, h_/2, 0);
        bird_.setScale(0.8, 0.8, 0.8);
        bird_.setRotation(1, 45, 0, 1, 0);
		
		elephant_.loadModel("astroBoy_walk.dae",true);
        
        
        
		animation_time_	= 0.0;
		frame_index_ = 0;
	}

	void GamingScene_1::Update()
	{
		if(bird_enabled_)
		{
			animation_time_ += ofGetLastFrameTime();
			if( animation_time_ >= 1.0 ){
				animation_time_ = 0.0;
			}
			bird_.setAnimation(0);
			bird_.setNormalizedTime(animation_time_);

			bird_.setAnimation(1);
			bird_.setNormalizedTime(animation_time_);
		}
		
	}

	void GamingScene_1::Draw()
	{
        ofSetColor(255, 255, 255);      
        background_.draw(0, 0);
       
        if(Jungle::KINECT_ENABLE)
		{
			glPushMatrix();
			ofTranslate(0, h_ - 0.4*h_);
			ofScale(0.4, 0.4);
            JungleApp::KinectInstance().debugDraw();
			glPopMatrix();
		}
        
        ofSetColor(255, 255, 255);   
		glPushMatrix();
		glEnable(GL_DEPTH_TEST);
		/*if(giraffe_enabled_)
		{
			int gifW = 200;//giraffe_.getWidth()*0.5;
			int gifH = 200;//giraffe_.getHeight()*0.5;
			frame_index_++;
			if( frame_index_ >= giraffe_.getNumFrames() ){
				frame_index_ = 0;
			}
			giraffe_.drawFrame(frame_index_, frame_index_ * 2, 200, 200, 200);
		}*/
		if(bird_enabled_)
		{
			bird_.drawFaces();
		}
		glDisable(GL_DEPTH_TEST);
		glPopMatrix();
	}


	void GamingScene_1::inPose( ofxUser & user )
	{
		cout << "INPOSE : " ;
		cout<<user.pose<<endl;
		if(user.pose == "GIRAFFE" && !bird_enabled_)
		{
			cout<<"GIRAFFE"<<endl;
			bird_enabled_ = true;
		}
	}

	void GamingScene_1::inGesture( ofxUser & user )
	{
		cout << "INGESTURE : "; 
		cout<<user.gesture<<endl;
		if(user.gesture == "FLY" &&!bird_enabled_)
		{
			cout<<"BIRD"<<endl;
			bird_enabled_ =true;
		}
	}

	void GamingScene_1::userIn( ofxUser & user )
	{
		cout << "USERIN" << endl; 
		cout << user.userId << endl;
	}

	void GamingScene_1::userMove( ofxUser & user )
	{
	}

	void GamingScene_1::userOut( ofxUser & user )
	{
	}

	void GamingScene_1::keyPressed( int key )
	{

	}

	void GamingScene_1::mouseDragged( int x, int y, int button )
	{
		JungleApp::KinectInstance().mouseDragged(x / 0.4, (y - h_ + 0.4*h_) / 0.4, button);
	}
    void GamingScene_1::windowResized(int w, int h)
    {
        w_ = w;
        h_ = h;
    }

}
