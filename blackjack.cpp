#include "raylib.h"

#include "game.h"
#include "resources.h"
#include "window.h"

int main()
{
    // Config config("hangman.cfg");

    ::SetTraceLogLevel(LOG_WARNING);

    CPPRaylib::Window window{Blackjack::Constants::Width, Blackjack::Constants::Height, "Blackjack"};
    Blackjack::Game game{window};

    game.run();
}
