#include "JungleApp.h"

namespace Jungle
{
	const bool KINECT_ENABLE = false;
	const bool JUNGLE_DEBUG = true;
	//--------------------------------------------------------------
	void JungleApp::setup(){
        ofSetLogLevel(OF_LOG_VERBOSE);
        if(KINECT_ENABLE)
        {
            KinectInstance().setup("config.xml");
            ofAddListener(KinectInstance().inPose,this,&JungleApp::inPose);
            ofAddListener(KinectInstance().inGesture,this,&JungleApp::inGesture);
            ofAddListener(KinectInstance().userIn,this,&JungleApp::userIn);
            ofAddListener(KinectInstance().userMove,this,&JungleApp::userMove);
            ofAddListener(KinectInstance().userOut,this,&JungleApp::userOut);
        }

		game_1_ = 0;
		//game_2_ = new GamingScene2();
		//game_2_->Steup();
		
		//game_3_ = new GamingScene3();
		//game_3_->Steup();

		//game_4_ = new GamingScene4();
		//game_4_->Steup();


		//game_5_ = new GamingScene5();
		//game_5_->Steup();

		//game_6_ = new GamingScene6();
		//game_6_->Steup();

		static_scene_ = new StaticScene();
		static_scene_->Steup();

		//setup all level here
		StateManagerInstance().ChangeState(static_scene_, SOP_PUSH);
        
		level1_ = new Level1();
		level1_->Steup();
		StateManagerInstance().ChangeState(level1_, SOP_PUSH);
        
        ofSetFrameRate(60);
        ofEnableSmoothing();
		//ofEnableAlphaBlending();
//         
         
	}

	//--------------------------------------------------------------
	void JungleApp::update(){
        if(KINECT_ENABLE)
            KinectInstance().update();
		StateManagerInstance().Update();
	}

	//--------------------------------------------------------------
	void JungleApp::draw(){
		if(StateManagerInstance().CurrentState() == NULL) return;
		StateManagerInstance().CurrentState()->Draw();
	}

	//--------------------------------------------------------------
	void JungleApp::keyPressed(int key){
		if(StateManagerInstance().CurrentState() == NULL) return;
		StateManagerInstance().CurrentState()->keyPressed(key);
// 		switch(key){
// 		case 'i':
// 			/*drawInterfaceDebug=!drawInterfaceDebug;*/
// 			break;
// 		case '1':
// 			inter.setPerspective(0);
// 			break;
// 		case '2':
// 			inter.setPerspective(1);
// 			break;
// 		case '3':
// 			inter.setPerspective(2);
// 			break;
// 		}
	}

	//--------------------------------------------------------------
	void JungleApp::keyReleased(int key){
		switch (key) 
		{
#if defined (TARGET_OSX)
#ifdef HARDWARE
			//adjust kinect camera
			case 357: // up key
				//KinectInstance().CameraMoveUp();
				break;
			//adjust kinect camera
			case 359: // down key
				//KinectInstance().CameraMoveDown();
				break;
#endif
#endif
			default:
				break;
		}

		if(StateManagerInstance().CurrentState() == NULL) return;
		StateManagerInstance().CurrentState()->keyReleased(key);
	}

	//--------------------------------------------------------------
	void JungleApp::mouseMoved(int x, int y ){
		if(StateManagerInstance().CurrentState() == NULL) return;
		StateManagerInstance().CurrentState()->mouseMoved(x, y);
	}

	//--------------------------------------------------------------
	void JungleApp::mouseDragged(int x, int y, int button){

		KinectInstance().mouseDragged(x,y,button);

		if(StateManagerInstance().CurrentState() == NULL) return;
		StateManagerInstance().CurrentState()->mouseDragged(x, y, button);
	}

	//--------------------------------------------------------------
	void JungleApp::mousePressed(int x, int y, int button){
		if(StateManagerInstance().CurrentState() == NULL) return;
		StateManagerInstance().CurrentState()->mousePressed(x, y, button);
	}

	//--------------------------------------------------------------
	void JungleApp::mouseReleased(int x, int y, int button){
		if(StateManagerInstance().CurrentState() == NULL) return;
		StateManagerInstance().CurrentState()->mouseReleased(x, y, button);
	}

	//--------------------------------------------------------------
	void JungleApp::windowResized(int w, int h){
		if(StateManagerInstance().CurrentState() == NULL) return;
		StateManagerInstance().CurrentState()->windowResized(w, h);
	}

	StateManager& JungleApp::StateManagerInstance()
	{
		static StateManager state_manager;
		return state_manager;
	}

	SceneManager& JungleApp::SceneManagerInstance()
	{
		static SceneManager scene_manager;
		return scene_manager;
	}

	Player& JungleApp::PlayerInstance()
	{
		static Player player;
		//cout<<"instance "<<&player<<endl;
		return player;
	}


	ofxKinectUsers& JungleApp::KinectInstance()
	{
		static ofxKinectUsers inter;
		return inter;
	}

	void JungleApp::inPose( ofxUser & user )
	{
		StateManagerInstance().CurrentState()->inPose(user);
	}

	void JungleApp::inGesture( ofxUser & user )
	{
		StateManagerInstance().CurrentState()->inGesture(user);
	}

	void JungleApp::userIn( ofxUser & user )
	{
		StateManagerInstance().CurrentState()->userIn(user);
	}

	void JungleApp::userMove( ofxUser & user )
	{
		StateManagerInstance().CurrentState()->userMove(user);
	}

	void JungleApp::userOut( ofxUser & user )
	{
		StateManagerInstance().CurrentState()->userOut(user);
	}

/*
	//--------------------------------------------------------------
	void JungleApp::inPose(ofxUser & user){
		//cout << "INPOSE : " ;
		//cout<<user.pose<<endl;
		if(user.pose == "GIRAFFE" && !giraffe_enabled_)
		{
			cout<<"GIRAFFE"<<endl;
			giraffe_enabled_ = true;
		}

		if(user.pose == "ELEPHANT" &&!elephant_enabled_)
		{
			cout<<"ELEPHANT"<<endl;
			elephant_enabled_ = true;
		}
	}

	void JungleApp::inGesture(ofxUser & user){
		cout << "INGESTURE : "; 
		cout<<user.gesture<<endl;
		if(user.gesture == "FLY" &&!bird_enabled_)
		{
			cout<<"BIRD"<<endl;
			bird_enabled_ =true;
		}
	}

	void JungleApp::userIn(ofxUser & user){
		cout << "USERIN" << endl; 
	}

	void JungleApp::userMove(ofxUser & user){
		//cout << "USERMOVE" << endl; 
	}

	void JungleApp::userOut(ofxUser & user){
		cout << "USEROUT" << endl; 
	}*/

}
