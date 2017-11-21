#pragma once

#include "State.h"
#include "Action.h"
#include "LinearSarsaValueFn.h"
#include "LinearParameters.h"
#include "DiscreteGreedyPolicy.h"
#include "Sarsa.h"

class MountainCar
{
public:

	static const unsigned int NumStateDimensions;

	static const double MaxPosition;
	static const double MaxVelocity;
	static const double MinPosition;
	static const double MinVelecity;

	MountainCar(std::vector<std::shared_ptr<Tiling>> tilings);
	~MountainCar();

	void run(double lambda, double gamma, double alpha,
		const std::string& statesFilename, const std::string& valueFunctionFileName );

private:

	static const double MinStartPosition;
	static const double MaxStartPosition;

	static const unsigned int StatePositionIndex;
	static const unsigned int StateVelocityIndex;
	static const unsigned int ActionAccelIndex;

	State nextState(const State& state, const Action& action);
	bool isTerminal(const State& state);
	State initializeFirstState();
	double randomPosition(double start, double end);
	void printStateAction(const State& state, const Action& action);

	void valueFnMaxActionToFile(const std::string& filename);
	void stepsToFile(const std::string& filename, const std::vector<State>& states);

	double clamp(double value, double min, double max);

	State _currentState;
	std::vector<std::shared_ptr<Action>> _actions;

	std::shared_ptr< LinearSarsaValueFn > _valueFunction;
	std::shared_ptr< ModelParameters > _modelParameters;
	DiscreteGreedyPolicy _greedyPolicy;
};

