#include "SpatialPartitionManager.h"

SpatialPartitionManager::SpatialPartitionManager() :
type(PARTITION_DEFAULT),
partitions(NULL),
worldDimension(1, 1, 1),
partitionDimension(1, 1, 1),
numPartition(1, 1, 1)
{
}

SpatialPartitionManager::~SpatialPartitionManager()
{
	switch (type)
	{
	case SpatialPartitionManager::PARTITION_2D:
		for (int i = 0; i < numPartition.x; ++i)
		{
			for (int j = 0; j < numPartition.y; ++j)
			{
			}
		}
		break;
	case SpatialPartitionManager::PARTITION_3D:
		for (int i = 0; i < numPartition.x; ++i)
		{
			for (int j = 0; j < numPartition.y; ++j)
			{
				for (int k = 0; k < numPartition.z; ++k)
				{
				}
			}
		}
		break;
	case SpatialPartitionManager::PARTITION_DEFAULT:
		break;
	default:
		break;
	}

	delete[] partitions;
}

// bool numPartitionBased
// true if worldDivision is num of partition for the world
bool SpatialPartitionManager::Init(Vector2 minWorldDimension, Vector2 maxWorldDimension, Vector2 worldDivision, bool numPartitionBased)
{
	Vector2 worldDimension(maxWorldDimension.x - minWorldDimension.x, maxWorldDimension.y - minWorldDimension.y);

	// ensure the data are not 0
	if (!worldDimension.IsZero() && !worldDivision.IsZero())
	{

	}

	return true;
}

// 3D spatial partition
bool SpatialPartitionManager::Init(Vector3 minWorldDimension, Vector3 maxWorldDimension, Vector3 worldDivision, bool numPartitionBased)
{
	return true;
}

int SpatialPartitionManager::getNumPartitionWidth(void)
{
	return (int)this->numPartition.x;
}

int SpatialPartitionManager::getNumPartitionHeight(void)
{
	return (int)this->numPartition.y;
}

int SpatialPartitionManager::getNumPartitionDepth(void)
{
	return (int)this->numPartition.z;
}

Partition SpatialPartitionManager::getPartition(Vector3 index)
{
	switch (type)
	{
	case SpatialPartitionManager::PARTITION_2D:
		break;
	case SpatialPartitionManager::PARTITION_3D:
		break;
	case SpatialPartitionManager::PARTITION_DEFAULT:
		break;
	default:
		break;
	}

	return Partition();
}

void SpatialPartitionManager::setPartitionMesh(Vector3 index, Mesh* partitionMesh)
{
	switch (type)
	{
	case SpatialPartitionManager::PARTITION_2D:
		break;
	case SpatialPartitionManager::PARTITION_3D:
		break;
	case SpatialPartitionManager::PARTITION_DEFAULT:
		break;
	default:
		break;
	}
}

Mesh* SpatialPartitionManager::getPartitionMesh(Vector3 index)
{
	switch (type)
	{
	case SpatialPartitionManager::PARTITION_2D:
		break;
	case SpatialPartitionManager::PARTITION_3D:
		break;
	case SpatialPartitionManager::PARTITION_DEFAULT:
		break;
	default:
		break;
	}

	return NULL;
}

bool SpatialPartitionManager::addNode(SceneNode* node)
{
	switch (type)
	{
	case SpatialPartitionManager::PARTITION_2D:
		break;
	case SpatialPartitionManager::PARTITION_3D:
		break;
	case SpatialPartitionManager::PARTITION_DEFAULT:
		break;
	default:
		break;
	}

	return true;
}

bool SpatialPartitionManager::removeNode(SceneNode* node)
{
	switch (type)
	{
	case SpatialPartitionManager::PARTITION_2D:
		break;
	case SpatialPartitionManager::PARTITION_3D:
		break;
	case SpatialPartitionManager::PARTITION_DEFAULT:
		break;
	default:
		break;
	}

	return true;
}

void SpatialPartitionManager::Update(void)
{
}