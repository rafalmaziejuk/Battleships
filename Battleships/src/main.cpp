#include "Application.h"
#include <windows.h>

/*
*   Battleships
*   Done - 03.03.2021
* 
*   @ Maziejuk Rafal & Mlynarz Pawel
*/

static void hideConsole(void)
{
    ShowWindow(GetConsoleWindow(), 0);
}

int main(void)
{
    hideConsole();

    Application battleships;
    battleships.run();

    return 0;
}