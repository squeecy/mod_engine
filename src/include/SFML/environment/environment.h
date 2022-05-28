
// C++ implementation of the approach
#ifndef ENVIRONMENT_H
#define ENVIRONMENT_H
extern "C"
{

/* aircraft knots */
double act_knt();
/* aircraft Foot-per-minuite */
double act_fpm();

double slv_temp();
/* sea level pressure */
double slv_pressure();
/* Air pressure at altitude */
double alt_pressure(double p0, double h, double h0, double T);
/* Air Density */
double air_density(double Pa, double T);
double temp_at_altitude(double Ta, double ha, double h);
double amb_pressure(double T, double h, double P0);
}
#endif
