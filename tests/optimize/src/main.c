/*
 ============================================================================
 Name        : Astar.c
 Author      : Daniel Mårtensson
 Version     : 1.0
 Copyright   : MIT
 Description : A* algorithm - Find the shortest path
 ============================================================================
 */

#include <unity.h>
#include <stdio.h>
#include <control/optimization.h>
#include <control/misc.h>

void test_linprog(void)
{
#if 0
	// Matrix A
	float A[6*4] = {0.7179787,   0.7985186,   0.1000046,   0.2203064,
					0.9044292,   0.5074379,   0.3539301,   0.9475452,
					0.0029252,   0.4930148,   0.3209303,   0.5289174,
					0.6546133,   0.7354447,   0.9989453,   0.0310190,
					0.7434944,   0.0874402,   0.3388867,   0.8256180,
					0.7483093,   0.3624991,   0.2039784,   0.5528368};

	// Vector b
	float b[6] = {0.31028,
				  0.69595,
				  0.31662,
				  0.33631,
				  0.15131,
				  0.83935};
#endif

	// Lower and upper bounds are b_l <= Ax <= b_u, which is [A; -A]x = [b_u; -b_l] (notice the negative signs!)
	float bounds_A[(6 * 2) * 4] = {
		0.7179787,  0.7985186,	0.1000046,  0.2203064,	0.9044292,  0.5074379,	0.3539301,
		0.9475452,  0.0029252,	0.4930148,  0.3209303,	0.5289174,  0.6546133,	0.7354447,
		0.9989453,  0.0310190,	0.7434944,  0.0874402,	0.3388867,  0.8256180,	0.7483093,
		0.3624991,  0.2039784,	0.5528368,  -0.7179787, -0.7985186, -0.1000046, -0.2203064,
		-0.9044292, -0.5074379, -0.3539301, -0.9475452, -0.0029252, -0.4930148, -0.3209303,
		-0.5289174, -0.6546133, -0.7354447, -0.9989453, -0.0310190, -0.7434944, -0.0874402,
		-0.3388867, -0.8256180, -0.7483093, -0.3624991, -0.2039784, -0.5528368
	};
	float bounds_b[6 * 2] = { 0.90000, // upper
				  0.60000, // upper
				  0.60000, // upper
				  0.90000, // upper
				  0.90000, // upper
				  0.90000, // upper
				  0.40000, // lower
				  0.10000, // lower
				  0.50000, // lower
				  1.00000, // lower
				  0.40000, // lower
				  0.20000 }; // lower

	// Objective function is c^T = bounds_A^T*bounds_b
	float c[4] = { 1.64160, 0.92620, 0.47139, 1.43351 };

	// Solution that need to have the same rows and columns from A
	float x[4];

	// Minimization problem:
	float C2[2] = { 9, 4 };
	float A2[3 * 2] = { 22, 13, 1, 5, 1, 20 };
	float B2[3] = { 25, 7, 7 };
	float y[2]; // Solution!

	/*
	 * Do linear programming with simplex method
	 * You can do a minimization problem as well with simplex
	 *  	Max c^Tx
	 * 		S.t Ax <= b
	 *      	 x >= 0
	 *
	 *  You can do a maximization problem as well with simplex
	 *  	Max b^Tx
	 * 		S.t A'x >= c
	 *      	 x >= 0
	 */
	// Do a maximization problem:
	uint8_t max_or_min = 0;
	linprog(c, bounds_A, bounds_b, x, 6 * 2, 4, max_or_min, 200);

	// Do a minimization problem:
	max_or_min = 1;
	linprog(C2, A2, B2, y, 3, 2, max_or_min, 200);
	// Print x
	printf("x\n");
	print(x, 4, 1);

	// Print y
	printf("y\n");
	print(y, 2, 1);

	// GNU Octave do the same thing - Try it.
	// x = glpk(c', bounds_A, bounds_b, [0;0;0;0], [], "UUUUUUUUUUUU", "CCCC", -1) % -1 is for maximize
}

/*
 * GNU Octave code:
 *
 * // Do maximization
   bounds_A = [0.7179787,   0.7985186,   0.1000046,   0.2203064,
			   0.9044292,   0.5074379,   0.3539301,   0.9475452,
			   0.0029252,   0.4930148,   0.3209303,   0.5289174,
			   0.6546133,   0.7354447,   0.9989453,   0.0310190,
			   0.7434944,   0.0874402,   0.3388867,   0.8256180,
			   0.7483093,   0.3624991,   0.2039784,   0.5528368,
			  -0.7179787,  -0.7985186,  -0.1000046,  -0.2203064,
			  -0.9044292,  -0.5074379,  -0.3539301,  -0.9475452,
			  -0.0029252,  -0.4930148,  -0.3209303,  -0.5289174,
			  -0.6546133,  -0.7354447,  -0.9989453,  -0.0310190,
			  -0.7434944,  -0.0874402,  -0.3388867,  -0.8256180,
			  -0.7483093,  -0.3624991,  -0.2039784,  -0.5528368];

	bounds_b = [0.90000,
				0.60000,
				0.60000,
				0.90000,
				0.90000,
				0.90000,
				0.40000,
				0.10000,
				0.50000,
				1.00000,
				0.40000,
				0.20000];

	c = [1.64160,
		 0.92620,
		 0.47139,
		 1.43351];

	x = glpk(c', bounds_A, bounds_b, [0;0;0;0], [], "UUUUUUUUUUUU", "CCCC", -1)

  	// Do minimization
	 A2 = [22  13;
        	1   5;
        	1 20];

  	  C2 = [9;
        	4];

  	  B2 = [25;
        	 7;
         	 7];

  	  y = glpk(C2', A2, B2, [0;0], [], "LLL", "CC", 1)
 *
 */
