#define GLEW_STATIC
#define n 3

#include <iostream>
#include <iomanip>
#include <string>
#include <cstdlib>
#include <assert.h>
#include <math.h>
#include <thread>
#include <malloc.h>
#include "SFML/Render/shaders/shader.h"
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

	if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}
	
	/* TIME STEP */
	float m_LastFrameTime = 0.0f;
	
/*
	float positions[6]
	{
		-0.5f, -0.5f,
			0.0f, 0.5f,
			0.5f, -0.5f

	};
	unsigned int buffer; //-> unique identifier 
	glGenBuffers(1, &buffer); //id of the generated buffer
	glBindBuffer(GL_ARRAY_BUFFER, buffer); //-> selected buffer
	glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(float), positions, GL_STATIC_DRAW);


	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
*/	


	shader_run();

	while(!glfwWindowShouldClose(window))
	{
		/* WINDOW CREATION */
		/*
		glBegin(GL_TRIANGLES);
		glVertex2f(-0.5f, -0.5f);
		glVertex2f(0.0f, 0.5f);
		glVertex2f(0.5f, -0.5f);
		glEnd();
		*/

		glClear(GL_COLOR_BUFFER_BIT);
		//glDrawArrays(GL_TRIANGLES, 0, 3);

		pressuremsr_rect_draw();

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
		cylinder_force(comb_chamber.P3, cylinder.F);
        cylinder_work();
        displacement();
        MEP();
        camTorque();
        wNet();
		eff(8.0,0.8,timeStep.d_t);
		vis_of_oil(oil.temp, oil.viscosity);
		gear_pump_Q(gear_pump.Q, timeStep.d_t);
        nth();
		oilTemp(oil.temp, timeStep.d_t);	
		oilPressure(oil.pressure, oil.viscosity ,gear_pump.Q);
		cross_product(comb_chamber.P3, hardware.cylForce);

		/* CONSOLE FUNCTIONS */
		/*
		ClearScreen();	
		radiation_print(0);
		temperature_of_oil_print(0);
		thermal_cv_print(0);
	
		std::cout << std::setw(24) << std::right << "| Oil Parameters |" << 
			std::setw(36) << std::right << "| Cylinder Parameters |" << std::endl
		 << std::setw(21) << std::right << "Oil_Pump_Flow: " << gear_pump.Q << std::setw(28) << 
		 std::right <<  "Cam_Torque: " << hardware.cylForce << std::endl
		 << std::setw(20) << std::right << "Oil_Pressure: " << KALMAN(oil.pressure)  << std::endl
		 << std::setw(23) << std::right << "Oil_Temperature: " << oil.temp << std::endl
		 << std::setw(26) << std::right << "Cylinder Force: " << cylinder.F << std::endl;
		*/
}	
	glfwTerminate();
	return 0;
}
