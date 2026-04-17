#include <iostream>
#include <SFML/Graphics.hpp>

#include "Ecs/Systems/SystemsManager.h"
#include "Ecs/World/World.h"

#include "Config.h"

#include "Sample/Systems/AsteroidSpawnSystem.h"
#include "Sample/Systems/CollisionDetectionSystem.h"
#include "Sample/Systems/CollisionHandlerSystem.h"
#include "Sample/Systems/GameOverSystem.h"
#include "Sample/Systems/InputSystem.h"
#include "Sample/Systems/MovementSystem.h"
#include "Sample/Systems/RenderSystem.h"
#include "Sample/Systems/RestartSystem.h"
#include "Sample/Systems/ScoringSystem.h"
#include "Sample/Systems/ShootSystem.h"

int main() {
    // Пример использования
    setlocale(LC_ALL, "");

    Config config("config.txt");
    const int windowWidth = config.getInt("window_width");
    const int windowHeight = config.getInt("window_height");

    sf::RenderWindow window(sf::VideoMode({
        static_cast<unsigned int>(windowWidth),
        static_cast<unsigned int>(windowHeight)
    }), "Test");
    window.setFramerateLimit(60);

    World world;
    SystemsManager systems(world);
    const auto restartSystem = std::make_shared<RestartSystem>(world);
    const auto shootSystem = std::make_shared<ShootSystem>(world);
    const auto asteroidSpawnSystem = std::make_shared<AsteroidSpawnSystem>(world, static_cast<float>(windowWidth));
    const auto renderSystem = std::make_shared<RenderSystem>(world, window);

    systems.AddSystem(std::make_shared<InputSystem>(world));
    systems.AddInitializer(restartSystem);
    systems.AddInitializer(shootSystem);
    systems.AddInitializer(asteroidSpawnSystem);
    systems.AddInitializer(renderSystem);
    systems.AddSystem(restartSystem);
    systems.AddSystem(shootSystem);
    systems.AddSystem(asteroidSpawnSystem);
    systems.AddSystem(std::make_shared<MovementSystem>(world));
    systems.AddSystem(std::make_shared<CollisionDetectionSystem>(world));
    systems.AddSystem(std::make_shared<CollisionHandlerSystem>(world));
    systems.AddSystem(std::make_shared<ScoringSystem>(world));
    systems.AddSystem(std::make_shared<GameOverSystem>(world));
    systems.AddSystem(renderSystem);

    while (window.isOpen()) {
        systems.Update();
    }

    return 0;
}
