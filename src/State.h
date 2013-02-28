#ifndef GAMESTATE_H_
#define GAMESTATE_H_

#pragma once

class ofxUser;
namespace Jungle
{
	class State
	{
	public:
		State(void);
		~State(void);

		void SetParent(State* parent){parent_ = parent;};
		State* GetParent(){return parent_;};

		virtual void Steup() = 0;
		virtual void Update() = 0;
		virtual void Draw() = 0;

		virtual void keyPressed  (int key){};
		virtual void keyReleased(int key){};
		virtual void mouseMoved(int x, int y ){};
		virtual void mouseDragged(int x, int y, int button){};
		virtual void mousePressed(int x, int y, int button){};
		virtual void mouseReleased(int x, int y, int button){};
		virtual void windowResized(int w, int h){};

		virtual void	inPose(ofxUser & user){};
		virtual void	inGesture(ofxUser & user){};
		virtual void	userIn(ofxUser & user){};
		virtual void	userMove(ofxUser & user){};
		virtual void	userOut(ofxUser & user){};

	private:
		State* parent_;
		bool kinect_init;
	};



}

#endif