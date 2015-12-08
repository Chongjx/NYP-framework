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
	void Init(Vector3 dimension, Vector3 minPosition, Vector3 maxPosition, int id, Mesh* mesh);

	void setMesh(Mesh* mesh);
	void addNode(SceneNode* node);
	void removeNode(SceneNode* node);
	vector<SceneNode*> getNodes(void);

	Mesh* getMesh(void);
	Vector3 getDimension(void);
	Vector3 getMinPosition(void);
	Vector3 getMaxPosition(void);

	void deleteObjects(void);

	void Render(void);
	void RenderObjects(const int resolution);

	void Update(void);

	void CleanUp(void);

	vector<SceneNode*> nodes;

private:
	Vector3 dimension;
	Vector3 minPosition;
	Vector3 maxPosition;
	int id;

	Mesh* partitionMesh;
};

#endif