#include "InputSystem.h"

void InputSystem::OnInit()
{
}

void InputSystem::OnUpdate()
{
    const bool shoot = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space);

    sf::Vector2f direction(0.0f, 0.0f);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left))
    {
        direction.x -= 1.0f;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right))
    {
        direction.x += 1.0f;
    }

    for (const auto player : _players)
    {
        auto& movement = _movementComponents.Get(player);
        movement.Direction = direction;

        if (shoot)
        {
            const int eventEnt = world.CreateEntity();
            _eventComponents.Add(eventEnt, ShootInputEvent(player, true));
        }
    }
}
