#include <stdio.h>
#include <conio.h>
#include <windows.h>
#include <stdlib.h>
#include <time.h>
#include <mmsystem.h>

void clear_screen_fast() {
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD pos = {0, 0};
    SetConsoleCursorPosition(h, pos);
}

int main() {
    system("color 4F");
    PlaySound(TEXT("bg.wav"), NULL, SND_ASYNC | SND_LOOP);

    srand(time(0));

    int x = 1;                     // player position (0,1,2)
    int step = 0;                  // obstacle vertical movement
    int obstaclePos = rand() % 3;  // 0,1,2

    int score = 0;                 // SCORE system
    int lives = 3;                 // 3 LIVES system
    int speed = 120;               // DIFFICULTY / SPEED

    while (lives > 0) {

        if (_kbhit()) {
            char ch = getch();

            if (ch == 75 && x > 0)        // LEFT
                x--;
            if (ch == 77 && x < 2)        // RIGHT
                x++;
        }

        clear_screen_fast();

        printf("Score: %d   Lives: %d\n", score, lives);
        printf("|--- --- ---|\n");

        for (int i = 0; i < 10; i++) {
            if (i == step) {

                if (obstaclePos == 0)
                    printf("| %c        |\n", 1);
                else if (obstaclePos == 1)
                    printf("|     %c    |\n", 1);
                else if (obstaclePos == 2)
                    printf("|        %c |\n", 1);

            } else {
                printf("|           |\n");
            }
        }

        if (x == 0)
            printf("| %c         |\n", 6);
        else if (x == 1)
            printf("|     %c     |\n", 6);
        else if (x == 2)
            printf("|        %c  |\n", 6);

        // COLLISION CHECK
        if (step == 10 && x == obstaclePos) {
            PlaySound(TEXT("impact.wav"), NULL, SND_ASYNC);
            lives--;      // lose 1 life
            step = 0;

            if (lives > 0) {
                obstaclePos = rand() % 3;
                Sleep(800);  // small break after hit
                continue;
            }
        }

        // If safe crossing, increase score
        if (step == 10 && x != obstaclePos) {
            score++;
        }

        Sleep(speed);
        step++;

        // Reset obstacle
        if (step > 10) {
            step = 0;
            obstaclePos = rand() % 3;

            // Increase difficulty (speed up)
            if (score % 5 == 0 && speed > 40) {
                speed -= 5;
            }
        }
    }

    PlaySound(NULL, NULL, 0);

    clear_screen_fast();
    printf("\n GAME OVER \n");
    printf(" Final Score: %d\n", score);

    return 0;
}
