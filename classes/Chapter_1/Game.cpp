#include "Game.h"

const int thickness = 15;
const float paddleH = 100.0f;

Game::Game() : mWindow(nullptr), mRenderer(nullptr), mTicksCount(0), mIsRunning(true), mPaddleDir(0){}

bool Game::Initialize() {
    //  Initialize SDL
    int sdlResult = SDL_Init(SDL_INIT_VIDEO);
    if ( sdlResult != 0 ) {
        SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
        return false;
    }

    //  Create SDL Window
    mWindow = SDL_CreateWindow( "Game Programming", 100, 100, 1024, 768, 0 );
    if ( !mWindow ) {
        SDL_Log( "Failed to create window: %s", SDL_GetError() );
        return false;
    }

    //  Create SDL Renderer
    mRenderer = SDL_CreateRenderer( mWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );
    if ( !mRenderer ) {
        SDL_Log( "Failed to create renderer: %s", SDL_GetError() );
        return false;
    }

    mPaddlePos.x = 10.0f;
	mPaddlePos.y = 768.0f/2.0f;
	mBallPos.x = 1024.0f/2.0f;
	mBallPos.y = 768.0f/2.0f;
	mBallVel.x = -200.0f;
	mBallVel.y = 235.0f;
	return true;
}

void Game::RunLoop() {
    while ( mIsRunning ){
        ProcessInput();
        UpdateGame();
        GenerateOutput();
    }
}

void Game::ProcessInput() {
    SDL_Event event;
    while ( SDL_PollEvent( &event ) ){
        switch ( event.type ){
            case SDL_QUIT:                  
                mIsRunning = false;
                break;
        }
    }

    //  Get keyboard state
    const Uint8* state = SDL_GetKeyboardState( NULL );
    //  If escape is pressed end loop
    if ( state[SDL_SCANCODE_ESCAPE] )
        mIsRunning = false;
    
    //  Update paddle direction based on W/S Keys
    mPaddleDir = 0;
    if ( state[SDL_SCANCODE_UP] )
        mPaddleDir += 1;

    if ( state[SDL_SCANCODE_DOWN] )
        mPaddleDir -= 1;
}

void Game::UpdateGame() {
    //  Wait until 16ms has elapsed since last frame
    while ( !SDL_TICKS_PASSED (SDL_GetTicks(), mTicksCount + 16) );

    //  Delta time in seconds
    float deltaTime = ( SDL_GetTicks() - mTicksCount ) / 1000.0f;

    //  Clamp maximum delta time value
    if ( deltaTime > 0.05f )
        deltaTime = 0.05f;
    
    //  Update paddle position based on direction
    if ( mPaddleDir != 0 ) {
        mPaddlePos.y += mPaddleDir * 300.0f * deltaTime;
        //  Set paddle boundaries
        if ( mPaddlePos.y < ( paddleH/2.0f + thickness ) )
            mPaddlePos.y = paddleH/2.0f + thickness;
        else if ( mPaddlePos.y > ( 768.0f - paddleH/2.0f -thickness ) )
            mPaddlePos.y = 768.0f - paddleH/2.0f - thickness;
        
        //  Update ball postion based on ball velocity
        mBallPos.x += mBallVel.x * deltaTime;
        mBallPos.y += mBallVel.y * deltaTime;

        //  Bounce if needed
        //  Did we intersect with the paddle
        float diff = mPaddlePos.y - mBallPos.y;

        //  Take absolute value of difference
        diff = ( diff > 0.0f ) ? diff: -diff;
        if (
            //  y-difference is small enough
            diff <= paddleH / 2.0f &&
            //  current x-position is correct
            mBallPos.x <= 25.0f && mBallPos.x >= 20.0f &&
            //  The ball is moving to the left
            mBallVel.x < 0.0f
        ) {
            mBallVel.x *= -1.0f;
        }

        //  Ball off screen?
        else if ( mBallPos.x < thickness )
            mBallVel.x *= -1;
        
        //  Ball collided with right wall?
        else if ( mBallPos.x >= ( 1024.0f - thickness ) && mBallVel.x > 0.0f ) 
            mBallVel.x *= -1.0f;
        
        //  Ball collided with top wall?
        if ( mBallPos.y <= thickness && mBallVel.y < 0.0f )
            mBallVel.y *= -1;
        
        else if ( mBallPos.y >= ( 768 - thickness ) && mBallVel.y > 0.0f )
            mBallVel.y *= -1;
    }
}

void Game::GenerateOutput() {
    //  Set draw color to blue
    SDL_SetRenderDrawColor( mRenderer, 0, 0, 255, 255 );    //  RGBA

    //  Clear back buffer
    SDL_RenderClear( mRenderer );

    //  Draw walls
    SDL_SetRenderDrawColor( mRenderer, 255, 255, 255, 255 );

    //  Draw top wall
    SDL_Rect wall {
        0,          //  Top left x
        0,          //  Top lext y
        1024,       //  width
        thickness   // Height
    };
    SDL_RenderFillRect( mRenderer, &wall );
    
    //  Draw bottom wall
    wall.y = 768 - thickness;
    SDL_RenderFillRect( mRenderer, &wall );

    //  Draw right wall
    wall.x = 1024 - thickness;
    wall.y = 0;
    wall.w = thickness;
    wall.h = 1024;
    SDL_RenderFillRect( mRenderer, &wall );

    //  Draw left window
    wall.x = 0;
    wall.y = 0;
    wall.w = thickness;
    wall.h = 1024;
    SDL_RenderFillRect( mRenderer, &wall );

    //  Draw paddle
    SDL_Rect paddle{
        static_cast<int>( mBallPos.x - thickness/2 ),
        static_cast<int>( mBallPos.y - thickness/2 ),
        thickness,
        static_cast<int>( paddleH )
    };
    SDL_RenderFillRect( mRenderer, &paddle );

    //  Draw ball
    SDL_Rect ball {
        static_cast<int>( mBallPos.x - thickness/2 ),
        static_cast<int>( mBallPos.y - thickness/2 ),
        thickness,
        thickness
    };
    SDL_RenderFillRect( mRenderer, &ball );

    // Swap front buffer and back buffer
    SDL_RenderPresent( mRenderer );
}

void Game::Shutdown() {
    SDL_DestroyRenderer( mRenderer );
    SDL_DestroyWindow( mWindow );
    SDL_Quit();
}

