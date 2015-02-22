/*
    player.cpp
        code for player, move, texture, helth
*/

// Include headers
#include "main.h"
#include "player.h"


Player::Player(void)
{
    this->x = 0.0;
    this->y = 0.0;
    this->width = 84.0;
    this->height = 100.0;
    this->speed = 10.0;
    this->helth = 3.0;
    this->isAlive = true;
    this->name = "";
    /*
    for(i = 0; i < 3; i++)
    {
        this->textureName.l[i] = 0;
        this->textureName.r[i] = 0;
        this->textureName.u[i] = 0;
        this->texutreName.d[i] = 0;
    }
    */
    this->textureState = 0;
    this->angle = PLAYER_ANGLE_DEFAULT;
    this->left = false;
    this->right = false;
    this->up = false;
    this->down = false;
}

void Player::moveState(int type, int state)
{
    switch(type)
    {
        case PLAYER_MOVE_ADD:
            switch(state)
            {
                case PLAYER_MOVE_LEFT:
                    this->left = true;
                break;
                case PLAYER_MOVE_RIGHT:
                    this->right = true;
                break;
                case PLAYER_MOVE_UP:
                    this->up = true;
                break;
                case PLAYER_MOVE_DOWN:
                    this->down = true;
                break;
            }
        break;
        case PLAYER_MOVE_DELETE:
            switch(state)
            {
                case PLAYER_MOVE_LEFT:
                    this->left = false;
                break;
                case PLAYER_MOVE_RIGHT:
                    this->right = false;
                break;
                case PLAYER_MOVE_UP:
                    this->up = false;
                break;
                case PLAYER_MOVE_DOWN:
                    this->down = false;
                break;
            }
        break;
    }
}

void Player::move(void)
{
    if(left)
    {
        this->x -= this->speed;
        this->angle = PLAYER_ANGLE_LEFT;
    }
    else if(right)
    {
        this->x += this->speed;
        this->angle = PLAYER_ANGLE_RIGHT;
    }
    else if(up)
    {
        this->y += this->speed;
        this->angle = PLAYER_ANGLE_UP;
        
    }
    else if(down)
    {
        this->x -= this->speed;
        this->angle = PLAYER_ANGLE_DOWN;
    }
    else
    {
        this->angle = PLAYER_ANGLE_DEFAULT;
    }
}

unsigned int Player::loadModel(char *fileName, SDL_Rect src, SDL_Rect dest)
{
    /*
    // Load image to memory
    this->model = SDL_DisplayFormat(SDL_LoadBMP("data/model.bmp"));

    // Source rectangle
    this->src.x = 0;
    this->src.y = 0;
    this->src.w = this->model->w;
    this->src.h = this->model->h;

    // Destination rectangle
    this->dest.x = 100;
    this->dest.y = 100;
    this->dest.w = this->model->w;
    this->dest.h = this->model->h;
    */

    // Load model

    SDL_Surface *image = IMG_Load(fileName);
    SDL_DisplayFormatAlpha(image);
    unsigned object(0);
    glGenTextures(1, &object);
    glBindTexture(GL_TEXTURE_2D, object);
    
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image->w, image->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, image->pixels);

    SDL_FreeSurface(image);   // Free surface


    // Copy texture

    // Return texture
    return object;
}

void Player::loadTexture(void)
{
    SDL_Rect src, dest;
    this->texture.s = this->loadModel("data/Model 1.png", src, dest);
    this->texture.l[0] = this->loadModel("data/Model 2.png", src, dest);
    this->texture.r[0] = this->loadModel("data/Model 3.png", src, dest);
    this->texture.u[0] = this->loadModel("data/Model 4.png", src, dest);
    this->texture.d[0] = this->loadModel("data/Model 1.png", src, dest);
}

void Player::render(void)
{
    glColor4ub(255, 255, 255, 255); // White color

    glEnable(GL_TEXTURE_2D);
    //glBindTexture(GL_TEXTURE_2D, texture.s);
    switch(angle)
    {
        case PLAYER_ANGLE_UP:
            glBindTexture(GL_TEXTURE_2D, texture.u[0]);
        break;
        case PLAYER_ANGLE_DOWN:
            glBindTexture(GL_TEXTURE_2D, texture.d[0]);
        break;
        case PLAYER_ANGLE_LEFT:
            glBindTexture(GL_TEXTURE_2D, texture.l[0]);
        break;
        case PLAYER_ANGLE_RIGHT:
            glBindTexture(GL_TEXTURE_2D, texture.r[0]);
        break;
        default:
            glBindTexture(GL_TEXTURE_2D, texture.s);
        break;
    }

    glBegin(GL_QUADS);
        glTexCoord2d(0, 0); glVertex2f(this->x, this->y);
        glTexCoord2d(1, 0); glVertex2f(this->x + this->width, this->y);
        glTexCoord2d(1, 1); glVertex2f(this->x + this->width, this->y + this->height);
        glTexCoord2d(0, 1); glVertex2f(this->x, this->y + this->height);
    glEnd;

    glDisable(GL_TEXTURE_2D);

    glColor4ub(255, 255, 255, 255);

    
    glBegin(GL_QUADS);
        glVertex2f(this->x, this->y);
        glVertex2f(this->x + this->width, this->y);
        glVertex2f(this->x + this->width, this->y + this->height);
        glVertex2f(this->x, this->y + this->height);
    glEnd();
}
