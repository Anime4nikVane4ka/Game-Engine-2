#ifndef INPUTSYSTEM_H
#define INPUTSYSTEM_H

#include <SFML/Graphics.hpp>

#include "../../Ecs/Filter/Filter.h"
#include "../../Ecs/Filter/FilterBuilder.h"
#include "../../Ecs/Systems/ISystem.h"

#include "../Components/MovementComponent.h"
#include "../Components/PlayerComponent.h"
#include "../Components/GameStateComponent.h"
#include "../Components/RestartInputEvent.h"
#include "../Components/ShootInputEvent.h"

class InputSystem : public ISystem {

    ComponentStorage<ShootInputEvent>& _shootInputEvents;
    ComponentStorage<RestartInputEvent>& _restartInputEvents;
    ComponentStorage<MovementComponent>& _movementComponents;
    ComponentStorage<GameStateComponent>& _gameStates;
    Filter _players;
    Filter _gameStateEntities;
    bool _restartInputWasPressed = false;

public:
    InputSystem(World &world)
        : ISystem(world),
        _shootInputEvents(world.GetStorage<ShootInputEvent>()),
        _restartInputEvents(world.GetStorage<RestartInputEvent>()),
        _movementComponents(world.GetStorage<MovementComponent>()),
        _gameStates(world.GetStorage<GameStateComponent>()),
        _players(FilterBuilder(world)
            .With<PlayerComponent>()
            .With<MovementComponent>()
            .Build()),
        _gameStateEntities(FilterBuilder(world)
            .With<GameStateComponent>()
            .Build())
    {

    }

    void OnInit() override;

    void OnUpdate() override;
};



#endif //INPUTSYSTEM_H
