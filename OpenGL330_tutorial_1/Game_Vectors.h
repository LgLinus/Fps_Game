#pragma once
#ifndef GAME_VECTORS_H
#define _GAME_VECTORS_H__

#include <vector>
#include "Model.h"
#include "Moving_Model.h"
#include "Door.h"
/* Vector used to store all the models*/
extern std::vector<Model*> models;

/* Vector used to store all the models*/
extern std::vector<Moving_Model*> moving_models;

extern std::vector<Door*> doors;
extern std::vector<int> keys;
#endif