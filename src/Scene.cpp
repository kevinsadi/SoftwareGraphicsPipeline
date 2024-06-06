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
        
        Triangle triangle(Eigen::Vector3f(v1x, v1y, v1z), Eigen::Vector3f(v2x, v2y, v2z), Eigen::Vector3f(v3x, v3y, v3z));
        m_triangles.push_back(triangle);
    }

    std::cout << "added " << m_triangles.size() << " number of triangles" << std::endl;
}

void Scene::applyWorldTransform()
{
    // LHS, row-coordinate convention 
    Eigen::Matrix4f transformMat(1, 0, 0, 0,
                                 0, 1, 0, 0,
                                 0, 0, 1, 0,
                                 m_modelPosition.x(), m_modelPosition.y(), m_modelPosition.z(), 1);

    Eigen::Matrix4f rotateXMat(1, 0, 0, 0,
                               0, cos(m_modelXRotation), sin(m_modelXRotation), 0,
                               0, -sin(m_modelXRotation), cos(m_modelXRotation), 0,
                               0, 0, 0, 1);

    Eigen::Matrix4f rotateYMat(cos(m_modelYRotation), 0, -sin(m_modelYRotation), 0,
                                0, 1, 0, 0,
                                sin(m_modelYRotation), 0, cos(m_modelYRotation), 0,
                                0, 0, 0, 1);

    Eigen::Matrix4f rotateZMat(cos(m_modelZRotation), sin(m_modelZRotation), 0, 0,
                                -sin(m_modelZRotation), cos(m_modelZRotation), 0, 0,
                                0, 0, 1, 0,
                                0, 0, 0, 1);

    for (Triangle& tri: m_triangles)
    {
    }
}

void Scene::applyViewTransform()
{
   
}

void Scene::applyPerspectiveTransform()
{
    
}