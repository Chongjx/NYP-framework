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

	int getNumPartitionWidth(void);
	int getNumPartitionHeight(void);
	int getNumPartitionDepth(void);

	Partition* getPartition(Vector3 index, bool trueIndex = true);

	bool addNode(SceneNode* node);
	bool removeNode(SceneNode* node);

	void Update(void);

private:
	PARTITION_TYPE type;
	vector<Partition*> partitions;
	Vector3 worldDimension;
	Vector3 partitionDimension;
	Vector3 numPartition;
};

#endif