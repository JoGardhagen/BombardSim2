#include "Dropdownmenu.h"

DropdownMenu::DropdownMenu(float x, float y, float width, float height, const std::vector<Payload*>& payloads)
    : buttonRect{x, y, width, height}, payloads(payloads), isOpen(false), selectedIndex(-1) {
    optionHeight = height; // Samma höjd för alternativen som för knappen
    optionsRect = {x, y + height, width, static_cast<float>(payloads.size()) * height};
}

void DropdownMenu::Update() {
    Vector2 mousePos = GetMousePosition();

    // Klick på huvudknappen för att öppna/stänga menyn
    if (CheckCollisionPointRec(mousePos, buttonRect) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        isOpen = !isOpen;
    }

    // Hantera val om menyn är öppen
    if (isOpen) {
        for (size_t i = 0; i < payloads.size(); ++i) {
            Rectangle optionRect = {optionsRect.x, optionsRect.y + i * optionHeight, optionsRect.width, optionHeight};

            if (CheckCollisionPointRec(mousePos, optionRect) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                selectedIndex = static_cast<int>(i);
                isOpen = false; // Stäng menyn efter valet
                break;
            }
        }
    }
}

void DropdownMenu::Draw() {
    // Rita huvudknappen
    DrawRectangleRec(buttonRect, LIGHTGRAY);
    // Visa det valda objektets namn på knappen
    //DrawText(selectedIndex == -1 ? "Select" : payloads[selectedIndex].name.c_str(), buttonRect.x + 10, buttonRect.y + 7, 20, BLACK);
    DrawText(selectedIndex == -1 ? "Select" : payloads[selectedIndex]->name.c_str(),
         buttonRect.x + 10, buttonRect.y + 7, 20, BLACK);


    // Rita alternativen om menyn är öppen
    if (isOpen) {
        DrawRectangleRec(optionsRect, DARKGRAY);
        for (size_t i = 0; i < payloads.size(); ++i) {
            Rectangle optionRect = {optionsRect.x, optionsRect.y + i * optionHeight, optionsRect.width, optionHeight};
            DrawRectangleRec(optionRect, LIGHTGRAY);
            //DrawText(payloads[i].name.c_str(), optionRect.x + 10, optionRect.y + 7, 20, BLACK);
            DrawText(payloads[i]->name.c_str(), optionRect.x + 10, optionRect.y + 7, 20, BLACK);
        }
    }
}

bool DropdownMenu::IsItemSelected() const {
    return selectedIndex != -1;  // Return true om ett objekt är valt
}

/*Payload DropdownMenu::GetSelectedItem() const {
    return selectedIndex == -1 ? Payload(0, 0, 0, 0, 0, "") : payloads[selectedIndex];  // Returnera vald Payload
}*/

Payload* DropdownMenu::GetSelectedItem() const {
    return selectedIndex == -1 ? nullptr : payloads[selectedIndex];
}
