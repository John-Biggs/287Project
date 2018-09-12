#include <ctime>
#include <vector>
#include "defs.h"
#include "Utilities.h"
#include "FrameBuffer.h"
#include "ColorAndMaterials.h"
#include "Rasterization.h"

FrameBuffer frameBuffer(WINDOW_WIDTH, WINDOW_HEIGHT);

void closed5x5Square(int x, int y, color C) {
	drawLine(frameBuffer, x - 2, y - 2, x + 2, y - 2, C);
	drawLine(frameBuffer, x - 2, y - 1, x + 2, y - 1, C);
	drawLine(frameBuffer, x - 2,     y, x + 2,     y, C);
	drawLine(frameBuffer, x - 2, y + 1, x + 2, y + 1, C);
	drawLine(frameBuffer, x - 2, y + 2, x + 2, y + 2, C);
}

void closed5x5Square(const glm::vec2 &centerPt, color C) {
	closed5x5Square(centerPt.x, centerPt.y, C);
}

void open5x5Square(const glm::vec2 &centerPt, color C) {
	//top
	drawLine(frameBuffer, centerPt.x - 2, centerPt.y - 2, centerPt.x + 2, centerPt.y - 2, C);
	//left
	drawLine(frameBuffer, centerPt.x - 2, centerPt.y - 2, centerPt.x - 2, centerPt.y + 2, C);
	//right
	drawLine(frameBuffer, centerPt.x + 2, centerPt.y - 2, centerPt.x + 2, centerPt.y + 2, C);
	//bottom
	drawLine(frameBuffer, centerPt.x - 2, centerPt.y + 2, centerPt.x + 2, centerPt.y + 2, C);
}

void pieChart(const glm::vec2 &centerPt, float rad, float perc, const color &C1, const color &C2) {
	//Big arc
	drawArc(frameBuffer, centerPt, rad, M_PI * perc, M_2PI * (1 - perc), C1);
	//Big arc top line
	drawLine(frameBuffer, centerPt.x, centerPt.y, pointOnCircle(centerPt, rad,  M_PI * perc).x, pointOnCircle(centerPt, rad,  M_PI * perc).y, C1);
	//Big arc bottom line
	drawLine(frameBuffer, centerPt.x, centerPt.y, pointOnCircle(centerPt, rad, -M_PI * perc).x, pointOnCircle(centerPt, rad, -M_PI * perc).y, C1);
	
	glm::vec2 newCenter = centerPt;
	newCenter.x = newCenter.x + rad * .3;
	//Small arc
	drawArc(frameBuffer, newCenter, rad, M_PI * perc, -M_2PI * perc, C2);
	//Small arc top line
	drawLine(frameBuffer, newCenter.x, newCenter.y, pointOnCircle(newCenter, rad,  M_PI * perc).x, pointOnCircle(newCenter, rad,  M_PI * perc).y, C2);
	//Small arc bottom line
	drawLine(frameBuffer, newCenter.x, newCenter.y, pointOnCircle(newCenter, rad, -M_PI * perc).x, pointOnCircle(newCenter, rad, -M_PI * perc).y, C2);
}

void render() {
	frameBuffer.clearColorAndDepthBuffers();
	closed5x5Square(50, 50, red);
	closed5x5Square(glm::vec2(100, 50), green);
	open5x5Square(glm::vec2(150, 50), blue);
	pieChart(glm::vec2(250, 100), 50, 0.25, red, green);
	frameBuffer.showColorBuffer();
}

void resize(int width, int height) {
	frameBuffer.setFrameBufferSize(width, height);
	glutPostRedisplay();
}

void keyboard(unsigned char key, int x, int y) {
	switch (key) {
	case ESCAPE:	glutLeaveMainLoop();
					break;
	}
}

int main(int argc, char *argv[]) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
	glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
	GLuint world_Window = glutCreateWindow(__FILE__);
	glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_GLUTMAINLOOP_RETURNS);

	glutDisplayFunc(render);
	glutReshapeFunc(resize);
	glutKeyboardFunc(keyboard);
	glutMouseFunc(mouseUtility);

	frameBuffer.setClearColor(black);
	std::cout << map(34, 12, 72, -11, -10);
	std::cout << quadratic(-2, 1, 3);
	std::cout << quadratic(9, 6, 1);
	std::cout << quadratic(10, -5, 1);

	glutMainLoop();

	return 0;
}