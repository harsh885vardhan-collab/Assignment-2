#include <stdio.h>
#include <conio.h>
#include <windows.h>
#include <stdlib.h>
#include <time.h>

void clear_screen_fast() {
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD pos = {0, 0};
    SetConsoleCursorPosition(h, pos);
}

// Game function
int startGame() {
    int playerPos = 1;  // Lane 0,1,2
    int score = 0, highScore = 0;

    // 3 obstacles
    int obsY[3] = {0, 4, 8};
    int obsX[3];

    for (int i = 0; i < 3; i++)
        obsX[i] = rand() % 3;

    while (1) {

        // INPUT ----
        if (_kbhit()) {
            char ch = getch();
            if (ch == 0 || ch == -32) ch = getch();
            if (ch == 75 && playerPos > 0) playerPos--; // LEFT
            if (ch == 77 && playerPos < 2) playerPos++; // RIGHT
        }

        // DRAW ----
        clear_screen_fast();
        printf("|--- SIMPLE ROAD GAME ---|\n");

        for (int row = 0; row < 10; row++) {
            printf("|");
            for (int lane = 0; lane < 3; lane++) {

                int printed = 0;

                for (int k = 0; k < 3; k++)
                    if (obsY[k] == row && obsX[k] == lane) {
                        printf(" # ");
                        printed = 1;
                        break;
                    }

                if (!printed) {
                    if (row == 9 && lane == playerPos)
                        printf(" O ");
                    else
                        printf("   ");
                }
            }
            printf("|\n");
        }

        printf("Score: %d\n", score);

        // COLLISION ----
        for (int k = 0; k < 3; k++) {
            if (obsY[k] == 9 && obsX[k] == playerPos) {
                printf("\nGAME OVER!\n");
                printf("Final Score: %d\n", score);
                return score;
            }
        }

        // SPEED
        Sleep(100);

        // MOVE OBSTACLES ----
        for (int k = 0; k < 3; k++) {
            obsY[k]++;

            if (obsY[k] > 9) {
                obsY[k] = 0;
                obsX[k] = rand() % 3;
                score += 5;   // bonus for dodging an obstacle
            }
        }

        score++; // score increases with time
    }
}

int main() {
    srand(time(NULL));
    system("color 1F");

    int highScore = 0;

    while (1) {
        int score = startGame();

        if (score > highScore)
            highScore = score;

        printf("High Score: %d\n", highScore);

        printf("\nPlay Again? (Y/N): ");
        char ch = getch();

        if (ch != 'y' && ch != 'Y')
            break;
    }

    printf("\nThanks for playing!\n");
    return 0;
}
