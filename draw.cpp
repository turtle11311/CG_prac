#include <cstdio>
#include <vector>
using std::vector;

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

const int WIN_WIDTH = 600;
const int WIN_HEIGHT = 600;
const GLdouble ORTHO_SIZE = 2;

int nowWidth;
int nowHeight;

float theta = 45.0;      // rotation angel of graph

vector<GLfloat> vertices;

void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glColor3f(0.7, 0.5, 0.4);
    glBegin(GL_POLYGON);
        glVertex2f(1.0, 0.0);
        glVertex2f(1.0, 1.0);
        glVertex2f(-1.5, 1.7);
    //     for (int i = 0; i < vertices.size(); i += 2) {
    //         glVertex2fv(&vertices[i]);
    //     }
    glEnd();
}

void reshape(int w, int h) {
    nowWidth = w, nowHeight = h;
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
	// if (w <= h)
	// 	glOrtho(-ORTHO_SIZE, ORTHO_SIZE,
    //                -ORTHO_SIZE * (GLdouble) h / (GLdouble) w,
	// 	           ORTHO_SIZE * (GLdouble) h / (GLdouble) w, -2.0, 2.0);
	// else
	// 	glOrtho(-ORTHO_SIZE * (GLdouble) w / (GLdouble) h,
    //                ORTHO_SIZE * (GLdouble) w / (GLdouble) h,
    //                -ORTHO_SIZE, ORTHO_SIZE, -2.0, 2.0);
    gluOrtho2D(-2.0, 2.0, -2.0, 2.0);
}

void rotate_it(int id) {
    theta++;
    glutPostRedisplay();
    glutTimerFunc(10,rotate_it,id);
}

void mouse(int btn, int status, int x, int y) {
    if (btn == GLUT_LEFT_BUTTON && status == GLUT_DOWN) {
        //vertices.push_back(((GLfloat)x / nowWidth) * ORTHO_SIZE);
        //vertices.push_back(((GLfloat)y / nowHeight) * ORTHO_SIZE);
    } else {
    }
    glutPostRedisplay();
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowPosition(0, 0);
    glutInitWindowSize(WIN_WIDTH, WIN_HEIGHT);
    glutCreateWindow("Drawer");

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    //glutMouseFunc(mouse);
    vertices.reserve(100);

    glutMainLoop();
}
