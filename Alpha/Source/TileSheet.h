#ifndef TILE_SHEET_H
#define TILE_SHEET_H

#include "Mesh.h"
#include <vector>

using std::vector;

class TileSheet : public Mesh
{
public:
	TileSheet(const std::string &meshName);
	~TileSheet(void);

	virtual void Render();

	int m_currentTile;
};

#endif