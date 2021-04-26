#include <SFML/Graphics.hpp>
#include <cstdio>
#include <iostream>
#include <memory>
#include <vector>

#include "utils.h"

using std::cout;
using std::endl;
using std::make_unique;
using std::move;
using std::shared_ptr;
using std::unique_ptr;
using std::vector;
using DrawablePtr = unique_ptr<sf::Drawable>;

vector<DrawablePtr> drawables = {};

const vector<DrawablePtr>& getDrawables()
{
    return drawables;
}

void handleEvent(const sf::Event& event, sf::RenderWindow& window)
{
    switch (event.type)
    {
    case sf::Event::Closed:
        window.close();
        break;
    default:
        break;
    }
}

void pollAndHandleEvents(sf::RenderWindow& window)
{
    sf::Event event;
    while (window.pollEvent(event))
    {
        // dispatch event
        handleEvent(event, window);
    }
}

void draw(sf::RenderWindow& window)
{
    window.clear();
    for (const auto& thing : getDrawables())
        window.draw(*thing);
    window.display();
}

void runLoop(sf::RenderWindow& window)
{
    while (window.isOpen())
    {
        pollAndHandleEvents(window);
        draw(window);
    }
}

void setupDrawables(vector<DrawablePtr>& drawables)
{
    auto circle = std::make_unique<sf::CircleShape>(100.f);
    circle->setFillColor(sf::Color::Green);
    drawables.push_back(std::move(circle));
}

unique_ptr<sf::RenderWindow> setupWindow()
{
    return make_unique<sf::RenderWindow>(sf::VideoMode(640, 480, 32), "SFML works!", sf::Style::Default);
}

int main([[maybe_unused]] int argc, [[maybe_unused]] char** argv)
{
    auto window = setupWindow();
    setupDrawables(drawables);
    runLoop(*window);

    return 0;
}
