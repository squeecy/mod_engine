#undef __gTRICT_ANSI__
#include <cmath>
#include "SFML/Global/variables.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "SFML/environment/environment.h"
#include "SFML/Physics/physics.h"

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



