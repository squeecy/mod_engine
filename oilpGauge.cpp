#include "SFML/Render/window_render/oilpGauge.h"




void pressuremsr_rect_draw()
{
	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(3, GL_FLOAT, 0, pressure_msr_matrix);
	glDrawArrays(GL_QUAD_STRIP, 0, 4);
	glDisableClientState(GL_VERTEX_ARRAY);
}
