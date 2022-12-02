//Muylle Laurens - DAE14 - DrawFunctions
#include "pch.h"
#include "Game.h"
#include <iostream>

using namespace std;

//Basic game functions
#pragma region gameFunctions											
void Start()
{
	// initialize game resources here
	ArrayStart();
	TileStart();
	SnakeStart();
}

void Draw()
{
	if (g_IsGameOver == false)
	{
	ClearBackground(0.6f,0.6f,1.0f);

	}
	else
	{
		ClearBackground(1.0f, 0.0f, 0.0f);
	}
	
	DrawTiles();

	


	// Put your own draw statements here

}

void Update(float elapsedSec)
{
	// process input, do physics 

	// e.g. Check keyboard state
	//const Uint8 *pStates = SDL_GetKeyboardState( nullptr );
	//if ( pStates[SDL_SCANCODE_RIGHT] )
	//{
	//	std::cout << "Right arrow key is down\n";
	//}
	//if ( pStates[SDL_SCANCODE_LEFT] && pStates[SDL_SCANCODE_UP])
	//{
	//	std::cout << "Left and up arrow keys are down\n";
	//}


	if (g_IsGameOver == false)
	{
	TurnTiming(elapsedSec);

	}

}

void End()
{
	// free game resources here
}
#pragma endregion gameFunctions

//Keyboard and mouse input handling
#pragma region inputHandling											
void OnKeyDownEvent(SDL_Keycode key)
{

}

void OnKeyUpEvent(SDL_Keycode key)
{
	switch (key)
	{
		case SDLK_UP:
		{
			/*if (IsCoordSnakeBlock(int(g_snake.snakeHeadCoords.x), int(g_snake.snakeHeadCoords.y + 1)))
			{

			}
			else
			{
				g_snake.currentDirection = Direction::Up;
			}*/

			g_snake.currentDirection = Direction::Up;

			break;
		}
		case SDLK_DOWN:
		{
			/*if (IsCoordSnakeBlock(int(g_snake.snakeHeadCoords.x), int(g_snake.snakeHeadCoords.y - 1)))
			{

			}
			else
			{
				g_snake.currentDirection = Direction::Down;
			}*/
			g_snake.currentDirection = Direction::Down;

			break;
		}
		case SDLK_RIGHT:
		{
			/*if (IsCoordSnakeBlock(int(g_snake.snakeHeadCoords.x +1), int(g_snake.snakeHeadCoords.y )))
			{

			}
			else
			{
				g_snake.currentDirection = Direction::Right;
			}*/

			g_snake.currentDirection = Direction::Right;
			break;
		}
		case SDLK_LEFT:
		{
			/*if (IsCoordSnakeBlock(int(g_snake.snakeHeadCoords.x -1), int(g_snake.snakeHeadCoords.y )))
			{
	
			}
			else
			{
				g_snake.currentDirection = Direction::Left;
			}*/
			g_snake.currentDirection = Direction::Left;
			break;
		}
		
	
	}
}

void OnMouseMotionEvent(const SDL_MouseMotionEvent& e)
{
	

	//std::cout << "  [" << e.x << ", " << e.y << "]\n";
	//Point2f mousePos{ float( e.x ), float( g_WindowHeight - e.y ) };
}

void OnMouseDownEvent(const SDL_MouseButtonEvent& e)
{
	
}

void OnMouseUpEvent(const SDL_MouseButtonEvent& e)
{

	////std::cout << "  [" << e.x << ", " << e.y << "]\n";
	//switch (e.button)
	//{
	//case SDL_BUTTON_LEFT:
	//{
	//	//std::cout << "Left mouse button released\n";
	//	//Point2f mousePos{ float( e.x ), float( g_WindowHeight - e.y ) };
	//	break;
	//}
	//case SDL_BUTTON_RIGHT:
	//	//std::cout << "Right mouse button released\n";
	//	break;
	//case SDL_BUTTON_MIDDLE:
	//	//std::cout << "Middle mouse button released\n";
	//	break;
	//}
}
#pragma endregion inputHandling

#pragma region ownDefinitions
// Define your own functions here

void DrawTiles()
{

	
	for (int columnIndex{ 0 }; columnIndex < g_Columns; columnIndex++)
	{
		for (int rowIndex{ 0 }; rowIndex < g_Rows; rowIndex++)
		{
		Tile* currentTile = &g_TileArray[columnIndex][rowIndex];

			if (currentTile->currentType == TileType::Snake)
			{
			Point2f origin{ GetOrigin(currentTile->coordinate) };
			Point2f size{ g_WindowWidth / g_Columns , g_WindowHeight / g_Rows };
			SetColor(1.0f, 1.0f, 1.0f, 1.0f);
			FillRect(origin, size.x, size.y);

			}


		}

	}
}

//initializationCode
void ArrayStart()
{
	for (int indexColumn{ 0 }; indexColumn < g_Columns; indexColumn++)
	{
		g_TileArray[indexColumn] = new Tile[g_Rows];

		for (int indexRow{ 0 }; indexRow < g_Rows; indexRow++)
		{
			Tile ptrNewTile =  Tile{};
			g_TileArray[indexColumn][indexRow] = ptrNewTile;


		}
		
	}

}

void TileStart()
{
	
	for (int indexColumn{0}; indexColumn <  g_Columns; indexColumn++)
	{
		for (int indexRow{ 0 }; indexRow < g_Rows; indexRow++)
		{
			
			Tile* currentTile = &g_TileArray[indexColumn][indexRow];
			currentTile->coordinate = Point2f(float(indexColumn), float(indexRow));

			

			std::cout << "index:" << indexColumn << '\t' << "coords:" << currentTile->coordinate.x << "," << currentTile->coordinate.y << '\n';
		}

		//debugging purposes to display tiles 
	}
}

