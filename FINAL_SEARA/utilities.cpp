#include "utilities.h"

void SetConsoleCursorPos(Vector2 pos) // posiciona el cursor en un vector2 especifico anteriormente escrito. Funcion creada en base a windows.h
{
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(handle, { static_cast<short>(pos.x), static_cast<short>(pos.y) });
}