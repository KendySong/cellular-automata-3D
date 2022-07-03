///Auhtor : kndysong@gmail.com
///Date : 02.07.2022
///Summary : Contain position and state

#include <glm/glm.hpp>

#include "State.h"

#pragma once
struct Cell
{
	glm::ivec3 position;
	State state;
};