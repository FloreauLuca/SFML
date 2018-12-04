// CreatureSimulationBadCode.cpp : Defines the entry point for the console application.
//


#include <cstdlib>
#include <iostream>
#include <CreatureSimulationClassRoom/Simulation.h>

void Simulate() {
	Simulation simulation(445);
	simulation.Init();
	simulation.Start();

	std::cout << "Simulation ended" << std::endl;
}


int main()
{
	Simulate();
	return EXIT_SUCCESS;
}

