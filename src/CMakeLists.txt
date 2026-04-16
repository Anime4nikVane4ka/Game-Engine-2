set(TARGET_NAME main)
set(SOURCES main.cpp
        Sample/Systems/MovementSystem.cpp
        Sample/Systems/MovementSystem.h
        Sample/Systems/InitSystem.cpp
        Sample/Systems/InitSystem.h
        Sample/Components/PositionComponent.h
        Sample/Components/MovementComponent.h
        Sample/Components/AsteroidComponent.h
        Sample/Components/BoxColliderComponent.h
        Sample/Components/BulletComponent.h
        Sample/Components/CircleColliderComponent.h
        Sample/Components/CircleShapeComponent.h
        Sample/Components/CollisionComponent.h
        Sample/Components/PlayerComponent.h
        Sample/Components/RectangleShapeComponent.h
        Sample/Components/ShooterComponent.h
        Sample/Systems/InputSystem.cpp
        Sample/Systems/InputSystem.h
        Sample/Components/MoveInputEvent.h
)

add_subdirectory(Ecs)

add_executable(${TARGET_NAME} 
    ${SOURCES})

#target_compile_options(${TARGET_NAME} PRIVATE -Wall -Wextra -Wpedantic -Werror)
target_compile_features(${TARGET_NAME} PRIVATE cxx_std_20)

target_link_libraries(${TARGET_NAME} PUBLIC ${ECS_LIB_NAME})
target_link_libraries(${TARGET_NAME} PUBLIC ImGui-SFML::ImGui-SFML)
