#include "SpatialPartitionManager.h"

SpatialPartitionManager::SpatialPartitionManager() :
type(PARTITION_DEFAULT),
worldDimension(1, 1, 1),
partitionDimension(1, 1, 1),
numPartition(1, 1, 1)
{
	// Ensure the partitions clear before start
	partitions.clear();
}

SpatialPartitionManager::~SpatialPartitionManager()
{
	int id = 0;

	// delete all partitions based on its type
	switch (type)
	{
	case SpatialPartitionManager::PARTITION_2D:
		for (int j = 0; j < numPartition.y; ++j)
		{
			for (int i = 0; i < numPartition.x; ++i)
			{
				id = i + j * (int)numPartition.x;

				if (partitions[id])
				{
					partitions[id]->CleanUp();
					delete partitions[id];
					partitions[id] = NULL;
				}
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
					id = i + j * (int)numPartition.x + k * (int)numPartition.x * (int)numPartition.y;

					if (partitions[id])
					{
						partitions[id]->CleanUp();
						delete partitions[id];
						partitions[id] = NULL;
					}
 				}
			}
		}
		break;

	default:
		break;
	}

	partitions.clear();
}

// bool numPartitionBased
// true if worldDivision is num of partition for the world
bool SpatialPartitionManager::Init(Vector2 minWorldDimension, Vector2 maxWorldDimension, Vector2 worldDivision, bool numPartitionBased, Mesh* mesh)
{
	worldDimension.Set(maxWorldDimension.x - minWorldDimension.x, maxWorldDimension.y - minWorldDimension.y);

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

	type = PARTITION_2D;

	int id = 0;
	for (int j = 0; j < numPartition.y; ++j)
	{
		for (int i = 0; i < numPartition.x; ++i)
		{
			id = i + j * (int)numPartition.x;

			Partition* partition = new Partition();
			partition->Init(partitionDimension, id);

			if (mesh)
			{
				partition->setMesh(mesh);
			}
			partitions.push_back(partition);
		}
	}

	return true;
}

// 3D spatial partition
bool SpatialPartitionManager::Init(Vector3 minWorldDimension, Vector3 maxWorldDimension, Vector3 worldDivision, bool numPartitionBased, Mesh* mesh)
{
	worldDimension = maxWorldDimension - minWorldDimension;

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

	type = PARTITION_3D;

	int id = 0;
	for (int k = 0; k < numPartition.z; ++k)
	{
		for (int j = 0; j < numPartition.y; ++j)
		{
			for (int i = 0; i < numPartition.x; ++i)
			{
				id = i + j * (int)numPartition.x + k * (int)numPartition.x * (int)numPartition.y;

				Partition* partition = new Partition();
				partition->Init(partitionDimension, id);

				if (mesh)
				{
					partition->setMesh(mesh);
				}
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

Partition* SpatialPartitionManager::getPartition(Vector3 index, bool positionBased)
{
	switch (type)
	{
	case SpatialPartitionManager::PARTITION_2D:
		if (positionBased)
		{

		}

		else
		{

		}
		break;
	case SpatialPartitionManager::PARTITION_3D:
		if (positionBased)
		{

		}

		else
		{

		}
		break;
	default:
		break;
	}

	return partitions[0];
}

bool SpatialPartitionManager::addNode(SceneNode* node)
{
	switch (type)
	{
	case SpatialPartitionManager::PARTITION_2D:
		break;
	case SpatialPartitionManager::PARTITION_3D:
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
	default:
		break;
	}

	return true;
}

void SpatialPartitionManager::Update(void)
{
}