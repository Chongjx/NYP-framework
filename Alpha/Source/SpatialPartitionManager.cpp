#include "SpatialPartitionManager.h"

SpatialPartitionManager::SpatialPartitionManager() :
type(PARTITION_DEFAULT),
worldDimension(1, 1, 1),
maxWorldDimension(1, 1, 1),
minWorldDimension(1, 1, 1),
partitionDimension(1, 1, 1),
numPartition(1, 1, 1)
{
	// Ensure the partitions clear before start
	partitions.clear();
}

SpatialPartitionManager::~SpatialPartitionManager()
{
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
	this->minWorldDimension.Set(minWorldDimension.x, minWorldDimension.y);
	this->maxWorldDimension.Set(maxWorldDimension.x, maxWorldDimension.y);

	int id = 0;
	for (int j = 0; j < numPartition.y; ++j)
	{
		for (int i = 0; i < numPartition.x; ++i)
		{
			id = i + j * (int)numPartition.x;

			Partition* partition = new Partition();
			partition->Init(partitionDimension,
				Vector3(minWorldDimension.x + i * partitionDimension.x, minWorldDimension.y + j * partitionDimension.y),
				Vector3(minWorldDimension.x + (i + 1) * partitionDimension.x, minWorldDimension.y + (j + 1) * partitionDimension.y),
				id,
				mesh);

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
	this->minWorldDimension = minWorldDimension;
	this->maxWorldDimension = maxWorldDimension;

	int id = 0;
	for (int k = 0; k < numPartition.z; ++k)
	{
		for (int j = 0; j < numPartition.y; ++j)
		{
			for (int i = 0; i < numPartition.x; ++i)
			{
				id = i + j * (int)numPartition.x + k * (int)numPartition.x * (int)numPartition.y;

				Partition* partition = new Partition();
				partition->Init(partitionDimension, 
					Vector3(minWorldDimension.x + i * partitionDimension.x, minWorldDimension.y + j * partitionDimension.y, minWorldDimension.z + k * partitionDimension.z),
					Vector3(minWorldDimension.x + (i + 1) * partitionDimension.x, minWorldDimension.y + (j + 1) * partitionDimension.y, minWorldDimension.z + (k + 1) * partitionDimension.z),
					id, 
					mesh);

				partitions.push_back(partition);
			}
		}
	}

	return true;
}

Vector3 SpatialPartitionManager::getNumPartition(void)
{
	return numPartition;
}

Vector3 SpatialPartitionManager::getParitionDimension(void)
{
	return partitionDimension;
}

Partition* SpatialPartitionManager::getPartition(Vector3 index, bool positionBased)
{
	// check position if its within world
	if (index.x < minWorldDimension.x || index.x > maxWorldDimension.x ||
		index.y < minWorldDimension.y || index.y > maxWorldDimension.y ||
		index.z < minWorldDimension.z || index.z > maxWorldDimension.z)
	{
		return NULL;
	}

	int xPart, yPart, zPart, partitionIndex;

	xPart = yPart = zPart = partitionIndex = 0;

	switch (type)
	{
	case SpatialPartitionManager::PARTITION_2D:
		// if given a point on the world, determine the x,y value
		if (positionBased)
		{
			Vector3 worldToParition = index - minWorldDimension;

			xPart = (int)worldToParition.x / (int)partitionDimension.x;
			yPart = (int)worldToParition.y / (int)partitionDimension.y;
		}

		else
		{
			xPart = (int)index.x;
			yPart = (int)index.y;
		}

		partitionIndex = xPart + yPart * (int)numPartition.x;

		break;
	case SpatialPartitionManager::PARTITION_3D:
		if (positionBased)
		{
			Vector3 worldToParition = index - minWorldDimension;

			xPart = (int)worldToParition.x / (int)partitionDimension.x;
			yPart = (int)worldToParition.y / (int)partitionDimension.y;
			zPart = (int)worldToParition.z / (int)partitionDimension.z;
		}

		else
		{
			xPart = (int)index.x;
			yPart = (int)index.y;
			zPart = (int)index.z;
		}

		partitionIndex = xPart + yPart * (int)numPartition.x + zPart * (int)numPartition.x * (int)numPartition.y;

		break;
	default:
		break;
	}

	return partitions[partitionIndex];
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

void SpatialPartitionManager::CleanUp(void)
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