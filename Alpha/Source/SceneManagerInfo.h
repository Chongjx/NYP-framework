#ifndef SCENE_MANAGER_INFO_H
#define SCENE_MANAGER_INFO_H

#include "SceneManager.h"

class SceneManagerInfo : public SceneManager
{
public:
	vector<Button2D> interactiveButtons;

	SceneManagerInfo() {}
	virtual ~SceneManagerInfo() {}

	virtual void Init(const int width, const int height, ResourcePool* RP, InputManager* controls)
	{
		SceneManager::Init(width, height, RP, controls);

		interactiveButtons.clear();
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
		interactiveButtons.clear();

		SceneManager::Exit();
	}

	virtual void BindShaders() 
	{
		SceneManager::BindShaders();
	}
	virtual void InitShader() {}
	virtual void InitLight() {}

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

			else if (branch->branchName == "Buttons")
			{
				std::cout << "Loading buttons" << std::endl;
				for (vector<Branch>::iterator childbranch = branch->childBranches.begin(); childbranch != branch->childBranches.end(); ++childbranch)
				{
					string name = "";
					string text = "";
					Button2D::BUTTON_TYPE type = Button2D::TEXT_BUTTON;
					Vector2 pos;
					float rotation = 0.f;
					Color tempColor;
					tempColor.Set(1, 1, 1);
					Vector2 scale;
					Mesh* mesh = NULL;

					for (vector<Attribute>::iterator attri = childbranch->attributes.begin(); attri != childbranch->attributes.end(); ++attri)
					{
						Attribute tempAttri = *attri;
						string attriName = tempAttri.name;
						string attriValue = tempAttri.value;

						name = childbranch->branchName;

						if (attriName == "Type")
						{
							if (attriValue == "Text")
							{
								type = Button2D::TEXT_BUTTON;
							}

							else
							{
								type = Button2D::IMAGE_BUTTON;
							}
						}

						else if (attriName == "Text")
						{
							text = attriValue;
						}

						else if (attriName == "Pos")
						{
							stringToVector(attriValue, pos);
						}

						else if (attriName == "Scale")
						{
							stringToVector(attriValue, scale);
						}

						else if (attriName == "Rotation")
						{
							rotation = stof(attriValue);
						}

						else if (attriName == "Color")
						{
							Vector3 tempCol;

							stringToVector(attriValue, tempCol);

							tempColor.Set(tempCol.x, tempCol.y, tempCol.z);
						}

						else if (attriName == "Mesh")
						{
							mesh = resourceManager.retrieveMesh(attriValue);

							if (type == Button2D::TEXT_BUTTON)
								mesh->textureID = resourceManager.retrieveTexture("FONT");

							//else
							//	mesh->textureID = resourceManager.retrieveTexture("Button");
						}
					}

					Button2D tempButton;
					
					tempButton.Init(name, text, mesh, pos, scale, rotation, tempColor, type);
					interactiveButtons.push_back(tempButton);
				}
			}
		}
	}
};

#endif