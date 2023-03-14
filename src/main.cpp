#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

void changeSize(int w, int h) {
    if (h == 0)
        h = 1;

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glViewport(0, 0, w, h);
    glMatrixMode(GL_MODELVIEW);
}

float angle = 0.0f;

void render(int) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    glRotatef(angle, 0.0f, 1.0f, 0.0f);

    glBegin(GL_TRIANGLES);
    glVertex3f(-1.0f,-1.0f, 0.0f);
    glVertex3f( 1.0f, 0.0f, 0.0);
    glVertex3f( 0.0f, 1.0f, 0.0);
    glEnd();

    angle+=1.0f;
    glutSwapBuffers();
    glutTimerFunc(1000/120, render, 0);
}

void start() {
    glutTimerFunc(1000/120, render, 0);
}

int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowPosition(300,200);
    glutInitWindowSize(320,320);
    glutCreateWindow("SP Engine");

    glutDisplayFunc(start);
    glutReshapeFunc(changeSize);

    glutMainLoop();
    return 0;
}