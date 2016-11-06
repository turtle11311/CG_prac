#include <cstdio>
#include <vector>
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

const int WIN_WIDTH = 600;
const int WIN_HEIGHT = 600;
const GLdouble ORTHO_SIZE = 5;

int nowWidth, nowHeight;

std::vector<GLfloat> vertices;

void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glColor3f(0.5, 0.5, 1.0);
    glBegin(GL_POLYGON);
        for (int i = 0; i < vertices.size(); i += 2) {
            glVertex2fv(&vertices[i]);
        }
    glEnd();
    glFlush();
}

void reshape(int w, int h) {
    glViewport(0, 0, w, h);
    nowWidth = w, nowHeight = h;
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    if (w <= h)
        gluOrtho2D(-ORTHO_SIZE, ORTHO_SIZE, -ORTHO_SIZE * (GLfloat)h / (GLfloat)w,
            ORTHO_SIZE * (GLfloat)h / (GLfloat)w);
    else
        gluOrtho2D(-ORTHO_SIZE * (GLfloat)w / (GLfloat)h,
            ORTHO_SIZE * (GLfloat)w / (GLfloat)h, -ORTHO_SIZE, ORTHO_SIZE);
}

void mouse(int btn, int status, int x, int y) {
    if (btn == GLUT_LEFT_BUTTON && status == GLUT_DOWN) {
        if (nowWidth <= nowHeight) {
            vertices.push_back((((GLdouble)x / nowWidth) * 2 - 1) * ORTHO_SIZE);
            vertices.push_back(-((((GLdouble)y / nowWidth) * 2 - (GLdouble)nowHeight / nowWidth) * ORTHO_SIZE));
        }
        else {
            vertices.push_back((((GLdouble)x / nowHeight) * 2 - (GLdouble)nowWidth / nowHeight) * ORTHO_SIZE);
            vertices.push_back(-((((GLdouble)y / nowHeight) * 2 - 1) * ORTHO_SIZE));
        }
    }
    glutPostRedisplay();
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowPosition(0, 0);
    glutInitWindowSize(WIN_WIDTH, WIN_HEIGHT);
    glutCreateWindow("Rotate");

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutMouseFunc(mouse);
    vertices.reserve(100);
    glutMainLoop();
}
