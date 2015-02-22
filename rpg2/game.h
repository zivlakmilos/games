#ifndef GAME_H
#define GAME_H

class Game
{
private:
    //float x;
    //float y;
    float width;
    float height;
    char *caption;
    bool isRunning;
    int fps;
    SDL_Event event;
    Player *player;

    void events(SDL_Event event);
    void init(void);
    //void free(void);

public:
    Game(void);
    ~Game(void);
    void mainLoop(void);
};

#endif  // GAME_H
