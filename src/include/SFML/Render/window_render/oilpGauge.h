#ifndef OILPGAUGE_ 
#define OILPGAUGE_
#include "glad/glad.h"
#include "GLFW/include/GLFW/glfw3.h"

static float pressure_msr_matrix[12] = {
-0.80f, 0.5f, 0.0f,
0.80f, 0.5f, 0.0f,
-0.75f, 0.0f, 0.0f,
0.75f, 0.0f, 0.0f
};

extern void pressuremsr_rect_draw();



#endif
