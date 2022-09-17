#include <iostream>
#include <iomanip>
#include <string>
#include <cstdlib>
#include <assert.h>
#include <math.h>
#include <thread>
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
#include "SFML/Global/timestep.h"
#include "GLFW/include/GLFW/glfw3.h"

#define n 3



int main(void )
{
	

	GLFWwindow* window;
	if(!glfwInit())
		return -1;
	
	window = glfwCreateWindow(200, 100, "Oil Pressure", NULL, NULL);
	if(!window)
	{
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);
	
	/* TIME STEP */
	float m_LastFrameTime = 0.0f;

	while(!glfwWindowShouldClose(window))
	{
		/* WINDOW CREATION */
		glClear(GL_COLOR_BUFFER_BIT);
		glfwSwapBuffers(window);
		glfwPollEvents();

		/* TIME STEP */
		float time = (float)glfwGetTime();
		timeStep.d_t = time - m_LastFrameTime;
		m_LastFrameTime = time;

		/* simulations teps */
        adi_compression();
        const_combustion();    
        adi_expansion();
        cylinder_work();
        displacement();
        MEP();
        camTorque();
        wNet();
		eff(8.0,0.8,timeStep.d_t);
		vis_of_oil(&oil.temp, &oil.viscosity);
		gear_pump_Q(&gear_pump.Q, timeStep.d_t);
        nth();
		oilTemp(&oil.temp, timeStep.d_t);	
		oilPressure(&oil.pressure, &oil.viscosity ,&gear_pump.Q);
		cross_product(&comb_chamber.P3, &hardware.cylForce);

		/* CONSOLE FUNCTIONS */
		ClearScreen();	
		radiation_print(0);
		temperature_of_oil_print(0);
		thermal_cv_print(0);
	
		std::cout << std::setw(24) << std::right << "| Oil Parameters |" << 
			std::setw(36) << std::right << "| Cylinder Parameters |" << std::endl
		 << std::setw(21) << std::right << "Oil_Pump_Flow: " << gear_pump.Q << std::setw(28) << 
		 std::right <<  "Cam_Torque: " << hardware.cylForce << std::endl
		 << std::setw(20) << std::right << "Oil_Pressure: " << KALMAN(oil.pressure)  << std::endl
		 << std::setw(23) << std::right << "Oil_Temperature: " << oil.temp << std::endl;
}	
	glfwTerminate();
	return 0;
}
