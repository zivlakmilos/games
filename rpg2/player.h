#ifndef PLAYER_H
#define PLAYER_H

// Player move type definition
#define PLAYER_MOVE_ADD     0
#define PLAYER_MOVE_DELETE  1

// Player move state definition
#define PLAYER_MOVE_DOWN    2
#define PLAYER_MOVE_RIGHT   3
#define PLAYER_MOVE_UP      4
#define PLAYER_MOVE_LEFT    5

// Player angle
#define PLAYER_ANGLE_DOWN   6
#define PLAYER_ANGLE_RIGHT  7
#define PLAYER_ANGLE_UP     8
#define PLAYER_ANGLE_LEFT   9

struct PlayerTexture
{
    unsigned int d[3];
    unsigned int r[3];
    unsigned int u[3];
    unsigned int l[3];
};

struct PlayerMove
{
    bool down;
    bool right;
    bool up;
    bool left;
};

class Player
{
private:
    float x;
    float y;
    float width;
    float height;
    float speed;
    float helth;
    bool isAlive;
    char *name;
    int angle;
    int textureState;
    int textureStateStep;
    PlayerMove moveState;
    PlayerTexture texture;

public:
    Player(void);
    ~Player(void);
    void move(void);
    void changeMoveState(int type, int side);
    unsigned int loadModel(SDL_Surface *image, SDL_Rect imageRect);
    void loadTexture(void);
    //void colision(void);
    void render(void);
};

#endif  // PLAYER_H
