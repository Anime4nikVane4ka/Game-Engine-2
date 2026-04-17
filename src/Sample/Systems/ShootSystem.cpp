#include "ShootSystem.h"

void ShootSystem::OnInit()
{
}

void ShootSystem::OnUpdate()
{
    for (const auto eventEntity : _shootEvents)
    {
        auto& shootEvent = _shootInputEvents.Get(eventEntity);
        const int shooterEntity = shootEvent.Entity;

        if (shootEvent.Shoot
            && _shooterComponents.Has(shooterEntity)
            && _positions.Has(shooterEntity))
        {
            auto& shooter = _shooterComponents.Get(shooterEntity); // Получение компонента стрельбы
            if (shooter.CanShoot)
            {
                const auto& shooterPosition = _positions.Get(shooterEntity);
                const int bulletEntity = world.CreateEntity();

                _positions.Add(bulletEntity, PositionComponent(
                    shooterPosition.Position.x,
                    shooterPosition.Position.y));
                _movements.Add(bulletEntity, MovementComponent(8.0f, 0.0f, -1.0f));
                _boxColliders.Add(bulletEntity, BoxColliderComponent(6.0f, 16.0f));
                _rectangleShapes.Add(bulletEntity, RectangleShapeComponent(6.0f, 16.0f, sf::Color::Yellow));
                _collisions.Add(bulletEntity, CollisionComponent());
                _bullets.Add(bulletEntity, BulletComponent(shooterEntity));

                shooter.Shot();
            }
        }

        world.RemoveEntity(eventEntity);
    }
}
