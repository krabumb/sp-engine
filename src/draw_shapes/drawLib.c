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

void drawPyramidBase3(GLPoint origin, GLfloat size) {
    float halfSize = size / 2.0f;

    GLPoint vertices[4] = {
            {origin.posX, origin.posY + halfSize, origin.posZ},
            {origin.posX + halfSize, origin.posY - halfSize, origin.posZ},
            {origin.posX - halfSize, origin.posY - halfSize, origin.posZ - halfSize},
            {origin.posX - halfSize, origin.posY - halfSize, origin.posZ + halfSize}
    };

    GLColor colors[4] = {
            {1.0f, 0.0f, 0.0f}, // Red
            {0.0f, 1.0f, 0.0f}, // Green
            {0.0f, 0.0f, 1.0f}, // Blue
            {1.0f, 0.0f, 1.0f}  // Magenta
    };

    int triangleIndices[4][3] = {
            {1, 2, 3}, // Base triangle
            {0, 2, 3}, // Side triangle 1
            {1, 0, 3}, // Side triangle 2
            {1, 2, 0}  // Side triangle 3
    };

    for (int i = 0; i < 4; i++) {
        GLPoint triangle[3] = {
                vertices[triangleIndices[i][0]],
                vertices[triangleIndices[i][1]],
                vertices[triangleIndices[i][2]]
        };
        drawTriangle(triangle, colors[i]);
    }
}

void drawPyramidBase4(GLPoint origin, GLfloat size) {
    float halfSize = size / 2.0f;

    GLPoint vertices[5] = {
            {origin.posX, origin.posY + halfSize, origin.posZ}, // Apex
            {origin.posX + halfSize, origin.posY - halfSize, origin.posZ + halfSize}, // Base vertex 1
            {origin.posX + halfSize, origin.posY - halfSize, origin.posZ - halfSize}, // Base vertex 2
            {origin.posX - halfSize, origin.posY - halfSize, origin.posZ - halfSize}, // Base vertex 3
            {origin.posX - halfSize, origin.posY - halfSize, origin.posZ + halfSize}  // Base vertex 4
    };

    GLColor colors[5] = {
            {1.0f, 0.0f, 0.0f}, // Red
            {0.0f, 1.0f, 0.0f}, // Green
            {0.0f, 0.0f, 1.0f}, // Blue
            {1.0f, 0.0f, 1.0f}, // Magenta
            {1.0f, 1.0f, 0.0f}  // Yellow
    };

    int triangleIndices[4][3] = {
            {0, 1, 2}, // Side triangle 1
            {0, 2, 3}, // Side triangle 2
            {0, 3, 4}, // Side triangle 3
            {0, 4, 1}  // Side triangle 4
    };

    // Draw the base using the drawSquare function
    GLPoint baseVertices[4] = {vertices[1], vertices[2], vertices[3], vertices[4]};
    drawSquare(baseVertices, colors[0]);

    // Draw the side triangles
    for (int i = 1; i <= 4; i++) {
        GLPoint triangle[3] = {
                vertices[triangleIndices[i - 1][0]],
                vertices[triangleIndices[i - 1][1]],
                vertices[triangleIndices[i - 1][2]]
        };
        drawTriangle(triangle, colors[i]);
    }
}
