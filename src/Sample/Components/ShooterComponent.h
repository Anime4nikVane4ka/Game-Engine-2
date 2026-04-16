#ifndef SHOOTERCOMPONENT_H
#define SHOOTERCOMPONENT_H

struct ShooterComponent
{
    float Cooldown = 0.5f;
    float TimeToShoot = 0.0f;
    bool CanShoot = true;

    ShooterComponent() = default;
    ShooterComponent(const float cooldown) : Cooldown(cooldown) {}
    void Shot()
    {
        CanShoot = false;
        TimeToShoot = Cooldown;
    }
    void Update(const float deltaTime)
    {
        if (CanShoot)
            return;
        TimeToShoot -= deltaTime;
        if (TimeToShoot <= 0.0f)
        {
            TimeToShoot = 0.0f;
            CanShoot = true;
        }
    }
};

#endif //SHOOTERCOMPONENT_H
