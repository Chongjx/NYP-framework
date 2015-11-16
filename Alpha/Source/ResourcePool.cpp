#include "ResourcePool.h"
#include "LoadTGA.h"

ResourcePool::ResourcePool()
{
}

ResourcePool::~ResourcePool()
{
}

void ResourcePool::Init(string config)
{
	resourceBranch = TextTree::FileToRead(config);

	Config();
}

void ResourcePool::Config()
{
	for (vector<Branch>::iterator branch = resourceBranch.childBranches.begin(); branch != resourceBranch.childBranches.end(); ++branch)
	{
		if (branch->branchName == "MeshContainer")
		{
			for (vector<Attribute>::iterator attri = branch->attributes.begin(); attri != branch->attributes.end(); ++attri)
			{
				Attribute tempAttri = *attri;
				string attriName = tempAttri.name;
				string attriValue = tempAttri.value;
				if (attriName == "Directory")
				{
					processMesh(attriValue);
				}
			}
		}

		else if (branch->branchName == "TextureContainer")
		{
			for (vector<Attribute>::iterator attri = branch->attributes.begin(); attri != branch->attributes.end(); ++attri)
			{
				Attribute tempAttri = *attri;
				string attriName = tempAttri.name;
				string attriValue = tempAttri.value;
				if (attriName == "Directory")
				{
					processTexture(attriValue);
				}
			}
		}

		else if (branch->branchName == "ColorContainer")
		{
			for (vector<Attribute>::iterator attri = branch->attributes.begin(); attri != branch->attributes.end(); ++attri)
			{
				Attribute tempAttri = *attri;
				string attriName = tempAttri.name;
				string attriValue = tempAttri.value;
				if (attriName == "Directory")
				{
					processColor(attriValue);
				}
			}
		}

		else if (branch->branchName == "ShaderContainer")
		{
			for (vector<Attribute>::iterator attri = branch->attributes.begin(); attri != branch->attributes.end(); ++attri)
			{
				Attribute tempAttri = *attri;
				string attriName = tempAttri.name;
				string attriValue = tempAttri.value;
				if (attriName == "Directory")
				{
					processShader(attriValue);
				}
			}
		}

		else if (branch->branchName == "SoundContainer")
		{
			for (vector<Attribute>::iterator attri = branch->attributes.begin(); attri != branch->attributes.end(); ++attri)
			{
				Attribute tempAttri = *attri;
				string attriName = tempAttri.name;
				string attriValue = tempAttri.value;
				if (attriName == "Directory")
				{
					//processSound(attriValue);
				}
			}
		}
	}
}

