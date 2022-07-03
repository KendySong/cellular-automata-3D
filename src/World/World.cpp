#include "World.h"

World::World() 
{
	tick = 0.05f;	//(seconds)
	for (size_t x = 0; x < GridSize::X; x++)
		for (size_t y = 0; y < GridSize::Y; y++)
			for (size_t z = 0; z < GridSize::Z; z++)
				_worldCells[x][y][z] = {glm::ivec3(x, y, z), State::Dead};

	//Set first position
	srand(time(nullptr));
	for (size_t x = 50; x < 70; x++)
	{
		for (size_t y = 50; y < 70; y++)
		{
			for (size_t z = 50; z < 70; z++)
			{
				if (rand() % 2 == 0)
				{
					_worldCells[x][y][z].state = State::Alive;
					cellsPosition.push_back(_worldCells[x][y][z].position);
				}		
			}
		}
	}
}

void World::Update() 
{
	if (_timerTick.GetElapsedTime() > tick)
	{
		GameOfLife();
		_timerTick.Restart();
	}
}

void World::GameOfLife() 
{
	_caseToBorn.clear();
	_caseToDelete.clear();

	for (size_t i = 0; i < cellsPosition.size(); i++)
	{
		glm::ivec3 currentCellPosition = cellsPosition[i];
		std::vector<Cell> neighbors = GetNeighbors(currentCellPosition);

		//Survive cases
		int nbAliveNeighbor = 0;
		for (size_t j = 0; j < neighbors.size(); j++)
		{
			switch (neighbors[j].state)
			{
			case State::Alive:
				nbAliveNeighbor++;
				break;

			case State::Dead:
				int neighborDeadCell = 0;
				std::vector<Cell> neighborNewCell = GetNeighbors(neighbors[j].position);
				
				for (size_t k = 0; k < neighborNewCell.size(); k++)
					if (neighborNewCell[k].state == State::Alive)
						neighborDeadCell++;

				if (neighborDeadCell == 3)				
					_caseToBorn.push_back(neighbors[j]);
				break;
			}
		}
			
		//Set case to destroy
		if (!(nbAliveNeighbor == 2 || nbAliveNeighbor == 3))		
			_caseToDelete.push_back(_worldCells[currentCellPosition.x][currentCellPosition.y][currentCellPosition.z]);		
	}

	//Death of cases
	for (size_t i = 0; i < _caseToDelete.size(); i++)
	{
		_worldCells[_caseToDelete[i].position.x][_caseToDelete[i].position.y][_caseToDelete[i].position.z].state = State::Dead;

		//Check width other cells which we have to delete
		for (size_t j = 0; j < cellsPosition.size(); j++)
		{
			if (_caseToDelete[i].position.x == cellsPosition[j].x && _caseToDelete[i].position.y == cellsPosition[j].y && _caseToDelete[i].position.z == cellsPosition[j].z)
			{
				cellsPosition.erase(cellsPosition.begin() + j);
			}
		}
	}

	//Born of cases
	for (size_t i = 0; i < _caseToBorn.size(); i++)
	{
		Cell& newCell = _worldCells[_caseToBorn[i].position.x][_caseToBorn[i].position.y][_caseToBorn[i].position.z];

		if (newCell.state == State::Dead)
		{
			newCell.state = State::Alive;
			cellsPosition.push_back(_caseToBorn[i].position);
		}		
	}
}

std::vector<Cell> World::GetNeighbors(glm::ivec3& cell)
{
	//neighbors.push_back(_worldCells[cell.x][cell.y][cell.z]);

	std::vector<Cell> neighbors;

	int leftPos = (cell.x - 1 + GridSize::X) % GridSize::X;

	//Left and Right
	neighbors.push_back(_worldCells[(cell.x - 1 + GridSize::X) % GridSize::X][cell.y][cell.z]);
	neighbors.push_back(_worldCells[(cell.x + 1) % GridSize::X][cell.y][cell.z]);

	//Bot and top
	neighbors.push_back(_worldCells[cell.x][(cell.y - 1 + GridSize::Y) % GridSize::Y][cell.z]);
	neighbors.push_back(_worldCells[cell.x][(cell.y + 1) % GridSize::Y][cell.z]);

	//Front and back
	neighbors.push_back(_worldCells[cell.x][cell.y][(cell.z - 1 + GridSize::Z) % GridSize::Z]);
	neighbors.push_back(_worldCells[cell.x][cell.y][(cell.z + 1) % GridSize::Z]);

	return neighbors;
}

void World::SetCaseState(Cell& cell, State state) 
{
	cell.state = state;
	cellsPosition.push_back(cell.position);
}