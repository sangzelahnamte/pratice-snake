#include <raylib.h>
#include <deque>
#include <raymath.h>

//Global variables
Color green = { 173, 204, 96, 255 };
Color darkGreen = { 43, 51, 24, 255 };
int cellSize = 20;
int cellCount = 30;
double lastUpdateTime = 0;

bool eventTriggered(double interval) // 200 millisecond a kal tir na
{
	double currentTime = GetTime(); // dar zat lakna
	if (currentTime - lastUpdateTime >= interval)
	{
		lastUpdateTime = currentTime;
		return true;
	}
	return false;
}

class Food
{
public:
	Vector2 position;
	Texture2D texture;
	Food()
	{
		Image image = LoadImage("image/food.png");
		texture = LoadTextureFromImage(image);
		UnloadImage(image);
		position = generateRandomPos();
	}
	~Food()
	{
		UnloadTexture(texture);
	}
	void draw() {
		DrawTexture(texture, position.x * cellSize, position.y * cellSize, WHITE);
	}
	Vector2 generateRandomPos()
	{
		float x = GetRandomValue(0, cellCount - 1);
		float y = GetRandomValue(0, cellCount - 1);
		return  Vector2{ x, y };
	}
};

class Snake
{
public:
	std::deque<Vector2> body = { Vector2{8, 9}, Vector2{7, 9}, Vector2{6, 9} };
	Vector2 direction{1, 0};
	void draw() {
		for (unsigned int i = 0; i < body.size(); i++)
		{
			float x = body[i].x;
			float y = body[i].y;
			Rectangle rec = Rectangle{ x * cellSize, y * cellSize, (float)cellSize, (float)cellSize };
			DrawRectangleRounded(rec, 0.6, 5, darkGreen);
		}
	}
	void update() {
		body.pop_back();
		body.push_front(Vector2Add(body[0], direction));
	}
};

int main() {

	InitWindow(cellSize * cellCount, cellSize * cellCount, "Game");

	SetTargetFPS(60);

	Food food = Food();
	Snake snake = Snake();

	while (!WindowShouldClose())
	{
		BeginDrawing();

		ClearBackground(green);
		if (eventTriggered(0.2)) // update snake movement to 200 millisecond
		{
			snake.update();
		}
		if (IsKeyPressed(KEY_UP))
		{
			snake.direction = { 0, -1 };
		}
		if (IsKeyPressed(KEY_DOWN))
		{
			snake.direction = { 0, 1 };
		}
		if (IsKeyPressed(KEY_LEFT))
		{
			snake.direction = { -1, 0 };
		}
		if (IsKeyPressed(KEY_RIGHT))
		{
			snake.direction = { 1, 0 };
		}
		food.draw();
		snake.draw();
		

		EndDrawing();
	}

	CloseWindow();

	return 0;
};