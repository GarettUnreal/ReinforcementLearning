#include "stdafx.h"
#include "MountainCar.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <iostream>
#include "LinearTraceUpdator.h"
#include "ReplaceTraceCalculator.h"

const unsigned int MountainCar::NumStateDimensions = 2;

const double MountainCar::MaxPosition = 0.5;
const double MountainCar::MinPosition = -1.2;
const double MountainCar::MaxVelocity = 0.07;
const double MountainCar::MinVelecity = -0.07;

const double MountainCar::MinStartPosition = -0.6;
const double MountainCar::MaxStartPosition = -0.4;

const unsigned int MountainCar::StatePositionIndex = 0;
const unsigned int MountainCar::StateVelocityIndex = 1;
const unsigned int MountainCar::ActionAccelIndex = 0;

MountainCar::MountainCar( std::vector<std::shared_ptr<Tiling>> tilings ) :
	_currentState(MountainCar::NumStateDimensions)
{
	
	Action* accelerateBackwards = new Action(1);
	accelerateBackwards->set(0, -1);
	_actions.push_back(std::shared_ptr<Action>(accelerateBackwards));

	Action* noAcceleration = new Action(1);
	noAcceleration->set(0, 0);
	_actions.push_back(std::shared_ptr<Action>(noAcceleration));

	Action* accelerateForwards = new Action(1);
	accelerateForwards->set(0, +1);
	_actions.push_back(std::shared_ptr<Action>(accelerateForwards));

	_greedyPolicy.setActions(_actions);

	FeatureCalculator* featureCalculator = new FeatureCalculator(tilings);
	_valueFunction = std::shared_ptr<LinearSarsaValueFn>(new LinearSarsaValueFn(featureCalculator));

	unsigned int numFeatures = _valueFunction->getFeatureCalculator()->getNumFeatures();
	_modelParameters = std::shared_ptr<ModelParameters>(new LinearParameters(numFeatures));
	_valueFunction->setModelParameters(std::shared_ptr<ModelParameters>(_modelParameters));

	_greedyPolicy.setValueFunction(_valueFunction);
	_greedyPolicy.setEpsilonGreedy(0.3);
}

MountainCar::~MountainCar()
{
}

void MountainCar::run( double lambda, double gamma, double alpha,
	const std::string& statesFilename, const std::string& valueFunctionFileName)
{
	_currentState = initializeFirstState();

	LinearSarsaValueFn* valueFunction = dynamic_cast<LinearSarsaValueFn*>(_valueFunction.get());
	unsigned int numFeatures = valueFunction->getFeatureCalculator()->getNumFeatures();
	std::shared_ptr< ModelParameters > eligibilityTraces = std::shared_ptr< ModelParameters >(new LinearParameters(numFeatures));

	double reward = -1;
	
	std::shared_ptr<Action> action = _greedyPolicy.chooseAction(_currentState);
	std::shared_ptr<EligibilityTraceUpdater> traceUpdater = std::shared_ptr<EligibilityTraceUpdater>(new LinearTraceUpdator());
	traceUpdater->setNextTraceCalculator(std::shared_ptr< NextTraceCalculator >(new ReplaceTraceCalculator()));

	Sarsa sarsa(_valueFunction, eligibilityTraces, _modelParameters, traceUpdater);
	sarsa.setInitialStateAction(_currentState, *action);
	//printStateAction(_currentState, *action);

	std::vector<State> states;
	states.push_back(_currentState);

	long printFilesInterval = 100000;

	long iteration = 1;
	while (!isTerminal(_currentState))
	{
		_currentState = nextState(_currentState, *action);
		action = _greedyPolicy.chooseAction(_currentState);
		if (states.size() < 2000)
		{
			states.push_back(_currentState);
		}

		//printStateAction(_currentState, *action);

		// DEBUG START
		/*FeatureCalculator* calculator = _valueFunction->getFeatureCalculator();
		std::vector<unsigned int> requiredIndicies;
		calculator->calculateFeatures(_currentState, *action, &requiredIndicies);
		for (unsigned int index = 0; index < requiredIndicies.size(); ++index)
		{
			std::cout << "Feature Index: " << requiredIndicies.at(index) << std::endl;
		}
		std::cout << std::endl;*/
		// DEBUG END

		sarsa.stepUpdate(lambda, gamma, alpha, reward, _currentState, *action);


		/*if (iteration % printFilesInterval == 0)
		{
			if (states.size() < 2000 )
			{
				stepsToFile(statesFilename, states);
			}
			valueFnMaxActionToFile(valueFunctionFileName);
		}*/
		iteration += 1;
	}

	sarsa.terminalUpdate(lambda, gamma, alpha, reward);

	stepsToFile(statesFilename, states);
	valueFnMaxActionToFile(valueFunctionFileName);
}