void ResourcePool::processMesh(string config)
{
	Branch meshBranch = TextTree::FileToRead(config);

	for (vector<Branch>::iterator branch = meshBranch.childBranches.begin(); branch != meshBranch.childBranches.end(); ++branch)
	{
		string meshName = branch->branchName;
		Color meshColor;
		unsigned textureID = 0;

		enum MISC_VARIABLE
		{
			VAR_LENGTH,
			VAR_WIDTH,
			VAR_HEIGHT,
			VAR_RADIUS,
			VAR_INNER_RADIUS,
			VAR_OUTER_RADIUS,
			VAR_SLICES,
			VAR_STACKS,
			VAR_ANIM_TIME,
			MAX_VAR,
		};

		float meshVar[MAX_VAR];
		for (int i = 0; i < MAX_VAR; ++i)
		{
			meshVar[i] = 1.0f;
		}

		string meshVarNames[MAX_VAR] =
		{
			"Length",
			"Width",
			"Height",
			"Radius",
			"InnerRadius",
			"OuterRadius",
			"Slices",
			"Stacks",
		};

		// default 2D mesh variables
		int meshPosX = 0;
		int meshPosY = 0;

		int meshTextRow = 0;
		int meshTextCol = 0;

		// Spirte Animation
		int meshSpriteRow = 0;
		int meshSpriteCol = 0;

		// Tile sheet
		int meshTileRow = 0;
		int meshTileCol = 0;

		string directory = "";
		string meshType = "";

		for (vector<Attribute>::iterator attri = branch->attributes.begin(); attri != branch->attributes.end(); ++attri)
		{
			Attribute tempAttri = *attri;
			string attriName = tempAttri.name;
			string attriValue = tempAttri.value;

			if (attriName == "ColorValue")
			{
				Vector3 tempColor;

				stringToVector(attriValue, tempColor);

				meshColor.Set(tempColor.x, tempColor.y, tempColor.z);
			}

			if (attriName == "ColorName")
			{
				meshColor = retrieveColor(attriValue);
			}

			else if (attriName == "Type")
			{
				meshType = attriValue;
			}

			else if (attriName == "Directory")
			{
				directory = attriValue;
			}

			else if (attriName == "SpriteRow")
			{
				meshSpriteRow = stoi(attriValue);
			}

			else if (attriName == "SpriteCol")
			{
				meshSpriteCol = stoi(attriValue);
			}

			else if (attriName == "TextRow")
			{
				meshTextRow = stoi(attriValue);
			}

			else if (attriName == "TextCol")
			{
				meshTextCol = stoi(attriValue);
			}

			else if (attriName == "PosX")
			{
				meshPosX = stoi(attriValue);
			}

			else if (attriName == "PosY")
			{
				meshPosY = stoi(attriValue);
			}

			else if (attriName == "TileRow")
			{
				meshTileRow = stoi(attriValue);
			}

			else if (attriName == "TileCol")
			{
				meshTileCol = stoi(attriValue);
			}

			else if (attriName == "Texture")
			{
				textureID = LoadTGA(attriValue.c_str());
			}

			else
			{
				for (int k = 0; k < MAX_VAR; ++k)
				{
					if (attriName == meshVarNames[k])
					{
						meshVar[k] = stof(attriValue);
						break;
					}
				}
			}
		}

		// process data, generate mesh using meshbuilder
		Mesh* mesh = NULL;

		if (meshType == "Quad")
		{
			mesh = MeshBuilder::GenerateQuad(meshName, meshColor, meshVar[VAR_LENGTH], meshVar[VAR_WIDTH]);
		}

		else if (meshType == "Cube")
		{
			mesh = MeshBuilder::GenerateCube(meshName, meshColor, meshVar[VAR_LENGTH]);
		}

		else if (meshType == "Circle")
		{
			mesh = MeshBuilder::GenerateCircle(meshName, meshColor, (unsigned)meshVar[VAR_SLICES], meshVar[VAR_RADIUS]);
		}

		else if (meshType == "DebugQuad")
		{
			mesh = MeshBuilder::GenerateDebugQuad(meshName, meshColor, meshVar[VAR_LENGTH]);
		}

		else if (meshType == "DebugCircle")
		{
			mesh = MeshBuilder::GenerateDebugCircle(meshName, meshColor, (unsigned)meshVar[VAR_SLICES], meshVar[VAR_RADIUS]);
		}

		else if (meshType == "Sphere")
		{
			mesh = MeshBuilder::GenerateSphere(meshName, meshColor, (unsigned)meshVar[VAR_STACKS], (unsigned)meshVar[VAR_SLICES], meshVar[VAR_RADIUS]);
		}

		else if (meshType == "Obj")
		{
			mesh = MeshBuilder::GenerateOBJ(meshName, directory);
		}

		else if (meshType == "Text")
		{
			mesh = MeshBuilder::GenerateText(meshName, meshTextRow, meshTextCol);
		}

		else if (meshType == "2D")
		{
			mesh = MeshBuilder::Generate2DMesh(meshName, meshColor, (int)meshVar[VAR_WIDTH], (int)meshVar[VAR_HEIGHT]);
		}

		else if (meshType == "SpriteAnimation")
		{
			mesh = MeshBuilder::GenerateSpriteAnimation(meshName, meshSpriteRow, meshSpriteCol);

			SpriteAnimation *sa = dynamic_cast<SpriteAnimation*>(mesh);

			Branch tempBranch = *branch;
			// handle animations variables
			for (vector<Branch>::iterator childbranch = tempBranch.childBranches.begin(); childbranch != tempBranch.childBranches.end(); ++childbranch)
			{
				int id = 0;
				int startFrame = 0;
				int endFrame = 0;
				bool repeat = false;
				bool pause = false;
				float animationTime = 0.f;

				for (vector<Attribute>::iterator childAttri = childbranch->attributes.begin(); childAttri != childbranch->attributes.end(); ++childAttri)
				{
					Attribute tempAttri = *childAttri;
					string attriName = tempAttri.name;
					string attriValue = tempAttri.value;

					if (attriName == "ID")
					{
						id = stoi(attriValue);
					}

					else if (attriName == "StartFrame")
					{
						startFrame = stoi(attriValue);
					}

					else if (attriName == "EndFrame")
					{
						endFrame = stoi(attriValue);
					}

					else if (attriName == "Repeat")
					{
						stringToBool(attriValue, repeat);
					}

					else if (attriName == "Pause")
					{
						stringToBool(attriValue, pause);
					}

					else if (attriName == "AnimationTime")
					{
						animationTime = stof(attriValue);
					}
				}

				if (sa)
				{
					Animation* anime = new Animation();
					anime->Set(id, startFrame, endFrame, repeat, pause, animationTime);
					sa->animations.push_back(anime);
				}
			}

			//sort (sa->animations.begin(), sa->animations.end());
		}

		else if (meshType == "TileSheet")
		{
			mesh = MeshBuilder::GenerateTileSheet(meshName, meshTileRow, meshTileCol);
		}

		// push back mesh
		if (mesh != NULL)
		{
			addMesh(branch->branchName, mesh);

			if (textureID != NULL)
			{
				mesh->textureID = textureID;
			}
		}
	}
}

