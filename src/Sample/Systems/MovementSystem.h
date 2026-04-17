#ifndef MOVEMENTSYSTEM_H
#define MOVEMENTSYSTEM_H

#include "../../Ecs/Filter/Filter.h"
#include "../../Ecs/Filter/FilterBuilder.h"
#include "../../Ecs/Systems/ISystem.h"

#include "../Components/PositionComponent.h"
#include "../Components/MovementComponent.h"
#include "../Components/PauseStateComponent.h"

class MovementSystem final : public ISystem {
    ComponentStorage<PositionComponent>& _positionComponents;
    ComponentStorage<MovementComponent>& _movementComponents;
    ComponentStorage<PauseStateComponent>& _pauseStates;

    Filter _moveables;

    void Print(int ent); // ��� ���� ����� ������� � ��������� �������

public:
    MovementSystem(World &world)
        : ISystem(world),
            _positionComponents(world.GetStorage<PositionComponent>()),
            _movementComponents(world.GetStorage<MovementComponent>()),
            _pauseStates(world.GetStorage<PauseStateComponent>()),
            _moveables(FilterBuilder(world)
                .With<PositionComponent>()
                .With<MovementComponent>()
                .Build())
    {
    }

    void OnInit() override;

    void OnUpdate() override;
};

#endif //MOVEMENTSYSTEM_H
