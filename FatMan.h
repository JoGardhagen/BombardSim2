#ifndef FATMAN_H
#define FATMAN_H

#include "Payload.h"
#include "raylib.h"

class FatMan : public Payload {
public:
    Texture2D texture;
    float rotation;

    FatMan(float x,float y,float radius,float speedX, float speedY,const std::string& payloadName, const std::string& texturePath);

    void Update(float deltaTime, float windSpeed) override;

    void Draw() const override;

    ~FatMan() override;

};

#endif