void ResourcePool::processTexture(string config)
{
}

void ResourcePool::processColor(string config)
{
}

void ResourcePool::processShader(string config)
{
}

bool ResourcePool::addMesh(string meshName, Mesh* mesh)
{
	map<string, Mesh*>::iterator it = meshContainer.find(meshName);

	// If a mesh of the same name is found
	if (it != meshContainer.end())
	{
		return false;
	}

	else
	{
		meshContainer.insert(std::pair<string, Mesh*>(meshName, mesh));

		return true;
	}
}

Mesh* ResourcePool::retrieveMesh(string resourceName)
{
	map<string, Mesh*>::iterator it = meshContainer.find(resourceName);

	if (it != meshContainer.end())
	{
		return it->second;
	}

	return NULL;
}

bool ResourcePool::addTexture(string textureName, string directory)
{
	map<string, string>::iterator it = textureContainer.find(textureName);

	// If a mesh of the same name is found
	if (it != textureContainer.end())
	{
		return false;
	}

	else
	{
		textureContainer.insert(std::pair<string, string>(textureName, directory));

		return true;
	}
}

string ResourcePool::retrieveTexture(string textureName)
{
	map<string, string>::iterator it = textureContainer.find(textureName);

	if (it != textureContainer.end())
	{
		return it->second;
	}

	return NULL;
}

bool ResourcePool::addColor(string colorName, Color color)
{
	map<string, Color>::iterator it = colorContainer.find(colorName);

	// If a mesh of the same name is found
	if (it != colorContainer.end())
	{
		return false;
	}

	else
	{
		colorContainer.insert(std::pair<string, Color>(colorName, color));

		return true;
	}
}

Color ResourcePool::retrieveColor(string colorName)
{
	map<string, Color>::iterator it = colorContainer.find(colorName);

	if (it != colorContainer.end())
	{
		return it->second;
	}

	return NULL;
}

bool ResourcePool::addShader(string shaderName, SHADER shader)
{
	map<string, SHADER>::iterator it = shaderContainer.find(shaderName);

	// If a mesh of the same name is found
	if (it != shaderContainer.end())
	{
		return false;
	}

	else
	{
		shaderContainer.insert(std::pair<string, SHADER>(shaderName, shader));

		return true;
	}
}

SHADER ResourcePool::retrieveShader(string shaderName)
{
	map<string, SHADER>::iterator it = shaderContainer.find(shaderName);

	if (it != shaderContainer.end())
	{
		return it->second;
	}

	return SHADER();
}

void ResourcePool::cleanUp(void)
{
	for (map<string, Mesh*>::iterator it = meshContainer.begin(); it != meshContainer.end(); ++it)
	{
		delete it->second;
		meshContainer.erase(it);
	}
}