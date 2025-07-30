#include "bumper.h"
#include "utility.h" 

Sound bumpsound = LoadSound("assets/sounds/bumper.wav"); // Som do bumper

Bumper::Bumper(Vector2 pos, float r, Color c) :
    position(pos),
    radius(r),
    originalRadius(r),
    color(c),
    isHit(false),
    hitTimer(0.0f)
{ }

void Bumper::draw() {
    DrawCircleV(position, radius, color);
}

void Bumper::update(float dt) {
    if (isHit) {
        hitTimer += dt;
        float pulseDuration = 0.15f; // Duração do pulso em segundos
        float maxIncrease = 1.2f; // O quanto o raio aumenta (1.2 = 20% a mais)

        if (hitTimer < pulseDuration / 2) {
            // Aumenta o tamanho
            radius = originalRadius * (1.0f + (maxIncrease - 1.0f) * (hitTimer / (pulseDuration / 2)));
        } else if (hitTimer < pulseDuration) {
            // Diminui o tamanho
            radius = originalRadius * (maxIncrease - (maxIncrease - 1.0f) * ((hitTimer - pulseDuration / 2) / (pulseDuration / 2)));
        } else {
            // Reseta para o tamanho original
            radius = originalRadius;
            isHit = false;
            hitTimer = 0.0f;
        }
    }
}


bool Bumper::checkCollision(const Vector2& ballPos, float ballRadius, Vector2& normal, float& penetration) {
    Vector2 diff = Sub(ballPos, position); 
    float distance = Length(diff); 
    float minDistance = radius + ballRadius;

    if (distance <= minDistance) {
        normal = Normalize(diff); 
        penetration = minDistance - distance;
        return true;
    }
    return false;
}

void Bumper::onHit() {
    PlaySound(bumpsound);
    isHit = true;
    hitTimer = 0.0f;
}