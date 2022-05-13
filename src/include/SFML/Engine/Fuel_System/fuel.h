#ifndef FUEL_H
#define FUEL_H 
#define IN2MET(x)   ((x) / 39.37) /* inch to meters */
extern "C"
{
    void right_tank();
    void left_tank();
    double heat_capacity_oil();
    struct{
        /* amount of fuel in kg */
        double right_tank;
        double left_tank;
        double total_fuel;
        double fTemp = 21;
        double area = IN2MET(29) * IN2MET(17);  /* Fuel tank area m^2 */
    }fuelTank;
        

}
#endif
