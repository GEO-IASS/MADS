// MADS: Model Analyses & Decision Support (v1.1) 2011
//
// Velimir V Vesselinov (monty), vvv@lanl.gov, velimir.vesselinov@gmail.com
// Dylan Harp, dharp@lanl.gov
//
// http://www.ees.lanl.gov/staff/monty/codes/mads
//
// LA-CC-10-055; LA-CC-11-035
//
// Copyright 2011.  Los Alamos National Security, LLC.  All rights reserved.
// This material was produced under U.S. Government contract DE-AC52-06NA25396 for
// Los Alamos National Laboratory, which is operated by Los Alamos National Security, LLC for
// the U.S. Department of Energy. The Government is granted for itself and others acting on its
// behalf a paid-up, nonexclusive, irrevocable worldwide license in this material to reproduce,
// prepare derivative works, and perform publicly and display publicly. Beginning five (5) years after
// --------------- March 11, 2011, -------------------------------------------------------------------
// subject to additional five-year worldwide renewals, the Government is granted for itself and
// others acting on its behalf a paid-up, nonexclusive, irrevocable worldwide license in this
// material to reproduce, prepare derivative works, distribute copies to the public, perform
// publicly and display publicly, and to permit others to do so.
//
// NEITHER THE UNITED STATES NOR THE UNITED STATES DEPARTMENT OF ENERGY, NOR LOS ALAMOS NATIONAL SECURITY, LLC,
// NOR ANY OF THEIR EMPLOYEES, MAKES ANY WARRANTY, EXPRESS OR IMPLIED, OR ASSUMES ANY LEGAL LIABILITY OR
// RESPONSIBILITY FOR THE ACCURACY, COMPLETENESS, OR USEFULNESS OF ANY INFORMATION, APPARATUS, PRODUCT, OR
// PROCESS DISCLOSED, OR REPRESENTS THAT ITS USE WOULD NOT INFRINGE PRIVATELY OWNED RIGHTS.

#define _GNU_SOURCE
#include <math.h>
#include <string.h>
#include "../mads.h"

int set_test_problems( struct opt_data *op );
double test_problems( int D, int function, double *x, int nObs, double *f );
char **char_matrix( int maxCols, int maxRows );

