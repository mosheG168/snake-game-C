#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define WIDTH 20
#define HEIGHT 10
#define MAX_TAIL 100

typedef enum { STOP = 0, LEFT, RIGHT, UP, DOWN } Direction;

typedef struct {
    int x, y;
} Point;

Point snake[MAX_TAIL];
int tailLength = 1;
Point fruit;
Direction dir = STOP;
int score = 0;
int gameOver = 0;

void initGame()
{
    snake[0].x = WIDTH / 2;
    snake[0].y = HEIGHT / 2;
    srand((unsigned)time(NULL));
    fruit.x = rand() % WIDTH;
    fruit.y = rand() % HEIGHT;
    score = 0;
    tailLength = 1;
    dir = STOP;
    gameOver = 0;
}

void drawBoard()
{
    system("clear");

    for (int i = 0; i < WIDTH + 2; i++) printf("#");
    printf("\n");

    for (int y = 0; y < HEIGHT; y++)
    {
        for (int x = 0; x < WIDTH; x++)
        {
            if (x == 0) printf("#");

            int printed = 0;

            if (snake[0].x == x && snake[0].y == y)
            {
                printf("O"); // head
                printed = 1;
            }
            else if (fruit.x == x && fruit.y == y)
            {
                printf("F");
                printed = 1;
            }
            else
            {
                for (int k = 1; k < tailLength; k++)
                {
                    if (snake[k].x == x && snake[k].y == y)
                    {
                        printf("o");
                        printed = 1;
                        break;
                    }
                }
            }

            if (!printed) printf(" ");

            if (x == WIDTH - 1) printf("#");
        }
        printf("\n");
    }

    for (int i = 0; i < WIDTH + 2; i++) printf("#");
    printf("\nScore: %d\n", score);
}

void input()
{
    printf("Move (W-A-S-D then ENTER): ");
    char c;
    scanf(" %c", &c);

    switch (c) {
        case 'a': case 'A': dir = LEFT; break;
        case 'd': case 'D': dir = RIGHT; break;
        case 'w': case 'W': dir = UP; break;
        case 's': case 'S': dir = DOWN; break;
        case 'x': case 'X': gameOver = 1; break;
        default: break;
    }
}

void logic()
{
    Point prev = snake[0];
    Point temp;

    for (int i = 1; i < tailLength; i++)
    {
        temp = snake[i];
        snake[i] = prev;
        prev = temp;
    }

    switch (dir)
    {
        case LEFT:  snake[0].x--; break;
        case RIGHT: snake[0].x++; break;
        case UP:    snake[0].y--; break;
        case DOWN:  snake[0].y++; break;
        default: break;
    }

    if (snake[0].x < 0 || snake[0].x >= WIDTH || snake[0].y < 0 || snake[0].y >= HEIGHT)
        gameOver = 1;

    for (int i = 1; i < tailLength; i++)
    {
        if (snake[0].x == snake[i].x && snake[0].y == snake[i].y)
            gameOver = 1;
    }

    if (snake[0].x == fruit.x && snake[0].y == fruit.y)
    {
        if (tailLength < MAX_TAIL) tailLength++;
        score += 10;
        fruit.x = rand() % WIDTH;
        fruit.y = rand() % HEIGHT;
    }
}

int main()
{
    initGame();
    while (!gameOver)
    {
        drawBoard();
        input();
        logic();
    }

    printf("Game Over! Final Score: %d\n", score);
    return 0;
}
