# main.cpp README

## 1. Alla #include – vad betyder de egentligen?

```c

#include "raylib.h"

#include "Payload.h"

#include "Aircraft.h"

#include "Dropdownmenu.h"

#include <vector>

#include <string>

#include "FatMan.h"

#include <iostream>

```

#### Vad händer här?

 

När kompilatorn ser #include:

* Den klistrar in innehållet från den filen här innan kompilering.

 

Det är en preprocessor-operation.

 

### #include "raylib.h"

Detta ger dig:

 

* InitWindow()

* BeginDrawing()

* DrawText()

* Vector2

* Rectangle

* Texture2D

* CheckCollisionPointRec()

* GetFrameTime()

* osv.

 

Utan detta → inga raylib-funktioner existerar.

 

### #include "Payload.h"

Ger dig:

 

* Definition av klassen Payload

* Alla publika funktioner

* Alla publika variabler (t.ex. name, isActive)

 

Det är därför du kan skriva:

````c

Payload* selectedPayload;

````

 

### #include "Aircraft.h"

Gör så att du kan skapa:

````c

Aircraft plane;

````

 

### #include "FatMan.h"

FatMan ärver från Payload.

 

Main måste känna till den klassen → därför inkluderas den.

 

### \<vector> och \<string>

 

Dessa är standardbibliotek:

* std::vector

* std::string

 

## 2. Programstart

````c

int main(){

````

Detta är programmets entry point.

 

## 3. Debug-utskrift

````c

std::cout << "Current working directory: " << GetWorkingDirectory() << std::endl;

````

Här används :

* std::cout från \<iostream>

* GetWorkingDirectory() från raylib

 

Detta hjälper dig se var programmet körs (bra för asset-path debugging).

 

## 4. Initiera raylib

````c

InitWindow(800,600, "Bombardment Simulator");

SetTargetFPS(60);

````

 

Detta:

1. Skapar ett 800x600 fönster

2. Startar OpenGL-context

3. Begränsar loopen till 60 FPS

 

Efter detta är grafiksystemet aktivt.

 

## 5. Skapa Aircraft

````c

Aircraft plane(-150,200,300.0f,"./assets/plane.png");

````

Detta:

 

* Skapar ett objekt på stacken

* Anropar konstruktorn i Aircraft.cpp

* Laddar en textur

* Sätter startposition och hastighet

 

Plane lever tills main slutar.

 

## 6. Skapa UI-knappar

````c

Rectangle button = { 350, GetScreenHeight()-100.0f, 100, 50 };

````

Rectangle är en struct från raylib:

````c

typedef struct Rectangle {

    float x;

    float y;

    float width;

    float height;

} Rectangle;

````

Du skapar alltså bara en databehållare.

 

Ingen klass.

Ingen logik.

Bara data.

 

## 7. Vindhastighet

````c

float windSpeed = 0.0f;

````

Den påverkar payloadens fysik senare.

 

## 8. Dynamisk allokering – viktig del

````c

FatMan* fatMan = new FatMan(...);

````

 

## 9. Vector med polymorfism

````c

std::vector<Payload*> payloadOptions = {

    new Payload(...),

    new Payload(...),

    fatMan

};

````

Nu händer OOP-magi.

 

Här lagras:

 

* Payload*

* Payload*

* FatMan*

 

Det är polymorfism.

 

Vectorn kan lagra alla objekt som är av typen Payload eller ärver från den.

 

## 10. DropdownMenu

````c

DropdownMenu dropdownMenu(50,50,200,30,payloadOptions);

````

Nu skickas in:

 

* position

* storlek

* lista med Payload*

 

DropdownMenu håller referenser till dina objekt.

 

## 11. Pekare till vald payload

````c

Payload* selectedPayload = nullptr;

````

nullptr betyder:

 

"Det finns inget valt objekt ännu."

 

## 12. Huvudloopen

````c

while (!WindowShouldClose())

````

Den kör 60 gånger per sekund.

 

## 13. Input-delen

````c

Vector2 mousePoint = GetMousePosition();

````

Hämtar musens position.

 

Sedan:

````c

CheckCollisionPointRec(mousePoint, button);

````

Detta kollar om musen är inom rektangeln.

 

Om klick sker:

````c

plane.Start();

````

Det sätter planet i rörelse.

 

## 14. Update – Fysik & logik

````c

plane.Update(GetFrameTime());

````

GetFrameTime() ger deltaTime.

 

Sedan detta viktiga block:

````c

if (selectedPayload && !selectedPayload->isActive && plane.position.x >= 200 ...

````

 

Det betyder:

 

* En payload är vald

* Den är inte redan aktiv

* Planet har nått position 200

* Den har inte redan släppts

 

Då:

````c

selectedPayload->Drop(...)

````

Nu börjar fysiken.

 

## 15. Dropdown uppdatering

````c

dropdownMenu.Update();

````

Den kollar om användaren klickat på ett objekt.

 

Om nytt objekt valts:

````c

selectedPayload = newSelectedPayload;

````

 

Byter pekare.

 

Inget nytt objekt skapas.

<br>

Pekar bara på ett annat.

 

## 16. Rendering

````c

BeginDrawing();

ClearBackground(RAYWHITE);

````

Startar frame.

 

### Payload

````c

selectedPayload->Update(GetFrameTime(), windSpeed);

selectedPayload->Draw();

````

 

<b>Polymorfism:</b>

 

Om selectedPayload är FatMan →<br>

FatMan::Draw() körs.

 

Annars →<br>

Payload::Draw() körs.

 

Detta bestäms vid runtime.

 

### Rita UI

 

````c

DrawRectangleRec(...)

DrawText(...)

````

All grafik ritas varje frame.

 

## 17. Avslut

````c

CloseWindow();

````

Stänger OpenGL och raylib.