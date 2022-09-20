#include <iostream>
#include "SFML/Engine/Hardware/engine_trig.h"
#include "eigen/Eigen/Dense"
#include "SFML/Physics/physics.h"
#define n 3
using namespace Eigen;

void cross_product(double& pressure, double& force)
{

	double vect_A[] = {hardware.crankRod_r * cos(hardware.crank_theta),hardware.crankRod_r * 
			sin(hardware.crank_theta),0};
	double vect_B[] = {0,pressure,0};
	double cross_P[n];
	cross_P[0] = vect_A[1] * vect_B[2] - vect_A[2] * vect_B[1];
	cross_P[1] = vect_A[2] * vect_B[0] - vect_A[0] * vect_B[2];
	cross_P[2] = vect_A[0] * vect_B[1] - vect_A[1] * vect_B[0];
	force = cross_P[2];
}




 /*
 how much energy is dissipated - 
  *current cam position relative to the center point 
  */


