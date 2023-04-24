#pragma once

#include <string>

#include "core/gpu/mesh.h"
#include "utils/glm_utils.h"


namespace object2D_t1
{

    // Create square with given bottom left corner, length and color
    Mesh* CreateSquare(const std::string &name, glm::vec3 leftBottomCorner, float length, glm::vec3 color, bool fill = false);

    Mesh* CreateRectangle(const std::string& name, glm::vec3 leftBottomCorner, float length, glm::vec3 color, bool fill = false);
    
    //Circle(std::string name, glm::vec3 center, float radius, glm::vec3 color)
    //Mesh* CreateTr
    //void CreateMesh(const char* name, const std::vector<VertexFormat>& vertices, const std::vector<unsigned int>& indices);
}

/*
namespace object2D_circle
{
    Mesh* CreateCircle(const std::string& name, glm::vec3 center, float radius, glm::vec3 color);
}
*/
