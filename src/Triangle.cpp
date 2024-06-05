#include "Triangle.hpp"

Triangle::Triangle()
{

}

Triangle::Triangle(Eigen::Vector3f a, Eigen::Vector3f b, Eigen::Vector3f c)
{
    m_a = a;
    m_b = b;
    m_c = c;
}


Triangle::~Triangle()
{
    
}