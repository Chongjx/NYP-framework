#include "SpatialPartitionManager.h"

SpatialPartitionManager::SpatialPartitionManager() :
type(PARTITION_DEFAULT),
worldDimension(1, 1, 1),
partitionDimension(1, 1, 1),
numPartition(1, 1, 1)
{
	partitions.clear();
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
		for (int k = 0; k < numPartition.z; ++k)
		{
			for (int j = 0; j < numPartition.y; ++j)
			{
				for (int i = 0; i < numPartition.x; ++i)
				{
					//partitions()
				}
			}
		}
		break;

	case SpatialPartitionManager::PARTITION_DEFAULT:
		break;

	default:
		break;
	}
}

// bool numPartitionBased
// true if worldDivision is num of partition for the world
bool SpatialPartitionManager::Init(Vector2 minWorldDimension, Vector2 maxWorldDimension, Vector2 worldDivision, bool numPartitionBased)
{
	Vector2 worldDimension = maxWorldDimension - minWorldDimension;

	// ensure the data are not 0
	if (worldDimension.IsZero() || worldDivision.IsZero())
	{
		return false;
	}

	else
	{
		// divide the world base on the number of partition given
		if (numPartitionBased)
		{
			numPartition.Set(worldDivision.x, worldDivision.y);
			partitionDimension.Set(worldDimension.x / worldDivision.x, worldDimension.y / worldDivision.y);
		}

		else
		{
			partitionDimension.Set(worldDivision.x, worldDivision.y);
			numPartition.Set(worldDimension.x / partitionDimension.x, worldDimension.y / partitionDimension.y);
		}
	}

	for (int j = 0; j < numPartition.y; ++j)
	{
		for (int i = 0; i < numPartition.x; ++i)
		{
			int id = i + j * numPartition.x;

			Partition* partition = new Partition();
			partition->Init(partitionDimension, id++);
			partitions.push_back(partition);
		}
	}

	return true;
}

// 3D spatial partition
bool SpatialPartitionManager::Init(Vector3 minWorldDimension, Vector3 maxWorldDimension, Vector3 worldDivision, bool numPartitionBased)
{
	Vector3 worldDimension = maxWorldDimension - minWorldDimension;

	// ensure the data are not 0
	if (worldDimension.IsZero() || worldDivision.IsZero())
	{
		return false;
	}

	else
	{
		// divide the world base on the number of partitons given
		if (numPartitionBased)
		{
			numPartition = worldDivision;
			partitionDimension.Set(worldDimension.x / worldDivision.x, worldDimension.y / worldDivision.y, worldDimension.z / worldDivision.z);
		}

		else
		{
			partitionDimension = worldDivision;
			numPartition.Set(worldDimension.x / partitionDimension.x, worldDimension.y / partitionDimension.y, worldDimension.z / partitionDimension.z);
		}
	}

	for (int k = 0; k < numPartition.z; ++k)
	{
		for (int j = 0; j < numPartition.y; ++j)
		{
			for (int i = 0; i < numPartition.x; ++i)
			{
				int id = i + j * numPartition.x + k * numPartition.x * numPartition.y;

				Partition* partition = new Partition();
				partition->Init(partitionDimension, id++);
				partitions.push_back(partition);
			}
		}
	}

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