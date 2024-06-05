#pragma once

#include <Eigen/Dense>

class Triangle
{
private:
    Eigen::Vector3f m_a;
    Eigen::Vector3f m_b;
    Eigen::Vector3f m_c;

    Eigen::Vector3f m_normal;
    Eigen::Vector3f m_color;

public:
    Triangle();
    Triangle(Eigen::Vector3f a, Eigen::Vector3f b, Eigen::Vector3f c);
    ~Triangle();
    
};