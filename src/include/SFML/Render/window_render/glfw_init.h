#pragma once

void glfw_init()
{
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glMatrixMode(GLUT_SINGLE | GLUT_RGB);
	glLoadIdentity();
	glOrtho(-90.0, 100.0, -15.0, 100.0, 0.0, 1.0);
}

void glfw_display()
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-20,20,-20,20,-1,1);


	glEnable(GL_ALPHA_TEST);
	glAlphaFunc(GL_EQUAL,1.0);

	glPixelZoom(1,1);
	glRasterPos2i(-20, -20);
	pix[0].draw();

	glutSwapBuffers();
	glFlush();
}
