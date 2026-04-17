#include "RestartSystem.h"

#include <algorithm>

#include <SFML/Graphics/Color.hpp>
#include <SFML/System/Vector2.hpp>

#include "../../Config.h"

void RestartSystem::OnInit()
{
    Config config("config.txt");
    _playerSpeed = config.getFloat("player_speed");
    _shootCooldown = config.getFloat("shoot_cooldown");
    _windowWidth = config.getFloat("window_width");
    _windowHeight = config.getFloat("window_height");

    CreateGameState();
    CreatePlayer();
}

void RestartSystem::AddEntityToRemove(std::vector<int>& entitiesToRemove, const int entity) const
{
    if (std::find(entitiesToRemove.begin(), entitiesToRemove.end(), entity) == entitiesToRemove.end())
        entitiesToRemove.push_back(entity);
}

void RestartSystem::ResetGameState()
{
    for (const int entity : _gameStatesFilter)
    {
        auto& gameState = _gameStates.Get(entity);
        gameState.IsGameOver = false;
        gameState.Player = -1;
        gameState.Score = 0;
    }
}

void RestartSystem::CreateGameState()
{
    const int gameStateEntity = world.CreateEntity();
    _gameStates.Add(gameStateEntity, GameStateComponent(false, -1, 0));
}

void RestartSystem::CreatePlayer()
{
    const int player = world.CreateEntity();

    _positions.Add(player, PositionComponent(_windowWidth / 2.0f, _windowHeight - 60.0f));
    _movements.Add(player, MovementComponent(_playerSpeed, sf::Vector2f(0.0f, 0.0f)));
    _players.Add(player, PlayerComponent());
    _shooters.Add(player, ShooterComponent(_shootCooldown));
    _boxColliders.Add(player, BoxColliderComponent(48.0f, 24.0f));
    _circleShapes.Add(player, CircleShapeComponent(24.0f, 3, sf::Color::Green));
    _collisions.Add(player, CollisionComponent());
}

void RestartSystem::OnUpdate()
{
    std::vector<int> restartEvents;
    for (const int entity : _restartInputEvents)
        restartEvents.push_back(entity);

    if (restartEvents.empty())
        return;

    std::vector<int> entitiesToRemove;

    for (const int entity : restartEvents)
        AddEntityToRemove(entitiesToRemove, entity);
    for (const int entity : _asteroids)
        AddEntityToRemove(entitiesToRemove, entity);
    for (const int entity : _bullets)
        AddEntityToRemove(entitiesToRemove, entity);
    for (const int entity : _playersFilter)
        AddEntityToRemove(entitiesToRemove, entity);
    for (const int entity : _scoreIncreaseEvents)
        AddEntityToRemove(entitiesToRemove, entity);
    for (const int entity : _gameOverEvents)
        AddEntityToRemove(entitiesToRemove, entity);

    for (const int entity : entitiesToRemove)
    {
        if (world.IsEntityAlive(entity))
            world.RemoveEntity(entity);
    }

    ResetGameState();
    CreatePlayer();
}

