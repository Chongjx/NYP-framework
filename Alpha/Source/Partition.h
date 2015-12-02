#ifndef PARTITION_H
#define PARTITION_H

#include <vector>
#include "SceneNode.h"

using std::vector;

class Partition
{
public:
	Partition();
	~Partition();

	void Init(Vector3 dimension, int id);
	void Init(Vector3 dimension, int id, Mesh* mesh);

	void setMesh(Mesh* mesh);
	void addNode(SceneNode* node);
	vector<SceneNode*> getNodes(void);

	Mesh* getMesh(void);

	void deleteObjects(void);

	void Render(void);
	void RenderObjects(const int resolution);

	void Update(void);

	void CleanUp(void);

private:
	Vector3 dimension;
	int id;

	Mesh* partitionMesh;
	vector<SceneNode*> nodes;

};

#endif