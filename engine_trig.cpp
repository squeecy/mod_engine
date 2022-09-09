#include <iostream>
#include "SFML/Engine/Hardware/engine_trig.h"
#include "eigen/Eigen/Dense"
#include "SFML/Physics/physics.h"
#define n 3
using namespace Eigen;
/* find the center of the circle 
(x-h)^2 + (y-k)^2 = r 
*/


double arr1[] = {hardware.camRod_r * cos(hardware.cam_theta),hardware.camRod_r * 
		sin(hardware.cam_theta),0};
double arr2[] = {0,hardware.cylForce,0};
double cross_P[n];


/*
double cross_product(double vect_A[], double vect_B[], double cross_P[])
{
	return cross_P[2];
}
*/
double cross_product(double vect_A[], double vect_B[], double cross_P[])
{
	cross_P[0] = vect_A[1] * vect_B[2] - vect_A[2] * vect_B[1];
	cross_P[1] = vect_A[2] * vect_B[0] - vect_A[0] * vect_B[2];
	cross_P[2] = vect_A[0] * vect_B[1] - vect_A[1] * vect_B[0];
	return cross_P[2];
}


void cam_torque(double *cylinder_force, double *cam_theta)
{
	//hardware.camRod, hardware.cam_theta
	double vect_A[] = {hardware.camRod_r * cos(*cam_theta), 
		hardware.camRod_r * sin(*cam_theta), 0.0};
	double vect_B[] = {0.0, cylinder.F, 0.0};
	double cross_P[n];
	//cross_product(vect_A, vect_B, cross_P);
	hardware.camTorque = cross_product(vect_A, vect_B, cross_P);
}


 /*
 how much energy is dissipated - 
  *current cam position relative to the center point 
  */