int set_test_problems( struct opt_data *op )
{
	int d, oddefined = 0;
	double a, b, dx;
	struct calc_data *cd;
	struct param_data *pd;
	struct obs_data *od;
	cd = op->cd;
	pd = op->pd;
	od = op->od;
	// cd->sintrans = 0; // No sin transformations
	cd->compute_phi = 1;
	if( cd->test_func >= 40 ) pd->nParam = pd->nOptParam = cd->test_func_npar;
	if( cd->test_func == 9 || cd->test_func == 10 || cd->test_func == 20 || cd->test_func == 23 ) pd->nParam = pd->nOptParam = cd->test_func_dim = 2;
	else pd->nParam = pd->nOptParam = cd->test_func_dim;
	pd->nFlgParam = 0;
	pd->var_id = char_matrix( ( *pd ).nParam, 50 );
	pd->var = ( double * ) malloc( ( *pd ).nParam * sizeof( double ) );
	cd->var = ( double * ) malloc( ( *pd ).nParam * sizeof( double ) );
	pd->var_opt = ( int * ) malloc( ( *pd ).nParam * sizeof( int ) );
	pd->var_log = ( int * ) malloc( ( *pd ).nParam * sizeof( int ) );
	pd->var_dx = ( double * ) malloc( ( *pd ).nParam * sizeof( double ) );
	pd->var_min = ( double * ) malloc( ( *pd ).nParam * sizeof( double ) );
	pd->var_max = ( double * ) malloc( ( *pd ).nParam * sizeof( double ) );
	pd->var_range = ( double * ) malloc( ( *pd ).nParam * sizeof( double ) );
	pd->var_index = ( int * ) malloc( ( *pd ).nOptParam * sizeof( int ) );
	pd->var_current = ( double * ) malloc( ( *pd ).nOptParam * sizeof( double ) );
	pd->var_truth = ( double * ) malloc( ( *pd ).nOptParam * sizeof( double ) );
	pd->var_best = ( double * ) malloc( ( *pd ).nOptParam * sizeof( double ) );
	for( d = 0; d < pd->nParam; d++ )
	{
		sprintf( pd->var_id[d], "Parameter #%d", d + 1 );
		pd->var[d] = cd->var[d] = pd->var_current[d] = pd->var_best[d] = 0;
		pd->var_min[d] = -100; pd->var_max[d] = 100; pd->var_log[d] = 0; pd->var_opt[d] = 1;
		if( cd->problem_type == ABAGUS ) pd->var_dx[d] = .1;
		else pd->var_dx[d] = 0; // if not zero will force PSO/TRIBES/SQUADS to use discretized parameter space; if SQUADS/LM is called, dx = sindx is assumed for LM
		pd->var_range[d] = pd->var_max[d] - pd->var_min[d];
		pd->var_index[d] = d;
	}
#if 1
	if( cd->test_func == 40 )
	{
		pd->var[0] = cd->var[0] = pd->var_current[0] = pd->var_best[0] = 100.5;
		pd->var[1] = cd->var[1] = pd->var_current[1] = pd->var_best[1] = 102.5;
		pd->var_min[0] = 50; pd->var_max[0] = 150;
		pd->var_min[1] = 50; pd->var_max[1] = 150;
		pd->var_range[0] = pd->var_max[0] - pd->var_min[0];
		pd->var_range[1] = pd->var_max[1] - pd->var_min[1];
	}
#endif
	od->nObs = 0; // modified for test problems with observations below
	switch( cd->test_func )
	{
		case 1: // Parabola (Sphere)
			printf( "Parabola (Sphere)" );
			od->nObs = cd->test_func_dim;
			for( d = 0; d < pd->nOptParam; d++ )
				pd->var_truth[d] = pd->var[d] = cd->var[d] = pd->var_current[d] = pd->var_best[d] = 0; // global minimum at (0,0, ... )
			break;
		case 2: // Griewank
			printf( "Griewank" );
			od->nObs = cd->test_func_dim;
			for( d = 0; d < pd->nOptParam; d++ )
				pd->var_truth[d] = pd->var[d] = cd->var[d] = pd->var_current[d] = pd->var_best[d] = 0; // global minimum at (0,0, ... )
			break;
		case 3: // Rosenbrock
			printf( "Rosenbrock" );
			od->nObs = cd->test_func_dim;
			for( d = 0; d < pd->nOptParam; d++ )
				pd->var_truth[d] = pd->var[d] = cd->var[d] = pd->var_current[d] = pd->var_best[d] = 1; // global minimum at (1,1, ... )
			break;
		case 4: // De Jong's Function 4
			printf( "De Jong's Function #4" );
			od->nObs = cd->test_func_dim;
			break;
		case 5: // Step
			printf( "Step" );
			od->nObs = cd->test_func_dim;
			break;
		case 6: // Clerc's f1, Alpine function, min 0
			printf( "Alpine function (Clerc's Function #1)" );
			od->nObs = cd->test_func_dim;
			for( d = 0; d < pd->nOptParam; d++ )
				pd->var_truth[d] = pd->var[d] = cd->var[d] = pd->var_current[d] = pd->var_best[d] = 0; // global minimum at (0,0, ... )
			break;
		case 7: // Rastrigin Minimum value 0. Solution (0,0 ...0)
			printf( "Rastrigin" );
			od->nObs = cd->test_func_dim;
			for( d = 0; d < pd->nOptParam; d++ )
				pd->var_truth[d] = pd->var[d] = cd->var[d] = pd->var_current[d] = pd->var_best[d] = 0; // global minimum at (0,0, ... )
			break;
		case 8: // Krishna Kumar
			printf( "Krishna Kumar" );
			od->nObs = ( cd->test_func_dim - 1 ) * 2;
			break;
		case 9: // 2D Tripod function (Louis Gacogne) Search [-100, 100] min 0 on (0  -50)
			printf( "2D Tripod function" );
			pd->var_truth[0] = 0;
			pd->var_truth[1] = -50;
			od->nObs = cd->test_func_dim = 2;
			break;
		case 10: // Shekel�s Foxholes 2D (alternative)
			printf( "Shekel�s Foxholes 2D (alternative)" );
			od->nObs = 30;
			break;
		case 11: // Shekel�s Foxholes 5D (alternative)
			printf( "Shekel�s Foxholes 10D" );
			od->nObs = 30;
			break;
		case 12: // Shekel�s Foxholes 10D (alternative)
			printf( "Shekel�s Foxholes 10D" );
			od->nObs = 30;
			break;
		case 20: // Foxholes 2D
			printf( "Shekel�s Foxholes 2D" );
			if( cd->test_func_dim != 2 ) cd->test_func_dim = 2;
			break;
		case 21: // Polynomial fitting problem on [-100 100]
			printf( "Polynomial fitting" );
			break;
		case 22: // Ackley
			printf( "Ackley" );
			break;
		case 23: // Eason 2D (usually on [-100,100] Minimum -1 on (pi,pi)
			printf( "Eason 2D " );
			if( cd->test_func_dim != 2 ) cd->test_func_dim = 2;
			break;
		case 33: // Rosenbrock
			printf( "Rosenbrock (with observations = (d-1)*2)" );
			od->nObs = ( cd->test_func_dim - 1 ) * 2;
			for( d = 0; d < pd->nOptParam; d++ )
				pd->var_truth[d] = pd->var[d] = cd->var[d] = pd->var_current[d] = pd->var_best[d] = 1; // global minimum at (1,1, ... )
			break;
		case 40: // sin/cos
			pd->var_truth[0] = a = 100;
			pd->var_truth[1] = b = 102;
			printf( "Sin/Cos test function with %i observations (%g/%g)", cd->test_func_dim, a, b );
			od->nObs = cd->test_func_nobs;
			od->obs_target = ( double * ) malloc( ( *od ).nObs * sizeof( double ) );
			dx = ( double ) M_PI * 2 / ( od->nObs - 1 );
			od->obs_target = ( double * ) malloc( ( *od ).nObs * sizeof( double ) );
			for( d = 0; d < od->nObs; d++ )
			{
				od->obs_target[d] = a * cos( b * d * dx ) + b * sin( a * d * dx );
				// printf( "o %g %g\n", d * dx, od->obs_target[d] );
			}
			oddefined = 1;
			break;
		case 41: // sin/cos
			pd->var_truth[0] = a = 93;
			pd->var_truth[1] = b = 95;
			printf( "Simplified Sin/Cos test function with %i observations (%g/%g)", cd->test_func_dim, a, b );
			od->nObs = cd->test_func_nobs;
			od->obs_target = ( double * ) malloc( ( *od ).nObs * sizeof( double ) );
			dx = ( double ) M_PI * 2 / ( od->nObs - 1 );
			od->obs_target = ( double * ) malloc( ( *od ).nObs * sizeof( double ) );
			for( d = 0; d < od->nObs; d++ )
			{
				od->obs_target[d] = a * cos( d * dx ) + b * sin( d * dx );
				// printf( "o %g %g\n", d * dx, od->obs_target[d] );
			}
			oddefined = 1;
			break;
	}
	if( od->nObs > 1 )
	{
		od->obs_id = char_matrix( ( *od ).nObs, 50 );
		if( !oddefined ) od->obs_target = ( double * ) malloc( ( *od ).nObs * sizeof( double ) );
		od->obs_weight = ( double * ) malloc( ( *od ).nObs * sizeof( double ) );
		od->obs_min = ( double * ) malloc( ( *od ).nObs * sizeof( double ) );
		od->obs_max = ( double * ) malloc( ( *od ).nObs * sizeof( double ) );
		od->obs_current = ( double * ) malloc( ( *od ).nObs * sizeof( double ) );
		od->obs_best = ( double * ) malloc( ( *od ).nObs * sizeof( double ) );
		od->res = ( double * ) malloc( ( *od ).nObs * sizeof( double ) );
		od->obs_log = ( int * ) malloc( ( *od ).nObs * sizeof( int ) );
	}
	for( d = 0; d < od->nObs; d++ )
	{
		sprintf( od->obs_id[d], "Observation #%d", d + 1 );
		if( oddefined ) { od->obs_max[d] = od->obs_target[d] + 0.1; od->obs_min[d] = od->obs_target[d] - 0.1; }
		else od->obs_target[d] = od->obs_max[d] = od->obs_min[d] = 0;
		od->obs_weight[d] = 1;
		od->obs_log[d] = 0;
	}
	return( 0 );
}

