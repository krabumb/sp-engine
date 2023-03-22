#include "drawLib.h"
#include <math.h>
#include <stdio.h>

typedef struct SphereCache {
    long size;
    GLPoint** triangle1;
    GLPoint** triangle2;
} SphereCache;

SphereCache sphereCache;
char is_sphere_cached = 0;

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

    GLColor color1 = {1.0f, 0.0f, 0.0f};
    GLColor color2 = {0.0f, 1.0f, 0.0f};

    if (is_sphere_cached == 1) {
        for (long i = 0; i < sphereCache.size; i++) {
            drawTriangle(sphereCache.triangle1[i], color1);
            drawTriangle(sphereCache.triangle2[i], color2);
        }
        printf("%ld\n", sphereCache.size);
        return;
    }

    long num_latitude_segments = (long)(M_PI * radius / size_of_triangle_vertice);
    long num_longitude_segments = (long)(2.0f * M_PI * radius / size_of_triangle_vertice);

    long mallocation = num_latitude_segments*num_longitude_segments;

    sphereCache.size = mallocation;
    sphereCache.triangle1 = malloc(sizeof(GLPoint[mallocation][3]));
    sphereCache.triangle2 = malloc(sizeof(GLPoint[mallocation][3]));

    GLfloat lat_increment = M_PI / num_latitude_segments;
    GLfloat lon_increment = 2.0f * M_PI / num_longitude_segments;
    GLfloat lat_angle, lon_angle;

    GLfloat sin_lat[num_latitude_segments + 1], cos_lat[num_latitude_segments + 1];
    GLfloat sin_lon[num_longitude_segments + 1], cos_lon[num_longitude_segments + 1];

    for (long lat_index = 0; lat_index <= num_latitude_segments; lat_index++) {
        lat_angle = lat_index * lat_increment;
        sin_lat[lat_index] = sin(lat_angle);
        cos_lat[lat_index] = cos(lat_angle);
    }

    for (long lon_index = 0; lon_index <= num_longitude_segments; lon_index++) {
        lon_angle = lon_index * lon_increment;
        sin_lon[lon_index] = sin(lon_angle);
        cos_lon[lon_index] = cos(lon_angle);
    }

    long indice = 0;
    for (long lat_index = 0; lat_index < num_latitude_segments; lat_index++) {
        for (long lon_index = 0; lon_index < num_longitude_segments; lon_index++) {
            GLPoint vertices[4] = {
                    {
                            origin.posX + radius * sin_lat[lat_index] * cos_lon[lon_index],
                            origin.posY + radius * sin_lat[lat_index] * sin_lon[lon_index],
                            origin.posZ + radius * cos_lat[lat_index]
                    },
                    {
                            origin.posX + radius * sin_lat[lat_index + 1] * cos_lon[lon_index],
                            origin.posY + radius * sin_lat[lat_index + 1] * sin_lon[lon_index],
                            origin.posZ + radius * cos_lat[lat_index + 1]
                    },
                    {
                            origin.posX + radius * sin_lat[lat_index + 1] * cos_lon[lon_index + 1],
                            origin.posY + radius * sin_lat[lat_index + 1] * sin_lon[lon_index + 1],
                            origin.posZ + radius * cos_lat[lat_index + 1]
                    },
                    {
                            origin.posX + radius * sin_lat[lat_index] * cos_lon[lon_index + 1],
                            origin.posY + radius * sin_lat[lat_index] * sin_lon[lon_index + 1],
                            origin.posZ + radius * cos_lat[lat_index]
                    }
            };

            // Draw the first triangle
            GLPoint* triangle1 = malloc(sizeof(GLPoint[3]));
            triangle1[0] = vertices[0];
            triangle1[1] = vertices[1];
            triangle1[2] = vertices[2];
            drawTriangle(triangle1, color1);
            sphereCache.triangle1[indice] = triangle1;

            // Draw the second triangle
            GLPoint* triangle2 = malloc(sizeof(GLPoint[3]));
            triangle2[0] = vertices[2];
            triangle2[1] = vertices[3];
            triangle2[2] = vertices[0];
            drawTriangle(triangle2, color2);
            sphereCache.triangle2[indice] = triangle2;

            indice++;
        }
    }

    is_sphere_cached = 1;
}