#pragma once

#include "State.h"
#include "Action.h"
#include "Circumstance.h"

struct StateActionCircumstance : public Circumstance
{
	StateActionCircumstance();
	virtual ~StateActionCircumstance();
	State state;
	Action action;
};

