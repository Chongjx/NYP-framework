#include <iostream>
#include <fstream>
#include <cmath>
#include "LoadHmap.h"
#include "Vector3.h"

float barryCentric(Vector3 p1, Vector3 p2, Vector3 p3, float x, float z)
{
	float det = (p2.z - p3.z) * (p1.x - p3.x) + (p3.x - p2.x) * (p1.z - p3.z);
	float l1 = ((p2.z - p3.z) * (x - p3.x) + (p3.x - p2.x) * (z - p3.z)) / det;
	float l2 = ((p3.z - p1.z) * (x - p3.x) + (p1.x - p3.x) * (z - p3.z)) / det;
	float l3 = 1.0f - l1 - l2;
	return l1 * p1.y + l2 * p2.y + l3 * p3.y;
}

bool LoadHeightMap(const char *file_path, std::vector<unsigned char> &heightMap)
{
	std::ifstream fileStream(file_path, std::ios::binary);
	if(!fileStream.is_open())
	{
		std::cout << "Impossible to open " << file_path << ". Are you in the right directory ?\n";
		return false;
	}

    fileStream.seekg(0, std::ios::end);
    std::streampos fsize = (unsigned)fileStream.tellg();
	
	fileStream.seekg(0, std::ios::beg);
	heightMap.resize((unsigned)fsize);
	fileStream.read((char *)&heightMap[0], fsize);
	
	fileStream.close();

	for(int z = 0; z < 256; ++z)
	{
		for(int x = 0; x < 256; ++x)
		{
			heights[x][z] = (float)heightMap[z * 256 + x];
		}
	}

	return true;
}

float ReadHeightMap(std::vector<unsigned char> &heightMap, float x, float z)
{
	if (x > 0.5f || x < -0.5f || z > 0.5f || z < -0.5f)
	{
		return 0.f;
	}

	unsigned terrainSize = (unsigned)sqrt((double)heightMap.size());

	float gridSquareSize = 1.f / (terrainSize);

	unsigned gridX = (x + 0.5f) / gridSquareSize;
	unsigned gridZ = (z + 0.5f) / gridSquareSize;

	float xCoord = fmod((x + 0.5f), gridSquareSize) / gridSquareSize;
	float zCoord = fmod((z + 0.5f), gridSquareSize) / gridSquareSize;

	float answer = 0.f;

	// find the triangle which the player lies on
	if (xCoord <= 1 - zCoord)
	{
		answer = barryCentric(Vector3(0, heights[gridX][gridZ], 0),
			Vector3(1, heights[gridX + 1][gridZ], 0),
			Vector3(0, heights[gridX][gridZ + 1], 1),
			xCoord, zCoord);
	}

	else
	{
		answer = barryCentric(Vector3(1, heights[gridX + 1][gridZ], 0),
			Vector3(1, heights[gridX + 1][gridZ + 1], 1),
			Vector3(0, heights[gridX][gridZ + 1], 1),
			xCoord, zCoord);
	}

	return answer / 256.f;
}