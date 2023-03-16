#include "drawLib.h"

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

void drawPyramidBase3(GLPoint origin, GLfloat size){
    float halfSize = size / 2.0f;
    GLPoint triangleBase[3] = {
            {origin.posX + halfSize,  origin.posY - halfSize, origin.posZ},
            {origin.posX - halfSize, origin.posY - halfSize, origin.posZ - halfSize},
            {origin.posX - halfSize, origin.posY - halfSize, origin.posZ + halfSize}
    };
    GLPoint triangleSideOne[3] = {
            {origin.posX,  origin.posY + halfSize, origin.posZ},
            {origin.posX - halfSize, origin.posY - halfSize, origin.posZ - halfSize},
            {origin.posX - halfSize, origin.posY - halfSize, origin.posZ + halfSize}
    };
    GLPoint triangleSideTwo[3] = {
            {origin.posX + halfSize,  origin.posY - halfSize, origin.posZ},
            {origin.posX, origin.posY + halfSize, origin.posZ},
            {origin.posX - halfSize, origin.posY - halfSize, origin.posZ + halfSize}
    };
    GLPoint triangleSideThree[3] = {
            {origin.posX + halfSize,  origin.posY - halfSize, origin.posZ},
            {origin.posX - halfSize, origin.posY - halfSize, origin.posZ - halfSize},
            {origin.posX, origin.posY + halfSize, origin.posZ}
    };
    drawTriangle(triangleBase, (GLColor){1.0f, 0.0f, 0.0f});
    drawTriangle(triangleSideOne, (GLColor){0.0f, 1.0f, 0.0f});
    drawTriangle(triangleSideTwo, (GLColor){0.0f, 0.0f, 1.0f});
    drawTriangle(triangleSideThree, (GLColor){1.0f, 0.0f, 1.0f});
}