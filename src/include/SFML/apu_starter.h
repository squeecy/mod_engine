/* https://quizlet.com/77413940/boeing-717-engines-and-apu-flash-cards */
/* https://www.grc.nasa.gov/www/k-12/airplane/etr.html */
/*https://liu.diva-portal.org/smash/get/diva2:934580/FULLTEXT01.pdf Page-18*/

/*Adiabatic process*/
/*https://www.omnicalculator.com/physics/thermodynamic-processes*/
/*http://hyperphysics.phy-astr.gsu.edu/hbase/thermo/diesel.html#c2*/
/* https://www.ohio.edu/mechanical/thermo/Intro/Chapt.1_6/Chapter3d.html */
#undef __gTRICT_ANSI__
#include <cmath>
#include "SFML/variables.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <random>
#include "SFML/environment/environment.h"
#include "SFML/physics.h"
#include <vector>

int suction_random_number()
{
    srand(time(NULL));
    int random = rand() % 35 + 1;
    int r = random; 
    if(r < random)
       random = r; 
    return r;
}

static double air_airtake(sf::Clock& clock, int d_t)
{
   /*Fkr gallon * 7.481 */ 
    double volume = M_PI * pow(0.9, 2) * 1.2; 
    //double area = 1 * 0.4;
    //CF/M
    double air_suction =  suction_random_number();
    apu_hardware.air_inlet = volume * air_suction;
    double R,P1,T1,V2,P2;
    /*air compression*/
    /* P1(V1)/ T1 = P2(V2) / T2*/ 
    R = 287; // J/kg*K
    P1 = 1; // atm
    T1 = C2KELVIN(slv_temp()); 
    V2 = (1.0/64.0) * volume;
    P2 = 40; // atm
    apu_hardware.apu_compressor.air_temp = (T1 * P2/P1 * V2) - 273.15; 
    
    double air_temp = apu_hardware.apu_compressor.air_temp;
    double last_temp = apu_hardware.apu_compressor.air_temp - air_temp;
    
    double filter_test = filter_in(apu_hardware.air_inlet, air_temp, d_t, 10.0);
    /*temp*/
    apu_hardware.apu_compressor.compressed_air_temp = filter_test;
   
    return 0;
}


double PERCENTRAT(double final_point, double current_point)
{
    return (current_point / final_point) * 100.0;
}

double fuelairr()
{
    return env_stuff.ambient_pressure / carborator.fuelFlow;
}

/* 1 - 2 Adiabatic compression */ 
void adi_compression(){

   comb_chamber.Ta = C2KELVIN(env_stuff.amb_temp); 
   double dT = comb_chamber.Ta - comb_chamber.T2; 

   /* Compression temp Tb = Ta * rC^y-1 = T2 */ 
   comb_chamber.T2 = comb_chamber.Ta * pow(comb_chamber.rC,(comb_chamber.k - 1.0)); 

   /* Compression pressure Pb = Pa * Rc^y = P2 */
   comb_chamber.P2 = comb_chamber.Pa * (7.0 * (comb_chamber.T2 / comb_chamber.Ta)); 
   
   /* Net work */  
   therm_phy.w12 = therm_phy.Cv * (dT); /* [kJ/Kg] */   

}

/* 2 - 3 Constant Volume Combustion */
void const_combustion()
{
   /* Combustion temp */  
   comb_chamber.T3 = ((therm_phy.qin * 1000.0) / (therm_phy.Cv * 1000.0)) + comb_chamber.T2;  

   /* Combustion Pressure */ 
   comb_chamber.P3 = comb_chamber.P2 * (comb_chamber.T3 / comb_chamber.T2); 
}


/* 3 - 4 Adiabatic expansion */
void adi_expansion()
{
    double dT = comb_chamber.T4 - comb_chamber.T3;
    /* expansion temp */
    comb_chamber.T4 = comb_chamber.T3 * pow((1.0/7.0),comb_chamber.k - 1.0); 
    /* expansion pressure */
    comb_chamber.P4 = comb_chamber.P3 * ((1.0/7.0) * (comb_chamber.T4 / comb_chamber.T3)); 
    /* Net work */
    therm_phy.w34 = std::abs (therm_phy.Cv * (dT));  
}

double vol_exhaust()
{
    therm_phy.q41 = therm_phy.Cv * (comb_chamber.Ta - comb_chamber.T4);
    return 0;
}

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

/* https://www.kitplanes.com/determining-engine-power/ */
void rpm(double d_t)
{
    engine.rpm = fx_lin(23,28,2700,18,2000);
    
}


