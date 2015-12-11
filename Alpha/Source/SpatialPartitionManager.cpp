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
	this->CleanUp();
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
				Vector3(minWorldDimension.x + i * partitionDimension.x, 
						minWorldDimension.y + j * partitionDimension.y),
				Vector3(minWorldDimension.x + (i + 1) * partitionDimension.x, 
						minWorldDimension.y + (j + 1) * partitionDimension.y), 
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
					Vector3(minWorldDimension.x + i * partitionDimension.x,
							minWorldDimension.y + j * partitionDimension.y,
							minWorldDimension.z + k * partitionDimension.z),

					Vector3(minWorldDimension.x + (i + 1) * partitionDimension.x, 
							minWorldDimension.y + (j + 1) * partitionDimension.y, 
							minWorldDimension.z + (k + 1) * partitionDimension.z),
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

		partitionIndex = generatePartitionIndex(xPart, yPart);

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

		partitionIndex = generatePartitionIndex(xPart, yPart, zPart);

		break;
	default:
		break;
	}

	return partitions[partitionIndex];
}

bool SpatialPartitionManager::addNode(SceneNode* node, SpatialPartitionManager::PARTITION_TYPE type)
{
	Vector3 nodeBox;
	Vector3 boxMidpoint;

	// only add the node if it has a body (gameObject)
	if (node->GetGameObject() != NULL)
	{
		switch (type)
		{
		case SpatialPartitionManager::PARTITION_2D:

			break;
		case SpatialPartitionManager::PARTITION_3D:
		{
			nodeBox.Set(node->GetGameObject()->getHitbox().getLength() / 2,
				node->GetGameObject()->getHitbox().getHeight() / 2,
				node->GetGameObject()->getHitbox().getDepth() / 2);

			SceneNode* tempNode = node;
			boxMidpoint = node->GetGameObject()->getPosition();

			while (tempNode->parentNode != NULL && tempNode->parentNode->GetGameObject() != NULL)
			{
				boxMidpoint += tempNode->GetParentNode()->GetGameObject()->getPosition();
				tempNode = tempNode->GetParentNode();
			}

			// calculate the index which the obj is in the world
			Vector3 topLeftBack, topLeftFront;
			Vector3 topRightBack, topRightFront;
			Vector3 bottomLeftBack, bottomLeftFront;
			Vector3 bottomRightBack, bottomRightFront;

			unsigned partitionIndex = 0;

			topLeftBack.Set((boxMidpoint.x - nodeBox.x - minWorldDimension.x) / partitionDimension.x,
							(boxMidpoint.y + nodeBox.y - minWorldDimension.y) / partitionDimension.y,
							(boxMidpoint.z - nodeBox.z - minWorldDimension.z) / partitionDimension.z);

			topLeftFront.Set((boxMidpoint.x - nodeBox.x - minWorldDimension.x) / partitionDimension.x,
							 (boxMidpoint.y + nodeBox.y - minWorldDimension.y) / partitionDimension.y,
							 (boxMidpoint.z + nodeBox.z - minWorldDimension.z) / partitionDimension.z);

			topRightBack.Set((boxMidpoint.x + nodeBox.x - minWorldDimension.x) / partitionDimension.x,
							 (boxMidpoint.y + nodeBox.y - minWorldDimension.y) / partitionDimension.y,
							 (boxMidpoint.z - nodeBox.z - minWorldDimension.z) / partitionDimension.z);

			topRightFront.Set((boxMidpoint.x + nodeBox.x - minWorldDimension.x) / partitionDimension.x,
							  (boxMidpoint.y + nodeBox.y - minWorldDimension.y) / partitionDimension.y,
							  (boxMidpoint.z + nodeBox.z - minWorldDimension.z) / partitionDimension.z);

			bottomLeftBack.Set((boxMidpoint.x - nodeBox.x - minWorldDimension.x) / partitionDimension.x,
								(boxMidpoint.y - nodeBox.y - minWorldDimension.y) / partitionDimension.y,
								(boxMidpoint.z - nodeBox.z - minWorldDimension.z) / partitionDimension.z);

			bottomLeftFront.Set((boxMidpoint.x - nodeBox.x - minWorldDimension.x) / partitionDimension.x,
								(boxMidpoint.y - nodeBox.y - minWorldDimension.y) / partitionDimension.y,
								(boxMidpoint.z + nodeBox.z - minWorldDimension.z) / partitionDimension.z);

			bottomRightBack.Set((boxMidpoint.x + nodeBox.x - minWorldDimension.x) / partitionDimension.x,
								(boxMidpoint.y - nodeBox.y - minWorldDimension.y) / partitionDimension.y,
								(boxMidpoint.z - nodeBox.z - minWorldDimension.z) / partitionDimension.z);

			bottomRightFront.Set((boxMidpoint.x + nodeBox.x - minWorldDimension.x) / partitionDimension.x,
							 	 (boxMidpoint.y - nodeBox.y - minWorldDimension.y) / partitionDimension.y,
								 (boxMidpoint.z + nodeBox.z - minWorldDimension.z) / partitionDimension.z);

			// check top left back
			partitionIndex = generatePartitionIndex(topLeftBack);
			if (partitionIndex > 0 && partitionIndex < partitions.size())
			{
				partitions[partitionIndex]->addNode(node);
			}

			// check top left front
			partitionIndex = generatePartitionIndex(topLeftFront);
			if (partitionIndex > 0 && partitionIndex < partitions.size())
			{
				partitions[partitionIndex]->addNode(node);
			}

			// check top right back
			partitionIndex = generatePartitionIndex(topRightBack);
			if (partitionIndex > 0 && partitionIndex < partitions.size())
			{
				partitions[partitionIndex]->addNode(node);
			}

			// check top right front
			partitionIndex = generatePartitionIndex(topRightFront);
			if (partitionIndex > 0 && partitionIndex < partitions.size())
			{
				partitions[partitionIndex]->addNode(node);
			}

			// check bottom left back
			partitionIndex = generatePartitionIndex(bottomLeftBack);
			if (partitionIndex > 0 && partitionIndex < partitions.size())
			{
				partitions[partitionIndex]->addNode(node);
			}

			// check bottom left front
			partitionIndex = generatePartitionIndex(bottomLeftFront);
			if (partitionIndex > 0 && partitionIndex < partitions.size())
			{
				partitions[partitionIndex]->addNode(node);
			}

			// check bottom right back
			partitionIndex = generatePartitionIndex(bottomRightBack);
			if (partitionIndex > 0 && partitionIndex < partitions.size())
			{
				partitions[partitionIndex]->addNode(node);
			}

			// check bottom right front
			partitionIndex = generatePartitionIndex(bottomRightFront);
			if (partitionIndex > 0 && partitionIndex < partitions.size())
			{
				partitions[partitionIndex]->addNode(node);
			}
		}
			break;
		default:
			break;
		}
	}

	// do a reursive
	for (unsigned i = 0; i < node->childNodes.size(); ++i)
	{
		this->addNode(node->childNodes[i], type);
	}

	return true;
}

