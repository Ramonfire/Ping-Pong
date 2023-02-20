



#include"raylib.h"
#include<iostream>



struct Ball
{
	float x,y,speedX,speedY,radius;
	
	void Draw() {
		DrawCircle(x, y, radius, WHITE);
	}


};

struct Player {
	float x, y,width,height;
	float speed;
	int score;




	Rectangle GetRectangle(){
		return Rectangle{ x - width / 2, y - height / 3, width, height };
	}

	void Draw() {
		DrawRectangleRec(GetRectangle(), WHITE);
	}

};



int main() {
	InitWindow(800,600,"Ping Pong");
	SetWindowState(FLAG_VSYNC_HINT);

	std::unique_ptr<Ball> ball = std::make_unique<Ball>();
	std::unique_ptr<Player> playerLeft = std::make_unique<Player>();
	std::unique_ptr<Player> playerRight = std::make_unique<Player>();

	ball->x = (GetScreenWidth() / 2.0f);
	ball->y = (GetScreenHeight() / 2.0f);
	ball->speedX = 100;
	ball->speedY = 100;
	ball->radius = 5;
	playerLeft->x = 50;
	playerLeft->y = (GetScreenHeight() / 2) ;
	playerLeft->height = 100;
	playerLeft->width = 7;
	playerLeft->speed = 500;
	playerLeft->score = 0;
	

	playerRight->x = (GetScreenWidth() - 50); 
	playerRight->y = (GetScreenHeight() / 2) ;
	playerRight->height = 100;
	playerRight->width = 7;
	playerRight->speed = 500;
	playerRight->score = 0;

	const char* text{ nullptr };
	const char* leftScore{ nullptr };
	const char* rightScore{ nullptr };

	while (!WindowShouldClose()) {

		
		ball->x += ball->speedX * GetFrameTime();
		ball->y += ball->speedY * GetFrameTime();

		if (ball->y>GetScreenHeight())
		{
			ball->y = GetScreenHeight();
			ball->speedY *= -1;
		}
		if (ball->y <0)
		{
			ball->y = 0;
			ball->speedY *= -1;
		}


		if (IsKeyDown(KEY_W) && playerLeft->y>0)
		{
			playerLeft->y -= (playerLeft->speed * GetFrameTime());
		}
		if (IsKeyDown(KEY_S) && playerLeft->y<GetScreenHeight())
		{
			playerLeft->y += (playerLeft->speed * GetFrameTime());
		}


		if (IsKeyDown(KEY_UP) && playerRight->y > 0)
		{
			playerRight->y -= (playerRight->speed * GetFrameTime());
		}
		if (IsKeyDown(KEY_DOWN) && playerRight->y < GetScreenHeight())
		{
			playerRight->y += (playerRight->speed * GetFrameTime());
		}


		if (CheckCollisionCircleRec(Vector2{ ball->x,ball->y }, ball->radius,playerLeft->GetRectangle()))
		{
			if (ball->speedX<0)
			{
				ball->speedX *= -1.1;
				ball->speedY = (ball->y - playerLeft->y)/(playerLeft->height) *  ball->speedX;
				
			}
			
		}
		if (CheckCollisionCircleRec(Vector2{ ball->x,ball->y }, ball->radius,playerRight->GetRectangle()))
		{
			if (ball->speedX >0)
			{
				ball->speedX *= -1.1;
				ball->speedY = (ball->y - playerRight->y) / (playerRight->height ) * -ball->speedX;
			}
		}

		if (ball->x>GetScreenWidth())
		{
			text = "Left player Won! \n Press SPACE to restart";
			playerLeft->score++;
		}
		if (ball->x < 0)
		{
			text = "Right player Won! \n Press SPACE to restart";
			playerRight->score++;
		}

		  leftScore = "" + playerLeft->score;
		  rightScore = "" + playerRight->score;

		DrawText(leftScore, 0, 50 , 50, WHITE);
		DrawText(rightScore, 0, GetScreenWidth() -50 , 50, WHITE);



		BeginDrawing();
		ClearBackground(BLACK);


		ball->Draw();
		playerLeft->Draw();
		playerRight->Draw();
		
		if (text)
		{
			DrawText(text, 100, GetScreenWidth() / 2.0f - 30, 50, WHITE);
		}
		DrawFPS(10, 10);
		EndDrawing();

		if (IsKeyDown(KEY_SPACE))
		{
			ball->x = (GetScreenWidth() / 2.0f);
			ball->y = (GetScreenHeight() / 2.0f);
			ball->speedX = 100;
			ball->speedY = 100;
			ball->radius = 5;
			playerLeft->x = 50;
			playerLeft->y = (GetScreenHeight() / 2);
			playerLeft->height = 100;
			playerLeft->width = 7;
			playerLeft->speed = 500;
			


			playerRight->x = (GetScreenWidth() - 50);
			playerRight->y = (GetScreenHeight() / 2);
			playerRight->height = 100;
			playerRight->width = 7;
			playerRight->speed = 500;
			text = nullptr;
		}



	}


	CloseWindow();
	return 0;
}