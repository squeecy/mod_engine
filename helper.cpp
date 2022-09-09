#include "SFML/Helper/helper.h"

double filter_in(double old_val,double new_val, double d_t, double lag)
{
    do{
        double o = (old_val);
        double n = (new_val); 
        old_val += (n - o) * ((d_t) / (lag));
        if((o < n && old_val > n) || (o > n && old_val < n))
            old_val = n;
        //std::cout << "filter in: " << old_val << std::endl;
        return old_val;
    } while(0);
}

double filter_in_lin(double old_val, double tgt, double d_t, double step)
{
    do{
        double o = (old_val);
        double t = (tgt);
        double s;
        if(isnan(o))
            o = t;
       if(o < t)
            s = (d_t) * (step);
        else
            s = (d_t) * (-(step));
       
       if((o <= t && o + s > t) || (o >= t && o + s < t))
            (old_val) = t;
        else
            (old_val) += s;

    
        return old_val;
    } while(0);
    return 0;
}


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
fx_lin(double x, double x1, double y1, double x2, double y2)
{
	return (((x - x1) / (x2 - x1)) * (y2 - y1) + y1);
}

double PERCENTRAT(double final_point, double current_point)
{
    return (current_point / final_point) * 100.0;
}


double C2KELVIN(double c)
{
    return c + 273.15;
}


