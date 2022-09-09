
struct{
	double prev_error = 0.0;
}pid;





double pid(double Kp, double Ki, double dt, double current, double set_point)
{
	double et = set_point - current;
	double de = prev_error - et;

	double proportional = Kp * et;

	double integreal = integral * et * Ki * dt * (et + pid.prev_error); 
	
	double proportional = Kp * (de/dt)
	


	return (proportional + integreal);
}
