/*https://www.lycoming.com/sites/default/files/O-320%20Operator%20Manual%2060297-30.pdf*/
/*https://x-engineer.org/mean-effective-pressure-mep/.*/ 
#include "SFML/Helper/helper.h"
#include "SFML/Global/variables.h"
#include "SFML/Render/draw.h"
#include "SFML/Engine/Fuel_System/fuel.h"
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
    double Qa; /*Heat Added ...Qa = mass * Cp * d_t */
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


void cylinder_force()
{
    cylinder.mass = engine_cfg.boreArea * 0.259; /* area * density of steel */
    cylinder.F = HPA2PA(comb_chamber.P3) * engine_cfg.boreArea; /* Returns in N */ 
}

void cylinder_work()
{
   cylinder.W = (cylinder.F * engine_cfg.stroke) / (1.0/2.0 * cylinder.mass); 
   cylinder.V = (sqrt(cylinder.W)) / 1000; /* m/s */ 
}

void camTorque()
{
   /* NM = F * Radius of camshaft */ 
   camshaft.cam_torque = cylinder.F * 0.032; 
}



/* change in temp = heat in joiles / amount in grams * specific heat */
double dT_oil(double *T1, double *T2, double J, double g, double sh, double d_t)
{
    *T1+= (J / (g * sh));
    return filter_in(*T2, *T1, d_t, 60);
}



double heat_capacity_fuel(double d_t)
{
    /* H = m * Cp * dT */
    return (fuelTank.total_fuel * 2.22 * fuelTank.fTemp - fuelTank.fTemp) /d_t;
}

double thermal_conductivity_oil(double T)
{
    /* W/(m-K) */
    return fx_lin(T, C2KELVIN(0), 0.15, C2KELVIN(200), 0.119);
}

double heat_capacity_oil(double T)
{
    /* Specific heat J/(g-K) */
    return fx_lin(T, C2KELVIN(0) , 1900, C2KELVIN(300), 2900);
}

double heat_capacity_steel(double T)
{
   /* Q = mcdT J/(kg-K)  */
   return (0.443 + 2E-4 * T - 8E-10 * pow(T, 2)) * 1000;  
}

double heat_transfer(double k, double A, double T0, double T1, double t, double d)
{
    /* Q = (kA(dT)^t) / d */
    return (k * A * (T0 - T1) * t) / d;
}

/* dynamic viscosity, newtonian model 
 FIX LATER  - change interp to math model */ 
double vis_of_oil(double *T)
{
    return fx_lin(*T,0,3.82,100,0.015);
}
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
double poiseuille(double vis, double L, double *Q, double R, double A)
{
      return (8 * vis * L * *Q) / (M_PI * (pow(R,A))); 
}

/*  
Heat transfer by radiation
e = emissivity of the object
A = area of the object
T1 = temperature of object 
T2 = outside source temperature
*/
double rad_tran(double e, double A, double T1, double T2) 
{
	return ((BOLTZMANN_CONST) * (e) * (A) ) * ((pow(T2,4)) - (pow(T1,4)));
}

/*
Fourier's law
how heat "Q" leaves a container 
gamma = thermal conductivity of container
A = area of container
d = thickness
T = temperature of liquid
Te = temperature effecting the object 
*/
double fourier(double gamma, double A, double d, double T, double Te)
{
	return(((gamma * A) / d) * (T - Te));
}

double eff(double s1, double s2, double d_t)
{
	return (s1 * d_t) + s2;
}

void gear_pump_Q(double d_t)
{
	gear_pump.Q = ((gear_pump.Vd * 2000.0) / oil.tank_cap) * eff(8.0,0.8,d_t); 
}

/* ENGINE */

/* net work output per cycle */
void wNet()
{
    therm_phy.wnet = therm_phy.w12 + therm_phy.w34;
}

/* Thermal Efficiency */
void nth()
{
    therm_phy.therm_eff = (therm_phy.wnet / therm_phy.qin) * 100;
}

void displacement()
{
    cylinder.displacement = CUIN2CUCM((M_PI / 4) * pow(5.125, 2) * 3.875 * 4);

}
void MEP()
{
    cylinder.MEP = therm_phy.w34 / cylinder.displacement;
}

void HP()
{
    /* Work out (n) aka # of cycles per minute */ 
    //cylinder.HP = cylinder.MEP * IN2MET(3.875) * engine_cfg.boreArea * n / 0.4566;
}
