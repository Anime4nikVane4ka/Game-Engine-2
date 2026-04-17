#include "CollisionHandlerSystem.h"

#include <vector>

void CollisionHandlerSystem::OnInit()
{
}

void CollisionHandlerSystem::OnUpdate()
{
    std::vector<int> entitiesToRemove;

    for (const auto entity : _collidableEntities)
    {
        if (!_asteroids.Has(entity)) // Если не астероид, скипаем
            continue;

        const auto& collision = _collisions.Get(entity);
        for (const int collidedEntity : collision.CollidedEntities)
        {
            if (_bullets.Has(collidedEntity))
            {
                const int playerEntity = _bullets.Get(collidedEntity).Owner;
                const int eventEntity = world.CreateEntity();
                _scoreIncreaseEvents.Add(eventEntity, ScoreIncreaseEvent(playerEntity, _scorePerAsteroid));

                entitiesToRemove.push_back(entity);
                entitiesToRemove.push_back(collidedEntity);
                break;
            }
            else if (_players.Has(collidedEntity))
            {
                const int score = _players.Get(collidedEntity).Score;
                const int eventEntity = world.CreateEntity();
                _gameOverEvents.Add(eventEntity, GameOverEvent(collidedEntity, score));

                entitiesToRemove.push_back(entity);
                entitiesToRemove.push_back(collidedEntity);
                break;
            }
        }
    }

    for (const int entity : entitiesToRemove)
    {
        if (world.IsEntityAlive(entity))
            world.RemoveEntity(entity);
    }
}

