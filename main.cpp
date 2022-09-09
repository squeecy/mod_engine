#include <iostream>
#include <iomanip>
#include <string>
#include <cstdlib>
#include <assert.h>
#include <math.h>
#include <thread>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "SFML/Engine/Hardware/engine_trig.h"
#include "SFML/Electrical/electronic.h"
#include "SFML/Helper/debug.h"
#include "SFML/Engine/Thermodynamics/Otto_cycle/otto.h"
#include "SFML/Engine/Oil_System/oil.h"
#include "SFML/environment/environment.h"
#include "SFML/Data_Filter/kalman.h"
#include "SFML/Sensor/print.h"
#include "SFML/Render/draw.h"
#include "SFML/Render/console_format.h"
#define n 3



int main( )
{
    sf::RenderWindow window_3( sf::VideoMode ( 200, 100), "Oil Pressure");

    sf::Texture texture_3;

    sf::Time micro = sf::microseconds(10000);
    sf::Time seconds = sf::seconds(0.01f);
    sf::Clock clock; 

    /* ENVIRONMENT VARIABLES */
    double temp = global_environment.amb_temp;
    double sea_pressure = global_environment.sea_pressure; 
    double temp_at_alt = temp_at_altitude(temp, FEET2MET(0.0),FEET2MET(10000.0));
    double pressure_altitude = amb_pressure(temp_at_alt,FEET2MET(10000.0),INHG2HPA(sea_pressure));
    double density_air = air_density(pressure_altitude,C2KELVIN(temp)); // change slv_temperature to dynamic temp

	/*
    std::cout << "ground temperature: " << slv_temp() << " \370C" << std::endl;
    std::cout << "temperature at altitude: " << temp_at_alt << " \370C" << std::endl;
    std::cout << "sea_lvl_pressure: " << slv_pressure() << std::endl;
    std::cout << "pressure at altitude: " << HPA2ATM(pressure_altitude)  << " ATM" << std::endl;
    std::cout << "density at altitude: " << density_air << " kg/m^3" << std::endl;*/

    if (!texture_3.loadFromFile("src/res/img/oil_preassure.png"))
    {
        std::cout << "Load failed" << std::endl;
        
        system("pause");
    }

    sf::Sprite sprite_3;
    sprite_3.setTexture(texture_3);
    sprite_3.setTextureRect(sf::IntRect(0, 0, 500, 444400));
    sf::Time previousTime = clock.getElapsedTime();
    sf::Time currentTime;
	sf::RectangleShape rect;	
	sf::Vector2f rectanglePosition(0,50);
	rect.setPosition(rectanglePosition);
	rect.setSize(sf::Vector2f(3,30));
    while (window_3.isOpen())
    {
		/* setup */
        sf::Event event;
        sf::Event event_2;
        sf::Event event_3;
        sf::Time elapsed = clock.getElapsedTime(); 
        double d_t = elapsed.asSeconds(); 
        double dd_t = clock.restart().asSeconds();

		/* simmulations teps */
        adi_compression();
        const_combustion();    
        adi_expansion();
        cylinder_work();
        displacement();
        MEP();
        camTorque();
        wNet();
		eff(8.0,0.8,dd_t);
		gear_pump_Q(dd_t);
        nth();
		cam_torque(&comb_chamber.P3, &hardware.cam_theta);
        oil.temp = dT_oil(&oil.sump.pIn_T, &oil.sump.sump_T, 197500, oil.tank_mass,2,dd_t);
		oil.pressure = poiseuille(vis_of_oil(&oil.temp), IN2MET(15), &gear_pump.Q, 
			M_PI*pow(0.0762,2), 0.005574);

		
		//double arr1[] = {hardware.camRod_r * cos(hardware.cam_theta),hardware.camRod_r * 
		//sin(hardware.cam_theta),0};
		//double arr2[] = {0,cylinder.F,0};
		//double cross_P[n];
		
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
		rectanglePosition.x = line(oil.pressure);
		rect.setPosition(rectanglePosition);
        window_3.clear( ); 
        window_3.draw(sprite_3);
		window_3.draw(rect);

        sf::Vector2i mousePos_3 = sf::Mouse::getPosition(window_3);

        m_pos.x_3 = mousePos_3.x;
        m_pos.y_3 = mousePos_3.y;
        //std::cout<< "X:"<< m_pos.x_3<< ","<< "Y:" << m_pos.y_3 << std::endl;

        window_3.display( );

		ClearScreen();	
		radiation_print(0);
		temperature_of_oil_print(0);
		thermal_cv_print(0);
	
		std::cout << std::setw(24) << std::right << "| Oil Parameters |" << std::endl
		 << std::setw(17) << std::right << "Pump_Flow: " << gear_pump.Q  << std::endl
		 << std::setw(20) << std::right << "Oil_Pressure: " << KALMAN(oil.pressure)  << std::endl
		 << std::setw(23) << std::right << "Oil_Temperature: " << oil.temp << std::endl
		 << std::setw(26) << std::right << "Combustion Pressure: " << comb_chamber.P3 << std::endl
		 << std::setw(26) << std::right << "Cam Torque: " <<  cross_product(arr1,arr2,cross_P) << std::endl;
    }

    
    return EXIT_SUCCESS;
}
