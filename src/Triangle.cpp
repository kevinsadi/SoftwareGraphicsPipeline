#include "Triangle.hpp"

const Eigen::Vector3f Triangle::ERROR_COLOR(255, 0, 220);

Triangle::Triangle() :
    m_a(Eigen::Vector3f(0)), m_b(Eigen::Vector3f(0)), m_c(Eigen::Vector3f(0)), m_color(ERROR_COLOR) 
{
}

Triangle::Triangle(const Eigen::Vector3f &a, const Eigen::Vector3f &b, const Eigen::Vector3f &c) :
    m_a(a), m_b(b), m_c(c), m_color(ERROR_COLOR)
{
    m_a = a;
    m_b = b;
    m_c = c;
}

void Triangle::computeNormal()
{
    // assuming right handed rule (counter clockwise winding)
    m_normal = m_a.cross(m_b);
}

void Triangle::setColor(const Eigen::Vector3f &color)
{
    m_color = color;
}


Eigen::Vector3f Triangle::getNormal() const
{
    return m_normal;
}

void Triangle::translateVertsByMat4(Eigen::Matrix4f& mat)
{
}
