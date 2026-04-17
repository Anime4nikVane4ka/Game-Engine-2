#ifndef GUI_H
#define GUI_H

#include "Ecs/World/World.h"

class GUI
{
public:
    GUI() = default;

    void Draw(World& world);

private:
    void DrawAsteroidSpawnControls(World& world);
    void DrawEntities(World& world);
};

#endif //GUI_H
