#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct Game {
    int randomNumber;
    int guess;
    int attempts;
};

void generateRandomNumber(int min, int max, int* randomNumber) {
    srand(time(NULL));
    *randomNumber = (rand() % (max - min + 1)) + min;
}

void initializeGame(struct Game* game, int min, int max) {
    game->randomNumber = 0;
    game->guess = 0;
    game->attempts = 0;
    generateRandomNumber(min, max, &(game->randomNumber));
}

void playGame(struct Game* game) {
    int min, max;
    printf("Enter the minimum and maximum range for the random number:\n");
    printf("Minimum: ");
    scanf("%d", &min);
    printf("Maximum: ");
    scanf("%d", &max);

    initializeGame(game, min, max);

    printf("\n");
    printf("===== Guessing Number Game =====\n");
    printf("Guess a number between %d and %d.\n", min, max);

    while (1) {
        printf("Enter your guess: ");
        scanf("%d", &(game->guess));

        (game->attempts)++;

        if (game->guess == game->randomNumber) {
            printf("\nCongratulations! You guessed the correct number in %d attempts.\n", game->attempts);
            break;
        } else if (game->guess < game->randomNumber) {
            printf("Too low. Try again!\n");
        } else {
            printf("Too high. Try again!\n");
        }
    }
}

void saveGameStats(struct Game* game) {
    FILE* file = fopen("game_stats.txt", "a");

    if (file == NULL) {
        printf("Error: Failed to open file for writing.\n");
        return;
    }

    fprintf(file, "Game Statistics:\n");
    fprintf(file, "Random Number: %d\n", game->randomNumber);
    fprintf(file, "Attempts: %d\n", game->attempts);
    fprintf(file, "\n");

    fclose(file);
    printf("\nGame statistics saved to file.\n");
}

int main() {
    struct Game game;

    printf("\nWelcome to the Guessing Number Game!\n\n");

    char choice;
    do {
        playGame(&game);
        saveGameStats(&game);

        printf("\n");
        printf("Do you want to play again? (y/n): ");
        scanf(" %c", &choice);
        printf("\n");
    } while (choice == 'y' || choice == 'Y');

    return 0;
}

