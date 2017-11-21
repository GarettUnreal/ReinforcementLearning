// MountainCarRLTest.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include "MountainCar.h"

#include <sstream>
#include <iostream>

#pragma float_control (except,on)

int main()
{
	
	// Make the application throw floating point exceptions.
	/*unsigned int currentControl;
	errno_t err;
	err = _controlfp_s(&currentControl, ~_EM_OVERFLOW, _MCW_EM);
	if (err != 0)
		printf_s("_controlfp_s failed!\n");*/

	std::vector<TilesConfig> dimensionConfigs;

	TilesConfig configPosition;
	configPosition.max = MountainCar::MaxPosition;
	configPosition.min = MountainCar::MinPosition;
	configPosition.numTiles = 9;
	dimensionConfigs.push_back(configPosition);

	TilesConfig configVelocity;
	configVelocity.max = MountainCar::MaxVelocity;
	configVelocity.min = MountainCar::MinVelecity;
	configVelocity.numTiles = 9;
	dimensionConfigs.push_back(configVelocity);

	TilesConfig configAction;
	configAction.max = 1.5;
	configAction.min = -1.5;
	configAction.numTiles = 9;
	dimensionConfigs.push_back(configAction);

	std::vector<std::shared_ptr<Tiling>> tilings;

	unsigned int numTilings = 10;
	for (unsigned int index = 0; index < numTilings; ++index)
	{
		std::shared_ptr<Tiling> tiling = std::shared_ptr<Tiling>(new Tiling());
		tiling->initialize(dimensionConfigs);
		tilings.push_back(tiling);
	}

	MountainCar mountainCar(tilings);

	double lambda = 0.9;
	double gamma = 1;
	double alpha = 0.1 / static_cast<double>(numTilings);

	int episode = 0;
	int dropFileInterval = 500; // episode units
	while (episode < 10000)
	{
		std::ostringstream stepsStream;
		stepsStream << "StepsEpisode";// << episode;
		std::string episodeFilename;
		if (episode % dropFileInterval == 0)
		{
			episodeFilename = stepsStream.str();
		}

		std::ostringstream valueFnStream;
		valueFnStream << "ValueFn"; // << episode;
		std::string valueFilename;
		if (episode % dropFileInterval == 0)
		{
			valueFilename = valueFnStream.str();
		}

		std::cout << "Episode: " << episode << std::endl;

		mountainCar.run(lambda, gamma, alpha, episodeFilename, valueFilename);
		++episode;
	}

    return 0;
}

