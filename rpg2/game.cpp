/*
    Game class
*/

#include "main.h"
#include "player.h"
#include "game.h"

Game::Game(void)
{
    //x = 100;
    //y = 100;
    width = 640;
    height = 480;
    caption = "";
    isRunning = true;
    fps = 10;
    player = new Player();
}

Game::~Game(void)
{
    delete player;
}

void Game::init(void)
{
    // initialize SDL
    SDL_Init(SDL_INIT_EVERYTHING);

    // Get OpenGL memory usage
    SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE, 32);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 16);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

    // Caption of the window
    SDL_WM_SetCaption(this->caption, NULL);

    // Size of window
    SDL_SetVideoMode(this->width, this->height, 32, SDL_OPENGL);

    // Specific the clear color
    //glClearColor(1, 1, 1, 1);   // White color
    glClearColor(1, 0, 1, 1);   // Puprple color

    // What portion of the screen we will display
    glViewport(0, 0, this->width, this->height);

    // Shader model
    glShadeModel(GL_SMOOTH);

    // 2D rendering
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    // Disable depth checking
    glDisable(GL_DEPTH_TEST);

    // Enable texture
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    std::cout << "OpenGL is initialize\n";

    // Initizle texture
    player->loadTexture();
    std::cout << "Texture is initialize\n";
}

/*
void free(void)
{
    delete player;
}
*/

void Game::events(SDL_Event event)
{
    while(SDL_PollEvent(&event))
    {
        if(event.type == SDL_QUIT)
            isRunning = false;
        if(event.type == SDL_KEYUP && event.key.keysym.sym == SDLK_ESCAPE)
            isRunning = false;
        
        switch(event.type)
        {
            case SDL_KEYDOWN:
                switch(event.key.keysym.sym)
                {
                    case SDLK_DOWN:
                        player->changeMoveState(PLAYER_MOVE_ADD, PLAYER_MOVE_DOWN);
                    break;
                    case SDLK_RIGHT:
                        player->changeMoveState(PLAYER_MOVE_ADD, PLAYER_MOVE_RIGHT);
                    break;
                    case SDLK_UP:
                        player->changeMoveState(PLAYER_MOVE_ADD, PLAYER_MOVE_UP);
                    break;
                    case SDLK_LEFT:
                        player->changeMoveState(PLAYER_MOVE_ADD, PLAYER_MOVE_LEFT);
                    break;
                }
            break;
            case SDL_KEYUP:
                switch(event.key.keysym.sym)
                {
                    case SDLK_DOWN:
                        player->changeMoveState(PLAYER_MOVE_DELETE, PLAYER_MOVE_DOWN);
                    break;
                    case SDLK_RIGHT:
                        player->changeMoveState(PLAYER_MOVE_DELETE, PLAYER_MOVE_RIGHT);
                    break;
                    case SDLK_UP:
                        player->changeMoveState(PLAYER_MOVE_DELETE, PLAYER_MOVE_UP);
                    break;
                    case SDLK_LEFT:
                        player->changeMoveState(PLAYER_MOVE_DELETE, PLAYER_MOVE_LEFT);
                    break;
                }
            break;
        }
    }
}

void Game::mainLoop(void)
{
    // Initialization
    this->init();
    
    // Main loop
    std::cout << "Main loop is started\n";
    while(isRunning)
    {
        // Hadler event
        this->events(event);

        // Logic
        player->move();

        // Render
        glClear(GL_COLOR_BUFFER_BIT);
        glPushMatrix();
        glOrtho(0, this->width, 0, this->height, -1, 1);    // Set the matrix
        // Begin render
        player->render();
        // End render
        glPopMatrix();
        SDL_GL_SwapBuffers();
        SDL_Delay(fps);
    }

    // Free
    SDL_Quit();
}
