#include <SFML/Graphics.hpp>
#include <cstdio>
#include <iostream>
#include <memory>
#include <unordered_map>
#include <vector>

#include "utils.h"

using std::cout;
using std::endl;
using std::make_unique;
using std::move;
using std::shared_ptr;
using std::unique_ptr;
using std::unordered_map;
using std::vector;
using DrawablePtr = shared_ptr<sf::Drawable>;
using ShapePtr = shared_ptr<sf::Shape>;

// Globals

// End of Globals

class Player
{
public:
    enum Direction
    {
        UP = 0,
        DOWN,
        LEFT,
        RIGHT
    };
    Player() : _shape(nullptr)
    {
    }
    Player(const ShapePtr& shape) : _shape(shape)
    {
    }
    void setMoveDirection(Direction dir, bool yes)
    {
        _moves[dir] = yes;
    }
    void move()
    {
        assert(_shape != nullptr);
        for (int i = 0; i < 4; i++)
        {
            if (_moves[i])
            {
                _shape->move(_unitMoves[i] * _moveScaler);
            }
        }
    }

    ShapePtr getShape()
    {
        return _shape;
    }

private:
    ShapePtr _shape;
    vector<bool> _moves = {false, false, false, false};
    vector<sf::Vector2f> _unitMoves = {sf::Vector2f{0.f, -1.f}, sf::Vector2f{0.f, 1.f}, sf::Vector2f{-1.f, 0.f},
                                       sf::Vector2f{1.f, 0.f}};
    const float _moveScaler{1.f};
};

class Game
{
public:
    Game()
    {
        setupDrawables();
    }
    virtual ~Game() = default;
    virtual void handleEvent(const sf::Event& event)
    {
        switch (event.type)
        {
        case sf::Event::Closed:
            // clean up logic should go here
            break;
        case sf::Event::KeyPressed:
            handleKeyEvent(event.key, true);
            break;
        case sf::Event::KeyReleased:
            handleKeyEvent(event.key, false);
            break;
        default:
            break;
        }
    }

    virtual void update()
    {
        _player->move();
    }

    const vector<DrawablePtr>& getDrawables() const
    {
        return _drawables;
    }

protected:
    void handleKeyEvent(const sf::Event::KeyEvent& keyEvent, bool keyPressed)
    {
        sf::Keyboard::Key key = keyEvent.code;
        switch (key)
        {
        case sf::Keyboard::Up:
            _player->setMoveDirection(Player::UP, keyPressed);
            break;
        case sf::Keyboard::Down:
            _player->setMoveDirection(Player::DOWN, keyPressed);
            break;
        case sf::Keyboard::Left:
            _player->setMoveDirection(Player::LEFT, keyPressed);
            break;
        case sf::Keyboard::Right:
            _player->setMoveDirection(Player::RIGHT, keyPressed);
            break;
        default:
            break;
        }
    }

    virtual void setupDrawables()
    {
        _player = make_unique<Player>(std::make_shared<sf::CircleShape>(100.f));
        _player->getShape()->setFillColor(sf::Color::Green);
        _drawables.push_back(_player->getShape());
    }

private:
    unique_ptr<Player> _player; // should go to Game subclass
    vector<DrawablePtr> _drawables = {};
};

void pollAndHandleEvents(sf::RenderWindow& window, Game& game)
{
    sf::Event event;
    while (window.pollEvent(event))
    {
        // dispatch event
        game.handleEvent(event);
        if (event.type == sf::Event::Closed)
        {
            window.close();
        }
    }
}

void draw(sf::RenderWindow& window, const vector<DrawablePtr>& drawables)
{
    window.clear();
    for (const auto& thing : drawables)
        window.draw(*thing);
    window.display();
}

void runLoop(sf::RenderWindow& window, Game& game)
{
    while (window.isOpen())
    {
        pollAndHandleEvents(window, game);
        game.update();
        draw(window, game.getDrawables());
    }
}

unique_ptr<sf::RenderWindow> setupWindow()
{
    auto window = make_unique<sf::RenderWindow>(sf::VideoMode(640, 480, 32), "SFML works!", sf::Style::Default);
    if (!window)
        exit(-1);
    window->setFramerateLimit(60);
    return window;
}

int main([[maybe_unused]] int argc, [[maybe_unused]] char** argv)
{
    auto window = setupWindow();
    Game game;
    runLoop(*window, game);

    return 0;
}
