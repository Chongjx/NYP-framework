#include "Application.h"
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
	soundPool = new SoundPool();
	soundPool->Init();
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
					soundPool->processSound(attriValue);
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

		unsigned textureID = 0;

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

			else if (attriName == "Texture")
			{ 
				textureID = this->retrieveTexture(attriValue);
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

		if (meshType == "Axis")
		{
			mesh = MeshBuilder::GenerateAxes(meshName, meshVar[VAR_LENGTH], meshVar[VAR_HEIGHT], meshVar[VAR_WIDTH]);
		}

		else if (meshType == "Ray")
		{
			mesh = MeshBuilder::GenerateRay(meshName, meshVar[VAR_LENGTH]);
		}

		else if (meshType == "Quad")
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

		else if (meshType == "DebugCube")
		{
			mesh = MeshBuilder::GenerateDebugCube(meshName, meshColor, meshVar[VAR_LENGTH]);
		}

		else if (meshType == "Sphere")
		{
			mesh = MeshBuilder::GenerateSphere(meshName, meshColor, (unsigned)meshVar[VAR_STACKS], (unsigned)meshVar[VAR_SLICES], meshVar[VAR_RADIUS]);
		}

		else if (meshType == "Skyplane")
		{
			mesh = MeshBuilder::GenerateSkyPlane(meshName, meshColor, (unsigned)meshVar[VAR_SLICES], (float)meshVar[VAR_INNER_RADIUS], (float)meshVar[VAR_OUTER_RADIUS], (float)meshTileRow, (float)meshTileCol);
		}

		else if (meshType == "Terrain")
		{
			HEIGHTMAP tempHeightmap;
			tempHeightmap.name = meshName;
			mesh = MeshBuilder::GenerateTerrain(meshName, directory, tempHeightmap.heightMap);

			if (this->addHeightmap(tempHeightmap.name, tempHeightmap))
			{
				std::cout << "Successfully added new heightmap!" << std::endl;
			}
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
			if (textureID != 0)
			{
				mesh->textureID = textureID;
			}

			if (addMesh(branch->branchName, mesh))
			{
				std::cout << "Successfully added new mesh!" << std::endl;
			}
		}
	}
}

void ResourcePool::processTexture(string config)
{
	Branch textureBranch = TextTree::FileToRead(config);

	for (vector<Branch>::iterator branch = textureBranch.childBranches.begin(); branch != textureBranch.childBranches.end(); ++branch)
	{
		string textureName = branch->branchName;
		for (vector<Attribute>::iterator attri = branch->attributes.begin(); attri != branch->attributes.end(); ++attri)
		{
			Attribute tempAttri = *attri;
			string attriName = tempAttri.name;
			string attriValue = tempAttri.value;

			if (attriName == "Directory")
			{
				if (this->addTexture(textureName, attriValue))
				{
					std::cout << "Successfully added new texture!" << std::endl;
				}
			}
		}
	}
}

void ResourcePool::processColor(string config)
{
	Branch colorBranch = TextTree::FileToRead(config);
	// various colors needed for text

	for (vector<Branch>::iterator branch = colorBranch.childBranches.begin(); branch != colorBranch.childBranches.end(); ++branch)
	{
		Color tempColor;
		Vector3 colorValue;

		for (vector<Attribute>::iterator attri = branch->attributes.begin(); attri != branch->attributes.end(); ++attri)
		{
			Attribute tempAttri = *attri;
			string attriName = tempAttri.name;
			string attriValue = tempAttri.value;

			stringToVector(attriValue, colorValue);

			tempColor.Set(colorValue.x, colorValue.y, colorValue.z, branch->branchName);


			if (this->addColor(branch->branchName, tempColor))
			{
				std::cout << "Successfully added new color!" << std::endl;
			}
		}
	}
}

void ResourcePool::processShader(string config)
{
	Branch shaderBranch = TextTree::FileToRead(config);

	for (vector<Branch>::iterator branch = shaderBranch.childBranches.begin(); branch != shaderBranch.childBranches.end(); ++branch)
	{
		SHADER tempShader;

		for (vector<Attribute>::iterator attri = branch->attributes.begin(); attri != branch->attributes.end(); ++attri)
		{
			Attribute tempAttri = *attri;
			string attriName = tempAttri.name;
			string attriValue = tempAttri.value;

			if (tempAttri.name == "VertexShader")
			{
				tempShader.vertexShaderDirectory = tempAttri.value;
			}

			else if (tempAttri.name == "FragmentShader")
			{
				tempShader.fragmentShaderDirectory = tempAttri.value;
			}
		}

		tempShader.name = branch->branchName;

		if (this->addShader(tempShader.name, tempShader))
		{
			std::cout << "Successfully added new shader!" << std::endl;
		}
	}
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

	std::cout << "Unable to find mesh! Check your naming!" << std::endl;

	return NULL;
}

bool ResourcePool::addTexture(string textureName, string directory)
{
	map<string, unsigned>::iterator it = textureContainer.find(textureName);

	// If a mesh of the same name is found
	if (it != textureContainer.end())
	{
		return false;
	}

	else
	{
		textureContainer.insert(std::pair<string, unsigned>(textureName, LoadTGA(directory.c_str())));

		return true;
	}
}

unsigned ResourcePool::retrieveTexture(string textureName)
{
	map<string, unsigned>::iterator it = textureContainer.find(textureName);

	if (it != textureContainer.end())
	{
		return it->second;
	}

	std::cout << "Unable to find texture! Check your naming!" << std::endl;

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

	std::cout << "Unable to find color! Check your naming!" << std::endl;

	return Color(1, 1, 1);
}

Color ResourcePool::retrieveRandomColor()
{
	if (colorContainer.size() > 0)
	{
		auto it = colorContainer.begin();

		std::advance(it, Math::RandIntMinMax(0, colorContainer.size() - 1));

		return (*it).second;
	}

	return Color(1, 1, 1);
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

	std::cout << "Unable to find shader! Check your naming!" << std::endl;

	return SHADER();
}

bool ResourcePool::addHeightmap(string heightmapName, HEIGHTMAP heightmap)
{
	map<string, HEIGHTMAP>::iterator it = heightmapContainer.find(heightmapName);

	// If a mesh of the same name is found
	if (it != heightmapContainer.end())
	{
		return false;
	}

	else
	{
		heightmapContainer.insert(std::pair<string, HEIGHTMAP>(heightmapName, heightmap));

		return true;
	}
}

HEIGHTMAP ResourcePool::retrieveHeightmap(string heightmapName)
{
	map<string, HEIGHTMAP>::iterator it = heightmapContainer.find(heightmapName);

	if (it != heightmapContainer.end())
	{
		return it->second;
	}

	std::cout << "Unable to find heightmap! Check your naming!" << std::endl;

	return HEIGHTMAP();
}

void ResourcePool::cleanUp(void)
{
	map<string, Mesh*>::iterator it = meshContainer.begin();

	while (it != meshContainer.end())
	{
		if (it->second)
		{
			map<string, Mesh*>::iterator toErase = it;
			++it;
			meshContainer.erase(toErase);
		}

		else
		{
			++it;
		}
	}

	meshContainer.clear();
	textureContainer.clear();
	colorContainer.clear();
	shaderContainer.clear();
	heightmapContainer.clear();

	soundPool->cleanUp();
}