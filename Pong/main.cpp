#include <iostream>
#include "raylib.h"

int player_score = 0, cpu_score = 0;

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

            if(x+radius >= GetScreenWidth())
            {
                cpu_score++;
            }
            if(x+radius <=0)
            {
                player_score++;
            }
            if(y+radius >= GetScreenHeight() || y-radius <= 0)
            {
                speed_y = -speed_y;
            }
        }
};

class Paddle{
    public:
        float x,y;      //position of the paddle
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

class CPUPaddle : public Paddle
{
   public:
    
};


Ball ball;
Paddle player;
CPUPaddle CPU;

int main()
{
    //set window size
    const int screen_width = 1280;
    const int screen_height = 800;
    InitWindow(screen_width,screen_height,"Retro Games - Pong");
    SetTargetFPS(60);    

    //Ball Specs
    ball.radius = 20;
    ball.x = screen_width/2;
    ball.y = screen_height/2;
    ball.speed_x = 7;
    ball.speed_y = 7;

    //player paddle specs(on RHS)
    player.width = 25;
    player.height = 120;
    player.x = screen_width-player.width-10;
    player.y = screen_height/2 - player.height/2;
    player.speed = 6;

    //CPU paddle specs(on LHS)
    CPU.width = 25;
    CPU.height = 120;
    CPU.x = 10;
    CPU.y = screen_height/2 - CPU.height/2;
    CPU.speed = 6;

    while(!WindowShouldClose())
    {
        BeginDrawing();

        ball.Update();
        player.Update();

        ClearBackground(BLACK);

        ball.Draw();
    
        player.Draw();
        CPU.Draw();

        //check for collision
        if(CheckCollisionCircleRec(Vector2{ball.x,ball.y},ball.radius,Rectangle{player.x,player.y,player.width,player.height}))
        {
            ball.speed_x *= -1;
        }
        if(CheckCollisionCircleRec(Vector2{ball.x,ball.y},ball.radius,Rectangle{CPU.x,CPU.y,CPU.width,CPU.height}))
        {
            ball.speed_x *= -1;
        }
        
        DrawLine(screen_width/2,0,screen_width/2,screen_height,WHITE);

        
        EndDrawing();
    }

    CloseWindow();

   return 0; 
}