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
    Triangle(const Eigen::Vector3f &a, const Eigen::Vector3f &b, const Eigen::Vector3f &c);
    ~Triangle() = default;

    void computeNormal();
    Eigen::Vector3f getNormal() const;
    void setColor(const Eigen::Vector3f &color);

    // let's make this a const static member so it is shared among all instances of the triangle class
    static const Eigen::Vector3f ERROR_COLOR;
};