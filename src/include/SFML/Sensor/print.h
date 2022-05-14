		//std::cout << "radiation: " << rad_tran(emi_of_6601,FEET2MET(3.3 * 2.2),30 + 273.15, temp + 273.15) << std::endl;
        //std::cout << "Temperature of oil: " <<test_oil << std::endl;
        //std::cout << "CV: "<<therm_phy.Cv<< std::endl;
        //std::cout << "Ta: " <<comb_chamber.Ta << std::endl;
        //std::cout << "T2: " <<comb_chamber.T2 << std::endl;
        //std::cout << "Force: " <<cylinder.F << " N" << std::endl;
        //std::cout << "Torque: " <<camshaft.cam_torque << " NM" << std::endl;
        //std::cout << "Velocity: " <<cylinder.V << " m/ms" << std::endl;
		//std::cout << "pump flow rate: " << gear_pump.Q << std::endl;
		//std::cout << "oil_p_line_pos: " << rectanglePosition.x << std::endl; 
		//std::cout << "oil pressure: " << KALMAN(oil_press) << std::endl;
		//std::cout << "efficency: " << eff(8.0,0.8,dd_t)<< std::endl;  
        //std::cout << "vol1: " <<engine_cfg.cyl_volume<< std::endl;
        //std::cout << "T4: " <<comb_chamber.T4 << std::endl;
        //std::cout << "P3: " <<comb_chamber.P3 << std::endl; 
        //std::cout << "T3: " <<comb_chamber.T3 << std::endl;
        //std::cout << "net work: "<<therm_phy.wnet << std::endl;
        //std::cout << "d/t: " << dd_t << std::endl;
        //std::cout << "displacement: " << cylinder.displacement << std::endl;
        //std::cout << "MEP: " <<cylinder.MEP << std::endl;
        //std::cout << "work 34: "<<therm_phy.w34 << std::endl;
        //std::cout << "thermal efficiency: "<<therm_phy.therm_eff<< std::endl;
/*
void radiation_print()
{
	std::cout << "radiation: " << rad_tran(emi_of_6601,FEET2MET(3.3 * 2.2),30 + 273.15, temp + 273.15) << std::endl;
}

void temp_of_oil_print()
{
	std::cout << "Temperature of oil: " <<test_oil << std::endl;
}
*/

bool cv_print(bool switcher)
{
	if(switcher == true)
		std::cout << "CV: "<<therm_phy.Cv<< std::endl;
}



