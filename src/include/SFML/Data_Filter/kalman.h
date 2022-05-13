


double KALMAN(double U)
{
	static const double R = 40.00;
	static const double H = 1.00;
	static double Q = 10.0;
	static double P = 0.0;
	static double U_hat = 0;
	static double K = 0;


	K = P*H/(H*P*H+R);
	U_hat = U_hat + K*(U-H*U_hat);

	P = (1-K*H)*P+Q;

	return U_hat;
}
