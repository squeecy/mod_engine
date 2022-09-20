#ifndef SHADER_ 
#define SHADER 
#include <iostream>
#include <malloc.h>
#include "SFML/Render/window_render/oilPGauge.h"

static unsigned int CompileShader(unsigned int type, const std::string& source);

static unsigned int 
	CreateShader(const std::string& vertexShader, const std::string& fragmentShader);

void shader_run();


#endif
