///Auhtor : kndysong@gmail.com
///Date : 23.06.2022
///Summary : Contain data for rendering like position, models...

#include <vector>

#include <glm/glm.hpp>

#include "State.h"
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
	State _worldState[GridSize::X][GridSize::Y][GridSize::Z];

	//Add method foreach rules
	
	//std::vector of position to set uniform for instancing

public :
	std::vector<glm::vec3> cellsPosition;
	float tick;

	World();

	void Update();

	void CellsMovements();
};