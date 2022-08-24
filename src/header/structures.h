#ifndef BIODICT_STRUCTURES_H
#define BIODICT_STRUCTURES_H

#include "raylib.h"
#include "enums.h"

typedef struct bullet {

    float sinus, cosinus, angle;
    Vector2 position;
    struct bullet *previous_bullet;

} BULLET;

typedef struct {

    Texture2D mushroom;
    Texture2D player;
    Texture2D crosshair;
    Texture2D spider;
    Texture2D millipede;
    Texture2D bullet;
} GAME_TEXTURES;

typedef struct {

    Rectangle frame_rectangle;
    Vector2 position;
    MUSHROOM_STATE state;

} MUSHROOM;

typedef struct {

    Vector2 position;
    int remaining_bullets;
    int lives;
    Rectangle frame_rectangle;
} PLAYER;

#endif
