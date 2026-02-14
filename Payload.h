#ifndef PAYLOAD_H
#define PAYLOAD_H

#include "raylib.h"
#include <string>

class Payload {
public:
    Vector2 position;   // Objektets position
    Vector2 speed;      // Objektets hastighet (x och y)
    float radius;       // Radie för objektet
    bool isActive;      // Om objektet är aktivt (på skärmen)
    std::string name;

    // Konstruktor för att initialisera objektet
    Payload(float x, float y, float radius, float speedX, float speedY,const std::string& payloadName);

    /// Virtuella metoder för att möjliggöra arv
    virtual void Update(float deltaTime, float windSpeed); // Uppdatera objektets position
    virtual void Draw() const;                            // Rita objektet

    // Släpp objektet från en given startposition
    virtual void Drop(float startX, float startY);

    // Virtuell destruktor för korrekt nedärvning
    virtual ~Payload() = default;
};

#endif // PAYLOAD_H
