#include "initEngine.h"

GLfloat angleX = 0.0f;
GLfloat angleY = 0.0f;

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    glTranslatef(0.0f, 0.0f, -5.0f);
    glRotatef(angleX, 1.0f, 0.0f, 0.0f);
    glRotatef(angleY, 0.0f, 1.0f, 0.0f);

    GLPoint origin1 = {0.0f, 0.0f, 0.0f};
    GLfloat size = 2.0f;

    drawSphere(origin1, size, 0.01f); // Optimize this shit

    glutSwapBuffers();
}

void reshape(int w, int h) {
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0f, (GLfloat)w / (GLfloat)h, 1.0f, 100.0f);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void timer(__attribute__((unused)) int ignored) {
    angleX += 1.0f;
    angleY += 1.0f;

    glutPostRedisplay();
    glutTimerFunc(16, timer, 0);
}
