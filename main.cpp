#include <SFML/Graphics.hpp>
#include <cstdio>
#include <iostream>

#include "utils.h"

using namespace std;

int main([[maybe_unused]] int argc, [[maybe_unused]] char** argv)
{
    sf::RenderWindow window(sf::VideoMode(200, 200), "SFML works!");
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            cout << event_type_str(event) << "\n";
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        window.draw(shape);
        window.display();
    }
    return 0;
}
