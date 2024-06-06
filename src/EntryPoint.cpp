#include "Scene.hpp"

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 800), "Software Renderer");

    sf::VertexArray triangle(sf::Triangles, 3);
    triangle[0].position = sf::Vector2f(400, 100);
    triangle[1].position = sf::Vector2f(200, 500);
    triangle[2].position = sf::Vector2f(600, 500);

    // Create the scene
    Scene scene;
    scene.loadScene(std::string("Models/Mew_lp.raw"));
    scene.applyWorldTransform();
    scene.calculateLighting();
    scene.applyViewTransform();
    scene.applyPerspectiveTransform(window.getSize().x, window.getSize().y);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }

            window.clear();
            window.draw(triangle);
            // scene.renderScene();
            window.display();
        }
    }

    return 0;
}