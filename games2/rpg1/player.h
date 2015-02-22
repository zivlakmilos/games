#ifndef PLAYER_H
#define PLAYER_H

// Include headers
// #include "headers.h"

// Player moce state
#define PLAYER_MOVE_ADD         0
#define PLAYER_MOVE_DELETE      1
#define PLAYER_MOVE_UP          2
#define PLAYER_MOVE_DOWN        3
#define PLAYER_MOVE_LEFT        4
#define PLAYER_MOVE_RIGHT       5

// Player angle
#define PLAYER_ANGLE_DEFAULT    0
#define PLAYER_ANGLE_UP         1
#define PLAYER_ANGLE_DOWN       2
#define PLAYER_ANGLE_LEFT       3
#define PLAYER_ANGLE_RIGHT      4


struct PlayerTexture
{
    unsigned int s;
    unsigned int l[3];
    unsigned int r[3];
    unsigned int u[3];
    unsigned int d[3];
};


class Player
{
// private:
private:
    float x;
    float y;
    float width;
    float height;
    float speed;
    float helth;
    bool isAlive;
    char *name;
    //PlayerTexture textureName;
    PlayerTexture texture;
    int textureState;
    int angle;
    bool left, right, up, down;

// public:
public:
    Player(void);
    void moveState(int type, int state);
    void move(void);
    unsigned int loadModel(char *fileName, SDL_Rect src, SDL_Rect dest);
    void loadTexture(void);
    void render(void);
};

#endif  // PLAYER_H
