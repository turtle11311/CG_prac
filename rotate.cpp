#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <cstdio>

const size_t POINTNUM = 4;
const size_t WIN_WIDTH = 800;
const size_t WIN_HEIGHT = 600;

float theta = 45.0;      // rotation angel of graph

GLfloat vertices[POINTNUM][3] = {{-1.0,-1.0},{1.0,-1.0}, {1.0,1.0}, {-1.0,1.0}};


void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glRotatef(theta, 0.0, 0.0, 1.0);

    glBegin(GL_POLYGON);
        glColor3f(0.5, 0.5, 1.0);
        for (size_t i = 0; i < POINTNUM; ++i) {
            glVertex2fv(vertices[i]);
        }
    glEnd();
    glFlush();
}

void reshape(int w, int h) {
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
	if (w <= h)
		glOrtho(-2.0, 2.0, -2.0 * (GLfloat) h / (GLfloat) w,
		2.0 * (GLfloat) h / (GLfloat) w, -10.0, 10.0);
	else
		glOrtho(-2.0 * (GLfloat) w / (GLfloat) h,
		2.0 * (GLfloat) w / (GLfloat) h, -2.0, 2.0, -10.0, 10.0);
}

void rotate_it(int id) {
    theta++;
    glutPostRedisplay();
    glutTimerFunc(10,rotate_it,id);
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowPosition(0, 0);
    glutInitWindowSize(WIN_WIDTH, WIN_HEIGHT);
    glutCreateWindow("Color");

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutTimerFunc(10, rotate_it, 1);

    glutMainLoop();
}
