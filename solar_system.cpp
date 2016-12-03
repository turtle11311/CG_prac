#ifdef __APPLE__
    #include <GLUT/glut.h>
#else
    #include <GL/glut.h>
#endif

const size_t WIN_WIDTH = 600;
const size_t WIN_HEIGHT = 600;
const size_t CLOCK_INTERVAL = 20;

bool play = false;

void drawAxis(float length = 30.0)
{
    glBegin(GL_LINES);
        glColor3ub(255, 0, 0);
        glVertex3f(0.0, 0.0, 0.0);
        glVertex3f(length, 0.0, 0.0);
        glColor3ub(0, 255, 0);
        glVertex3f(0.0, 0.0, 0.0);
        glVertex3f(0.0, length, 0.0);
        glColor3ub(0, 0, 255);
        glVertex3f(0.0, 0.0, 0.0);
        glVertex3f(0.0, 0.0, length);
    glEnd();
}

void display(void)
{
    static float earthTheta = 0.0;
    static float moonTheta = 0.0;
    glMatrixMode(GL_MODELVIEW);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    gluLookAt(0, 600.0, 0, 0, 0, 0, 0, 0, 1);

    glPushMatrix();
    glColor3ub(255, 255, 0);
    glutSolidSphere(30.0f, 30, 17);
    if (!play) drawAxis(60.0);

    glRotatef(earthTheta, 0.0, 1.0, 0.0);
    glTranslatef(150.0, 0.0, 0.0);
    glColor3ub(0, 0, 200);
    glutSolidSphere(20.0f, 30, 17);
    glPushMatrix();

    // draw City on the Earth
    glTranslatef(20.0f, 0.0, 0.0);
    glColor3ub(200, 0, 0);
    glutSolidSphere(6.0f, 15, 10);

    glPopMatrix();

    glRotatef(moonTheta, 0, 1, 0);
    glTranslatef(40.0, 0.0, 0.0);
    glColor3ub(100, 100, 100);
    glutSolidSphere(10.0, 15, 10);


    glFlush();
    if (play) {
        earthTheta = (earthTheta > 360.0) ? 0.0 : earthTheta + 1.0f;
        moonTheta = (moonTheta > 360.0) ? 0.0 : moonTheta + 0.6f;
    }
    glutSwapBuffers();
}

void reshape(int w, int h)
{
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, (GLfloat)w / (GLfloat)h, 1.0, 1000.0);
    glMatrixMode(GL_MODELVIEW);
}

void motionPlay(int value)
{
    glutPostRedisplay();
    glutTimerFunc(CLOCK_INTERVAL, motionPlay, value);
}

void keyBoard(unsigned char key, int x, int y)
{
    switch (key) {
        case 'p': case 'P':
            play = !play; break;
    default:
            break;
    }
    glutPostRedisplay();
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(WIN_WIDTH, WIN_HEIGHT);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("Solar System");
    glEnable(GL_DEPTH_TEST);
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyBoard);
    glutTimerFunc(CLOCK_INTERVAL, motionPlay, CLOCK_INTERVAL);

    glutMainLoop();
}