/*****************************************************************************/
/* Type:        2D FUNCTION                                                  */
/* Name:        Objective2D_1                                                */
/* Description: 2D tooth                                                     */
/* Boundaries:  -6 < x < 6                                                   */
/*              -6 < y < 6                                                   */
/* Source:      modified Himmelblau's function from Deb, K.                  */
/*              'GA in multimodal function optimazation' Masters thesis      */
/*		TCGA Rep. 89002 / U. of Alabama                              */
/*****************************************************************************/
float
Function1( float x, float y )
{
	float z = -( ( x * x + y - 11 ) * ( x * x + y - 11 ) + ( x + y * y - 7 ) * ( x + y * y - 7 ) ) / 200 + 10;
	return z;
}



double test_problems( int D, int function, double *x, int nObs, double *o )
{
	int d, i, j, k;
	double f, p, xd, x1, x2;
	double sum1, sum2;
	double t0, tt, t1, E, pi;
	static int a1[2][25] = { { -32, -16,   0,  16,  32, -32, -16,   0,  16,  32, -32, -16,   0, 16, 32, -32, -16,   0, 16, 32, -32, -16,   0, 16, 32 },
		{ -32, -32, -32, -32, -32, -16, -16, -16, -16, -16,  16,  16,  16, 16, 16,  32,  32,  32, 32, 32,   0,   0,   0,  0,  0 }
	}; // For Shekel�s Foxholes problem 2D (standard and alternative)
	static double a2[30][10] =
	{
		{9.681, 0.667, 4.783, 9.095, 3.517, 9.325, 6.544, 0.211, 5.122, 2.020},
		{9.400, 2.041, 3.788, 7.931, 2.882, 2.672, 3.568, 1.284, 7.033, 7.374},
		{8.025, 9.152, 5.114, 7.621, 4.564, 4.711, 2.996, 6.126, 0.734, 4.982},
		{2.196, 0.415, 5.649, 6.979, 9.510, 9.166, 6.304, 6.054, 9.377, 1.426},
		{8.074, 8.777, 3.467, 1.863, 6.708, 6.349, 4.534, 0.276, 7.633, 1.567},
		{7.650, 5.658, 0.720, 2.764, 3.278, 5.283, 7.474, 6.274, 1.409, 8.208},
		{1.256, 3.605, 8.623, 6.905, 4.584, 8.133, 6.071, 6.888, 4.187, 5.448},
		{8.314, 2.261, 4.224, 1.781, 4.124, 0.932, 8.129, 8.658, 1.208, 5.762},
		{0.226, 8.858, 1.420, 0.945, 1.622, 4.698, 6.228, 9.096, 0.972, 7.637},
		{7.305, 2.228, 1.242, 5.928, 9.133, 1.826, 4.060, 5.204, 8.713, 8.247},
		{0.652, 7.027, 0.508, 4.876, 8.807, 4.632, 5.808, 6.937, 3.291, 7.016},
		{2.699, 3.516, 5.874, 4.119, 4.461, 7.496, 8.817, 0.690, 6.593, 9.789},
		{8.327, 3.897, 2.017, 9.570, 9.825, 1.150, 1.395, 3.885, 6.354, 0.109},
		{2.132, 7.006, 7.136, 2.641, 1.882, 5.943, 7.273, 7.691, 2.880, 0.564},
		{4.707, 5.579, 4.080, 0.581, 9.698, 8.542, 8.077, 8.515, 9.231, 4.670},
		{8.304, 7.559, 8.567, 0.322, 7.128, 8.392, 1.472, 8.524, 2.277, 7.826},
		{8.632, 4.409, 4.832, 5.768, 7.050, 6.715, 1.711, 4.323, 4.405, 4.591},
		{4.887, 9.112, 0.170, 8.967, 9.693, 9.867, 7.508, 7.770, 8.382, 6.740},
		{2.440, 6.686, 4.299, 1.007, 7.008, 1.427, 9.398, 8.480, 9.950, 1.675},
		{6.306, 8.583, 6.084, 1.138, 4.350, 3.134, 7.853, 6.061, 7.457, 2.258},
		{0.652, 2.343, 1.370, 0.821, 1.310, 1.063, 0.689, 8.819, 8.833, 9.070},
		{5.558, 1.272, 5.756, 9.857, 2.279, 2.764, 1.284, 1.677, 1.244, 1.234},
		{3.352, 7.549, 9.817, 9.437, 8.687, 4.167, 2.570, 6.540, 0.228, 0.027},
		{8.798, 0.880, 2.370, 0.168, 1.701, 3.680, 1.231, 2.390, 2.499, 0.064},
		{1.460, 8.057, 1.336, 7.217, 7.914, 3.615, 9.981, 9.198, 5.292, 1.224},
		{0.432, 8.645, 8.774, 0.249, 8.081, 7.461, 4.416, 0.652, 4.002, 4.644},
		{0.679, 2.800, 5.523, 3.049, 2.968, 7.225, 6.730, 4.199, 9.614, 9.229},
		{4.263, 1.074, 7.286, 5.599, 8.291, 5.200, 9.214, 8.272, 4.398, 4.506},
		{9.496, 4.830, 3.150, 8.270, 5.079, 1.231, 5.731, 9.494, 1.883, 9.732},
		{4.138, 2.562, 2.532, 9.661, 5.611, 5.500, 6.886, 2.341, 9.699, 6.500}
	}; // For Shekel�s Foxholes 5D and 10D problem
	static double c[30] = {0.806, 0.517, 0.1, 0.908, 0.965, 0.669, 0.524, 0.902,
						   0.531, 0.876, 0.462, 0.491, 0.463, 0.714, 0.352, 0.869, 0.813, 0.811, 0.828,
						   0.964, 0.789, 0.360, 0.369, 0.992, 0.332, 0.817, 0.632, 0.883, 0.608, 0.326
						  }; // For Shekel�s Foxholes 5D and 10D problem
	int const M = 60; // For polynomial fitting problem
	double py, y, dx;
	E = exp( 1 );
	pi = acos( -1 );
	switch( function )
	{
		case 1: // Parabola (Sphere)
			f = 0;
			p = 0; // Shift
			for( d = 0; d < D; d++ )
			{
				xd = x[d] - p;
				f += o[d] = xd * xd;
			}
			break;
		case 2: // Griewank
			f = 0;
			p = 1;
			for( d = 0; d < D; d++ )
			{
				xd = x[d];
				f += o[d] = xd * xd / 4000;
				p *= cos( xd / sqrt( ( double ) d + 1 ) );
			}
			for( d = 0; d < D; d++ )
				o[d] += ( -p + 1 ) / D;
			f += -p + 1;
			break;
		case 3: // Rosenbrock
			f = 0;
			t0 = x[0];
			for( d = 1; d < D; d++ )
			{
				tt = ( double ) 1.0 - t0;
				f += o[d] = tt * tt;
				if( d == 1 ) { o[0] = o[1]; o[1] = 0; } // first element
				t1 = x[d];
				tt = t1 - t0 * t0;
				f += x1 = tt * tt * 100;
				o[d] += x1;
				t0 = t1;
			}
			break;
		case 4: // De Jong's f4
			f = 0;
			p = 0; // Shift
			for( d = 0; d < D; d++ )
			{
				xd = x[d] - p;
				f += o[d] = ( d + 1 ) * xd * xd * xd * xd;
			}
			break;
		case 5: // Step
			f = 0;
			for( d = 0; d < D; d++ )
				f += o[d] = x[d];
			break;
		case 6: // Clerc's f1, Alpine function, min 0
			f = 0;
			for( d = 0; d < D; d++ )
			{
				xd = x[d];
				f += o[d] = fabs( xd * sin( xd ) + 0.1 * xd );
			}
			break;
		case 7: // Rastrigin Minimum value 0. Solution (0,0 ...0)
			k = 10;
			f = 0;
			for( d = 0; d < D; d++ )
			{
				xd = x[d];
				f += o[d] = k + xd * xd - k * cos( 2 * pi * xd );
			}
			break;
		case 8: // Krishna Kumar
			f = 0;
			for( i = 0, d = 0; d < D - 1; d++ )
			{
				o[i++] = x1 = sin( x[d] + x[d + 1] );
				o[i++] = x2 = sin( 2 * x[d] * x[d + 1] / 3 );
				f += x1 + x2;
			}
			break;
		case 9: // 2D Tripod function (Louis Gacogne) Search [-100, 100] min 0 on (0  -50)
			x1 = x[0];
			x2 = x[1];
			if( x2 < 0 )
			{
				o[0] = fabs( x1 );
				o[1] = fabs( x2 + 50 );
				f = fabs( x1 ) + fabs( x2 + 50 );
			}
			else
			{
				if( x1 < 0 )
				{
					o[0] = fabs( x1 + 50 ) + 0.5;
					o[1] = fabs( x2 - 50 ) + 0.5;
					f = 1 + fabs( x1 + 50 ) + fabs( x2 - 50 );
				}
				else
				{
					o[0] = fabs( x1 - 50 ) + 1;
					o[1] = fabs( x2 - 50 ) + 1;
					f = 2 + fabs( x1 - 50 ) + fabs( x2 - 50 );
				}
			}
			break;
		case 10: // Shekel�s Foxholes 2D (alternative)
			f = 0;
			for( j = 0; j < 30; j++ )
			{
				sum1 = 0;
				for( d = 0; d < 2; d++ )
					sum1 += ( x[d] - a2[d][j] );
				f += o[j] = ( double ) - 1.0 / ( sum1 + c[j] );
			}
			break;
		case 11: // Shekel�s Foxholes 5D
			f = 0;
			for( j = 0; j < 30; j++ )
			{
				sum1 = 0;
				for( d = 0; d < 5; d++ )
					sum1 += ( x[d] - a2[d][j] );
				f += o[j] = ( double ) - 1.0 / ( sum1 + c[j] );
			}
			break;
		case 12: // Shekel�s Foxholes 10D
			f = 0;
			for( j = 0; j < 30; j++ )
			{
				sum1 = 0;
				for( d = 0; d < 10; d++ )
					sum1 += ( x[d] - a2[d][j] );
				f += o[j] = ( double ) - 1.0 / ( sum1 + c[j] );
			}
			break;
		case 20: // Shekel�s Foxholes 2D
			f = 0;
			for( j = 0; j < 25; j++ )
			{
				sum1 = 0;
				for( d = 0; d < 2; d++ )
					sum1 += pow( x[d] - a1[d][j], 6 );
				f += ( double ) 1.0 / ( j + 1 + sum1 );
			}
			f = ( double ) 1.0 / ( 0.002 + f );
			break;
		case 21: // Polynomial fitting problem on [-100 100]
			f = 0;
			y = -1;
			dx = ( double ) 2.0 / M;
			for( i = 0; i <= M; i++ ) // M = 60
			{
				py = x[0];
				for( d = 1; d < D; d++ )
					py = y * py + x[d];
				if( py < -1 || py > 1 ) f += ( 1 - py ) * ( 1 - py );
				y += dx;
			}
			py = x[0];
			for( d = 1; d < D; d++ )
				py = -1.2 * py + x[d];
			py -= 72.661;
			if( py < 0 ) f += py * py;
			break;
		case 22: // Ackley
			sum1 = sum2 = 0;
			for( d = 0; d < D; d++ )
			{
				xd = x[d];
				sum1 += xd * xd;
				sum2 += cos( 2 * pi * xd );
			}
			y = D;
			f = ( -20 * exp( -0.2 * sqrt( sum1 / y ) ) - exp( sum2 / y ) + 20 + E );
			break;
		case 23: // Eason 2D (usually on [-100,100] Minimum -1 on (pi,pi)
			x1 = x[0]; x2 = x[1];
			f = -cos( x1 ) * cos( x2 ) / exp( ( x1 - pi ) * ( x1 - pi ) + ( x2 - pi ) * ( x2 - pi ) );
			break;
		case 33: // Rosenbrock (with more observations)
			f = 0;
			t0 = x[0];
			for( i = 1, d = 1; d < D; d++ )
			{
				tt = ( double ) 1.0 - t0;
				f += o[i++] = tt * tt;
				if( d == 1 ) { o[0] = o[1]; i = 1; } // first element
				t1 = x[d];
				tt = t1 - t0 * t0;
				f += x1 = tt * tt * 100;
				o[i++] = x1;
				t0 = t1;
			}
			break;
		case 40: // Sin/Cos
			f = 0;
			dx = ( double ) M_PI * 2 / ( nObs - 1 );
			for( d = 0; d < nObs; d++ )
				o[d] = x[0] * cos( x[1] * d * dx ) + x[1] * sin( x[0] * d * dx );
			break;
		case 41: // Sin/Cos
			f = 0;
			dx = ( double ) M_PI * 2  / ( nObs - 1 );
			for( d = 0; d < nObs; d++ )
				o[d] = x[0] * cos( d * dx ) + x[1] * sin( d * dx );
			break;
	}
	if( function < 40 )
	{
		for( d = 0; d < nObs; d++ )
			if( o[d] < 0.0 ) o[d] = -sqrt( fabs( o[d] ) );
			else o[d] = sqrt( o[d] );
	}
	return f;
}
