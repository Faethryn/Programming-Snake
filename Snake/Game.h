#pragma once
using namespace utils;
#pragma region gameInformation
// Set your name and group in the title here
std::string g_WindowTitle{ "Snake - Muylle_Laurens, DeBaere_Jurre - 1DAE14" };

// Change the window dimensions here
float g_WindowWidth{ 600 };
float g_WindowHeight{ 600 };

Point2f g_MousePos{1.0f,1.0f};

#pragma endregion gameInformation



#pragma region ownDeclarations
// Declare your own global variables here

int g_Rows{ 30 };
int g_Columns{ 30 };

const float g_TimePerTurn{ 0.5f };
float g_Timer{ 0.0f };

bool g_IsGameOver{ false };

enum class TileType 
{
	Inactive, Snake, Food
};

enum class Direction
{
	Up, Down, Left, Right
};

struct Tile
{
	TileType currentType{ TileType::Inactive };
	int lightTimer{ 0 };
	Point2f coordinate{ 0,0 };
};

Tile** g_TileArray = new Tile * [g_Columns];

struct Snake
{
	int length{ 4 };
	Point2f snakeHeadCoords{ (g_Columns / 2) - 1.0f , (g_Rows / 2) - 1.0f };
	Direction currentDirection{ Direction::Up };
	Tile* snakeArray = nullptr;
};

Snake g_snake{};

 Texture g_SnakeTexture{ };


// Declare your own functions here
void ArrayStart();
void TileStart();
void SnakeStart();

void TurnTiming(float elapsedSeconds);
void TurnUpdate();

void UpdateTiles();
void UpdateSnake();
void UpdateFood();

void SnakeMovement();
void SnakeMove(int newColumn, int newRow);
void SnakeEat(int newColumn, int newRow);
void SnakeIncreaseLength();

bool IsCoordSnakeBlock(int column, int row);
bool IsCoordFoodBlock(int column, int row);
bool IsCoordOutOfBounds(int column, int row);

void GameOverTrigger();

Point2f GetCoord(const Point2f& origin);
Direction GetRelativeDirection(int xCoord1, int xCoord2, int yCoord1, int yCoord2);

int GetArrayIndex(const Point2f& coord);
Point2f GetOrigin(const Point2f& coord);
void TileCountDown(Tile& currentTile);
void DrawTiles();
void DrawSnake();
void DrawHead();
void DrawBody();
void DrawTail();


void DrawSnakeTile(const Point2f& origin, const Point2f& size);
void DrawSnakeTile(const Point2f& origin, const Point2f& size, const Point2f& sourceRectOrigin, const Point2f& sourceRectSize, const Texture& texture);


void DrawFood();

#pragma endregion ownDeclarations

#pragma region gameFunctions											
void Start();
void Draw();
void Update(float elapsedSec);
void End();
#pragma endregion gameFunctions

#pragma region inputHandling											
void OnKeyDownEvent(SDL_Keycode key);
void OnKeyUpEvent(SDL_Keycode key);
void OnMouseMotionEvent(const SDL_MouseMotionEvent& e);
void OnMouseDownEvent(const SDL_MouseButtonEvent& e);
void OnMouseUpEvent(const SDL_MouseButtonEvent& e);
#pragma endregion inputHandling
