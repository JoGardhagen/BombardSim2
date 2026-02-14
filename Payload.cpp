#include "Payload.h"
#include <cstdlib>

//Konstruktor för att initialisera objektet 
Payload::Payload(float x, float y,float radius,float speedX,float speedY,const std::string& payloadName)
    : position({x,y}),speed({speedX,speedY}),radius(radius),isActive(false),name(payloadName) {}

//Updatera objektets position
void Payload::Update(float deltaTime, float windSpeed){
    if(isActive){
        position.x += speed.x + windSpeed * deltaTime;
        position.y += speed.y * deltaTime ;


        TraceLog(LOG_INFO, "Payload position: (%f, %f)", position.x, position.y);
        //kontrollera om objektet når botten och eller kanten av skärmen
        if(position.y > GetScreenHeight()||position.x > GetScreenWidth()){
            isActive = false; //Gör objektet inaktivt
            TraceLog(LOG_INFO,"Payload deactivated");
        }
    }
}
//Rita objekt
void Payload::Draw()const{
    if(isActive){
        DrawCircleV(position,radius,RED);
    }
}

void Payload::Drop(float startX,float startY){
    if(!isActive){
        position = {startX,startY};

        
        isActive = true;

        TraceLog(LOG_INFO,"Payload dropped att position : (%f, %f)",position.x,position.y);
    }
}