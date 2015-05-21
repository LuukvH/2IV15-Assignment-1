#pragma once
#include "integrationscheme.h"

class RungeKutta4thOrder :
	public IntegrationScheme
{
public:
	RungeKutta4thOrder(void);
	~RungeKutta4thOrder(void);
};

