#include "drawLib.h"
#include <math.h>
#include <stdio.h>

typedef struct SphereCache {
    long num_vertices;
    long num_indices;
    GLfloat* vertices;
    GLuint* indices;
} SphereCache;

SphereCache sphereCache;
char is_sphere_cached = 0;

GLuint sphereVBO;
GLuint sphereIBO;
char vboIboInit = 0;

// Function to initialize the VBO and IBO
void initSphereVBOandIBO() {
    glGenBuffers(1, &sphereVBO);
    glGenBuffers(1, &sphereIBO);
}

// Function to delete the VBO and IBO
void deleteSphereVBOandIBO() {
    glDeleteBuffers(1, &sphereVBO);
    glDeleteBuffers(1, &sphereIBO);
}

void drawTriangle(GLPoint vertices[3], GLColor color) {
    glBegin(GL_TRIANGLES);
    glColor3f(color.r, color.g, color.b);
    glVertex3f(vertices[0].posX, vertices[0].posY, vertices[0].posZ);
    glVertex3f(vertices[1].posX, vertices[1].posY, vertices[1].posZ);
    glVertex3f(vertices[2].posX, vertices[2].posY, vertices[2].posZ);
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

void drawCircle(GLPoint origin, GLfloat radius, GLfloat size_of_triangle_vertice) {
    // Calculate the number of triangle vertices for a smooth circle
    int num_triangle_vertices = (int)(2.0f * M_PI * radius / size_of_triangle_vertice);
    GLfloat angle_increment = 2.0f * M_PI / num_triangle_vertices;
    GLfloat angle;

    // Color for the triangles
    GLColor color = {0.5f, 0.5f, 0.5f};

    for (int i = 0; i < num_triangle_vertices; i++) {
        angle = i * angle_increment;

        // Calculate the positions of the triangle vertices
        GLPoint triangle_vertices[3] = {
                origin,
                {
                        origin.posX + radius * cos(angle),
                        origin.posY + radius * sin(angle),
                        origin.posZ
                },
                {
                        origin.posX + radius * cos(angle + angle_increment),
                        origin.posY + radius * sin(angle + angle_increment),
                        origin.posZ
                }
        };

        // Draw the triangle
        drawTriangle(triangle_vertices, color);
    }
}

void drawSphere(GLPoint origin, GLfloat radius, GLfloat size_of_triangle_vertice) {

    if (vboIboInit == 0) {
        initSphereVBOandIBO();
        vboIboInit = 1;
    }

    if (is_sphere_cached == 0) {
        long num_latitude_segments = (long)(M_PI * radius / size_of_triangle_vertice);
        long num_longitude_segments = (long)(2.0f * M_PI * radius / size_of_triangle_vertice);

        long num_vertices = (num_latitude_segments + 1) * (num_longitude_segments + 1);
        long num_indices = num_latitude_segments * num_longitude_segments * 6;

        sphereCache.num_vertices = num_vertices;
        sphereCache.num_indices = num_indices;
        sphereCache.vertices = malloc(num_vertices * 3 * sizeof(GLfloat));
        sphereCache.indices = malloc(num_indices * sizeof(GLuint));

        GLfloat lat_increment = M_PI / num_latitude_segments;
        GLfloat lon_increment = 2.0f * M_PI / num_longitude_segments;
        GLfloat lat_angle, lon_angle;

        // Calculate vertex data
        for (long lat_index = 0; lat_index <= num_latitude_segments; lat_index++) {
            lat_angle = lat_index * lat_increment;

            for (long lon_index = 0; lon_index <= num_longitude_segments; lon_index++) {
                lon_angle = lon_index * lon_increment;

                long vertex_index = lat_index * (num_longitude_segments + 1) + lon_index;
                sphereCache.vertices[vertex_index * 3 + 0] = origin.posX + radius * sin(lat_angle) * cos(lon_angle);
                sphereCache.vertices[vertex_index * 3 + 1] = origin.posY + radius * sin(lat_angle) * sin(lon_angle);
                sphereCache.vertices[vertex_index * 3 + 2] = origin.posZ + radius * cos(lat_angle);
            }
        }

        // Calculate index data
        long index = 0;
        for (long lat_index = 0; lat_index < num_latitude_segments; lat_index++) {
            for (long lon_index = 0; lon_index < num_longitude_segments; lon_index++) {
                GLuint vertex_a = lat_index * (num_longitude_segments + 1) + lon_index;
                GLuint vertex_b = (lat_index + 1) * (num_longitude_segments + 1) + lon_index;
                GLuint vertex_c = (lat_index + 1) * (num_longitude_segments + 1) + lon_index + 1;
                GLuint vertex_d = lat_index * (num_longitude_segments + 1) + lon_index + 1;

                sphereCache.indices[index++] = vertex_a;
                sphereCache.indices[index++] = vertex_b;
                sphereCache.indices[index++] = vertex_c;

                sphereCache.indices[index++] = vertex_c;
                sphereCache.indices[index++] = vertex_d;
                sphereCache.indices[index++] = vertex_a;
            }
        }

        // Store the vertex data in VBO
        glBindBuffer(GL_ARRAY_BUFFER, sphereVBO);
        glBufferData(GL_ARRAY_BUFFER, sphereCache.num_vertices * 3 * sizeof(GLfloat), sphereCache.vertices, GL_STATIC_DRAW);

        // Store the index data in IBO
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, sphereIBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sphereCache.num_indices * sizeof(GLuint), sphereCache.indices, GL_STATIC_DRAW);

        is_sphere_cached = 1;
    }

    glEnableClientState(GL_VERTEX_ARRAY);

    // Bind the sphere VBO and IBO
    glBindBuffer(GL_ARRAY_BUFFER, sphereVBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, sphereIBO);

    // Set the vertex pointer
    glVertexPointer(3, GL_FLOAT, 0, 0);

    // Draw the sphere using the index buffer object
    glDrawElements(GL_TRIANGLES, sphereCache.num_indices, GL_UNSIGNED_INT, 0);

    // Unbind the sphere VBO and IBO
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    glDisableClientState(GL_VERTEX_ARRAY);
}