#include <iostream>
#include <raylib.h>
using namespace std;
Color Green = {38, 245, 154, 255};        // A vibrant green color
Color DarkGreen = {20, 160, 133, 255};    // A standard dark green
Color light_green = {129, 204, 184, 255}; // A softer, lighter green
Color yellow = {243, 213, 154, 255};      // A bright yellow

int player_score = 0;
int cpu_score = 0;

class Ball
{
public:
   float x, y;
   int speed_x, speed_y;
   int radius;

   void Draw()
   {
      DrawCircle(x, y, radius, yellow);
   }

   void update()
   {
      x += speed_x;
      y += speed_y;

      // Bounce on top and bottom screen boundaries
      if (y + radius >= GetScreenHeight() || y - radius <= 0)
      {
         speed_y *= -1;
      }

      // Check if ball goes off the left or right side
      if (x + radius >= GetScreenWidth())
      {
         cpu_score++;
         resetball();
      }

      if (x - radius <= 0)
      {
         player_score++;
         resetball();
      }
   }
   void resetball()
   {
      x = GetScreenWidth() / 2;
      y = GetScreenHeight() / 2;
      int speedchoices[2] = {-1, 1};
      speed_x *= speedchoices[GetRandomValue(0, 1)];
      speed_y *= speedchoices[GetRandomValue(0, 1)];
   }
};

class Paddle
{
protected:
   void limitmovements()
   {
      if (y <= 0)
      {
         y = 0;
      }

      if (y + height >= GetScreenHeight())
      {
         y = GetScreenHeight() - height;
      }
   }

public:
   float x, y;
   float width, height;
   int speed;

   void Draw()
   {
      DrawRectangle(x, y, width, height, WHITE);
   }

   void update()
   {
      if (IsKeyDown(KEY_DOWN))
      {
         y += speed;
      }
      if (IsKeyDown(KEY_UP))
      {
         y -= speed;
      }
      limitmovements();
   }
};

class CPUPaddle : public Paddle
{
public:
   void update(int ball_y)
   {
      if (y + height / 2 > ball_y)
      {
         y -= speed;
      }
      if (y + height / 2 < ball_y)
      {
         y += speed;
      }
      limitmovements();
   }
};

Ball ball;
Paddle player;
CPUPaddle left_paddle;

int main()
{
   cout << "Game started" << endl;
   const int screen_width = 800;
   const int screen_height = 600;
   SetTargetFPS(60);

   // Initialize Ball
   ball.radius = 10;
   ball.x = screen_width / 2;
   ball.y = screen_height / 2;
   ball.speed_x = 7; // Ball starts moving to the right
   ball.speed_y = 7;

   // Initialize Left Paddle (CPU)
   left_paddle.width = 10;
   left_paddle.height = 120;
   left_paddle.x = 10;                                         // Positioned slightly away from the left edge
   left_paddle.y = screen_height / 2 - left_paddle.height / 2; // Centered vertically
   left_paddle.speed = 6;

   // Initialize Right Paddle (Player)
   player.width = 10;
   player.height = 120;
   player.x = screen_width - player.width - 10;      // Positioned slightly away from the right edge
   player.y = screen_height / 2 - player.height / 2; // Centered vertically
   player.speed = 6;

   InitWindow(screen_width, screen_height, "My Pong Game");

   while (!WindowShouldClose())
   {
      // Update Game Logic
      BeginDrawing();
      ball.update();
      player.update();
      left_paddle.update(ball.y);

      // Collision Detection
      if (CheckCollisionCircleRec((Vector2){ball.x, ball.y}, ball.radius,
                                  (Rectangle){player.x, player.y, player.width, player.height}))
      {
         ball.speed_x *= -1;
      }

      if (CheckCollisionCircleRec((Vector2){ball.x, ball.y}, ball.radius,
                                  (Rectangle){left_paddle.x, left_paddle.y, left_paddle.width, left_paddle.height}))
      {
         ball.speed_x *= -1;
      }

      // Drawing

      ClearBackground(DarkGreen);
      DrawRectangle(screen_width / 2, 0, screen_width / 2, screen_height, Green);
      DrawCircle(screen_width / 2, screen_height / 2, 150, light_green);
      DrawLine(screen_width / 2, 0, screen_width / 2, screen_height, WHITE); // Center line
      ball.Draw();
      player.Draw();
      left_paddle.Draw();
      DrawText(TextFormat("%i", cpu_score), screen_width / 4 - 20, 20, 50, WHITE);
      DrawText(TextFormat("%i", player_score), 3 * screen_width / 4 - 20, 20, 50, WHITE);

      EndDrawing();
   }

   CloseWindow();
   return 0;
}
