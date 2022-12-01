#pragma once
using namespace utils;
#pragma region gameInformation
// Set your name and group in the title here
std::string g_WindowTitle{ "Snake - Muylle_Laurens, DeBaere_Jurre - 1DAE14" };

// Change the window dimensions here
float g_WindowWidth{ 800 };
float g_WindowHeight{ 800 };

Point2f g_MousePos{1.0f,1.0f};

#pragma endregion gameInformation



#pragma region ownDeclarations
// Declare your own global variables here

int g_Rows{ 30 };
int g_Columns{ 30 };




enum class TileType 
{
	Inactive, Snake, Food
};

struct Tile
{
	TileType currentType{ TileType::Inactive };
	int lightTimer{ 0 };
	Point2f coordinate{ 0,0 };
};


Tile* g_TileArray = new Tile[ g_Columns * g_Rows];






// Declare your own functions here

void TileStart();
Point2f GetCoord(const Point2f& origin);
Point2f GetCoord(int index);
int GetArrayIndex(const Point2f& coord);
Point2f GetOrigin(const Point2f& coord);
void TileCountDown(Tile& currentTile);
void DrawTiles();

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
