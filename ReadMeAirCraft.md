# Aircraft.cpp README

## 1. Includes

````c

#include "Aircraft.h"

#include <stdexcept>

````

### #include "Aircraft.h"

Detta gör att:

 

* Klassens deklaration blir känd

* Kompilatorn vet att dessa funktioner existerar

* Den vet vilka medlemsvariabler som finns

 

Utan denna rad kan du inte skriva:

````c

Aircraft::Aircraft(...)

````

Eftersom klassen inte skulle vara definierad.

 

### \<stdexcept>

Detta behövs för:

````c

throw std::runtime_error(...)

````

Det är C++ standardbibliotekets undantagssystem.

 

## 2. Konstruktorn

````c

Aircraft::Aircraft(float startX,float startY,float aircraftSpeed,const std::string& texturePath)

    : position({startX,startY}),

      speed(aircraftSpeed),

      isMoving(false),

      startX(startX),

      startY(startY)      

````

Nu händer något viktigt.

 

* <b>Detta är en initializer list </b>

 

Den körs innan själva konstruktorns body.

 

Det betyder:

* position konstrueras direkt med värdet

* speed konstrueras direkt

* isMoving sätts direkt

Detta är bättre än att göra:

 

````c

position = {startX,startY};

````

 

Varför?

 

För då skulle position först default-konstrueras och sedan tilldelas.

<br>Initializer list är mer effektiv.

 

## 3. Ladda bilden

````c

Image image = LoadImage(texturePath.c_str());

````

 

Här händer:

* En bild laddas in i CPU-minnet (RAM)

* Detta är en Image-struktur från raylib

 

<b>Viktigt:</b>

 

texturePath.c_str() konverterar std::string till const char*.

 

raylib är skrivet i C → den förstår inte std::string.

 

## 4. Felhantering

````c

if(image.data == nullptr){

    throw std::runtime_error("Failed to load image: "+ texturePath);

}

````

 

Om bilden inte laddas:

 

* Programmet kastar ett exception

 

* main kraschar om det inte fångas

 

Detta är bättre än att ignorera felet.

 

## 5. Bildmodifiering

````c

ImageResize(&image,image.width/7,image.height/7);

ImageFlipHorizontal(&image);

````

 

## 6. Skapa Texture

````c

texture = LoadTextureFromImage(image);

````

<b>Nu händer något viktigt:</b>

 

* Bilden skickas till GPU

* Ett OpenGL-texturobjekt skapas

* texture innehåller ett GPU-handle

 

Nu är den redo att ritas.

 

## 7. Frigör Image

````c

UnloadImage(image);

````

<b>Viktigt.</b>

 

* Image i RAM → inte längre behövd

* Texture i GPU → används för rendering

 

## 8. Destruktorn

````c

Aircraft::~Aircraft(){

    UnloadTexture(texture);

}

````

 

<b>Detta är MYCKET viktigt.</b>

 

När objektet förstörs:

 

* GPU-texturen frigörs

* Annars skulle du få VRAM-läckor

 

Detta är korrekt RAII-princip.

 

## 9. Start()

````c

void Aircraft::Start(){

    isMoving = true;

}

````

Enkel state-förändring.

 

Du sätter ett internt tillstånd.

 

## 10.

````c

void Aircraft::Update(float deltaTime){

    if(isMoving){

        position.x += speed * deltaTime;

        if(position.x > GetScreenWidth()){

            Reset();

        }

    }

}

````

Här sker fysik.

 

<b>position.x += speed * deltaTime;</b>

 

Detta är:

````c

ny position = gammal position + (hastighet × tid)

````

DeltaTime gör rörelsen framerate-oberoende.

#### Om planet lämnar skärmen

````c

if(position.x > GetScreenWidth()){

    Reset();

}

````

GetScreenWidth() är raylib-funktion.

 

När planet lämnar höger sida:

 

→ Reset()

 

## 11. Draw()

````c

void Aircraft::Draw() const {

    DrawTexture(texture, position.x, position.y, WHITE);

}

````

 

const betyder:

 

Denna funktion ändrar inte objektets tillstånd.

 

DrawTexture:

* Ritar GPU-texturen

* På angiven position

* Med färgmodulator WHITE (ingen färgförändring)

 

## 12. Reset()

````c

void Aircraft::Reset(){

    position.x = startX;

    position.y = startY;

    isMoving = false;

}

````

 

Återställer:

* position

* rörelsestatus

 

startX och startY sparades från konstruktorn.

 

Detta är intern state management.

 

### Arkitekturförståelse

 

Aircraft är ett självständigt objekt som:

 

Hanterar sin egen textur

 

Hanterar sin egen rörelse

 

Hanterar sin egen rendering

 

Hanterar sin egen reset

 