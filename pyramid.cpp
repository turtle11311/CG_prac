#ifdef __APPLE__
    #include <GLUT/glut.h>
#else
    #include <GL/glut.h>
#endif
#include <cstdio>
#include <X11/Xlib.h>


const size_t POINTNUM = 4;
const size_t FLATNUM = 4;
const size_t WIN_WIDTH = 600;
const size_t WIN_HEIGHT = 600;
const size_t CLOCK_SIZE = 10;

float theta = 45.0;      // rotation angel of graph

GLfloat vertices[POINTNUM][3] = {{0.0, 0.0, 1.15}, {-1.0, -0.58, -0.58},
                                 {1.0, -0.58, -0.58}, {0.0, 1.15, -0.58}};
GLfloat colors[][3] = {{1.0, 0.0, 0.0}, { 0.0, 1.0, 0.0},
                       {0.0, 0.0, 1.0}, {1.0, 1.0, 1.0}};

void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glRotatef(theta, 0.5, 1.0, 1.0);

        for (size_t i = 0; i < FLATNUM; ++i) {
            glBegin(GL_TRIANGLES);
            glColor3fv(colors[i]);
            for (size_t j = i, c = 0; c < 3; ++c, (++j) %= 4) {
                glVertex3fv(vertices[j]);
            }
            glEnd();
        }
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
    // get X11 info
    Display* pdsp = XOpenDisplay(NULL);
    Window wid = DefaultRootWindow(pdsp);
    XWindowAttributes xwAttr;
    XGetWindowAttributes(pdsp, wid, &xwAttr);

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowPosition((xwAttr.width - WIN_WIDTH)/ 2,
                           (xwAttr.height - WIN_HEIGHT) / 2);
    glutInitWindowSize(WIN_WIDTH, WIN_HEIGHT);
    glutCreateWindow("Color");

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutTimerFunc(CLOCK_SIZE, rotate_it, 1);

    glutMainLoop();
}
