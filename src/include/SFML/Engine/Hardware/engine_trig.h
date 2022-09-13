#ifndef ENGINE_TRIG_H
#define ENGINE_TRIG_H
#include "SFML/Global/variables.h"
#include "SFML/Helper/helper.h"
#include <cmath>
/* c_x = center of the circle x
   c_y = center of the circle y
   r = radius of the circle

   "circle" is refering to the camshaft
*/

struct{
	//degree 
	double cam_theta = 30.0;
	double camTorque = 0.0;
	const double camRod_r = 0.1524; //length of the line in. (n)
	double cylForce;
}hardware;

extern double arr1[];
extern double arr2[];
extern double cross_P[];

extern void cross_product(double *pressure, double *force);
//extern void cam_torque(double *cylinder_force, double *cam_theta);

#endif
