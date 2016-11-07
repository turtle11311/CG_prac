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
const GLdouble ORTHO_SIZE = 5;

int nowWidth, nowHeight;

vector<vector<GLfloat>> graphs;
vector<GLfloat> vertices;

void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glColor3f(0.5, 0.5, 1.0);
    glBegin(GL_LINE_STRIP);
        for (int i = 0; i < vertices.size(); i += 2) {
            glVertex2fv(&vertices[i]);
        }
    glEnd();

    glColor3f(0.5, 0.5, 1.0);
    for (int i = 0; i < graphs.size(); ++i) {
        glBegin(GL_POLYGON);
            for (int j = 0; j < graphs[i].size(); j += 2) {
                glVertex2fv(&graphs[i][j]);
            }
        glEnd();
    }
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
    else if (btn == GLUT_RIGHT_BUTTON && status == GLUT_DOWN) {
        if (vertices.size() < 6)
            vertices.clear();
        else
            graphs.push_back(std::move(vertices));
    }
    glutPostRedisplay();
}

void keyBoard(unsigned char ch, int x, int y) {
    switch (ch) {
    case 'q': case 'Q':
        if (graphs.size())
            graphs.pop_back();
        break;
    case 'r': case 'R':
        if (vertices.size()) {
            vertices.pop_back();
            vertices.pop_back();
        }
    default:
        break;
    }
    glutPostRedisplay();
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowPosition(0, 0);
    glutInitWindowSize(WIN_WIDTH, WIN_HEIGHT);
    glutCreateWindow("Little Painter");

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutMouseFunc(mouse);
    glutKeyboardFunc(keyBoard);
    graphs.reserve(10);
    graphs.resize(1);
    glutMainLoop();
}
