#include "EnemyBehaviours.h"

sf::Vector2f EnemyBehaviours::calculateSeek(const sf::Vector2f& currentPosition, const sf::Vector2f& targetPosition, const sf::Vector2f& currentVelocity, float speed)
{
    // get direction 
    sf::Vector2f direction = targetPosition - currentPosition;
    sf::Vector2f desiredVelocity = normalize(direction) * maxSpeed;

    //calculate steering 
    sf::Vector2f steering = desiredVelocity - currentVelocity;

    //limit to max force
    float steeringMagnitude = std::sqrt(steering.x * steering.x + steering.y * steering.y);
    if (steeringMagnitude > maxForce)
    {
        steering = (steering / steeringMagnitude) * maxForce;
    }
    return steering;
}

sf::Vector2f EnemyBehaviours::calculateArrive(const sf::Vector2f& currentPosition, const sf::Vector2f& targetPosition, const sf::Vector2f& currentVelocity, float maxSpeed, float arrivalRadius, float slowRadius)
{
    sf::Vector2f direction = targetPosition - currentPosition;
    float distance = std::sqrt(direction.x * direction.x + direction.y * direction.y);
    float targetSpeed;
    //check how close the position is to the target to determine target speed
    if (distance < arrivalRadius)
    {
        targetSpeed = 0.0f;
    }
    else if (distance > slowRadius)
    {
        targetSpeed = maxSpeed;
    }
    else {
        targetSpeed = maxSpeed * (distance / slowRadius);
    }
    return calculateSeek(currentPosition,targetPosition,currentVelocity,targetSpeed);
}

float EnemyBehaviours::calculateRotation(const sf::Vector2f& currentPosition, const sf::Vector2f& targetPosition)
{
    sf::Vector2f direction = targetPosition - currentPosition;
    float angleInRadians = std::atan2(direction.y, direction.x);
    float angleInDegrees = angleInRadians * 180.f / 3.14159f;
    return angleInDegrees;
}
