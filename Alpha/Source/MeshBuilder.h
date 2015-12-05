#ifndef MESH_BUILDER_H
#define MESH_BUILDER_H

#include "Mesh.h"
#include "Vertex.h"
#include "SpriteAnimation.h"
#include "TileSheet.h"
/******************************************************************************/
/*!
		Class MeshBuilder:
\brief	Provides methods to generate mesh of different shapes
*/
/******************************************************************************/
class MeshBuilder
{
public:
	static Mesh* GenerateAxes(const std::string &meshName, float lengthX=0.0f, float lengthY=0.0f, float lengthZ=0.0f);
	static Mesh* GenerateRay(const std::string &meshName, float length = 1.f);
	static Mesh* GenerateQuad(const std::string &meshName, Color color, float length = 1.f);
	static Mesh* GenerateQuad(const std::string &meshName, Color color, float lengthX, float lengthY);
	static Mesh* GenerateCube(const std::string &meshName, Color color, float length = 1.f);
	static Mesh* GenerateRing(const std::string &meshName, Color color, unsigned numSlice, float outerR = 1.f, float innerR = 0.f);
	static Mesh* GenerateCircle(const std::string &meshName, Color color, unsigned numSlice, float radius = 1);
	static Mesh* GenerateSphere(const std::string &meshName, Color color, unsigned numStack, unsigned numSlice, float radius = 1.f);
	static Mesh* GenerateSkyPlane(const std::string & meshName, Color color, int slices, float PlanetRadius, float AtmosphereRadius, float hTile, float vTile);
	static Mesh* GenerateTerrain(const std::string & meshName, const std::string &file_path, std::vector<unsigned char> &heightMap);
	static Mesh* GenerateDebugQuad(const std::string &meshName, Color color, float length = 1.f);
	static Mesh* GenerateDebugCircle(const std::string &meshName, Color color, unsigned numSlice, float radius = 1.f);
	static Mesh* GenerateDebugCube(const std::string &meshName, Color color, float length = 1.f);
	static Mesh* GenerateCone(const std::string &meshName, Color color, unsigned numSlice, float radius, float height);
	static Mesh* GenerateOBJ(const std::string &meshName, const std::string &file_path);
	static Mesh* GenerateText(const std::string &meshName, unsigned row, unsigned col);
	static Mesh* Generate2DMesh(const std::string &meshName, Color color, int pos_x, int pos_y, int width, int height);
	static Mesh* Generate2DMesh(const std::string &meshName, Color color, int width, int height);
	static SpriteAnimation* GenerateSpriteAnimation(const std::string & meshName, unsigned numRow, unsigned numCol);
	static TileSheet* GenerateTileSheet(const std::string &meshName, unsigned numRow, unsigned numCol);
};

#endif