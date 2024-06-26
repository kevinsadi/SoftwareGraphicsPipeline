#include "Triangle.hpp"

const Eigen::Vector3f Triangle::ERROR_COLOR(255, 0, 220);

Triangle::Triangle() :
    m_a(Eigen::RowVector4f(0)), m_b(Eigen::RowVector4f(0)), m_c(Eigen::RowVector4f(0)), m_color(ERROR_COLOR) 
{
}

Triangle::Triangle(const Eigen::RowVector4f &a, const Eigen::RowVector4f &b, const Eigen::RowVector4f &c) :
    m_a(a), m_b(b), m_c(c), m_color(ERROR_COLOR)
{
}

void Triangle::computeNormal()
{
    // assuming right handed rule (counter clockwise winding)
    Eigen::Vector3f v0 = m_a.head<3>();
    Eigen::Vector3f v1 = m_b.head<3>();
    Eigen::Vector3f v2 = m_c.head<3>();
    m_normal = (v1 - v0).cross(v2 - v0).normalized();
}

void Triangle::setColor(const Eigen::Vector3f &color)
{
    m_color = color;
}


Eigen::Vector3f Triangle::getNormal() const
{
    return m_normal;
}

void Triangle::transformVertsByMat4(Eigen::Matrix4f& mat)
{
    m_a = m_a * mat;
    m_b = m_b * mat;
    m_c = m_c * mat;
}

void Triangle::printVerts() const
{
    std::cout << "vert a: (" << m_a << ")," << std::endl; 
    std::cout << "vert b: (" << m_b << ")" << std::endl;
    std::cout << "vert c: (" << m_c << ") " << std::endl;
}

void Triangle::divideVertsByW() 
{
    m_a = m_a / m_a.w();
    m_b = m_b / m_b.w();
    m_c = m_c / m_c.w();
}

Eigen::RowVector4f Triangle::getVertA() const
{
    return m_a;
}

Eigen::RowVector4f Triangle::getVertB() const
{
    return m_b;
}

Eigen::RowVector4f Triangle::getVertC() const
{
    return m_c;
}

void Triangle::calculateLighting(const Eigen::Vector3f& lightPos, const Eigen::Vector3f& matColor)
{
    Eigen::Vector3f triCentroid = (m_a.head<3>() + m_b.head<3>() + m_c.head<3>()) / 3.0f;
    Eigen::Vector3f lightDir = (lightPos - triCentroid).normalized();
    float intensity = std::max(0.0f, (lightDir.dot(m_normal)));
    Eigen::Vector3f triColor = matColor * intensity * 255;
    this->setColor(triColor);
}

Eigen::Vector3f Triangle::getTriColor() const
{
    return m_color;
}