bool SpatialPartitionManager::removeNode(SceneNode* node)
{
	// do a reursive for child first
	for (unsigned i = 0; i < node->childNodes.size(); ++i)
	{
		this->removeNode(node->childNodes[i]);
	}

	// only add the node if it has a body (gameObject)
	if (node->GetGameObject() != NULL)
	{
		switch (type)
		{
		case SpatialPartitionManager::PARTITION_2D:

			break;
		case SpatialPartitionManager::PARTITION_3D:
		{
			unsigned partitionIndex = 0;
			for (int k = 0; k < numPartition.z; ++k)
			{
				for (int j = 0; j < numPartition.y; ++j)
				{
					for (int i = 0; i < numPartition.x; ++i)
					{
						partitionIndex = generatePartitionIndex(i, j, k);

						if (partitionIndex > 0 && partitionIndex < partitions.size() && partitions[partitionIndex]->nodes.size() > 0)
						{
							partitions[partitionIndex]->removeNode(node);
						}
					}
				}
			}
		}
			break;
		default:
			break;
		}
	}

	return true;
}

void SpatialPartitionManager::Update(void)
{
	int id = 0;

	// clear all the nodes in all the partitions
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
					partitions[id]->Update();
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
						partitions[id]->Update();
					}
				}
			}
		}
		break;

	default:
		break;
	}
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
}

int SpatialPartitionManager::generatePartitionIndex(Vector3 index)
{
	return (int)index.x + (int)index.y * (int)numPartition.x + (int)index.z * (int)numPartition.x * (int)numPartition.y;
}

int SpatialPartitionManager::generatePartitionIndex(int x, int y, int z)
{
	return x + y * (int)numPartition.x + z * (int)numPartition.x * (int)numPartition.y;
}