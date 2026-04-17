set(TARGET_NAME main)
set(SOURCES main.cpp
        Config.cpp
        Config.h
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
        Sample/Components/GameOverEvent.h
        Sample/Components/GameStateComponent.h
        Sample/Components/PlayerComponent.h
        Sample/Components/RectangleShapeComponent.h
        Sample/Components/RestartInputEvent.h
        Sample/Components/ScoreIncreaseEvent.h
        Sample/Components/ShooterComponent.h
        Sample/Systems/InputSystem.cpp
        Sample/Systems/InputSystem.h
        Sample/Systems/AsteroidSpawnSystem.cpp
        Sample/Systems/AsteroidSpawnSystem.h
        Sample/Systems/CollisionDetectionSystem.cpp
        Sample/Systems/CollisionDetectionSystem.h
        Sample/Systems/CollisionHandlerSystem.cpp
        Sample/Systems/CollisionHandlerSystem.h
        Sample/Systems/GameOverSystem.cpp
        Sample/Systems/GameOverSystem.h
        Sample/Systems/RenderSystem.cpp
        Sample/Systems/RenderSystem.h
        Sample/Systems/RestartSystem.cpp
        Sample/Systems/RestartSystem.h
        Sample/Systems/ScoringSystem.cpp
        Sample/Systems/ScoringSystem.h
        Sample/Systems/ShootSystem.cpp
        Sample/Systems/ShootSystem.h
        Sample/Components/ShootInputEvent.h
)

add_subdirectory(Ecs)

add_executable(${TARGET_NAME} 
    ${SOURCES})

#target_compile_options(${TARGET_NAME} PRIVATE -Wall -Wextra -Wpedantic -Werror)
target_compile_features(${TARGET_NAME} PRIVATE cxx_std_20)

target_link_libraries(${TARGET_NAME} PUBLIC ${ECS_LIB_NAME})
target_link_libraries(${TARGET_NAME} PUBLIC ImGui-SFML::ImGui-SFML)

add_custom_command(TARGET ${TARGET_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        ${CMAKE_SOURCE_DIR}/config.txt
        $<TARGET_FILE_DIR:${TARGET_NAME}>/config.txt)
