/*https://stackoverflow.com/questions/15891781/how-to-call-on-a-function-found-on-another-file*/

#include "SFML/environment/environment.h"
#include <random>
#include <iostream>
#include <vector>
#include <ctime>
#include <algorithm>
#include <iomanip>
#include <cmath>






double slv_temp()
        {
   
            srand(time(NULL));
            double fMin = (rand() % 14 + 1) * 1.0;
            double fMax = (rand() % 15 + 30) * 1.0;
            double f = (double)rand() / RAND_MAX;
            double return_value = (fMin * 1.0) + f * ((fMax * 1.0) - (fMin * 1.0));
            double place_holder;
            if(return_value != 0)
            {
                place_holder = return_value;
                return place_holder;
            }

            return place_holder;
            
        }



double slv_pressure()
        {
            srand(time(NULL));
            double fMin = 29;
            double fMax = 30;
            double f = (double)rand() / RAND_MAX;
            double return_value = (fMin * 1.0) + f * ((fMax * 1.0) - (fMin * 1.0));
            if(return_value < 29.30)
                return_value += 0.70;
            return return_value; 
            
        }

double alt_pressure(double p0, double h, double h0, double T)
     {
        /* P = P0 exp(-gM(h-h0)/(RT)) */  
        return p0 * exp (((-9.80665 * 0.0289644) * (h - h0)) / (8.31432 * T));  
        
     }
        
double air_density(double Pa, double T)
{
    return Pa/(287.05 * T);
}        


double alt_temp(double temp, double altitude)
{
    double delta_alt = altitude - delta_alt;
    double delta_temp = temp - delta_temp;

    /* y0 ( x1 - x ) + y1 ( x - x0) / (x1 - x0) */
    //return (temp * (delta_alt - altitude) + delta_temp * (temp_at_altitude - altitude)) / (delta_alt - altitude); 
    return 0;
    
}

double temp_at_altitude(double Ta, double ha, double h)
{
    /* Ta = current temp in C, ha = current height in meters, h is destination altitude in m */
   return Ta - 0.0065 * (h - ha); /*C*/  
}

double  amb_pressure(double T, double h, double P0)
{
    /* Hypsometric formula P0 = hPa , h = meters, T = C */
    return P0 * pow((1 - (0.0065 * h) / (T + (0.0065 * h) + 273.15)), 5.257); /*hPa*/   
    
}
    
