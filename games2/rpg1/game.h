/*
    game.h
        header file for class Game
*/

#ifndef GAME_H
#define GAME_H

// Include headers


class Game
{
// private:
private:
    float x;
    float y;
    float width;
    float height;
    char *caption;
    bool isRunning;
    int fps;
    SDL_Event event;

    void initialization(void);
    void events(SDL_Event event);

// public:
public:
    Player player;

    Game();
    void mainloop(void);
};

#endif  // GAME_H