void SnakeStart()
{
	for (int i{0}; i < g_snake.length; i++)
	{
		Tile* currentTile = &g_TileArray[int(g_snake.snakeHeadCoords.x)][int(g_snake.snakeHeadCoords.y - i)];
		currentTile->currentType = TileType::Snake;
		currentTile->lightTimer = (g_snake.length - i);

	}
}

//update code

void TurnTiming(float elapsedSeconds)
{
	g_Timer += elapsedSeconds;

	if (g_Timer >= g_TimePerTurn)
	{
		g_Timer = 0.0f;
		TurnUpdate();
	}
}

void TurnUpdate()
{

	UpdateSnake();
	UpdateTiles();

}

void UpdateTiles()
{

	for (int indexColumn{ 0 }; indexColumn < g_Columns; indexColumn++)
	{
		for (int indexRow{ 0 }; indexRow < g_Rows; indexRow++)
		{

			Tile* currentTile = &g_TileArray[indexColumn][indexRow];
			TileCountDown(*currentTile);



			
		}

		
	}
	
}

void UpdateSnake()
{
	SnakeMovement();
}

void UpdateFood()
{

}


void GameOverTrigger()
{
	g_IsGameOver = true; 
	

}



//Tile code

void TileCountDown(Tile& currentTile)
{
	
	
	if(currentTile.lightTimer == 0)
	{
		if (currentTile.currentType != TileType::Inactive)
		{
			currentTile.currentType = TileType::Inactive;
		}
	}

	if (currentTile.lightTimer > 0)
	{
		currentTile.lightTimer -= 1;
	}
	
}

//snake code

void SnakeMovement()
{
	switch (g_snake.currentDirection)
	{
		case Direction::Up:
		{

			if (IsCoordSnakeBlock(int(g_snake.snakeHeadCoords.x ), int(g_snake.snakeHeadCoords.y + 1)))
			{
				GameOverTrigger();
			}
			else
			{
				g_snake.currentDirection = Direction::Left;
			
				g_snake.snakeHeadCoords.y += 1;

				Tile* currentTile = &g_TileArray[int(g_snake.snakeHeadCoords.x)][int(g_snake.snakeHeadCoords.y)];
				currentTile->currentType = TileType::Snake;
				currentTile->lightTimer = g_snake.length;

			}
				break;
		}
		case Direction::Down:
		{
			if (IsCoordSnakeBlock(int(g_snake.snakeHeadCoords.x), int(g_snake.snakeHeadCoords.y - 1)))
			{
				GameOverTrigger();

			}
			else
			{
				g_snake.snakeHeadCoords.y -= 1;

				Tile* currentTile = &g_TileArray[int(g_snake.snakeHeadCoords.x)][int(g_snake.snakeHeadCoords.y)];
				currentTile->currentType = TileType::Snake;
				currentTile->lightTimer = g_snake.length;

			}
				break;
		}
		case Direction::Right:
		{
			if (IsCoordSnakeBlock(int(g_snake.snakeHeadCoords.x + 1), int(g_snake.snakeHeadCoords.y  )))
			{
				GameOverTrigger();

			}
			else
			{
				g_snake.snakeHeadCoords.x += 1;

				Tile* currentTile = &g_TileArray[int(g_snake.snakeHeadCoords.x)][int(g_snake.snakeHeadCoords.y)];
				currentTile->currentType = TileType::Snake;
				currentTile->lightTimer = g_snake.length;

			}
				break;
		}
		case Direction::Left:
		{
			if (IsCoordSnakeBlock(int(g_snake.snakeHeadCoords.x -1), int(g_snake.snakeHeadCoords.y)))
			{
				GameOverTrigger();

			}
			else
			{

				g_snake.snakeHeadCoords.x -= 1;

				Tile* currentTile = &g_TileArray[int(g_snake.snakeHeadCoords.x)][int(g_snake.snakeHeadCoords.y)];
				currentTile->currentType = TileType::Snake;
				currentTile->lightTimer = g_snake.length;

			}
				break;
		}
	}

	
}

void SnakeEat()
{

}

void SnakeIncreaseLength()
{
	for (int indexColumn{ 0 }; indexColumn < g_Columns; indexColumn++)
	{
		for (int indexRow{ 0 }; indexRow < g_Rows; indexRow++)
		{

			Tile* currentTile = &g_TileArray[indexColumn][indexRow];
			if (currentTile->currentType == TileType::Snake)
			{
			currentTile->lightTimer += 1;

			}




		}


	}

}
	

//TileChecks
bool IsCoordSnakeBlock(int column, int row)
{
	if (g_TileArray[column][row].currentType == TileType::Snake)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool IsCoordFoodBlock(int column, int row)
{
	if (g_TileArray[column][row].currentType == TileType::Food)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool IsCoordOutOfBounds(int column, int row)
{
	if (((column < 0) || (column > (g_Columns - 1))) || ((row < 0) || (row > (g_Rows - 1))))
	{
		return true;
	}
	else
	{
		return false;
	}
}


//calculations
#pragma region CoordCalculations

Point2f GetCoord(const Point2f& origin)
{
	return Point2f{ 0,0 };
}



int GetArrayIndex(const Point2f& coord)
{

	return 0;
}

Point2f GetOrigin(const Point2f& coord)
{
	Point2f origin{coord.x * (g_WindowWidth / g_Columns)  , coord.y * (g_WindowHeight / g_Rows)};
	return origin;
}


#pragma endregion


#pragma endregion ownDefinitions