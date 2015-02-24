/*
    Class Player
        player.h
        player.cpp
*/

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
    this->moveState.down = false;
    this->moveState.right = false;
    this->moveState.up = false;
    this->moveState.left = false;
    this->angle = PLAYER_ANGLE_DOWN;
    this->textureState = 1;
    this->textureStateStep = 0;
}

Player::~Player(void)
{
    // Delete player
}

void Player::move(void)
{
    if(this->moveState.down)
    {
        this->y -= this->speed;
        this->angle = PLAYER_ANGLE_DOWN;
    }
    else if(this->moveState.right)
    {
        this->x += this->speed;
        this->angle = PLAYER_ANGLE_RIGHT;
    }
    else if(this->moveState.up)
    {
        this->y += this->speed;
        this->angle = PLAYER_ANGLE_UP;
    }
    else if(this->moveState.left)
    {
        this->x -= this->speed;
        this->angle = PLAYER_ANGLE_LEFT;
    }
}

unsigned int Player::loadModel(SDL_Surface *image, SDL_Rect imageRect)
{
    //SDL_Surface *image = IMG_Load(fileName);
    //SDL_DisplayFormatAlpha(image);
    SDL_Surface *tempImage;   // Tempoary surface
    tempImage = SDL_CreateRGBSurface(0, imageRect.w, imageRect.h,image->format->BitsPerPixel, image->format->Rmask, image->format->Gmask, image->format->Bmask, image->format->Amask);  // Make empty surface
    SDL_SetAlpha(image, 0, 0);

    SDL_Rect tempRect;  // Tempoary rectangle for dest information
    tempRect.x = 0;
    tempRect.y = 0;
    tempRect.w = imageRect.w;
    tempRect.h = imageRect.h;

    SDL_BlitSurface(image, &imageRect, tempImage, &tempRect);   // Copy image

    unsigned object(0);
    glGenTextures(1, &object);
    glBindTexture(GL_TEXTURE_2D, object);

    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, tempImage->w, tempImage->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, tempImage->pixels);

    //SDL_FreeSurface(image); // Free surface
    SDL_FreeSurface(tempImage); // Free tempImage surface

    // Return texture
    return object;
}

void Player::loadTexture(void)
{
    int counter;
    SDL_Surface *image = IMG_Load("data/player.png");
    SDL_DisplayFormatAlpha(image);
    SDL_Rect imageRect;
    imageRect.w = 367.33;
    imageRect.h = 429.5;
    
    //this->texture.d[0] = this->loadModel(image, imageRect);
    //this->texture.r[0] = this->loadModel(image, src, dest);
    //this->texture.u[0] = this->loadModel(image, src, dest);
    //this->texture.l[0] = this->loadModel(image, src, dest);
    
    imageRect.x = 0;
    imageRect.y = 0;
    for(counter = 0; counter < 3; counter++)
    {
        this->texture.d[counter] = this->loadModel(image, imageRect);
        imageRect.x += imageRect.w;
    }
    
    imageRect.x = 0;
    imageRect.y += imageRect.h;
    for(counter = 0; counter < 3; counter++)
    {
        this->texture.l[counter] = this->loadModel(image, imageRect);
        imageRect.x += imageRect.w;
    }

    imageRect.x = 0;
    imageRect.y += imageRect.h;
    for(counter = 0; counter < 3; counter++)
    {
        this->texture.u[counter] = this->loadModel(image, imageRect);
        imageRect.x += imageRect.w;
    }

    imageRect.x = 0;
    imageRect.y += imageRect.h;
    for(counter = 0; counter < 3; counter++)
    {
        this->texture.r[counter] = this->loadModel(image, imageRect);
        imageRect.x += imageRect.w;
    }
    
    SDL_FreeSurface(image); // Free surface
}

// Logic

void Player::changeMoveState(int type, int state)
{
    switch(type)
    {
        case PLAYER_MOVE_ADD:
            switch(state)
            {
                case PLAYER_MOVE_DOWN:
                    this->moveState.down = true;
                break;
                case PLAYER_MOVE_RIGHT:
                    this->moveState.right = true;
                break;
                case PLAYER_MOVE_UP:
                    this->moveState.up = true;
                break;
                case PLAYER_MOVE_LEFT:
                    this->moveState.left = true;
                break;
                default:
                    std::cout << "Player move state error\n";
                break;
            }
        break;
        case PLAYER_MOVE_DELETE:
            switch(state)
            {
                case PLAYER_MOVE_DOWN:
                    this->moveState.down = false;
                break;
                case PLAYER_MOVE_RIGHT:
                    this->moveState.right = false;
                break;
                case PLAYER_MOVE_UP:
                    this->moveState.up = false;
                break;
                case PLAYER_MOVE_LEFT:
                    this->moveState.left = false;
                break;
                default:
                    std::cout << "Player move state error\n";
                break;
            }
        break;
        default:
            std::cout << "Player move type error\n";
        break;
    }
}

// Render player
void Player::render(void)
{
    /*
    glColor4ub(0, 0, 0, 255);   // Black color
    glBegin(GL_QUADS);
        glVertex2f(this->x, this->y);
        glVertex2f(this->x + this->width, this->y);
        glVertex2f(this->x + this->width, this->y + this->height);
        glVertex2f(this->x, this->y + this->height);
    glEnd();
    */

    glColor4ub(255, 255, 255, 255); // White color
    glEnable(GL_TEXTURE_2D);
    
    switch(this->angle)
    {
        case PLAYER_ANGLE_DOWN:
            glBindTexture(GL_TEXTURE_2D, this->texture.d[textureState]);
        break;
        case PLAYER_ANGLE_RIGHT:
            glBindTexture(GL_TEXTURE_2D, this->texture.r[textureState]);
        break;
        case PLAYER_ANGLE_UP:
            glBindTexture(GL_TEXTURE_2D, this->texture.u[textureState]);
        break;
        case PLAYER_ANGLE_LEFT:
            glBindTexture(GL_TEXTURE_2D, this->texture.l[textureState]);
        break;
    }

    glBegin(GL_QUADS);
        glTexCoord2d(0, 1); glVertex2f(this->x, this->y);
        glTexCoord2d(1, 1); glVertex2f(this->x + this->width, this->y);
        glTexCoord2d(1, 0); glVertex2f(this->x + this->width, this->y + this->height);
        glTexCoord2d(0, 0); glVertex2f(this->x, this->y + this->height);
    glEnd();

    glDisable(GL_TEXTURE_2D);
}
