// Take the following structures and create functions that perform CRUD (create, read, update delete) operations in a file or multiple files depending on the need based on your understanding. Add a comment that exlpains your choice.

// struct player{
// char name[20];
// char team[20];
// };

// struct bowl{
// char type[10]; // seemer, pacer, spinner// N/A
// char arm[5]; //left or right
// struct player ply;
// };

// struct bat{
// char type[10]; // top order, middle order, lower order
// char handed[8]; //lefty or righty
// struct bowl ply2;
// };

// // suppose that you have to store data for 5 players with at least 3 bowlers. The rest will be N/A.
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FILENAME "players_data.txt"

// Structures
struct player {
    char name[20];
    char team[20];
};

struct bowl {
    char type[10]; // seemer, pacer, spinner, or N/A
    char arm[5];   // left or right, or N/A
    struct player ply;
};

struct bat {
    char type[10];   // top order, middle order, lower order, or N/A
    char handed[8];  // lefty or righty, or N/A
    struct bowl ply2;
};

// Function Declarations
void create_player();
void read_players();
void update_player(char *name);
void delete_player(char *name);

// Main Function
int main() {
    int choice;
    char name[20];

    do {
        printf("\n--- Player Management System ---\n");
        printf("1. Create Player\n");
        printf("2. Read All Players\n");
        printf("3. Update Player\n");
        printf("4. Delete Player\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                create_player();
                break;
            case 2:
                read_players();
                break;
            case 3:
                printf("Enter the name of the player to update: ");
                scanf("%s", name);
                update_player(name);
                break;
            case 4:
                printf("Enter the name of the player to delete: ");
                scanf("%s", name);
                delete_player(name);
                break;
            case 5:
                printf("Exiting program.\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 5);

    return 0;
}

// Function Definitions

// Create a new player
void create_player() {
    struct bat player_data;
    FILE *file = fopen(FILENAME, "a");

    if (file == NULL) {
        perror("Error opening file");
        return;
    }

    printf("Enter Player Name: ");
    scanf("%s", player_data.ply2.ply.name);
    printf("Enter Team Name: ");
    scanf("%s", player_data.ply2.ply.team);

    printf("Enter Bowler Type (seemer, pacer, spinner, or N/A): ");
    scanf("%s", player_data.ply2.type);
    printf("Enter Bowling Arm (left, right, or N/A): ");
    scanf("%s", player_data.ply2.arm);

    printf("Enter Batter Type (top, middle, lower, or N/A): ");
    scanf("%s", player_data.type);
    printf("Enter Batting Hand (lefty, righty, or N/A): ");
    scanf("%s", player_data.handed);

    fwrite(&player_data, sizeof(struct bat), 1, file);
    fclose(file);

    printf("Player created successfully.\n");
}

// Read all players
void read_players() {
    struct bat player_data;
    FILE *file = fopen(FILENAME, "r");

    if (file == NULL) {
        perror("Error opening file");
        return;
    }

    printf("\n--- Player Data ---\n");
    while (fread(&player_data, sizeof(struct bat), 1, file)) {
        printf("Name: %s, Team: %s\n", player_data.ply2.ply.name, player_data.ply2.ply.team);
        printf("Bowler Type: %s, Arm: %s\n", player_data.ply2.type, player_data.ply2.arm);
        printf("Batter Type: %s, Handed: %s\n\n", player_data.type, player_data.handed);
    }

    fclose(file);
}

// Update a player's data
void update_player(char *name) {
    struct bat player_data;
    int found = 0;
    FILE *file = fopen(FILENAME, "r+");

    if (file == NULL) {
        perror("Error opening file");
        return;
    }

    while (fread(&player_data, sizeof(struct bat), 1, file)) {
        if (strcmp(player_data.ply2.ply.name, name) == 0) {
            found = 1;

            printf("Enter Updated Player Name: ");
            scanf("%s", player_data.ply2.ply.name);
            printf("Enter Updated Team Name: ");
            scanf("%s", player_data.ply2.ply.team);

            printf("Enter Updated Bowler Type (seemer, pacer, spinner, or N/A): ");
            scanf("%s", player_data.ply2.type);
            printf("Enter Updated Bowling Arm (left, right, or N/A): ");
            scanf("%s", player_data.ply2.arm);

            printf("Enter Updated Batter Type (top, middle, lower, or N/A): ");
            scanf("%s", player_data.type);
            printf("Enter Updated Batting Hand (lefty, righty, or N/A): ");
            scanf("%s", player_data.handed);

            fseek(file, -sizeof(struct bat), SEEK_CUR);
            fwrite(&player_data, sizeof(struct bat), 1, file);

            printf("Player updated successfully.\n");
            break;
        }
    }

    if (!found) {
        printf("Player with name '%s' not found.\n", name);
    }

    fclose(file);
}

// Delete a player
void delete_player(char *name) {
    struct bat player_data;
    FILE *file = fopen(FILENAME, "r");
    FILE *temp = fopen("temp.txt", "w");

    if (file == NULL || temp == NULL) {
        perror("Error opening file");
        return;
    }

    int found = 0;
    while (fread(&player_data, sizeof(struct bat), 1, file)) {
        if (strcmp(player_data.ply2.ply.name, name) != 0) {
            fwrite(&player_data, sizeof(struct bat), 1, temp);
        } else {
            found = 1;
        }
    }

    fclose(file);
    fclose(temp);

    remove(FILENAME);
    rename("temp.txt", FILENAME);

    if (found) {
        printf("Player deleted successfully.\n");
    } else {
        printf("Player with name '%s' not found.\n", name);
    }
}
