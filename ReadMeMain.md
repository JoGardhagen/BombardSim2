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