#ifdef __APPLE__
    #include <GLUT/glut.h>
#else
    #include <GL/glut.h>
#endif
#include <cstdio>


const size_t POINTNUM = 4;
const size_t WIN_WIDTH = 600;
const size_t WIN_HEIGHT = 600;
const size_t CLOCK_SIZE = 10;

float theta = 0.0;      // rotation angel of graph

GLfloat vertices[POINTNUM][3] = {{0.0, 0.0, 1.15}, {-1.0, -0.58, -0.58},
                                 {1.0, -0.58, -0.58}, {0.0, 1.15, -0.58}};
GLfloat colors[][3] = {{1.0, 1.0, 1.0}, {1.0, 0.0, 0.0},
                       {0.0, 1.0, 0.0 }, {0.0, 0.0, 1.0}};
void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glRotatef(theta, 0.0, 1.0, 0.0);

    glBegin(GL_TRIANGLES);
        glColor3fv(colors[1]);
        glVertex3fv(vertices[0]);
        glVertex3fv(vertices[1]);
        glVertex3fv(vertices[2]);
    glEnd();

    glBegin(GL_TRIANGLES);
        glColor3fv(colors[2]);
        glVertex3fv(vertices[2]);
        glVertex3fv(vertices[3]);
        glVertex3fv(vertices[0]);
    glEnd();

    glBegin(GL_TRIANGLES);
        glColor3fv(colors[3]);
        glVertex3fv(vertices[0]);
        glVertex3fv(vertices[3]);
        glVertex3fv(vertices[1]);
    glEnd();

    glBegin(GL_TRIANGLES);
        glColor3fv(colors[0]);
        glVertex3fv(vertices[1]);
        glVertex3fv(vertices[3]);
        glVertex3fv(vertices[2]);
    glEnd();

    glFlush();
}

void reshape(int w, int h) {
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-2.0, 2.0, -2.0, 2.0, -2.0, 2.0);
}

void rotate_it(int id) {
    theta++;
    glutPostRedisplay();
    glutTimerFunc(CLOCK_SIZE, rotate_it, id);
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowPosition(0, 0);
    glutInitWindowSize(WIN_WIDTH, WIN_HEIGHT);
    glutCreateWindow("Color");
    glEnable(GL_DEPTH_TEST);

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutTimerFunc(CLOCK_SIZE, rotate_it, 1);

    glutMainLoop();
}
