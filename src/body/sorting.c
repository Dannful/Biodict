#include "functions/sorting.h"

#include <string.h>

void save_to_leaderboard_position(RECORD records[], PLAYER player, int position) {
    strcpy(records[position].name, player.name);
    records[position].score = player.harvested;
}

void check_last_position(RECORD records[], PLAYER player, int inserted) {
    if (!inserted && records[PLAYER_RECORD_COUNT - 1].score < player.harvested)
        save_to_leaderboard_position(records, player, PLAYER_RECORD_COUNT - 1);
}

void switch_positions(RECORD records[], int i, int j) {
    char name_aux[MAX_STRING_LENGTH];
    unsigned int score_aux;

    strcpy(name_aux, records[i].name);
    score_aux = records[i].score;

    strcpy(records[i].name, records[j].name);
    records[i].score = records[j].score;
    strcpy(records[j].name, name_aux);
    records[j].score = score_aux;
}

void sort_records(RECORD records[]) {
    int i, j;

    for (i = 0; i < PLAYER_RECORD_COUNT; i++)
        for (j = 0; j < PLAYER_RECORD_COUNT - i - 1; j++)
            if (records[j].name[0] * records[j + 1].name[0] != 0 &&
                records[j].score < records[j + 1].score)
                switch_positions(records, j, j + 1);
}

void save_to_leaderboard(GAME *game) {
    int i = 0;
    int inserted = 0;

    while (i < PLAYER_RECORD_COUNT && !inserted) {
        if (game->temp_data.records[i].name[0] == '\0' ||
            strcmp(game->player.name, game->temp_data.records[i].name) == 0 &&
            game->temp_data.records[i].score < game->player.harvested) {
            save_to_leaderboard_position(game->temp_data.records, game->player, i);
            inserted = 1;
        }
        i++;
    }
    check_last_position(game->temp_data.records, game->player, inserted);
    sort_records(game->temp_data.records);
}
