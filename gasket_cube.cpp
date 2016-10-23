#ifdef __APPLE__
    #include <GLUT/glut.h>
#else
    #include <GL/glut.h>
#endif
#include <cstdio>

size_t m = 3;
const size_t POINTNUM = 8;
const size_t WIN_WIDTH = 600;
const size_t WIN_HEIGHT = 600;
const size_t CLOCK_SIZE = 10;

float theta = 0.0;      // rotation angel of graph

typedef GLfloat Point3[3];

Point3 vertices[POINTNUM] = {
    {-1.0, -1.0, 1.0}, {-1.0, -1.0, -1.0}, {1.0, -1.0, -1.0}, {1.0, -1.0, 1.0},
    {-1.0, 1.0, 1.0}, {-1.0, 1.0, -1.0}, {1.0, 1.0, -1.0}, {1.0, 1.0, 1.0}
};

Point3 colors[POINTNUM] = {
    {1.0, 0.0, 0.0}, {0.0, 1.0, 0.0}, {0.0, 0.0, 1.0},
    {1.0, 1.0, 0.0}, {1.0, 0.0, 1.0}, {0.0, 1.0, 1.0}
};


void build_cube(Point3 p0, Point3 p1, Point3 p2, Point3 p3) {
    glBegin(GL_POLYGON);
        glVertex3fv(p0);
        glVertex3fv(p1);
        glVertex3fv(p2);
        glVertex3fv(p3);
    glEnd();
}

void divide_cube(Point3 p0, Point3 p1, Point3 p2, Point3 p3, size_t m) {
    Point3 d0, d1, d2, d3;      // point for divide
    Point3 center;
    int i = 0;
    if (m > 0) {
        for (i = 0; i < 3; ++i) d0[i] = (p0[i] + p1[i]) / 2;
        for (i = 0; i < 3; ++i) d1[i] = (p1[i] + p2[i]) / 2;
        for (i = 0; i < 3; ++i) d2[i] = (p2[i] + p3[i]) / 2;
        for (i = 0; i < 3; ++i) d3[i] = (p3[i] + p0[i]) / 2;
        for (i = 0; i < 3; ++i) center[i] = (d0[i] + d2[i]) / 2;

        divide_cube(p0, d0, center, d3, m - 1);
        divide_cube(center, d1, p2, d2, m - 1);
    } else build_cube(p0, p1, p2, p3);
}

void gasket_cube(size_t m) {
    glColor3fv(colors[0]);
    divide_cube(vertices[0], vertices[1], vertices[2], vertices[3], m);
    glColor3fv(colors[1]);
    divide_cube(vertices[3], vertices[2], vertices[6], vertices[7], m);
    glColor3fv(colors[2]);
    divide_cube(vertices[7], vertices[6], vertices[5], vertices[4], m);
    glColor3fv(colors[3]);
    divide_cube(vertices[4], vertices[5], vertices[1], vertices[0], m);
    glColor3fv(colors[4]);
    divide_cube(vertices[0], vertices[3], vertices[7], vertices[4], m);
    glColor3fv(colors[5]);
    divide_cube(vertices[1], vertices[5], vertices[6], vertices[2], m);
}

void rotate_it(int id) {
    theta++;
    glutPostRedisplay();
    glutTimerFunc(CLOCK_SIZE, rotate_it, id);
}

void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glRotatef(theta, 1.0, 1.0, 1.0);

    gasket_cube(m);

    glFlush();
}

void reshape(int w, int h) {
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-2.0, 2.0, -2.0, 2.0, -2.0, 2.0);
}

void mouseCallback(int btn, int status, int x, int y) {
    if (btn == GLUT_LEFT_BUTTON && status == GLUT_DOWN)
        ++m;
    else if (btn == GLUT_RIGHT_BUTTON && status == GLUT_DOWN)
        m = (m == 0) ? 0 : m - 1;
    glutPostRedisplay();
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowPosition(0, 0);
    glutInitWindowSize(WIN_WIDTH, WIN_HEIGHT);
    glutCreateWindow("Rasket Cube");
    glEnable(GL_DEPTH_TEST);

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutMouseFunc(mouseCallback);
    glutTimerFunc(CLOCK_SIZE, rotate_it, 1);

    glutMainLoop();
}
