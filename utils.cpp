#include "utils.h"
#include <string>

std::string event_type_str(const sf::Event& event)
{
    switch (event.type)
    {
    case sf::Event::Closed:
        return "Closed";
    case sf::Event::Count:
        return "Count";
    case sf::Event::GainedFocus:
        return "GainedFocus";
    case sf::Event::KeyPressed:
        return "KeyPressed";
    case sf::Event::KeyReleased:
        return "KeyReleased";
    case sf::Event::LostFocus:
        return "LostFocus";
    case sf::Event::MouseButtonPressed:
        return "MouseButtonPressed";
    case sf::Event::MouseButtonReleased:
        return "MouseButtonReleased";
    case sf::Event::MouseEntered:
        return "MouseEntered";
    case sf::Event::MouseLeft:
        return "MouseLeft";
    case sf::Event::MouseMoved:
        return "MouseMoved";
    case sf::Event::MouseWheelMoved:
        return "MouseWheelMoved";
    case sf::Event::MouseWheelScrolled:
        return "MouseWheelScrolled";
    case sf::Event::Resized:
        return "Resized";
    case sf::Event::SensorChanged:
        return "SensorChanged";
    case sf::Event::TextEntered:
        return "TextEntered";
    case sf::Event::TouchBegan:
        return "TouchBegan";
    case sf::Event::TouchEnded:
        return "TouchEnded";
    default:
        char arr[64] = {0};
        sprintf(arr, "Unknown event type: %d", event.type);
        return arr;
    }
}
