/*******************************************************************************************
*
*   raylib [core] example - input mouse
*
*   Example complexity rating: [★☆☆☆] 1/4
*
*   Example originally created with raylib 1.0, last time updated with raylib 5.5
*
*   Example licensed under an unmodified zlib/libpng license, which is an OSI-certified,
*   BSD-like license that allows static linking with closed source software
*
*   Copyright (c) 2014-2025 Ramon Santamaria (@raysan5)
*
********************************************************************************************/

#include "raylib.h"

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
struct Ball {
    Vector2 position;
    Vector2 velocity;
    float radius;
};

struct Paddle {
    Vector2 position;
    Vector2 size;
};

int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "pong");

    Vector2 ballPosition = { 5.0f, 0.0f };
    Ball ball = {
        {400, 300},
        {300, 200},
        10
    };
    Paddle playerPaddle = {
        {5, 5},
        {20, 80}
    };
    Paddle opponentPaddle = {
        {775, 185},
        {20, 80}
    };

    Color ballColor = DARKBLUE;
    int opponentVelocity = 250;

    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    //---------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {

        playerPaddle.position.y = GetMouseY();
        float dt = GetFrameTime();
        ball.position.x += ball.velocity.x * dt;
        ball.position.y += ball.velocity.y * dt;
        if (ball.position.y - ball.radius <= 0) {
            ball.position.y = ball.radius;
            ball.velocity.y *= -1;
        }

        if (ball.position.y + ball.radius >= screenHeight) {
            ball.position.y = screenHeight - ball.radius;
            ball.velocity.y *= -1;
        }

        // player paddle bounce
        if (ball.velocity.x < 0 &&
            ball.position.x - ball.radius < playerPaddle.position.x + playerPaddle.size.x &&
            ball.position.x + ball.radius > playerPaddle.position.x &&
            ball.position.y - ball.radius < playerPaddle.position.y + playerPaddle.size.y &&
            ball.position.y + ball.radius > playerPaddle.position.y)
        {
            ball.position.x = playerPaddle.position.x + playerPaddle.size.x + ball.radius;
            ball.velocity.x *= -1;
        }
        // opponent paddle bounce

        float paddleCenter = opponentPaddle.position.y + opponentPaddle.size.y / 2;

        if (paddleCenter < ball.position.y) {
            opponentPaddle.position.y += opponentVelocity * dt;
        }

        if (paddleCenter > ball.position.y) {
            opponentPaddle.position.y -= opponentVelocity * dt;
        }

        if (opponentPaddle.position.y < 0) {
            opponentPaddle.position.y = 0;
        }

        if (opponentPaddle.position.y + opponentPaddle.size.y > screenHeight) {
            opponentPaddle.position.y = screenHeight - opponentPaddle.size.y;
        }
        if (ball.velocity.x > 0 &&
            ball.position.x + ball.radius > opponentPaddle.position.x &&
            ball.position.x - ball.radius < opponentPaddle.position.x + opponentPaddle.size.x &&
            ball.position.y + ball.radius > opponentPaddle.position.y &&
            ball.position.y - ball.radius < opponentPaddle.position.y + opponentPaddle.size.y)
        {
            ball.position.x = opponentPaddle.position.x - ball.radius;
            ball.velocity.x *= -1;
        }



        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

            ClearBackground(RAYWHITE);

            DrawRectangleV(playerPaddle.position, playerPaddle.size, RED);
            DrawRectangleV(opponentPaddle.position, opponentPaddle.size, RED);
            DrawCircleV(ball.position, ball.radius, BLACK);

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}
