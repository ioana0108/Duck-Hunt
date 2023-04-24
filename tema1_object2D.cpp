#include "tema1_object2D.h" //dgvhghjhjjkhkjjkj

#include <vector>
//#include "brickbreaker/generic/circle.h" //??
#include "core/engine.h"
#include "utils/gl_utils.h"


Mesh* object2D_t1::CreateSquare(
    const std::string &name,
    glm::vec3 leftBottomCorner,
    float length,
    glm::vec3 color,
    bool fill) // semnatura formei, cum ar veni
{
    glm::vec3 corner = leftBottomCorner;

    std::vector<VertexFormat> vertices =
    {
        VertexFormat(corner, color),
        VertexFormat(corner + glm::vec3(length, 0, 0), color),
        VertexFormat(corner + glm::vec3(length, length, 0), color),
        VertexFormat(corner + glm::vec3(0, length, 0), color)
    };

    Mesh* square = new Mesh(name);
    std::vector<unsigned int> indices = { 0, 1, 2, 3 };

    if (!fill) {
        square->SetDrawMode(GL_LINE_LOOP);
    } else {
        // Draw 2 triangles. Add the remaining 2 indices
        indices.push_back(0);
        indices.push_back(2);
    }

    square->InitFromData(vertices, indices);
    return square;
}

Mesh* object2D_t1::CreateRectangle(
    const std::string& name,
    glm::vec3 leftBottomCorner,
    float length,
    glm::vec3 color,
    bool fill) // semnatura formei, cum ar veni
{
    glm::vec3 corner = leftBottomCorner;

    std::vector<VertexFormat> vertices =
    {
        VertexFormat(corner, color),
        VertexFormat(corner + glm::vec3(5*length, 0, 0), color),
        VertexFormat(corner + glm::vec3(5*length, length, 0), color),
        VertexFormat(corner + glm::vec3(0, length, 0), color)
    };

    Mesh* square = new Mesh(name);
    std::vector<unsigned int> indices = { 0, 1, 2, 3 };

    if (!fill) {
        square->SetDrawMode(GL_LINE_LOOP);
    }
    else {
        // Draw 2 triangles. Add the remaining 2 indices
        indices.push_back(0);
        indices.push_back(2);
    }

    square->InitFromData(vertices, indices);
    return square;
}


/*
Mesh* object2D_circle::CreateCircle(
    const std::string &name, 
    glm::vec3 center, 
    float radius, 
    glm::vec3 color)
        //: AnimatedMesh(name) 
{

    float theta = 0;
    float x, y;

    std::vector<VertexFormat> vertices;
    std::vector<unsigned int> indices;

    vertices.push_back(VertexFormat(center, color));

    while (theta <= 6.5) {
        x = radius * cos(theta);
        y = radius * sin(theta);
        vertices.push_back(VertexFormat(glm::vec3(x, y, 0) + center, color));
        theta += 0.1f;
    }

    for (int i = 1; i < vertices.size() - 1; i++) {
        indices.push_back(0);
        indices.push_back(i);
        indices.push_back(i + 1);
    }

    Mesh* circle = new Mesh(name);
    //circle->SetDrawMode(GL_TRIANGLE_FAN);
    circle->InitFromData(vertices, indices);
    //InitFromData(vertices, indices);
}
*/
  //  Circle::~Circle() {}
  // namespace animatedmesh



