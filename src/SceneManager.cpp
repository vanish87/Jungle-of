#include "SceneManager.h"
#include "Flower.h"
#include "Group.h"
#include "Tree.h"

namespace Jungle
{
	SceneManager::SceneManager(void)
	{
	}


	SceneManager::~SceneManager(void)
	{
	}

	void SceneManager::Update()
	{
		render_list_.clear();
		for(int i = 0; i < scene_obj_list_.size(); ++i)
		{
			if(scene_obj_list_[i]->Enabled())
			{
				scene_obj_list_[i]->Update(ofGetLastFrameTime());
				render_list_.push_back(scene_obj_list_[i]);
			}
		}
	}

	void SceneManager::Draw()
	{
		for(int i =0; i < render_list_.size(); ++i)
		{
			render_list_[i]->drawFaces();
		}
	}

	void SceneManager::AddToScene( SceneModel* scene_obj )
	{
		scene_obj_list_.push_back(scene_obj);
	}

	bool SceneManager::LoadScene( string file_name )
	{
		cout<<"=========Loading Scene Config================"<<endl;
		ofxXmlSettings file;
		if(!file.loadFile(file_name))
		{
			cout<<"Cannot load "<<file_name<<endl;
			return false;
		}
		if(!file.tagExists("LevelIndex"))
		{
			cout<<"Cannot find LevelIndex"<<endl;
			return false;
		}


		file.pushTag("LevelIndex");
		for(size_t i =0; i < file.getNumTags("Level"); ++i)
		{
			vector<string> group_name;
			for(size_t i =0; i < file.getNumTags("Group"); ++i)
			{
				file.pushTag("Group",i);
				string name = file.getValue("Name","NONE");
				group_name.push_back(name);
				file.popTag();
			}
			level_index_.push_back(group_name);
		}
		file.popTag();

		SceneType scene;

		for(size_t i =0; i < file.getNumTags("Group"); ++i)
		{
			file.pushTag("Group",i);
			string name = file.getValue("Name","NONE");
			//if(name == group_name[i])
			{
				string type = file.getValue("Type","NONE");
				if(type == "Flower")
				{
					vector<Flower*> group_model;
					if(file.tagExists("GroupObj"))
					{
						file.pushTag("GroupObj");
						for(size_t j =0; j < file.getNumTags("Model"); ++j)
						{
							file.pushTag("Model",j);
							string url = file.getValue("ObjURL", "NA");
							ofVec3f pos;
							file.pushTag("Position");
							pos.set(file.getValue("X",0), file.getValue("Y",0), file.getValue("Z",0));
							file.popTag();
							float rotation = file.getValue("Rotation",0);
							float max_scale = file.getValue("MaxScale",0.1);
							float scale_speed = file.getValue("ScaleSpeed", 0.01);
							float staying_time = file.getValue("StayingTime", 1);
							float holding_time = file.getValue("HoldingTime", 1);
							float circle_size = file.getValue("CircleSize", 200);
							file.pushTag("CircleColor");
							ofColor color;
							color.set(file.getValue("R",255), file.getValue("G",255), file.getValue("B",255), file.getValue("A",255));
							file.popTag();
							file.pushTag("ModelColor");
							ofColor mcolor;
							mcolor.set(file.getValue("R",255), file.getValue("G",255), file.getValue("B",255), file.getValue("A",255));
							file.popTag();


							bool falling = file.getValue("FallingEnable", false);
							float pitch = file.getValue("Pitch", 1.0f);

							Flower* flower = new Flower();
							flower->loadModel(url);
							flower->setPosition(pos.x,pos.y,pos.z);
							flower->setRotation(0,180,1,0,0);
							flower->setRotation(1,rotation,0,0,1);
							flower->SetMaxScale(max_scale);
							flower->SetScaleSpeed(scale_speed);
							flower->staying_time_ = staying_time + ofRandom(-3, 3);
							flower->holding_time_ = holding_time;
							flower->SetCircleSize(circle_size);
							flower->SetCircleColor(color);
							flower->SetColor(mcolor);
							flower->SetFalling(falling);
							flower->SetPitch(pitch);
							flower->Enable(false);
							group_model.push_back(flower);
							file.popTag();
						}
						file.popTag();

						float group_staying_time= file.getValue("StayingTime",1);

						Group flower_group(name, group_staying_time, group_model, Group::LEAF);
						scene.push_back(flower_group);
					}
				}
				else
                if(type == "MUSHROOM")
                {
                    vector<Flower*> group_model;
					if(file.tagExists("GroupObj"))
					{
						file.pushTag("GroupObj");
						for(size_t j =0; j < file.getNumTags("Model"); ++j)
						{
							file.pushTag("Model",j);
							string url = file.getValue("ObjURL", "NA");
							ofVec3f pos;
							file.pushTag("Position");
							pos.set(file.getValue("X",0), file.getValue("Y",0), file.getValue("Z",0));
							file.popTag();
							float rotation = file.getValue("Rotation",0);
							float max_scale = file.getValue("MaxScale",0.1);
							float scale_speed = file.getValue("ScaleSpeed", 0.01);
							float staying_time = file.getValue("StayingTime", 1);
							float holding_time = file.getValue("HoldingTime", 1);
							float circle_size = file.getValue("CircleSize", 200);
							file.pushTag("CircleColor");
							ofColor color;
							color.set(file.getValue("R",255), file.getValue("G",255), file.getValue("B",255), file.getValue("A",255));
							file.popTag();
							file.pushTag("ModelColor");
							ofColor mcolor;
							mcolor.set(file.getValue("R",255), file.getValue("G",255), file.getValue("B",255), file.getValue("A",255));
							file.popTag();
                            
                            
							bool falling = file.getValue("FallingEnable", false);
							float pitch = file.getValue("Pitch", 1.0f);
                            
							Flower* flower = new Flower();
							flower->loadModel(url);
							flower->setPosition(pos.x,pos.y,pos.z);
							flower->setRotation(0,180,1,0,0);
							flower->setRotation(1,rotation,0,0,1);
							flower->SetMaxScale(max_scale);
							flower->SetScaleSpeed(scale_speed);
							flower->staying_time_ = staying_time + ofRandom(-3, 3);
							flower->holding_time_ = holding_time;
							flower->SetCircleSize(circle_size);
							flower->SetCircleColor(color);
							flower->SetColor(mcolor);
							flower->SetFalling(falling);
							flower->SetPitch(pitch);
							flower->Enable(false);
							group_model.push_back(flower);
							file.popTag();
						}
						file.popTag();
                        
						float group_staying_time= file.getValue("StayingTime",1);
                        
						Group flower_group(name, group_staying_time, group_model, Group::MUSHROOM);
						scene.push_back(flower_group);
					}
                }
                else
				if(type == "Tree")
				{
					vector<Flower*> group_model;
					if(file.tagExists("GroupObj"))
					{
						file.pushTag("GroupObj");
						for(size_t j =0; j < file.getNumTags("Model"); ++j)
						{
							file.pushTag("Model",j);
							string url = file.getValue("ObjURL", "NA");
							ofVec3f pos;
							file.pushTag("Position");
							pos.set(file.getValue("X",0), file.getValue("Y",0), file.getValue("Z",0));
							file.popTag();
							float rotation = file.getValue("Rotation",0);
							float max_scale = file.getValue("MaxScale",0.1);
							float scale_speed = file.getValue("ScaleSpeed", 0.01);
							float staying_time = file.getValue("StayingTime", 1);
							float holding_time = file.getValue("HoldingTime", 1);
							float circle_size = file.getValue("CircleSize", 200);
							file.pushTag("CircleColor");
							ofColor color;
							color.set(file.getValue("R",255), file.getValue("G",255), file.getValue("B",255), file.getValue("A",255));
							file.popTag();
							file.pushTag("ModelColor");
							ofColor mcolor;
							mcolor.set(file.getValue("R",255), file.getValue("G",255), file.getValue("B",255), file.getValue("A",255));
							file.popTag();


							bool falling = file.getValue("FallingEnable", false);
							float pitch = file.getValue("Pitch", 1.0f);

							Tree* flower = new Tree();
							flower->loadModel(url);
							flower->setPosition(pos.x,pos.y,pos.z);
							flower->setRotation(0,180,1,0,0);
							flower->setRotation(1,rotation,0,0,1);
							flower->SetMaxScale(max_scale);
							flower->SetScaleSpeed(scale_speed);
							flower->staying_time_ = staying_time + ofRandom(-3, 3);
							flower->holding_time_ = holding_time;
							flower->SetCircleSize(circle_size);
							flower->SetCircleColor(color);
							flower->SetColor(mcolor);
							flower->SetFalling(falling);
							flower->SetPitch(pitch);
							flower->Enable(false);
							group_model.push_back(flower);
							file.popTag();
						}
						file.popTag();

						float group_staying_time= file.getValue("StayingTime",1);

						Group flower_group(name, group_staying_time, group_model, Group::TREE);
						scene.push_back(flower_group);
					}
				}
				

			}
			file.popTag();

			
		}

		dynamic_objects_ =  scene;
		return true;
	}

	Jungle::SceneType &SceneManager::GetDynamicObj()
	{
		return dynamic_objects_;
	}

	void SceneManager::Enable( Group::GROUP_TYPE type, bool enable )
	{
		for(SceneType::iterator it = dynamic_objects_.begin(); it!= dynamic_objects_.end(); ++it)
		{
			if(it->GetType() == type)
				it->Enable(enable);
		}
	}

}
