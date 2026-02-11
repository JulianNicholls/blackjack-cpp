#ifndef GAME_H
#define GAME_H

#include <memory>

#include "raylib.h"

#include "block_grid.h"
#include "button.h"
#include "images.h"
#include "window.h"

namespace Flood
{

enum struct GameState
{
    PLAYING,
    SUCCESS,
    FAILURE,
    COMPLETE
};

class Game
{
  public:
    Game(const CPPRaylib::Window &window);
    ~Game();

    void run();
    void update();
    void draw() const;

  private:
    void say_click_to_continue() const;
    void drawPlaying() const;
    void drawComplete() const;

    const CPPRaylib::Window &window_;
    GameState state_;
    const ::Font font_;
    CPPRaylib::ImageLoader images_;
    BlockGrid grid_;
    ::Sound changeSound_;
    CPPRaylib::Button exit_button_;

    unsigned int moves_ = 0;
};

}

#endif // GAME_H
