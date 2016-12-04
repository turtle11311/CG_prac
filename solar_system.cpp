#ifdef __APPLE__
    #include <GLUT/glut.h>
#else
    #include <GL/glut.h>
#endif

// Lighting values
GLfloat  sourceLight[] = { 0.8f, 0.8f, 0.8f, 1.0f };
GLfloat	 lightPos[] = { 0.0f, 0.0f, 0.0f, 1.0f };
GLfloat  whiteLight[] = { 0.2f, 0.2f, 0.2f, 1.0f };
const size_t WIN_WIDTH = 600;
const size_t WIN_HEIGHT = 600;
const size_t CLOCK_INTERVAL = 20;

bool play = false;

void drawAxis(float length = 30.0)
{
    glPushAttrib(GL_LIGHTING_BIT);
    glDisable(GL_LIGHTING);
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
    glPopAttrib();
}

void display(void)
{
    static float earthTheta = 0.0;
    static float earthSelfTheta = 0.0;
    static float moonTheta = 0.0;
    static float marsTheta = 0.0;
    static float marsSelfTheta = 0.0;
    glMatrixMode(GL_MODELVIEW);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    gluLookAt(0, 600.0, 0, 0, 0, 0, 0, 0, 1);

    // draw sun
    glDisable(GL_LIGHTING);
    glColor3ub(255, 255, 0);
    glutSolidSphere(25.0f, 30, 17);
    if (!play) drawAxis(60.0);
    glEnable(GL_LIGHTING);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, sourceLight);
    glLightfv(GL_LIGHT0, GL_POSITION, lightPos);
    glPushMatrix();

        glRotatef(earthTheta, 0.0, 1.0, 1.0);
        glTranslatef(100.0, 0.0, 0.0);
        glRotatef(earthSelfTheta, 0.0, 0.7, 0.1);
        glColor3ub(0, 0, 200);
        glutSolidSphere(15.0f, 30, 17);
        if (!play) drawAxis(25);
        glPushMatrix();

            // draw City on the Earth
            glTranslatef(15.0f, 0.0, 0.0);
            glColor3ub(200, 0, 0);
            glutSolidSphere(4, 15, 10);

        glPopMatrix();

        // draw the moon
        glRotatef(moonTheta - earthSelfTheta, 0, 1, 0);
        glTranslatef(40.0, 0.0, 0.0);
        glColor3ub(100, 100, 100);
        glutSolidSphere(8.0, 15, 10);
        if (!play) drawAxis(20);
    glPopMatrix();

    glPushMatrix();
        // draw Mars
        glRotatef(marsTheta, 0, 0.3, 0.8);
        glTranslatef(200, 0, 0);
        glRotatef(marsSelfTheta, 0, 0, 1);
        glColor3ub(216, 89, 14);
        glutSolidSphere(15.0, 15, 10);
        if (!play) drawAxis(25);
        glPushMatrix();
            // add city
            glTranslatef(0, 15, 0);
            glColor3ub(2, 122, 26);
            glutSolidSphere(4, 15, 10);
            // draw settlelite
            glTranslatef(0, 30, 0);
            glColor3ub(189, 16, 203);
            glutSolidSphere(4, 15, 10);
        glPopMatrix();

    glPopMatrix();


    glFlush();
    if (play) {
        earthTheta = (earthTheta > 360.0) ? 0.0 : earthTheta + 1.2f;
        earthSelfTheta = (earthSelfTheta > 360.0) ? 0.0 : earthSelfTheta + 0.2f;
        moonTheta = (moonTheta > 360.0) ? 0.0 : moonTheta + 1.0f;
        marsTheta = (marsTheta > 360.0) ? 0.0 : marsTheta + 0.8f;
        marsSelfTheta = (marsSelfTheta > 360.0) ? 0.0 : marsSelfTheta + 0.5f;
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
    glEnable(GL_LIGHTING);
    // Enable color material
    glEnable(GL_COLOR_MATERIAL);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, sourceLight);
    glLightfv(GL_LIGHT0, GL_POSITION, lightPos);
    glEnable(GL_LIGHT0);

    // Black background
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyBoard);
    glutTimerFunc(CLOCK_INTERVAL, motionPlay, CLOCK_INTERVAL);

    glutMainLoop();
}
