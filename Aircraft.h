#ifndef AIRCRAFT_H
#define AIRCRAFT_H

#include "raylib.h"
#include <string>

class Aircraft {
public:
    Vector2 position;
    float speed;
    Texture2D texture;
    bool isMoving;

    Aircraft(float startX,float startY,float aircraftSpeed,const std::string& texturePath);
    ~Aircraft();

    void Start();
    void Update(float deltaTime);
    void Draw() const;
    void Reset();

private:
    float startX;
    float startY;

};


#endif //AIRCRAFT_H
