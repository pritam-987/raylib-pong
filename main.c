#include <stdio.h>
#include "include/raylib.h"
#include <stdbool.h>

typedef struct{
    float x;                
    float y;                
    float radius;
    Color color;
    
} Circle;


int main(void){
    float window_width = 800, window_height=600;
    bool pause = true;
    Vector2 speed = {5.5, 5.5};
    Vector2 score = {0,0};

    Circle circle = {
        .x = (window_width/2.0),
        .y = (window_height/2.0), 
        .radius = 10.0, 
        .color = BLUE

    } ;

    Rectangle player1 = {
        .x = 0,
        .y = window_height/2,
        .width = 25,
        .height = 200,
    };

    Rectangle player2 = {
        .x = window_width - player1.width,
        .y = window_height/2,
        .width = 25,
        .height = 200,
    };

    InitWindow(window_width, window_height, "pong");

    SetTargetFPS(60);

    while (!WindowShouldClose())
    {

        if (IsKeyDown(KEY_G)){
            pause = false;
        }
        if (!pause){
            circle.x += speed.x;
            circle.y += speed.y;

            // ball movement
            bool collision1 = CheckCollisionCircleRec((Vector2){circle.x, circle.y}, circle.radius, player1);
            bool collision2 = CheckCollisionCircleRec((Vector2){circle.x, circle.y}, circle.radius, player2);
            if(collision1 || collision2){
                speed.x *= -1;
            }
            else {
                if (circle.x <= circle.radius){
                    score.y += 1;
                    circle.x = window_width/2.0;
                    circle.y = window_height/2.0;
                    pause = true;
                } 
                if (circle.x >= (window_width - circle.radius)) {
                    score.x += 1;
                    circle.x = window_width/2.0;
                    circle.y = window_height/2.0;
                    pause = true;
                }
            }
            if ((circle.y >= (window_height - circle.radius)) || (circle.y <= circle.radius)) {
                speed.y *= -1;
            }
            //player movement
            if (IsKeyDown(KEY_S)){
                if ((player1.y + player1.height) <= window_height)
                player1.y += 5;
            }
            if (IsKeyDown(KEY_W)){
                if (player1.y  >= 0)
                player1.y -= 5;
            }
            if (IsKeyDown(KEY_DOWN)){
                if ((player2.y + player2.height) <= window_height)
                player2.y += 5;
            }
            if (IsKeyDown(KEY_UP)){
                if (player2.y  >= 0)
                player2.y -= 5;
            }

        }

        // draw here 
        BeginDrawing();

        DrawCircle(circle.x, circle.y, circle.radius,circle.color );
        DrawRectangle(player1.x, player1.y, player1.width, player1.height, RED);
        DrawRectangle(player2.x, player2.y, player2.width, player2.height, RED);

        DrawText(TextFormat(("%d"), (int)(score.x)), 200, 100, 100, WHITE);
        DrawText(TextFormat(("%d"), (int)(score.y)), window_width - 200, 100, 100, WHITE);

        ClearBackground(BLACK);

        EndDrawing();

    }
    CloseWindow();
    printf(", (int)(score.x) = %d\n", (int)(score.x));
    printf(", (int)(score.y) = %d\n", (int)(score.y));


    return 0;
}

