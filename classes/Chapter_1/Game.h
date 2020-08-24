#pragma once
#include "SDL2/SDL.h"

// Vector2 struct stores x/y coordinates

struct Vector2 {
    float x;
    float y;
};

class Game {
public:
    Game();
    bool Initialize();          //  Initialize the game
    void RunLoop();             //  Runs game loop until game ends
    void Shutdown();            //  Shutdown the game

private:
    //  Helper functions for the game loop
    void ProcessInput();
    void UpdateGame();
    void GenerateOutput();

    SDL_Window* mWindow;        //  Window created by SDL
    SDL_Renderer* mRenderer;    //  Renderer for 2D drawings
    Uint32 mTicksCount;         //  Number of ticks since start of game
    bool mIsRunning;            //  Game should continue to run

    //  Pong specific
    int mPaddleDir;             //  Direction of paddle
    Vector2 mPaddlePos;         //  Position of paddle
    Vector2 mBallPos;           //  Position of ball
    Vector2 mBallVel;           //  Ball velocity
};