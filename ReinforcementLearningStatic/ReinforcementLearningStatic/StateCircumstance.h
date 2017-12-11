#pragma once

#include "State.h"
#include "Circumstance.h"

struct StateCircumstance : public Circumstance
{
	StateCircumstance();
	virtual ~StateCircumstance();
	State state;
};

