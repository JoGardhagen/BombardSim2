#ifndef DROPDOWNMENU_H
#define DROPDOWNMENU_H

#include "raylib.h"
#include <vector>
#include "Payload.h"  //inkluderar Payload-klassen

class DropdownMenu {
public:
    // Konstruktor ändras för att ta en lista med Payload-objekt
    DropdownMenu(float x, float y, float width, float height, const std::vector<Payload*>& payloads);

    void Update();  // Uppdatera menyn
    void Draw();    // Rita menyn
    bool IsItemSelected() const;  // Kollar om ett objekt är valt
    Payload* GetSelectedItem() const;  // Hämta det valda Payload-objektet

private:
    Rectangle buttonRect;  // Huvudknappen
    Rectangle optionsRect; // Rektangel för alternativen
    std::vector<Payload*> payloads;  // Lista av Payload-objekt
    float optionHeight;  // Höjd för varje alternativ i menyn
    int selectedIndex;   // Index för det valda objektet
    bool isOpen;         // Om menyn är öppen eller inte
};

#endif // DROPDOWNMENU_H