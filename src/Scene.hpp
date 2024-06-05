#pragma once

#include <Eigen/Dense>

class Scene 
{
private:
    Eigen::Vector3f m_lightPosition;
    Eigen::Vector3f m_cameraPosition;
    Eigen::Vector3f m_cameraDirection;
    Eigen::Vector3f m_modelPosition;
    float m_modelXRotation;
    float m_modelYRotation;
    float m_modelZRotation;

public:
    Scene();

    /**
     * Given a filePath to a raw model format, load it into the scene as a std::vector of `Triangle`s
    */
    void LoadScene(std::string filePath);

};