#pragma once
#include "SFML/environment/environment.h"

#define  M_PI 3.14159265358979323846 /* pi */
#define LBS2G(lbs)  ((lbs) * 453.5)
#define	FEET2MET(x)	((x) * 0.3048)		/* feet to meters */
#define INHG2HPA(p) ((p) * (33.86389))
#define Q2L(q)	((q) / (1.0567))


struct 
{
	double one_resistance = 12.0;
    double battery = one_resistance;  
}bat;

struct {
    double air_inlet;
    double air_duct;
    double access_door;
    double combustion_can;
    double turbine;
    double actuator;
    double fuel_line;
    double cooling_air;
    double bleed_air;
    double ehaust_pipe;
    struct compress{
            double air_temp;
            double compressed_air_temp;
    };
    compress apu_compressor;
    struct fuel{
            double fuel_temperature;
            double fuel_per_hour;
            bool fuel_spray;
            double fuel_capacity; // place holder
            double fuel_block_quantity = 36000; //place holder
            /*350 lbs/h = 0.0972 lbs/s */
    };
    fuel apu_fuel_vars;
    
}apu_hardware;

struct
{
    double sump_T = 70.0;
	double pIn_T = sump_T; 
    double tank_mass = LBS2G(15.12);
	double tank_cap = Q2L(8) * 0.001; /*in m^3*/ 

	struct Sump{
		double sump_T = 70.0;
		double pIn_T = sump_T; 
	};
	Sump sump;
} oil;

struct
{
	/* gear displacement */
	double D1 = 0.0325;
	double D0 = 0.045;
	double L = 0.085;
	double Vd = ((M_PI / 4) * D0 - D1) * L;  
	double N; /*RPM*/ 
	double Q; /*Flow rate*/
}gear_pump;

struct {
    double throttle;
    double mixture = 1; 
}axis;

struct {
    double fuelAir;
    double fuelFlow = 10.28137247 * axis.mixture;
}carborator;

struct {
  /*residual gas fraction*/
  double k = 1.344;
  /*compression ratio*/
  const double rC = 7.0;
  /*expansion ratio */
  double rE = 5.0;
  /*ideal effciency*/
  double ide = 50.6658508;
  /*initial temperature K */
  double Ta; 
  /*compression temperature K */
  double T2;
  double T3;
  double T4;
  /*pressure in kPa*/
  double Pa = 101.3;
  /*pressure out*/
  double P2;
  double P3;
  double P4;
   
}comb_chamber;

struct{
    double mass; /* Weight of the cylinder head in kg */
    double F; /* N Force  F = P * A */
    double W;
    double V; /* velocity in M/s */
    double displacement;
    double MEP;
}cylinder;

struct{
    double cam_torque;
}camshaft;

struct{

    double crank_shaft_rotation; /*degrees*/
    double complete_cycle_pSecond; 
    int current_position;
    double rpm;
    double pid;

    }engine;

struct {
    double amb_temp = slv_temp();
    double sea_pressure = slv_pressure();
    double airDensity = air_density(sea_pressure, amb_temp); 
    /* pressure at altitude */
    double ambient_pressure = amb_pressure(amb_temp,FEET2MET(10000),INHG2HPA(sea_pressure));
}env_stuff;

struct {
    /* stainless steel conductivity */
    double ss_conductivity = 16.2;
    /* area of fuel tank */
    double FT_A = FEET2MET(3.5) * FEET2MET(4); //m^2 
}hard_const; 





