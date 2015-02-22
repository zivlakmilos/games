/*
    game.cpp
        code for game, main loop, window drawing, handle events
*/

// Include headers
#include "main.h"
#include "player.h"
#include "game.h"

Game::Game()
{
    this->x = 100;
    this->x = 100;
    this->width = 640;
    this->height = 480;
    this->caption = "";
    this->isRunning = true;
    this->fps = 10;
}

void Game::initialization(void)
{
    // SDL initialization
    SDL_Init(SDL_INIT_EVERYTHING);

    // Set OpenGL memory usage
    SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE, 32);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 16);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

    // Set window caption
    SDL_WM_SetCaption(this->caption, NULL);

    // Set size of window
    SDL_SetVideoMode(this->width, this->height, 32, SDL_OPENGL);

    // Set initialize clear color
    glClearColor(0, 1, 0, 1);

    // Part of screen to be display
    glViewport(0, 0, this->width, this->height);

    // Shade model
    glShadeModel(GL_SMOOTH);

    // Enable textures
    glEnable(GL_TEXTURE_2D);

    // 2D rendering
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    // Disable depth checking
    glDisable(GL_DEPTH_TEST);

    // Enable 2D texture
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // Clear the window
    glClear(GL_COLOR_BUFFER_BIT);

    // Player initialization
    player.loadTexture();   // Load player texture

    // Load musics
}

// void for handle events
void Game::events(SDL_Event event)
{
    while(SDL_PollEvent(&event))
    {
        if(event.type == SDL_QUIT)
            this->isRunning = false;
        if(event.type == SDL_KEYUP && event.key.keysym.sym == SDLK_ESCAPE)
            this->isRunning = false;

        if(event.type == SDL_KEYDOWN)
        {
            if(event.key.keysym.sym == SDLK_UP)
                player.moveState(PLAYER_MOVE_ADD, PLAYER_MOVE_UP);
            else if(event.key.keysym.sym == SDLK_DOWN)
                player.moveState(PLAYER_MOVE_ADD, PLAYER_MOVE_DOWN);
            else if(event.key.keysym.sym == SDLK_LEFT)
                player.moveState(PLAYER_MOVE_ADD, PLAYER_MOVE_LEFT);
            else if(event.key.keysym.sym == SDLK_RIGHT)
                player.moveState(PLAYER_MOVE_ADD, PLAYER_MOVE_RIGHT);
        }

        if(event.type == SDL_KEYUP)
        {
            if(event.key.keysym.sym == SDLK_UP)
                player.moveState(PLAYER_MOVE_DELETE, PLAYER_MOVE_UP);
            else if(event.key.keysym.sym == SDLK_DOWN)
                player.moveState(PLAYER_MOVE_DELETE, PLAYER_MOVE_DOWN);
            else if(event.key.keysym.sym == SDLK_LEFT)
                player.moveState(PLAYER_MOVE_DELETE, PLAYER_MOVE_LEFT);
            else if(event.key.keysym.sym == SDLK_RIGHT)
                player.moveState(PLAYER_MOVE_DELETE, PLAYER_MOVE_RIGHT);
        }

        if(event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_c)
            glClear(GL_COLOR_BUFFER_BIT);
    }
}

void Game::mainloop(void)
{
    // Initialization
    this->initialization();

    /*
        main loop
    */
    while(this->isRunning)
    {

        // EVENTS
        this->events(this->event);

        // LOGIC
        this->player.move();

        // RENDER
        glClear(GL_COLOR_BUFFER_BIT);   // Cear screen
        glPushMatrix(); //Begin render
        glOrtho(0, this->width, this->height, 0, -1, 1); // Coordinate system
        this->player.render();
        glPopMatrix();  // End render

        // Swap buffers
        SDL_GL_SwapBuffers();

        // Regulate FPS
        SDL_Delay(this->fps);
    }
}
