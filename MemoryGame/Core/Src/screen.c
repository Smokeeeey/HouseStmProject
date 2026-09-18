#include "screen.h"

void DisplayCounter(int count)
{
    char text[20];

    sprintf(text, "%d", count);

    ssd1306_Fill(Black);

    ssd1306_SetCursor(10, 5);
    ssd1306_WriteString("Counter", Font_7x10, White);

    ssd1306_SetCursor(10, 25);
    ssd1306_WriteString(text, Font_11x18, White);

    ssd1306_UpdateScreen();
}
