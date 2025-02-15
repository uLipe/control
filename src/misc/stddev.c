// SPDX-License-Identifier: MIT
/**
 * Copyright 2019 Daniel Mårtensson <daniel.martensson100@outlook.com>
 * Copyright 2022 Martin Schröder <info@swedishembedded.com>
 * Consulting: https://swedishembedded.com/consulting
 * Simulation: https://swedishembedded.com/simulation
 * Training: https://swedishembedded.com/training
 */

#include <math.h>
#include <control/misc.h>

/*
 * Compute Standard deviation
 * x[L] Vector with values
 * L = Length of vector x
 */
float stddev(float x[], uint16_t length)
{
	float mu = mean(x, length);
	float sigma = 0;

	for (uint16_t i = 0; i < length; i++)
		sigma += (x[i] - mu) * (x[i] - mu);
	return sqrt(sigma / ((float)length));
}
