#pragma once

#include <fstream>
#include <vector>
#include <iostream>
#include <filesystem>
#include <cmath>

#include <Eigen/Dense>
#include <SFML/Graphics.hpp>

#include "Triangle.hpp"

// some systems don't support cmath? So just in case bc it's been a problem before
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

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
    float m_scale;
    float m_fov;
    float m_near;
    float m_far;
    Eigen::Vector3f m_matColor;
    std::vector<Triangle> m_triangles;

    // return angle in radians
    float radians(const float degrees) const;
    // take cotangent of angle (expected in radians)
    float cotangent(const float radians) const;

public:
    Scene();

    /**
     * Given a filePath to a raw model format, load it into the scene as a std::vector of `Triangle`s
    */
    void loadScene(std::string& filePath);

    void applyWorldTransform();
    void applyViewTransform();
    void applyPerspectiveTransform(float width, float height);

    void calculateLighting();

    void renderScene(sf::RenderWindow& window) const;
    void printTriangles() const;
    void sortTriangles();

};