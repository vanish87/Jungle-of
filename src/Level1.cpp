#include "Level1.h"

namespace Jungle
{
	Level1::Level1( void )
		//not use right now
		:wind_("config.xml")
	{
		
	}

	Level1::~Level1( void )
	{

	}

	void Level1::Steup()
	{
		wind_.Init();

		b_pos_.set(300,300,0);
	}

	void Level1::Update()
	{
		wind_.Update(hand_pos_);


		b_pos_+= wind_.butterfly_force_ * 0.1;
		b_pos_.x = ofClamp(b_pos_.x, 50, 1280-50);
		b_pos_.y = ofClamp(b_pos_.y, 50, 720-50);
	}

	void Level1::Draw()
	{
		wind_.Draw();

		ofPushMatrix();
		ofTranslate(b_pos_);
		ofSphere(50);
		ofPopMatrix();
	}

	void Level1::keyPressed( int key )
	{

	}

	void Level1::mouseMoved( int x, int y )
	{
		hand_pos_.set(x,y,0);
		wind_.Enable(true, hand_pos_);		
	}

	void Level1::windowResized( int w, int h )
	{

	}

	void Level1::inPose( ofxUser & user )
	{

	}

	void Level1::inGesture( ofxUser & user )
	{

	}

	void Level1::userIn( ofxUser & user )
	{

	}

	void Level1::userMove( ofxUser & user )
	{

	}

	void Level1::userOut( ofxUser & user )
	{

	}

}
