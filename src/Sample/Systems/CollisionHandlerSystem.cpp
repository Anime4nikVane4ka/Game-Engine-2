#include "CollisionHandlerSystem.h"

#include <algorithm>
#include <vector>

void CollisionHandlerSystem::OnInit()
{
}

void CollisionHandlerSystem::AddEntityToRemove(std::vector<int>& entitiesToRemove, const int entity)
{
    if (std::find(entitiesToRemove.begin(), entitiesToRemove.end(), entity) == entitiesToRemove.end())
        entitiesToRemove.push_back(entity);
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

                AddEntityToRemove(entitiesToRemove, entity);
                AddEntityToRemove(entitiesToRemove, collidedEntity);
                break;
            }
            else if (_players.Has(collidedEntity))
            {
                const int score = _players.Get(collidedEntity).Score;
                const int eventEntity = world.CreateEntity();
                _gameOverEvents.Add(eventEntity, GameOverEvent(collidedEntity, score));

                AddEntityToRemove(entitiesToRemove, entity);
                AddEntityToRemove(entitiesToRemove, collidedEntity);
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



