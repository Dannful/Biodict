#ifndef BIODICT_STRUCTURES_H
#define BIODICT_STRUCTURES_H

#include "constants.h"
#include "raylib.h"
#include "enums.h"

typedef struct {

    unsigned int frame;
    unsigned int last_bullet_frame;
    Vector2 target;

} SHOT;

typedef struct {

    float sinus;
    float cosinus;

} MOVEMENT;

typedef struct {

    unsigned int size;
    Vector2 position;
    DIRECTION direction;

} MILLIPEDE;

typedef struct {

    Texture2D mushroom;
    Texture2D player;
    Texture2D crosshair;
    Texture2D spider;
    Texture2D millipede;
    Texture2D bullet;
    Texture2D load_game;
    Texture2D pause_game;
    Texture2D start_game;
    Texture2D game_ranking;
    Texture2D exit_game;
    Texture2D paused_hint;
} GAME_TEXTURES;

typedef struct {

    Vector2 position;
    MUSHROOM_STATE mushroom_state;

} MUSHROOM;

typedef struct {

    unsigned int editing;
    unsigned int count;

} NAME_EDIT;

typedef struct {

    unsigned int remaining_bullets;
    unsigned int lives;
    unsigned int harvested;
    unsigned int sick;
    unsigned int invulnerability_frames;
    Vector2 position;
    SHOT shot;
    FARMER_STATE state;
    Rectangle frame_rectangle;
    char name[MAX_STRING_LENGTH];

} PLAYER;

typedef struct {

    Vector2 position;
    unsigned int dead;
    MOVEMENT movement;
    Vector2 target;

} SPIDER;

typedef struct {

    char name[MAX_STRING_LENGTH];
    unsigned int score;

} RECORD;

typedef struct {

    RECORD records[PLAYER_RECORD_COUNT];
    MENU_OPTION selected;
    unsigned int game_time;
    GAME_TEXTURES game_textures;

} TEMP_DATA;

typedef struct {

    MUSHROOM mushrooms[MUSHROOMS];
    unsigned int mushroom_count;
    PLAYER player;
    SPIDER spiders[SPIDERS];
    MILLIPEDE millipede;

    TEMP_DATA temp_data; // Excluded from loading/saving

} GAME;

typedef struct {
    SPIDER spider;
    Texture2D spider_texture;
} SPIDER_WITH_TEXTURE;

#endif
