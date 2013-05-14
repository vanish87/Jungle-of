#include "SceneManager.h"
#include "Flower.h"
#include "Group.h"
#include "Tree.h"
#include "Cloud.h"
#include "Mushroom.h"

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
    
    void SceneManager::Reset()
    {
        unsigned char objcolor = ofRandom(0, obj_colors_.size());        
       for(SceneType::iterator it = dynamic_objects_.begin(); it!= dynamic_objects_.end(); ++it)
		{
			if(it->GetType() == Group::TREE)
           {
               it->SetColor(obj_colors_[objcolor][0]);
           }
           else
           if(it->GetType() == Group::LEAF)
           {
               it->SetColor(obj_colors_[objcolor][1]);
           }
           else
           if(it->GetType() == Group::MUSHROOM)
           {
               it->SetColor(obj_colors_[objcolor][2]);
           }
           else
           if(it->GetType() == Group::FRUIT)
           {
               it->SetColor(obj_colors_[objcolor][3]);
           }
		}
        
        //cout<<stage_index_[0]<<stage_index_[1]<<stage_index_[2]<<stage_index_[3]<<endl;
//        unsigned short index = ofRandom(0,2);
//        cout<<index<<endl;
//        swap(stage_index_[index],stage_index_[3-index]);
//        swap(stage_index_[1-index],stage_index_[2+index]);
        random_shuffle(stage_index_.begin(), stage_index_.end());
       // cout<<stage_index_[0]<<stage_index_[1]<<stage_index_[2]<<stage_index_[3]<<endl;
        
        
        
    }
    vector<unsigned short>& SceneManager::GetLightingIndex()
    {
        return stage_index_;
    }
    
    vector<vector<ofColor> > SceneManager::GetStageColor()
    {
        return stage_colors_;
    }
    
    void SceneManager::ReadColorSet(ofxXmlSettings &file)
    {
        file.pushTag("ColorSet");
		for(size_t i =0; i < file.getNumTags("Stage"); ++i)
		{
            file.pushTag("Stage",i);
			vector<ofColor> stage_color;
            file.pushTag("Backgroud_Start");
            ofColor color = ofColor(
                file.getValue("R",0), file.getValue("G",0), file.getValue("B",0), file.getValue("A",0));
            file.popTag();
			
			file.pushTag("Backgroud_End");
            ofColor ecolor = ofColor(
				file.getValue("R",0), file.getValue("G",0), file.getValue("B",0), file.getValue("A",0));
            file.popTag();
			
            file.pushTag("Light");            
            ofColor lcolor = ofColor(
                file.getValue("R",0), file.getValue("G",0), file.getValue("B",0), file.getValue("A",0));
            file.popTag();
			stage_color.push_back(color);
			stage_color.push_back(ecolor);
            stage_color.push_back(lcolor);
            cout<<(int)lcolor.r<<(int)lcolor.g<<(int)lcolor.b<<(int)lcolor.a<<endl;
            stage_colors_.push_back(stage_color);
            file.popTag();
		}
		file.popTag();
        
        file.pushTag("ObjColorSet");
		for(size_t i =0; i < file.getNumTags("Set"); ++i)
		{
            file.pushTag("Set",i);
			vector<ofColor> stage_color;
            file.pushTag("Tree");
            ofColor color = ofColor(
                                    file.getValue("R",0), file.getValue("G",0), file.getValue("B",0), file.getValue("A",0));
            file.popTag();
			stage_color.push_back(color);
            
            file.pushTag("Leaf");
            color =
                ofColor(file.getValue("R",0), file.getValue("G",0), file.getValue("B",0), file.getValue("A",0));
            file.popTag();
            stage_color.push_back(color);
            
            file.pushTag("Mushroom");
            color =
            ofColor(file.getValue("R",0), file.getValue("G",0), file.getValue("B",0), file.getValue("A",0));
            file.popTag();
            stage_color.push_back(color);
            
            file.pushTag("Fruit");
            color =
            ofColor(file.getValue("R",0), file.getValue("G",0), file.getValue("B",0), file.getValue("A",0));
            file.popTag();
            stage_color.push_back(color);
            
            obj_colors_.push_back(stage_color);
            file.popTag();
		}
        stage_index_.push_back(0);
        stage_index_.push_back(1);
        stage_index_.push_back(2);
        stage_index_.push_back(3);
		file.popTag();
        
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

        ReadColorSet(file);
        
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
                if(type == "Mushroom")
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
                            
							Mushroom* flower = new Mushroom();
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
                if (type == "Fruit")
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
                        
						Group flower_group(name, group_staying_time, group_model, Group::FRUIT);
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
                            flower->setScale(0.4, 0.4, 0.4);
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
                else
                    if(type == "Cloud")
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
                                
                                Cloud* flower = new Cloud();
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
								flower->InitDroplet();
                                flower->Enable(false);
                                group_model.push_back(flower);
                                file.popTag();
                            }
                            file.popTag();
                            
                            float group_staying_time= file.getValue("StayingTime",1);
                            
                            Group flower_group(name, group_staying_time, group_model, Group::CLOUD);
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

	void SceneManager::Enable( Group::GROUP_TYPE type, bool enable, unsigned int index)
	{
		for(SceneType::iterator it = dynamic_objects_.begin(); it!= dynamic_objects_.end(); ++it)
		{
			if(it->GetType() == type)
				it->Enable(enable);
		}
	}

	int SceneManager::GetTriggeringCount( Group::GROUP_TYPE type )
	{
		int ret = 0;
		for(SceneType::iterator it = dynamic_objects_.begin(); it!= dynamic_objects_.end(); ++it)
		{
			if(it->GetType() == type)
				ret+=it->GetTriggeringCount();
		}
		return ret;
	}

}
