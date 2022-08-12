#ifndef BIODICT_STRUCTURES_H
#define BIODICT_STRUCTURES_H

#include "raylib.h"
#include "enums.h"

typedef struct {

    Vector2 position;
    int remaining_bullets;
    int lives;
    Texture2D texture;
} Player;

typedef struct {

    Vector2 position;
    Texture2D texture;
    enum MushroomState state;

} Mushroom;

typedef struct Bullet {

    Vector2 position;
    struct Bullet *previous_bullet;

} Bullet;

#endif
