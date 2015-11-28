#ifndef SPATIAL_PARTITION_MANAGER
#define SPATIAL_PARTITION_MANAGER

#include "Partition.h"
#include "Vector3.h"

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
	bool Init(Vector2 minWorldDimension, Vector2 maxWorldDimension, Vector2 worldDivision, bool numPartitionBased);

	// 3D spatial partition
	bool Init(Vector3 minWorldDimension, Vector3 maxWorldDimension, Vector3 worldDivision, bool numPartitionBased);

	int getNumPartitionWidth(void);
	int getNumPartitionHeight(void);
	int getNumPartitionDepth(void);

	Partition getPartition(Vector3 index);

	void setPartitionMesh(Vector3 index, Mesh* partitionMesh);
	Mesh* getPartitionMesh(Vector3 index);

	bool addNode(SceneNode* node);
	bool removeNode(SceneNode* node);

	void Update(void);

private:
	PARTITION_TYPE type;
	Partition* partitions;
	Vector3 worldDimension;
	Vector3 partitionDimension;
	Vector3 numPartition;
};

#endif