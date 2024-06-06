#pragma once

#include <Eigen/Dense>
#include <fstream>
#include <vector>
#include <iostream>
#include <filesystem>

#include "Triangle.hpp"

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
    float m_fov;
    float m_near;
    float m_far;
    Eigen::Vector3f m_matColor;
    
    std::vector<Triangle> triangles;

public:
    Scene();

    /**
     * Given a filePath to a raw model format, load it into the scene as a std::vector of `Triangle`s
    */
    void loadScene(std::string& filePath);

};