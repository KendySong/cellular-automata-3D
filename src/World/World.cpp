#include "World.h"

World::World() 
{
	tick = 1;
	for (size_t x = 0; x < GridSize::X; x++)
		for (size_t y = 0; y < GridSize::Y; y++)
			for (size_t z = 0; z < GridSize::Z; z++)			
				_worldState[x][y][z] = Empty;

	//Set first position
	glm::vec3 startPosition(GridSize::X / 2, GridSize::Y / 2, GridSize::Z / 2);
	cellsPosition.push_back(startPosition);

	_worldState[(int)startPosition.x][(int)startPosition.y][(int)startPosition.z] = Alive;
}

void World::Update() 
{
	if (_timerTick.GetElapsedTime() > tick)
	{
		//Update cells
		CellsMovements();

		_timerTick.Restart();
	}
}

void World::CellsMovements()
{
	glm::vec3 lastPosition = cellsPosition[cellsPosition.size() - 1];

	glm::vec3 newPos(lastPosition.x + 1, lastPosition.y, lastPosition.z);

	cellsPosition.push_back(newPos);
}