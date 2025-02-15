// SPDX-License-Identifier: MIT
/**
 * Copyright 2019 Daniel Mårtensson <daniel.martensson100@outlook.com>
 * Copyright 2022 Martin Schröder <info@swedishembedded.com>
 * Consulting: https://swedishembedded.com/consulting
 * Simulation: https://swedishembedded.com/simulation
 * Training: https://swedishembedded.com/training
 */

#include <control/ai.h>
#include <control/misc.h>

/*
 * Check if the coordinates x and y are inside the polygon px and py
 * px[p] - Points in x-axis
 * py[p] - Points in y-axis
 * Return 1 or 0 if the coordinate x,y is inside the polygon px, py
 */
uint8_t inpolygon(float x, float y, float px[], float py[], uint8_t p)
{
	/* Get the max y, min y, max x, min y */
	float max_y = py[0];
	float max_x = px[0];
	float min_y = py[0];
	float min_x = px[0];

	for (uint8_t i = 0; i < p; i++) {
		max_y = vmax(py[i], max_y);
		max_x = vmax(px[i], max_x);
		min_y = vmin(py[i], min_y);
		min_x = vmin(px[i], min_x);
	}

	/* Check if we are outside the polygon */
	if (y < min_y || y > max_y || x < min_x || x > max_x) {
		return 0;
	}

	/* Do a better check */
	uint8_t ok = 0;
	uint8_t i = 0;
	uint8_t j = p - 1;

	while (i < p) {
		if (((px[i] > x) != (px[j] > x)) &&
		    (y < (py[j] - py[i]) * (x - px[i]) / (px[j] - px[i]) + py[i])) {
			ok = !ok;
		}
		j = i;
		i++;
	}
	return ok;
}
