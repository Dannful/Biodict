#ifndef BIODICT_CONSTANTS_H
#define BIODICT_CONSTANTS_H

/* Game constants */

#define FPS 60
#define MUSHROOMS 60 // Initial mushroom count

/* Files */

#define DATA_FILE_EXTENSION "bin"
#define RECORDS_FILE_NAME "records.txt"
#define RECORDS_SEPARATOR ";"

/* Millipede */

#define MAX_SIZE_MILLIPEDE 10
#define MIN_SIZE_MILLIPEDE 4
#define MILLIPEDE_SPEED 2.5f
#define MILLIPEDE_STEP 5.0f

/* Player */

#define PLAYER_BULLETS 200 // Initial player bullets
#define PLAYER_HEAL_AMOUNT 2
#define PLAYER_INVULNERABILITY_SECONDS 5
#define PLAYER_LIVES 3 // Initial player lives
#define PLAYER_RECORD_COUNT 5
#define PLAYER_SHOOT_COOLDOWN_SECONDS 0.5f
#define PLAYER_SHOT_COLOR BLUE
#define PLAYER_SPEED 2.0f

/* Spider */

#define SPIDER_SPAWN_CHANCE 50
#define SPIDER_SPAWN_PERIOD_SECONDS 5
#define SPIDER_SPEED 5.0f
#define SPIDER_STEP 130
#define SPIDERS 2

/* Image constants */

#define BULLET_IMAGE_PATH "resources/bullet.png"
#define CROSSHAIR_IMAGE_PATH "resources/crosshair.png"
#define MILLIPEDE_IMAGE_PATH "resources/millipede.png"
#define MUSHROOM_IMAGE_PATH "resources/mushroom.png"
#define PLAYER_IMAGE_PATH "resources/ships.png"
#define SPIDER_IMAGE_PATH "resources/spider.png"

/* UI */

/* General */

#define MAX_STRING_LENGTH 50
#define MENU_FONT 20

/* Bottom part */

#define HARVESTED_MUSHROOMS "COLHIDOS: %d"
#define REMAINING_BULLETS "BALAS: %d"
#define REMAINING_LIVES "VIDAS: %d"
#define REMAINING_MUSHROOMS "COGUMELOS: %d"

/* Upper part */

#define MENU_START "INICIAR"
#define MENU_LOAD "CARREGAR"
#define MENU_PAUSE "PAUSAR"
#define MENU_RANKING "RANKING"
#define MENU_EXIT "SAIR"
#define MENU_OPTION_COUNT 5
#define PAUSED_MENU_FONT_SIZE 20
#define PAUSED_MENU_TEXT "CLIQUE ABAIXO PARA DIGITAR SEU NOME E PRESSIONE ENTER \nPARA PARAR DE EDITAR"

#endif