State MountainCar::nextState(const State& state, const Action & action)
{
	State nextState(state);

	double currPosition = state.getValue().getAt(MountainCar::StatePositionIndex);
	double currVelocity = state.getValue().getAt(MountainCar::StateVelocityIndex);
	double accelFactor = action.getValue().getAt(MountainCar::ActionAccelIndex);

	double nextVelocity = clamp(
		currVelocity + 0.001 * accelFactor - 0.0025 * std::cos(3.0 * currPosition),
		MountainCar::MinVelecity,
		MountainCar::MaxVelocity
	);

	double nextPosition = clamp(currPosition + nextVelocity, MountainCar::MinPosition, MountainCar::MaxPosition);

	// The mountain car problem requires that when the next position reaches the left bound
	// the next velocity is set to zero.
	if (nextPosition <= MountainCar::MinPosition )
	{
		nextVelocity = 0.0;
	}

	nextState.set(MountainCar::StatePositionIndex, nextPosition);
	nextState.set(MountainCar::StateVelocityIndex, nextVelocity);

	return nextState;
}

bool MountainCar::isTerminal(const State & state)
{
	return state.getValue().getAt(MountainCar::StatePositionIndex) >= 0.5;
}

double MountainCar::clamp(double value, double min, double max)
{
	if (value > max)
	{
		return max;
	}
	else if (value < min)
	{
		return min;
	}

	return value;
}

State MountainCar::initializeFirstState()
{
	State startState(MountainCar::NumStateDimensions);
	startState.set(
		MountainCar::StatePositionIndex,
		randomPosition( MountainCar::MinPosition, MountainCar::MaxPosition )
	);
	startState.set(
		MountainCar::StateVelocityIndex,
		randomPosition( MountainCar::MinVelecity, MountainCar::MaxVelocity )
	);
	return startState;
}

double MountainCar::randomPosition(double start, double end)
{
	double normalizedRand = static_cast<double>(rand()) / static_cast<double>(RAND_MAX);
	return start + normalizedRand * (end - start);
}

void MountainCar::printStateAction(const State & state, const Action& action)
{
	std::cout << "Position: " << state.getValue().getAt(MountainCar::StatePositionIndex) <<
		" Velocity: " << state.getValue().getAt(MountainCar::StateVelocityIndex) <<
		" Action: " << action.getValue().getAt(MountainCar::ActionAccelIndex) << std::endl;
}

void MountainCar::valueFnMaxActionToFile(const std::string & filename)
{
	if (filename != "")
	{
		double numSamples = 80.0;
		double posInterval = (MountainCar::MaxPosition - MountainCar::MinPosition) / numSamples;
		double velInterval = (MountainCar::MaxVelocity - MountainCar::MinVelecity) / numSamples;

		for each (std::shared_ptr<Action> action in _actions)
		{
			std::ostringstream valueStream;
			valueStream << filename << "Action" << action->getValue().getAt(MountainCar::StatePositionIndex) << ".value";
			std::ofstream file;
			file.open(valueStream.str().c_str(), std::ios::out | std::ios::trunc);
			for (double position = MountainCar::MinPosition; position <= MountainCar::MaxPosition; position += posInterval)
			{
				for (double velocity = MountainCar::MinVelecity; velocity <= MountainCar::MaxVelocity; velocity += velInterval)
				{

					State state(MountainCar::NumStateDimensions);
					state.set(MountainCar::StatePositionIndex, position);
					state.set(MountainCar::StateVelocityIndex, velocity);

					double value = _valueFunction->value(state, *action);

					file << position << " " << velocity << " " << value << std::endl;
				}
			}
			file.close();
		}
	}
}

void MountainCar::stepsToFile(const std::string & filename, const std::vector<State>& states)
{
	if (filename != "")
	{
		std::ostringstream stepsStream;
		stepsStream << filename << ".episode";
		std::ofstream file;
		file.open(stepsStream.str().c_str(), std::ios::out | std::ios::trunc);
		for each (State state in states)
		{
			file << state.getValue().getAt(MountainCar::StatePositionIndex) <<
				" " << state.getValue().getAt(MountainCar::StateVelocityIndex) << std::endl;
		}
		file.close();
	}
}

