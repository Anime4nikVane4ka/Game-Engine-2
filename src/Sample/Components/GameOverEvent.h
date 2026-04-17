#ifndef GAMEOVEREVENT_H
#define GAMEOVEREVENT_H

struct GameOverEvent
{
    int Player = -1;

    GameOverEvent() = default;
    GameOverEvent(const int player): Player(player) {}
};

#endif //GAMEOVEREVENT_H
