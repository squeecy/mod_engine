/*https://www.lycoming.com/sites/default/files/O-320%20Operator%20Manual%2060297-30.pdf*/
/*https://x-engineer.org/mean-effective-pressure-mep/.*/ 
#ifndef PHYSICS_H
#define PHYSICS_H
#include "SFML/Helper/helper.h"
#include "SFML/Global/variables.h"
//#include "SFML/Render/draw.h"
//#include "SFML/Engine/Fuel_System/fuel.h"
#include <chrono>
#include <windows.h>
#include <thread>
#include <cmath>
#define  M_PI 3.14159265358979323846 /* pi */
struct{
    double CR = comb_chamber.rC; /*Compression Ratio ...CR = V1/V2 */   
    double cutoff_ratio = 1.0; /*Cut-off Ratio ...a = V3/V2 */
    double k; /*Ratio of specific heat ...k = Cp / Cv */
    double Ndisel; /*Thermal Efficiency ...nDiesel = 1 - ((1/CR^k-1) * (CR^k-1 / k(CR-1))) */
    double Qa; /*Heat Added ...Qa = mass * Cp *d_t */
    double NworkD; /*Net Work Done ...NworkD = Ndisel / Qa */
    double mass; /*mass ... P*V*M/R*T;(P*V = n * R * T) */
    double mean_effect_press; /*Mean effective Pressure NworkD / Displacement Volume */
    double Cv = 0.834; /* Specific Heat capacity */ 
    double w12; /* Net work of Adiabatic compression */ 
    double w34;
    double wnet;
    double qin = 800.0; /* Heat in during combustion */  /*[Kj/Kg] */
    double q41; /* Heat rejected during exhaust process */  /*[Kj/Kg]*/
    double therm_eff; /* Thernmal Efficiency */

                /* Constants */
    /* Compression factor within 14 to 23 */
    /* Universal Gas constant, R/r = 0.287 kJ/kh.K */
    /* Molecular weight of disel, M = 180 */
    /* Specific heat of air at constant volume, Cv = 0.718 kJ/kg.K */

}therm_phy;


/*Engine config, relocate later 0-320-A -E* SERIES */ 

struct{
    double bore = IN2MET(5.125); /* in -> M */
    double boreArea = M_PI * pow((bore / 2), 2); /* M2 */
    double stroke = IN2MET(3.875); /* in -> M */
    double cyl_volume = stroke * M_PI * pow((bore / 2.0), 2.0); /* M^3 */ 
    /*Compression ratio: 7.0:1 */
    /*Firing order: 1-3-2-4 */
    }engine_cfg;


extern void __attribute__((constructor)) cylinder_force();

extern void cylinder_work();

extern void camTorque();



/* change in temp = heat in joiles / amount in grams * specific heat 

T1 = Starting oil temperature (c)
T2 = Final oil temperature (c)
J = Heat in the system (j)
g = Amount of liquid (g)
sh = specific heat
*/
extern double dT_oil(double *T1, double *T2, double J, double g, double sh, double d_t);

//extern double heat_capacity_fuel(double d_t);

extern double thermal_conductivity_oil(double T);

extern double heat_capacity_oil(double T);

extern double heat_capacity_steel(double T);

extern double heat_transfer(double k, double A, double T0, double T1, double t, double d);

extern double vis_of_oil(double *T);
/*
Gives the pressure drop in an incompressible
and Newtonian fluid in laminar flow
flowing througj a long cylindrical pipe
of constant cross section.

vis - viscosity
L - length of the pipe
Q - volumetric flow rate
R - pipe radius
A - cross section of pipe
*/
extern double poiseuille(double vis, double L, double *Q, double R, double A);

/*  
Heat transfer by radiation
e = emissivity of the object
A = area of the object
T1 = temperature of object 
T2 = outside source temperature
*/
extern double rad_tran(double e, double A, double T1, double T2);

/*
Fourier's law
how heat "Q" leaves a container 
gamma = thermal conductivity of container
A = area of container
d = thickness
T = temperature of liquid
Te = temperature effecting the object 
*/
extern double fourier(double gamma, double A, double d, double T, double Te);

extern double eff(double s1, double s2, double d_t);

extern void gear_pump_Q(double *GQ, double d_t);

/* ENGINE */

/* net work output per cycle */
extern void wNet();

/* Thermal Efficiency */
extern void nth();

extern void displacement();

extern void MEP();

extern void HP();

#endif
