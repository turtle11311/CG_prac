#ifdef __APPLE__
    #include <GLUT/glut.h>
#else
    #include <GL/glut.h>
#endif
#include <cstdio>
#include <array>
using std::array;

size_t m = 0;
const size_t POINTNUM = 8;
const size_t WIN_WIDTH = 600;
const size_t WIN_HEIGHT = 600;
const size_t CLOCK_SIZE = 10;

float theta = 0.0;      // rotation angel of graph

typedef array<GLfloat, 3> Point3;
typedef array<Point3, 8> Cubev;

Point3 vertices[POINTNUM] = {
    {-1.0, -1.0, 1.0}, {-1.0, -1.0, -1.0}, {1.0, -1.0, -1.0}, {1.0, -1.0, 1.0},
    {-1.0, 1.0, 1.0}, {-1.0, 1.0, -1.0}, {1.0, 1.0, -1.0}, {1.0, 1.0, 1.0}
};

Point3 colors[POINTNUM] = {
    {1.0, 0.0, 0.0}, {0.0, 1.0, 0.0}, {0.0, 0.0, 1.0},
    {1.0, 1.0, 0.0}, {1.0, 0.0, 1.0}, {0.0, 1.0, 1.0}
};

const size_t cube_vert_id[6][4] = {
    {0, 1, 2, 3}, {3, 2, 6, 7}, {7, 6, 5, 4},
    {4, 5, 1, 0}, {0, 3, 7, 4}, {1, 5, 6, 2}
};

Cubev* cons_cube() {
    Cubev *cube = new Cubev;
}

void build_cube(Cubev cube) {
    for (int i = 0; i < 6; ++i) {
        glBegin(GL_POLYGON);
        glColor3fv(colors[i].begin());
        for(int j = 0; j < 4; ++j)
            glVertex3fv(cube[cube_vert_id[i][j]].begin());
        glEnd();
    }
}

void divide_cube(Cubev cube, size_t m) {
    Point3 d01, d04, d03, d12, d15, d23, d26, d37, d67, d47, d45, d56;
    Point3 cc, c[6] = {};
    int i = 0;
    if (m > 0) {
        for (i = 0; i < 3; ++i) d01[i] = (cube[0][i] + cube[1][i]) / 2;
        for (i = 0; i < 3; ++i) d04[i] = (cube[0][i] + cube[4][i]) / 2;
        for (i = 0; i < 3; ++i) d03[i] = (cube[0][i] + cube[3][i]) / 2;
        for (i = 0; i < 3; ++i) d12[i] = (cube[1][i] + cube[2][i]) / 2;
        for (i = 0; i < 3; ++i) d15[i] = (cube[1][i] + cube[5][i]) / 2;
        for (i = 0; i < 3; ++i) d23[i] = (cube[2][i] + cube[3][i]) / 2;
        for (i = 0; i < 3; ++i) d26[i] = (cube[2][i] + cube[6][i]) / 2;
        for (i = 0; i < 3; ++i) d56[i] = (cube[5][i] + cube[6][i]) / 2;
        for (i = 0; i < 3; ++i) d37[i] = (cube[3][i] + cube[7][i]) / 2;
        for (i = 0; i < 3; ++i) d67[i] = (cube[6][i] + cube[7][i]) / 2;
        for (i = 0; i < 3; ++i) d47[i] = (cube[4][i] + cube[7][i]) / 2;
        for (i = 0; i < 3; ++i) d45[i] = (cube[4][i] + cube[5][i]) / 2;
        int j, k;
        for (i = 0; i < 6; ++i) {
            for (j = 0; j < 4; ++j) {
                for (k = 0; k < 3; ++k) c[i][k] = 0;
            }
            for (j = 0; j < 4; ++j) {
                for (k = 0; k < 3; ++k) c[i][k] += cube[cube_vert_id[i][j]][k];
            }
            for (k = 0; k < 3; ++k) c[i][k] /= 4;
        }
        for (i = 0; i < 3; ++i) cc[i] = (c[0][i] + c[2][i]) / 2;

        divide_cube({cube[0], d01, c[0], d03, d04, c[3], cc, c[4]}, m - 1);
        divide_cube({c[4], cc, c[1], d37, d47, c[2], d67, cube[7]}, m - 1);
        divide_cube({c[3], d15, c[5], cc, d45, cube[5], d56, c[2]}, m - 1);
        divide_cube({c[0], d12, cube[2], d23, cc, c[5], d26, c[1]}, m - 1);
    } else build_cube(cube);
}

void gasket_cube(size_t m) {
    Cubev cube;
    for (int i = 0; i < 8; ++i) {
            for (int j = 0; j < 3; ++j) cube[i][j] = vertices[i][j];
    }
    divide_cube(cube, m);
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
