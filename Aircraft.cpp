#include "Aircraft.h"
#include <stdexcept>

Aircraft::Aircraft(float startX,float startY,float aircraftSpeed,const std::string& texturePath)
    : position({startX,startY}),speed(aircraftSpeed),isMoving(false),startX(startX),startY(startY){
        Image image = LoadImage(texturePath.c_str());
        if(image.data == nullptr){
            throw std::runtime_error("Failed to load image: "+ texturePath);
        }
        ImageResize(&image,image.width/7,image.height/7);
        ImageFlipHorizontal(&image);
        texture = LoadTextureFromImage(image);
        UnloadImage(image);
    }

Aircraft::~Aircraft(){
    UnloadTexture(texture);
}

void Aircraft::Start(){
    isMoving = true;
}

void Aircraft::Update(float deltaTime){
    if(isMoving){
        position.x +=speed * deltaTime;
        if(position.x > GetScreenWidth()){
            Reset();
        }
    }
}

void Aircraft::Draw()const {
    DrawTexture(texture,position.x,position.y,WHITE);
}

void Aircraft::Reset(){
    position.x = startX;
    position.y = startY;
    isMoving = false;
}