#ifndef INPUTSYSTEM_H
#define INPUTSYSTEM_H

#include <SFML/Graphics.hpp>

#include "../../Ecs/Filter/Filter.h"
#include "../../Ecs/Filter/FilterBuilder.h"
#include "../../Ecs/Systems/ISystem.h"

#include "../Components/MovementComponent.h"
#include "../Components/PlayerComponent.h"
#include "../Components/ShootInputEvent.h"

class InputSystem : public ISystem {

    ComponentStorage<ShootInputEvent>& _eventComponents;
    ComponentStorage<MovementComponent>& _movementComponents;
    Filter _players;

public:
    InputSystem(World &world)
        : ISystem(world),
        _eventComponents(world.GetStorage<ShootInputEvent>()),
        _movementComponents(world.GetStorage<MovementComponent>()),
        _players(FilterBuilder(world)
            .With<PlayerComponent>()
            .With<MovementComponent>()
            .Build())
    {

    }

    void OnInit() override;

    void OnUpdate() override;
};



#endif //INPUTSYSTEM_H
