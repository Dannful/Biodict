#ifndef BIODICT_ENUMS_H
#define BIODICT_ENUMS_H

typedef enum {

    LEFT = 0,
    RIGHT = 1

} DIRECTION;

typedef enum {

    FARMER_ACTIVE = 0,
    FARMER_PARALYSED = 1,
    FARMER_DEAD = 2

} FARMER_STATE;

typedef enum {

    START = 0,
    LOAD = 1,
    PAUSE = 2,
    RANKING = 3,
    SAVE_RANKING = 4,
    NONE = 5

} MENU_OPTION;

typedef enum {

    MUSHROOM_ACTIVE = 0,
    MUSHROOM_HARVESTED = 1,
    MUSHROOM_EATEN = 2

} MUSHROOM_STATE;

#endif
