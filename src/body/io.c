#include "functions/io.h"
#include "functions/sorting.h"

#include <string.h>
#include <stdlib.h>

void load_records(RECORD records[]) {
    FILE *f = fopen(RECORDS_FILE_NAME, "r");

    if (f) {
        read_record_lines(f, records);
        fclose(f);
    }
}

void print_to_file(FILE *file, RECORD records[]) {
    int i = 0;

    while (i < PLAYER_RECORD_COUNT && records[i].name[0] != '\0') {
        if (i == 0)
            fprintf(file, "%s;%d", records[i].name, records[i].score);
        else
            fprintf(file, "\n%s;%d", records[i].name, records[i].score);
        i++;
    }
}

void read_game(GAME *game) {
    char file_name[MAX_STRING_LENGTH + sizeof(DATA_FILE_EXTENSION)];
    FILE *file;

    sprintf(file_name, "%s.%s", game->player.name, DATA_FILE_EXTENSION);
    file = fopen(file_name, "rb");

    if (file) {
        fread(game,
              sizeof(GAME) - sizeof(TEMP_DATA),
              1, file); // Exclude temp fields from structure
        fclose(file);
    }
}

void read_record_lines(FILE *file, RECORD records[]) {
    int i = 0;
    char buffer[MAX_STRING_LENGTH];
    char *token;

    while (fgets(buffer, MAX_STRING_LENGTH, file)) {
        token = strtok(buffer, RECORDS_SEPARATOR);
        strcpy(records[i].name, token);
        records[i].score = strtol(strtok(NULL, RECORDS_SEPARATOR), &token, 10);
        i++;
    }
}

void save_game(GAME *game) {
    char file_name[MAX_STRING_LENGTH + sizeof(DATA_FILE_EXTENSION)];
    FILE *file;

    sprintf(file_name, "%s.%s", game->player.name, DATA_FILE_EXTENSION);
    file = fopen(file_name, "wb");

    if (file) {
        fwrite(game, sizeof(GAME) - sizeof(TEMP_DATA), 1,
               file);
        fclose(file);
    }
    save_to_leaderboard(game);
    save_to_leaderboard_file(game->temp_data.records);
}

void save_to_leaderboard_file(RECORD records[]) {
    FILE *file = fopen(RECORDS_FILE_NAME, "w");

    if (file) {
        print_to_file(file, records);
        fclose(file);
    }
}
