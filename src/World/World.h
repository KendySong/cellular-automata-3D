///Auhtor : kndysong@gmail.com
///Date : 23.06.2022
///Summary : Contain data for rendering like position, models...

#include <vector>
#include <iostream>

#include <glm/glm.hpp>

#include "Cell.h"
#include "../Application/Timer.h"

#pragma once
namespace GridSize
{
	const unsigned int X = 100;
	const unsigned int Y = 100;
	const unsigned int Z = 100;
}

class World
{
	//Attributes and properties
private :
	Timer _timerTick;
	Cell _worldCells[GridSize::X][GridSize::Y][GridSize::Z];

	//Game of life
	std::vector<Cell> _caseToBorn;
	std::vector<Cell> _caseToDelete;

public :
	std::vector<glm::vec3> cellsPosition;
	float tick;

	World();

	void Update();

	void GameOfLife();

	std::vector<Cell> GetNeighbors(glm::ivec3& cell);

	void SetCaseState(Cell& cell, State state);
};