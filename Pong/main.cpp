#include <iostream>
#include "raylib.h"

class Ball{
    public:
        float x,y;
        int speed_x,speed_y;
        int radius;
        void Draw(){
            DrawCircle(x,y,radius,WHITE);
        }

        void Update(){
            x+=speed_x;
            y+=speed_y;

            if(x+radius >= GetScreenWidth() || x-radius <= 0)
            {
                speed_x = -speed_x;
            }
            if(y+radius >= GetScreenHeight() || y-radius <= 0)
            {
                speed_y = -speed_y;
            }
        }
};

class Paddle{
    public:
        float x,y;
        float width,height;
        int speed;
        void Draw(){
            DrawRectangle(x,y,width,height,WHITE);
        }
        void Update(){

            if(IsKeyDown(KEY_UP) && y>=0)
            {
                y -=speed;
            }
            if(IsKeyDown(KEY_DOWN) && y+height<=GetScreenHeight())
            {
                y +=speed;
            }

            if(IsGamepadAvailable(0))
            {
                //controller arrow controls
                if(IsGamepadButtonDown(0,GAMEPAD_BUTTON_LEFT_FACE_UP) && y>=0)
                {
                    y -=speed;
                }
                if(IsGamepadButtonDown(0,GAMEPAD_BUTTON_LEFT_FACE_DOWN) && y+height<=GetScreenHeight())
                {
                    y +=speed;
                }

                //joystick controls
                float left_joystick_y = GetGamepadAxisMovement(0,GAMEPAD_AXIS_LEFT_Y);
                if(y+height<=GetScreenHeight() && left_joystick_y<0)
                    y += GetFrameTime() * speed * 100.0f * left_joystick_y;
                if(y>=0 && left_joystick_y>0)
                    y -= GetFrameTime() * speed * 100.0f * left_joystick_y;              
            }
        }

};

Ball ball;
Paddle player;

int main()
{
    const int screen_width = 1280;
    const int screen_height = 800;
    InitWindow(screen_width,screen_height,"Pong");
    SetTargetFPS(60);    

    ball.radius = 20;
    ball.x = screen_width/2;
    ball.y = screen_height/2;
    ball.speed_x = 7;
    ball.speed_y = 7;

    player.width = 25;
    player.height = 120;
    player.x = screen_width-player.width-10;
    player.y = screen_height/2 - player.height/2;
    player.speed = 6;

    while(!WindowShouldClose())
    {
        BeginDrawing();

        ball.Update();
        player.Update();

        ClearBackground(BLACK);

        ball.Draw();
    
        player.Draw();

        DrawRectangle(10,screen_height/2-60,25,120,WHITE);
        DrawLine(screen_width/2,0,screen_width/2,screen_height,WHITE);

        
        EndDrawing();
    }

    CloseWindow();

   return 0; 
}