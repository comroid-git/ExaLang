#pragma once

#include <stdio.h>

#include "ValueBase.h"

class ExaStack
{
public:
	Value* X;
	Value* T;
	FILE* F;
	Value* M;
};

