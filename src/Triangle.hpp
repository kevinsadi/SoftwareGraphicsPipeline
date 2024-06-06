#pragma once

#include <Eigen/Dense>

class Triangle
{
private:
    Eigen::RowVector4f m_a;
    Eigen::RowVector4f m_b;
    Eigen::RowVector4f m_c;

    Eigen::Vector3f m_normal;
    Eigen::Vector3f m_color;

public:
    Triangle();
    Triangle(const Eigen::RowVector4f &a, const Eigen::RowVector4f &b, const Eigen::RowVector4f &c);
    ~Triangle() = default;

    void computeNormal();
    Eigen::Vector3f getNormal() const;
    void setColor(const Eigen::Vector3f &color);
    void transformVertsByMat4(Eigen::Matrix4f& mat);

    // let's make this a const static member so it is shared among all instances of the triangle class
    static const Eigen::Vector3f ERROR_COLOR;
};