#include "FatMan.h"
#include <stdexcept>

FatMan::FatMan(float x,float y,float radius,float speedX,float speedY, const std::string& payloadName, const std::string& texturePath)
    : Payload(x,y,radius,speedX,speedY,payloadName),rotation(0.0f) {

    //texture = LoadTexture(texturePath.c_str());
    Image image = LoadImage(texturePath.c_str());
        if(image.data == nullptr){
            throw std::runtime_error("Failed to load image: "+ texturePath);
        }
        ImageResize(&image,image.width/10,image.height/10);
        //ImageFlipHorizontal(&image);
        texture = LoadTextureFromImage(image);
        UnloadImage(image);
    
    
    // Kontrollera om texturen laddades
    if (texture.id == 0) {
        TraceLog(LOG_ERROR, TextFormat("Failed to load texture: %s", texturePath.c_str()));
    }
}

void FatMan::Update(float deltaTime, float windSpeed) {
//void Update(float deltaTime, float windSpeed) override {
    Payload::Update(deltaTime ,windSpeed);
    rotation += 90.0f * deltaTime;
}

void FatMan::Draw()const {
    if(isActive){
        DrawTexturePro(
            texture,
            Rectangle{0,0,static_cast<float>(texture.width),static_cast<float>(texture.height)},
            //{0,0,(float)texture.width,(float)texture.height},
            {position.x,position.y,radius*2,radius*2},
            //{position.x,position.y,texture.width *1.2f,texture.height *1.2f},
            Vector2{radius,radius},
            rotation,
            WHITE
        );
        //DrawTexture(texture,static_cast<int>(position.x -texture.width / 2),static_cast<int>(position.y - texture.height/2),WHITE);
        //DrawTexture(texture, position.x - texture.width / 2, position.y - texture.height / 2, WHITE);
    }
}

FatMan::~FatMan(){
    UnloadTexture(texture);
}