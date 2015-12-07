#ifndef SCENE_MANAGER_GAMEPLAY_H
#define SCENE_MANAGER_GAMEPLAY_H

#include "SceneManager.h"

class SceneManagerGameplay : public SceneManager
{
protected:
	SpatialPartitionManager* spatialPartitionManager;
	Vector3 world3DStart;
	Vector3 world3DEnd;
	Vector2 world2DStart;
	Vector2 world2DEnd;
public:
	SceneManagerGameplay() : spatialPartitionManager(NULL) {}
	virtual ~SceneManagerGameplay() 
	{
		if (spatialPartitionManager)
		{
			spatialPartitionManager->CleanUp();
			spatialPartitionManager = NULL;
			delete spatialPartitionManager;
		}
	}

	virtual void Init(const int width, const int height, ResourcePool* RP, InputManager* controls)
	{
		SceneManager::Init(width, height, RP, controls);
	}

	virtual void Update(double dt)
	{
		SceneManager::Update(dt);
	}

	virtual void Render()
	{
		SceneManager::Render();
	}

	virtual void Exit()
	{
		SceneManager::Exit();
	}

	virtual void BindShaders() 
	{
		SceneManager::BindShaders();
	}

	virtual void InitShader() {}

	virtual void UpateMouse()
	{
		SceneManager::UpdateMouse();
	}

	virtual void RenderLight() {}
	virtual void RenderBG() {}
	virtual void RenderStaticObject() {}
	virtual void RenderMobileObject() {}

	void Config(string directory) 
	{
		sceneBranch = TextTree::FileToRead(directory);

		for (vector<Branch>::iterator branch = sceneBranch.childBranches.begin(); branch != sceneBranch.childBranches.end(); ++branch)
		{
			// setting up camera for the scene
			if (branch->branchName == "Camera")
			{
				std::cout << "Setting up camera!" << std::endl;
				Vector3 tempPos, tempTarget, tempUp;
				string cameraType;
				bool lockPitch = true;
				bool lockYaw = true;

				for (vector<Attribute>::iterator attri = branch->attributes.begin(); attri != branch->attributes.end(); ++attri)
				{
					Attribute tempAttri = *attri;
					string attriName = tempAttri.name;
					string attriValue = tempAttri.value;

					if (attriName == "Type")
					{
						cameraType = attriValue;
					}

					else if (attriName == "CameraPos")
					{
						stringToVector(attriValue, tempPos);
					}

					else if (attriName == "CameraTarget")
					{
						stringToVector(attriValue, tempTarget);
					}

					else if (attriName == "CameraUp")
					{
						stringToVector(attriValue, tempUp);
					}

					else if (attriName == "LockPitch")
					{
						stringToBool(attriValue, lockPitch);
					}

					else if (attriName == "LockYaw")
					{
						stringToBool(attriValue, lockYaw);
					}

				}

				if (cameraType == "FP")
				{
					fpCamera.Init(tempPos, tempTarget, tempUp);
				}

				else if (cameraType == "TP")
				{
					tpCamera.Init(tempPos, tempTarget, tempUp, lockPitch, lockYaw);
				}

				// default camera chosen for this scene. Shld vary depending on scene type
				else
				{
					fpCamera.Init(tempPos, tempTarget, tempUp);
				}
			}

			else if (branch->branchName == "Font")
			{
				std::cout << "Setting up font" << std::endl;
				for (vector<Attribute>::iterator attri = branch->attributes.begin(); attri != branch->attributes.end(); ++attri)
				{
					Attribute tempAttri = *attri;
					string attriName = tempAttri.name;
					string attriValue = tempAttri.value;

					if (attriName == "Default")
					{
						fontSize = stof(attriValue);
					}

					else if (attriName == "Special")
					{
						specialFontSize = stof(attriValue);
					}
				}
			}

			else if (branch->branchName == "Light")
			{
				std::cout << "Setting up lights" << std::endl;
				for (vector<Attribute>::iterator attri = branch->attributes.begin(); attri != branch->attributes.end(); ++attri)
				{
					Attribute tempAttri = *attri;
					string attriName = tempAttri.name;
					string attriValue = tempAttri.value;

					if (attriName == "Enable")
					{
						stringToBool(attriValue, lightEnabled);
					}
				}
			}

			else if (branch->branchName == "SpatialPartition")
			{
				// create a spatial partition manager if it is not defined
				if (spatialPartitionManager == NULL)
				{
					spatialPartitionManager = new SpatialPartitionManager();
				}

				int type = 0;
				Vector3 partitionDimension;
				Vector2 partitionDimension2D;
				bool numPartitionBased = true;

				std::cout << "Setting up spatial partitioning" << std::endl;
				for (vector<Attribute>::iterator attri = branch->attributes.begin(); attri != branch->attributes.end(); ++attri)
				{
					Attribute tempAttri = *attri;
					string attriName = tempAttri.name;
					string attriValue = tempAttri.value;

					if (attriName == "Type")
					{
						type = stoi(attriValue);
					}

					else if (attriName == "WorldStart")
					{
						if (type == 3)
						{
							stringToVector(attriValue, world3DStart);
						}

						else
						{
							stringToVector(attriValue, world2DStart);
						}
					}

					else if (attriName == "WorldEnd")
					{
						if (type == 3)
						{
							stringToVector(attriValue, world3DEnd);
						}

						else
						{
							stringToVector(attriValue, world2DEnd);
						}
					}

					else if (attriName == "Partitions")
					{
						if (type == 3)
						{
							stringToVector(attriValue, partitionDimension);
						}

						else
						{
							stringToVector(attriValue, partitionDimension2D);
						}
					}

					else if (attriName == "PartitionBased")
					{
						stringToBool(attriValue, numPartitionBased);
					}
				}

				// 3D spatial partition
				if (type == 3)
				{
					spatialPartitionManager->Init(world3DStart, world3DEnd, partitionDimension, numPartitionBased, resourceManager.retrieveMesh("DEBUG_CUBE"));
				}

				// assume its 2D
				else
				{
					spatialPartitionManager->Init(world2DStart, world2DEnd, partitionDimension2D, numPartitionBased, resourceManager.retrieveMesh("DEBUG_QUAD"));
				}
			}
		}
	}
};

#endif