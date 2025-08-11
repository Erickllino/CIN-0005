#include "bumper.h"
#include "utility.h" 

Bumper::Bumper() : 
    position({0, 0}),
    radius(0),
    originalRadius(0),
    color(WHITE),
    scoreValue(0),
    isHit(false),
    hitTimer(0.0f)
{ }

Bumper::Bumper(Vector2 pos, float r, Color c, int score) :
    position(pos),
    radius(r),
    originalRadius(r),
    color(c),
    scoreValue(score),
    isHit(false),
    hitTimer(0.0f)
{ }

Bumper::Bumper(const Bumper& other) :
    position(other.position),
    radius(other.radius),
    originalRadius(other.originalRadius),
    color(other.color),
    scoreValue(other.scoreValue),
    isHit(other.isHit),
    hitTimer(other.hitTimer)
{ }

Bumper& Bumper::operator=(const Bumper& other) {
    if (this != &other) {
        position = other.position;
        radius = other.radius;
        originalRadius = other.originalRadius;
        color = other.color;
        isHit = other.isHit;
        hitTimer = other.hitTimer;
    }
    return *this;
}

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
    isHit = true;
    hitTimer = 0.0f;
}