#ifndef _HELPER_H_
#define _HELPER_H_

#include <iostream>
#include <math.h>
#define  M_PI 3.14159265358979323846 /* pi */
#define	KELVIN2C(k)    ((k) - 273.15)
double 
C2KELVIN(double c);
#define	FAH2C(f)	(((f) - 32) * 0.555555)
#define	C2FAH(c)	(((c) * 1.8) + 32)
#define	FAH2KELVIN(f)	(((f) + 459.67) * 0.5555555555)
#define	KELVIN2FAH(k)	(((k) * 1.8) - 459.67)

/*
 * Length and velocity unit conversions.
 */
#define	FEET2MET(x)	((x) * 0.3048) /* feet to meters */
#define CUIN2CUCM(x)    ((x) * 16.387) /* Cubic in to Cubic cm */
#define IN2MM(x)    ((x) * 25.4) /* inch to mm */ 
#define IN2MET(x)   ((x) / 39.37) /* inch to meters */
#define	MET2FEET(x)	((x) * 3.2808398950131)	/* meters to feet */
#define IN2CM(x) ((x) * 2.54) /* inches to cm */
#define	NM2MET(x)	((x) * 1852)		/* nautical miles to meters */
#define	MET2NM(x)	((x) / 1852.0)		/* meters to nautical miles */
#define	KT2MPS(k)	(NM2MET(k) / 3600.0)	/* knots to m/s */
#define	MPS2KT(k)	(MET2NM(k) * 3600.0)	/* m/s to knots */
#define	MPS2KPH(k)	((k) * 3.6)		/* m/s to km/h */
#define	KPH2MPS(k)	((k) / 3.6)		/* km/h to m/s */
#define	FPM2MPS(f)	FEET2MET((f) / 60.0)	/* ft.min^-1 to m.s^-1 */
#define	MPS2FPM(m)	MET2FEET((m) * 60.0)	/* m.s^-1 to ft.min^-1 */

#define	INHG2PA(p)	((p) * (101325 / 29.92))
#define	PA2INHG(p)	((p) * (29.92 / 101325))
#define HPA2ATM(p)  ((p) * (0.0009869233))
#define INHG2HPA(p) ((p) * (33.86389))

#define	RADSEC2RPM(r)	(((r) / (2.0 * M_PI)) * 60.0)
#define	RPM2RADSEC(r)	(((r) / 60.0) * (2.0 * M_PI))

#define	USG2LIT(usg)	((usg) * 3.785411784)
#define	LIT2USG(lit)	((lit) / 3.785411784)
#define	LBS2KG(lbs)	((lbs) * 0.45359237)
#define LBS2G(lbs)  ((lbs) * 453.5)
#define	KG2LBS(kg)	((kg) / 0.45359237)

#define	LBF2NEWTON(lb)	(LBS2KG(lb) * EARTH_GRAVITY)
#define	NEWTON2LBF(f)	(KG2LBS((f) / EARTH_GRAVITY))
#define KJ2NM(j)    ((j) * 1000)

#define	WATT2HP(W)	((W) * 0.001341022)	/* Watts to horsepower */
#define	HP2WATT(W)	((W) / 0.001341022)	/* horsepower to Watts */
#define emi_of_6601 0.1 /* emissivity of 6601 aluminum */

/*
 * Pressure unit conversions
 */
#define	HPA2PA(x)	((x) * 100)
#define	PA2HPA(x)	((x) / 100)
#define	PSI2PA(x)	((x) * 6894.73326075122482308111)
#define	PA2PSI(x)	((x) / 6894.73326075122482308111)

/*
 * ISA (International Standard Atmosphere) parameters.
 */
#define	ISA_SL_TEMP_C		15.0	/* Sea level temperature in degrees C */
#define	ISA_SL_TEMP_K		288.15	/* Sea level temperature in Kelvin */
#define	ISA_SL_PRESS		101325.0/* Sea level pressure in Pa */
#define	ISA_SL_DENS		1.225	/* Sea level density in kg/m^3 */
#define	ISA_TLR_PER_1000FT	1.98	/* Temperature lapse rate per 1000ft */
#define	ISA_TLR_PER_1M		0.0065	/* Temperature lapse rate per 1 meter */
#define	ISA_SPEED_SOUND		340.3	/* Speed of sound at sea level */
#define	ISA_TP_ALT		36089	/* Tropopause altitude in feet */

/*
 * Physical constants.
 */
#define	EARTH_GRAVITY	9.80665		/* Earth surface grav. acceleration */
#define	EARTH_SID_DAY	86164.0905	/* Sidereal day on Earth in seconds */
#define	EARTH_ROT_RATE	(360.0 / EARTH_SID_DAY)	/* deg/sec */
#define	DRY_AIR_MOL	0.02896968	/* Molar mass of dry air */
#define	GAMMA		1.4		/* Specific heat ratio of dry air */
#define	R_univ		8.314462618	/* Universal gas constant */
#define	R_spec		287.058		/* Specific gas constant of dry air */
#define	BOLTZMANN_CONST	5.67E-8		/* Stefan-Boltzmann constant */

/* Calculates gravitational force for mass `m' in kg on Earth */
#define	MASS2GFORCE(m)	((m) * EARTH_GRAVITY)

/*
 * Fuel conversion macros.
 */
#define	JETA_KG2GAL(kg)		((kg) / 3.08447722)
#define	JETA_GAL2KG(gal)	((gal) * 3.08447722)




double filter_in(double old_val,double new_val, double d_t, double lag);

double filter_in_lin(double old_val, double tgt, double d_t, double step);


/*
* Interpolates a linear function defined by two points.
*
* @param x Point who's 'y' value we're looking for on the function.
* @param x1 First reference point's x coordinate.
* @param y1 First reference point's y coordinate.
* @param x2 Second reference point's x coordinate.
* @param y2 Second reference point's y coordinate.
*/
double
fx_lin(double x, double x1, double y1, double x2, double y2);
double PERCENTRAT(double final_point, double current_point);

#endif

