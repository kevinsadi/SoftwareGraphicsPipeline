#include "Scene.hpp"

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 800), "Software Renderer");

    // Create the scene
    Scene scene;
    scene.loadScene(std::string("Models/chief_ag.raw"));
    scene.applyWorldTransform();
    scene.calculateLighting();
    scene.applyViewTransform();
    scene.applyPerspectiveTransform(window.getSize().x, window.getSize().y);
    scene.sortTriangles();
    //scene.printTriangles();

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
            scene.renderScene(window);
            window.display();
        }
    }

    return 0;
}