#include <iostream>
#include <windows.h>
#include <cstdlib>
#include "SFML/electronic.h"
#include <windows.h>
#include <assert.h>
#include <math.h>
#include <time.h>
#include "SFML/oil.h"
#include "SFML/environment/environment.h"
#include <chrono>
#include <ctime>
#include <thread>
/*https://stackoverflow.com/questions/50968010/increment-a-value-up-to-a-specific-value-and-then-decrement-back-down-to-the-in*/





int main( )
{
    sf::RenderWindow window_3( sf::VideoMode ( 200, 100), "Oil Pressure");
	//window_3.setFramerateLimit(60);

    sf::Texture texture_3;

    sf::Time micro = sf::microseconds(10000);
    sf::Time seconds = sf::seconds(0.01f);
    sf::Clock clock; 

    /* ENVIRONMENT VARIABLES */
    double temp = slv_temp();
    double sea_pressure = slv_pressure(); 
    double temp_at_alt = temp_at_altitude(temp, FEET2MET(0.0),FEET2MET(10000.0));
    double pressure_altitude = amb_pressure(temp_at_alt,FEET2MET(10000.0),INHG2HPA(sea_pressure));
    double density_air = air_density(pressure_altitude,C2KELVIN(temp)); // change slv_temperature to dynamic temp

    std::cout << "ground temperature: " << slv_temp() << " \370C" << std::endl;

    std::cout << "temperature at altitude: " << temp_at_alt << " \370C" << std::endl;

    std::cout << "sea_lvl_pressure: " << slv_pressure() << std::endl;
    
    std::cout << "pressure at altitude: " << HPA2ATM(pressure_altitude)  << " ATM" << std::endl;

    std::cout << "density at altitude: " << density_air << " kg/m^3" << std::endl;



    
    if (!texture_3.loadFromFile("D:/Astro/src/res/img/oil_preassure.png"))
    {
        std::cout << "Load failed" << std::endl;
        
        system("pause");
    }



    sf::Sprite sprite_3;
    sprite_3.setTexture(texture_3);
    sprite_3.setTextureRect(sf::IntRect(0, 0, 500, 444400));
    //sf::Clock clock;
    sf::Time previousTime = clock.getElapsedTime();
    sf::Time currentTime;
	sf::RectangleShape rect;	
	sf::Vector2f rectanglePosition(0,50);
	rect.setPosition(rectanglePosition);
	rect.setSize(sf::Vector2f(3,30));
    while (window_3.isOpen())
    {
        sf::Event event;
        sf::Event event_2;
        sf::Event event_3;

        sf::Time elapsed = clock.getElapsedTime(); 
        double d_t = elapsed.asSeconds(); 
        double dd_t = clock.restart().asSeconds();
        adi_compression();
        const_combustion();    
        adi_expansion();
        cylinder_force();
        cylinder_work();
        displacement();
        MEP();
        camTorque();
        wNet();
		eff(8.0,0.8,dd_t);
		gear_pump_Q(dd_t);
        rpm(d_t);
        nth();
		

        double test_oil = dT_oil(&oil.sump.pIn_T, &oil.sump.sump_T, 197500, oil.tank_mass,2,dd_t);
		double oil_press = poiseuille(vis_of_oil(&test_oil), IN2MET(15), &gear_pump.Q, 
			M_PI*pow(0.0762,2), 0.005574);

        while (window_3.pollEvent ( event_3))
        {
				

			sf::Vector2i mousePos_3 = sf::Mouse::getPosition(window_3);

			m_pos.x_3 = mousePos_3.x;
			m_pos.y_3 = mousePos_3.y;
			//std::cout<< "X:"<< m_pos.x_3<< ","<< "Y:" << m_pos.y_3 << std::endl;
			sf::RectangleShape rect;	
			sf::Vector2f rectanglePosition(100,50);
			rect.setPosition(rectanglePosition);
			rect.setSize(sf::Vector2f(30,30));




			window_3.display( );
            switch ( event_3.type )
            {
                case sf::Event::Closed:
                        window_3.close( );
                        break;
                        
            }

        }

		rectanglePosition.x = line(oil_press);
		rect.setPosition(rectanglePosition);
        window_3.clear( ); 
        window_3.draw(sprite_3);
		window_3.draw(rect);


        sf::Vector2i mousePos_3 = sf::Mouse::getPosition(window_3);

        m_pos.x_3 = mousePos_3.x;
        m_pos.y_3 = mousePos_3.y;
        //std::cout<< "X:"<< m_pos.x_3<< ","<< "Y:" << m_pos.y_3 << std::endl;

        window_3.display( );

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
		std::cout << "oil pressure: " << oil_press << std::endl;
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
        //combustion(d_t);
        //env_temp();
        
        
        double air_temp = apu_hardware.apu_compressor.air_temp;
        double last_temp = apu_hardware.apu_compressor.air_temp - air_temp;
    }
    

    
    return EXIT_SUCCESS;
}
