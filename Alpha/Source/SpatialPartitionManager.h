#ifndef SPATIAL_PARTITION_MANAGER
#define SPATIAL_PARTITION_MANAGER

#include <vector>

#include "Partition.h"
#include "Vector3.h"

using std::vector;

class SpatialPartitionManager
{
public:

	enum PARTITION_TYPE
	{
		PARTITION_2D,
		PARTITION_3D,
		PARTITION_DEFAULT,
	};

	SpatialPartitionManager();
	~SpatialPartitionManager();

	// 2D spatial partition
	bool Init(Vector2 minWorldDimension, Vector2 maxWorldDimension, Vector2 worldDivision, bool numPartitionBased = true, Mesh* mesh = NULL);

	// 3D spatial partition
	bool Init(Vector3 minWorldDimension, Vector3 maxWorldDimension, Vector3 worldDivision, bool numPartitionBased = true, Mesh* mesh = NULL);

	Vector3 getNumPartition(void);
	Vector3 getParitionDimension(void);

	Partition* getPartition(Vector3 index, bool positionBased = true);

	bool addNode(SceneNode* node, PARTITION_TYPE type = PARTITION_DEFAULT);
	bool removeNode(SceneNode* node);

	void Update(void);

	void CleanUp(void);

	vector<Partition*> partitions;
	PARTITION_TYPE type;

	int generatePartitionIndex(Vector3 index);
	int generatePartitionIndex(int x, int y, int z = 0);
private:
	Vector3 worldDimension;
	Vector3 partitionDimension;
	Vector3 numPartition;

	Vector3 minWorldDimension;
	Vector3 maxWorldDimension;
};

#endif