#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

struct GLPoint {
    GLfloat posX;
    GLfloat posY;
    GLfloat posZ;
};

struct GLVector {
    GLPoint a;
    GLPoint b;
};

struct GLColor {
    GLfloat r;
    GLfloat g;
    GLfloat b;
};

void changeSize(int w, int h) {
    if (h == 0)
        h = 1;

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glViewport(0, 0, w, h);
    glMatrixMode(GL_MODELVIEW);
}

void drawTriangleRectangle(GLVector vector, GLColor color, GLboolean sensRect) {
    glColor3f(color.r,color.g,color.b);
    glBegin(GL_TRIANGLES);
    glVertex3f(vector.a.posX, vector.a.posY, vector.a.posZ);
    glVertex3f(vector.b.posX, vector.b.posY, vector.b.posZ);
    if (sensRect == 0) {
        glVertex3f((vector.b.posX - vector.a.posX)*vector.a.posX, (vector.a.posY - vector.b.posY)*vector.b.posY, (vector.b.posZ - vector.a.posZ)*vector.a.posZ);
    } else {
        glVertex3f((vector.b.posX - vector.a.posX)*vector.b.posX, (vector.a.posY - vector.b.posY)*vector.a.posY, (vector.b.posZ - vector.a.posZ)*vector.b.posZ);
    }
    glEnd();
}

void drawSquare(GLVector vector, GLColor color1, GLColor color2) {
    drawTriangleRectangle(vector, color1, 0);
    drawTriangleRectangle(vector, color2, 1);
}

float angle = 0.0f;

void render(int) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    glRotatef(angle, 1.0f, 1.0f, 1.0f);

    GLPoint a1 = {0.0f,1.0f,0.0f};
    GLPoint b1 = {1.0f,0.0f,0.0f};
    GLVector vect1 = {a1,b1};
    GLColor color11 = {0.0f,1.0f,0.0f};
    GLColor color12 = {1.0f,0.0f,0.0f};

    GLPoint a2 = {0.0f,1.0f,0.0f};
    GLPoint b2 = {1.0f,1.0f,1.0f};
    GLVector vect2 = {a2,b2};
    GLColor color21 = {0.0f,0.0f,1.0f};
    GLColor color22 = {1.0f,1.0f,0.0f};

    drawSquare(vect1, color11, color12);
    drawSquare(vect2, color21, color22);

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