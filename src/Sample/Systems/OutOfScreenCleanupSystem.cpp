#include "OutOfScreenCleanupSystem.h"

#include <algorithm>
#include <vector>

void OutOfScreenCleanupSystem::OnInit()
{
}

bool OutOfScreenCleanupSystem::IsOutsideScreen(const int entity) const
{
    const auto& position = _positions.Get(entity).Position;

    float halfWidth = 0.0f;
    float halfHeight = 0.0f;

    if (_circleColliders.Has(entity))
    {
        const float radius = _circleColliders.Get(entity).Radius;
        halfWidth = radius;
        halfHeight = radius;
    }
    else if (_boxColliders.Has(entity))
    {
        const auto& extents = _boxColliders.Get(entity).Extents;
        halfWidth = extents.x;
        halfHeight = extents.y;
    }

    return position.x + halfWidth < 0.0f
        || position.x - halfWidth > _screenWidth
        || position.y + halfHeight < 0.0f
        || position.y - halfHeight > _screenHeight;
}

void OutOfScreenCleanupSystem::AddEntityToRemove(std::vector<int>& entitiesToRemove, const int entity) const
{
    if (std::find(entitiesToRemove.begin(), entitiesToRemove.end(), entity) == entitiesToRemove.end())
        entitiesToRemove.push_back(entity);
}

void OutOfScreenCleanupSystem::OnUpdate()
{
    std::vector<int> entitiesToRemove;

    for (const int entity : _asteroidEntities)
    {
        if (IsOutsideScreen(entity))
            AddEntityToRemove(entitiesToRemove, entity);
    }

    for (const int entity : _bulletEntities)
    {
        if (IsOutsideScreen(entity))
            AddEntityToRemove(entitiesToRemove, entity);
    }

    for (const int entity : entitiesToRemove)
    {
        if (world.IsEntityAlive(entity))
            world.RemoveEntity(entity);
    }
}
