// SPDX-License-Identifier: MIT
/**
 * Copyright 2019 Daniel Mårtensson <daniel.martensson100@outlook.com>
 * Copyright 2022 Martin Schröder <info@swedishembedded.com>
 * Consulting: https://swedishembedded.com/consulting
 * Simulation: https://swedishembedded.com/simulation
 * Training: https://swedishembedded.com/training
 */

#include <string.h>
#include <control/linalg.h>

/*
 * Solve with forward substitution. This can be used with Cholesky decomposition
 * A [m*n] need to be lower triangular and square
 * b [m]
 * x [n]
 * n == m
 */
void linsolve_lower_triangular(float A[], float x[], float b[], uint16_t row)
{
	// Time to solve x from Ax = b.
	memset(x, 0, row * sizeof(float));
	float sum;

	for (uint16_t i = 0; i < row; i++) {
		sum = 0;
		for (uint16_t j = 0; j < i; j++)
			sum = sum + A[row * i + j] * x[j];

		x[i] = (b[i] - sum) / A[row * i + i];
	}
}
