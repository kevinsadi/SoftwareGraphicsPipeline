#include "Scene.hpp"

Scene::Scene() :  
    m_lightPosition(1.0f, 0.0f, 0.0f),
    m_cameraPosition(0.0f, 0.0f, 1.0f),
    m_cameraDirection(0.0f, 0.0f, -1.0f),
    m_modelPosition(0.0f, 0.0f, 0.0f),
    m_modelXRotation(0.0f),
    m_modelYRotation(0.0f),
    m_modelZRotation(0.0f),
    m_fov(45.0f),
    m_near(0.1f),
    m_far(100.0f),
    m_matColor(1.0f, 0.0f, 0.0f)
{
}

void Scene::loadScene(std::string& filePath) 
{
    std::filesystem::path executablePath = std::filesystem::current_path();
    std::filesystem::path fullPath = executablePath / filePath;
    fullPath.make_preferred();

    if (!std::filesystem::exists(fullPath))
    {
        std::cout << fullPath << std::endl;
        std::cerr << "Unable to open the model. It seems the file doesn't exist.";
        return;
    }

    std::ifstream file(fullPath);
    if (!file.is_open()) 
    {
        std::cout << fullPath << std::endl;
        std::cerr << "Unable to open the model." << std::endl;
        return;
    }

    std::string curLine;
    while (std::getline(file, curLine)) 
    {
        std::istringstream stringStream(curLine);

        // This is dirty but I should get to the actual assignment
        float v1x, v1y, v1z;
        float v2x, v2y, v2z;
        float v3x, v3y, v3z;

        stringStream >> v1x >> v1y >> v1z
                     >> v2x >> v2y >> v2z
                     >> v3x >> v3y >> v3z;
        
        Triangle triangle(Eigen::RowVector4f(v1x, v1y, v1z, 1), Eigen::RowVector4f(v2x, v2y, v2z, 1), Eigen::RowVector4f(v3x, v3y, v3z, 1));
        m_triangles.push_back(triangle);
    }

    std::cout << "added " << m_triangles.size() << " number of triangles" << std::endl;
}

void Scene::applyWorldTransform()
{
    // LHS, row-coordinate convention 
    Eigen::Matrix4f translateMat;
    translateMat << 1, 0, 0, 0,
                    0, 1, 0, 0,
                    0, 0, 1, 0,
                    m_modelPosition.x(), m_modelPosition.y(), m_modelPosition.z(), 1;

    Eigen::Matrix4f rotateXMat;
    rotateXMat <<   1, 0, 0, 0,
                    0, cos(m_modelXRotation), sin(m_modelXRotation), 0,
                    0, -sin(m_modelXRotation), cos(m_modelXRotation), 0,
                    0, 0, 0, 1;

    Eigen::Matrix4f rotateYMat;
    rotateYMat << cos(m_modelYRotation), 0, -sin(m_modelYRotation), 0,
                    0, 1, 0, 0,
                    sin(m_modelYRotation), 0, cos(m_modelYRotation), 0,
                    0, 0, 0, 1;

    Eigen::Matrix4f rotateZMat;
    rotateZMat << cos(m_modelZRotation), sin(m_modelZRotation), 0, 0,
                    -sin(m_modelZRotation), cos(m_modelZRotation), 0, 0,
                    0, 0, 1, 0,
                    0, 0, 0, 1;

    for (Triangle& tri: m_triangles)
    {
        tri.transformVertsByMat4(rotateXMat);
        tri.transformVertsByMat4(rotateYMat);
        tri.transformVertsByMat4(rotateZMat);
        tri.transformVertsByMat4(translateMat);
        // COMPUTE NORMAL AFTER WORLD SPACE TRANSFORM, FOR LIGHTING
        tri.computeNormal();
    }
    std::cout << "Applied World Transform" << std::endl;
}

void Scene::applyViewTransform()
{
    Eigen::Vector3f up(0.0, 1.0, 0.0);

    Eigen::Vector3f zAxis = (m_cameraPosition - m_cameraDirection).normalized();
    Eigen::Vector3f xAxis = up.cross(zAxis);
    Eigen::Vector3f yAxis = zAxis.cross(xAxis);

    Eigen::Matrix4f viewMat;
    viewMat <<  xAxis.x(), yAxis.x(), zAxis.x(), 0,
                xAxis.y(), yAxis.y(), zAxis.y(), 0, 
                xAxis.z(), yAxis.z(), zAxis.z(), 0, 
                -xAxis.dot(m_cameraPosition), -yAxis.dot(m_cameraPosition), -zAxis.dot(m_cameraPosition), 1; 

    for (Triangle& tri: m_triangles)
    {
        tri.transformVertsByMat4(viewMat);
    }
    std::cout << "Applied View Transform" << std::endl;
}

void Scene::applyPerspectiveTransform()
{
    
}

void Scene::calculateLighting()
{
    std::cout << "KEVIN COME BACK AND DO LIGHTING" << std::endl;
}

void Scene::renderScene(sf::RenderWindow& window) const
{
    sf::VertexArray triangle(sf::Triangles, 3);
    triangle[0].position = sf::Vector2f(400, 100);
    triangle[1].position = sf::Vector2f(200, 500);
    triangle[2].position = sf::Vector2f(600, 500);

    window.draw(triangle);
}