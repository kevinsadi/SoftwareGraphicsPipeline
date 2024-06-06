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
    std::filesystem::path projectRootPath = executablePath.parent_path().parent_path();
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
        triangles.push_back(triangle);
    }

    std::cout << "added " << triangles.size() << " number of triangles" << std::endl;
}