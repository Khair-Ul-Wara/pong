#include <raylib.h>
int main(){
    int BallX = 400;
    int BallY = 400;
    Color green={20,160,133,255};
    InitWindow(800,800,"my first game");
    SetTargetFPS(60);
    while (WindowShouldClose()==false)
    {    
         if(IsKeyDown(KEY_RIGHT)){
        BallX+=3;
    }
    else if(IsKeyDown(KEY_LEFT)){
        BallX-=3;
        }
         else if(IsKeyDown(KEY_UP)){
        BallY-=3;
        }
         else if(IsKeyDown(KEY_DOWN)){
        BallY+=3;
        }
        
        BeginDrawing();
        ClearBackground(green);
        DrawCircle(BallX,BallY,10,WHITE);
        EndDrawing();
    }
    
    CloseWindow();
    return 0;
}