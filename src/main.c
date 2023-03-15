#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

typedef struct GLPoint {
    GLfloat posX;
    GLfloat posY;
    GLfloat posZ;
} GLPoint;

typedef struct GLVector {
    GLPoint a;
    GLPoint b;
} GLVector;

typedef struct GLColor {
    GLfloat r;
    GLfloat g;
    GLfloat b;
} GLColor;

void drawTriangle(GLPoint vertices[3], GLColor color) {
    glBegin(GL_TRIANGLES);
    glColor3f(color.r, color.g, color.b);
    for (int i = 0; i < 3; i++) {
        glVertex3f(vertices[i].posX, vertices[i].posY, vertices[i].posZ);
    }
    glEnd();
}

void drawSquare(GLPoint vertices[4], GLColor color) {
    // Draw the first triangle of the square
    GLPoint triangle1[3] = { vertices[0], vertices[1], vertices[2] };
    drawTriangle(triangle1, color);

    color.r /= 2.0f;
    color.g /= 2.0f;
    color.b /= 2.0f;
    // Draw the second triangle of the square
    GLPoint triangle2[3] = { vertices[2], vertices[3], vertices[0] };
    drawTriangle(triangle2, color);
}

void drawCube(GLPoint origin, GLfloat size) {
    GLfloat halfSize = size / 2.0f;
    GLPoint vertices[] = {
            {origin.posX - halfSize, origin.posY - halfSize, origin.posZ + halfSize},
            {origin.posX + halfSize, origin.posY - halfSize, origin.posZ + halfSize},
            {origin.posX + halfSize, origin.posY + halfSize, origin.posZ + halfSize},
            {origin.posX - halfSize, origin.posY + halfSize, origin.posZ + halfSize},
            {origin.posX - halfSize, origin.posY - halfSize, origin.posZ - halfSize},
            {origin.posX + halfSize, origin.posY - halfSize, origin.posZ - halfSize},
            {origin.posX + halfSize, origin.posY + halfSize, origin.posZ - halfSize},
            {origin.posX - halfSize, origin.posY + halfSize, origin.posZ - halfSize}
    };

    // Colors for each face
    GLColor colors[] = {
            {1.0f, 0.0f, 0.0f}, // red
            {0.0f, 1.0f, 0.0f}, // green
            {0.0f, 0.0f, 1.0f}, // blue
            {1.0f, 1.0f, 0.0f}, // yellow
            {1.0f, 0.0f, 1.0f}, // magenta
            {0.0f, 1.0f, 1.0f}  // cyan
    };

    // Front face
    GLPoint frontFaceVertices[4] = { vertices[0], vertices[1], vertices[2], vertices[3] };
    drawSquare(frontFaceVertices, colors[0]);

    // Back face
    GLPoint backFaceVertices[4] = { vertices[4], vertices[5], vertices[6], vertices[7] };
    drawSquare(backFaceVertices, colors[1]);

    // Left face
    GLPoint leftFaceVertices[4] = { vertices[0], vertices[3], vertices[7], vertices[4] };
    drawSquare(leftFaceVertices, colors[2]);

    // Right face
    GLPoint rightFaceVertices[4] = { vertices[1], vertices[2], vertices[6], vertices[5] };
    drawSquare(rightFaceVertices, colors[3]);

    // Top face
    GLPoint topFaceVertices[4] = { vertices[3], vertices[2], vertices[6], vertices[7] };
    drawSquare(topFaceVertices, colors[4]);

    // Bottom face
    GLPoint bottomFaceVertices[4] = { vertices[0], vertices[1], vertices[5], vertices[4] };
    drawSquare(bottomFaceVertices, colors[5]);
}

GLfloat angleX = 0.0f;
GLfloat angleY = 0.0f;

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    glTranslatef(0.0f, 0.0f, -5.0f);
    glRotatef(angleX, 1.0f, 0.0f, 0.0f);
    glRotatef(angleY, 0.0f, 1.0f, 0.0f);

    GLPoint origin1 = {0.0f, 0.0f, 0.0f};
    GLfloat size = 1.0f;
    drawCube(origin1, size);

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

void timer(int value) {
    angleX += 1.0f;
    angleY += 1.0f;

    glutPostRedisplay();
    glutTimerFunc(16, timer, 0);
}

int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowPosition(300,200);
    glutInitWindowSize(320,320);
    glutCreateWindow("SP Engine");

    glEnable(GL_DEPTH_TEST);
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutTimerFunc(0, timer, 0);

    glutMainLoop();
    return 0;
}