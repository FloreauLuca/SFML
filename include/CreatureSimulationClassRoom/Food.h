#ifndef EX8_FOOD_H
#define EX8_FOOD_H
#include <CreatureSimulationClassRoom/GameObject.h>

class Simulation;
class Food : public GameObject {
public:
	Food(Simulation * simulation);

	char GetImage();

};

#endif