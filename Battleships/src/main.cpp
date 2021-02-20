#include "Application.h"
#include <windows.h>

static void hideConsole(void)
{
    ShowWindow(GetConsoleWindow(), 0);
}

int main(void)
{
    //hideConsole();

    Application battleships;
    battleships.run();

    return 0;
}