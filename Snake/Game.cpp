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
	TextureFromFile("./Resources/snake-graphics.png", g_SnakeTexture);

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
		default:
			break;
		
	
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
	DrawSnake();
	
	for (int columnIndex{ 0 }; columnIndex < g_Columns; columnIndex++)
	{
		for (int rowIndex{ 0 }; rowIndex < g_Rows; rowIndex++)
		{
		Tile* currentTile = &g_TileArray[columnIndex][rowIndex];

			/*if (currentTile->currentType == TileType::Snake)
			{
			Point2f origin{ GetOrigin(currentTile->coordinate) };
			Point2f size{ g_WindowWidth / g_Columns , g_WindowHeight / g_Rows };
			SetColor(1.0f, 1.0f, 1.0f, 1.0f);
			FillRect(origin, size.x, size.y);

			}*/

			if (currentTile->currentType == TileType::Food)
			{
				Point2f origin{ GetOrigin(currentTile->coordinate) };
				Point2f size{ g_WindowWidth / g_Columns , g_WindowHeight / g_Rows };
				SetColor(1.0f, 0.0f, 0.0f, 1.0f);
				FillRect(origin, size.x, size.y);

			}


		}

	}
}



void DrawSnake()
{
	DrawHead();

	 DrawBody();
	

	 DrawTail();

}

void DrawHead()
{
		Tile* currentSnakeTile = &g_snake.snakeArray[0];

		Point2f origin{ GetOrigin(currentSnakeTile->coordinate) };
		Point2f size{ g_WindowWidth / g_Columns , g_WindowHeight / g_Rows };

		Point2f sourceOrigin{ 64, 192 };

		

		int yOffset{ int(g_snake.snakeArray[1].coordinate.y - currentSnakeTile->coordinate.y) };
		int xOffset{ int(g_snake.snakeArray[1].coordinate.x - currentSnakeTile->coordinate.x) };

		switch (yOffset)
		{
			case -1:
			{
				//up
				sourceOrigin = Point2f{ 192, 64 };

				break;
			}
			case 1:
			{
				//down
				sourceOrigin = Point2f{ 256, 128 };

				break;
			}

		}

		switch (xOffset)
		{
		case -1:
		{
			//right
			sourceOrigin = Point2f{ 256, 64 };
			break;
		}
		case 1:
		{
			//left
			sourceOrigin = Point2f{ 192, 128 };

			break;
		}

		}

		


		Point2f sourceSize{ 64,64 };

		DrawSnakeTile(origin, size, sourceOrigin, sourceSize, g_SnakeTexture);
	}


void DrawBody()
{
	for (int i{ 1 }; i < (g_snake.length - 1); i++)
	{
		Tile* currentSnakeTile = &g_snake.snakeArray[i];

		Point2f origin{ GetOrigin(currentSnakeTile->coordinate) };
		Point2f size{ g_WindowWidth / g_Columns , g_WindowHeight / g_Rows };
		Point2f sourceOrigin{ 64, 192 };


		Direction previousTileDirection{GetRelativeDirection(int(currentSnakeTile->coordinate.x ), int(g_snake.snakeArray[i-1].coordinate.x), int(currentSnakeTile->coordinate.y) ,int( g_snake.snakeArray[i - 1].coordinate.y))};
		Direction nextTileDirection{ GetRelativeDirection(int(currentSnakeTile->coordinate.x) , int(g_snake.snakeArray[i + 1].coordinate.x), int(currentSnakeTile->coordinate.y) , int(g_snake.snakeArray[i + 1].coordinate.y)) };

		if (previousTileDirection == Direction::Left || nextTileDirection == Direction::Left)
		{
			if (nextTileDirection == Direction::Up || previousTileDirection == Direction::Up)
			{
				sourceOrigin = Point2f{ 128, 192 };
			}
			if (nextTileDirection == Direction::Down || previousTileDirection == Direction::Down)
			{
				sourceOrigin = Point2f{ 128, 64 };

			}
			if (nextTileDirection == Direction::Right || previousTileDirection == Direction::Right)
			{
				sourceOrigin = Point2f{ 64, 64 };

			}
		}

		if (previousTileDirection == Direction::Up || nextTileDirection == Direction::Up)
		{

			if (nextTileDirection == Direction::Down || previousTileDirection == Direction::Down)
			{
				sourceOrigin = Point2f{ 128, 128 };

			}
			if (nextTileDirection == Direction::Right || previousTileDirection == Direction::Right)
			{
				sourceOrigin = Point2f{ 0, 128 };

			}
		}

		if (previousTileDirection == Direction::Down || nextTileDirection == Direction::Down)
		{

			if (nextTileDirection == Direction::Right || previousTileDirection == Direction::Right)
			{
				sourceOrigin = Point2f{ 0, 64 };

			}
			
		}



		Point2f sourceSize{ 64,64 };

		DrawSnakeTile(origin, size, sourceOrigin, sourceSize, g_SnakeTexture);

	}
}

void DrawTail()
{
	Tile* currentSnakeTile = &g_snake.snakeArray[g_snake.length-1];

	Point2f origin{ GetOrigin(currentSnakeTile->coordinate) };
	Point2f size{ g_WindowWidth / g_Columns , g_WindowHeight / g_Rows };

	Point2f sourceOrigin{ 64, 192 };



	int yOffset{ int(g_snake.snakeArray[g_snake.length - 2].coordinate.y - currentSnakeTile->coordinate.y) };
	int xOffset{ int(g_snake.snakeArray[g_snake.length - 2].coordinate.x - currentSnakeTile->coordinate.x) };

	switch (yOffset)
	{
	case -1:
	{
		//up
		sourceOrigin = Point2f{ 256, 256 };


		break;
	}
	case 1:
	{
		//down
		sourceOrigin = Point2f{ 192, 192 };

		break;
	}

	}

	switch (xOffset)
	{
	case -1:
	{
		//right
		sourceOrigin = Point2f{ 192, 256 };

		break;
	}
	case 1:
	{
		//left
		sourceOrigin = Point2f{ 256, 192 };


		break;
	}

	}




	Point2f sourceSize{ 64,64 };

	DrawSnakeTile(origin, size, sourceOrigin, sourceSize, g_SnakeTexture);
}

Direction GetRelativeDirection(int xCoord1, int xCoord2, int yCoord1, int yCoord2)
{
	int yOffset1{ yCoord1 - yCoord2 };
	

	int xOffset1{ xCoord1 - xCoord2 };

	switch (yOffset1)
	{
	case -1:
	{
		//up
		return Direction::Up;
		break;
	}
	case 1:
	{
		//down
		return Direction::Down;

		break;
	}

	}

	switch (xOffset1)
	{
	case -1:
	{
		//right
		return Direction::Right;

		break;
	}
	case 1:
	{
		//left
		return Direction::Left;

		break;
	}

	}

	return Direction::Up;

}



void DrawSnakeTile(const Point2f& origin, const Point2f& size)
{
	SetColor(1.0f, 1.0f, 1.0f, 1.0f);
	FillRect(origin, size.x, size.y);
}

void DrawSnakeTile(const Point2f& origin, const Point2f& size, const Point2f& sourceRectOrigin, const Point2f& sourceRectSize, const Texture& texture)
{
	Rectf destinationRect{ origin.x, origin.y, size.x, size.y };
	Rectf sourceRect{ sourceRectOrigin.x, sourceRectOrigin.y, sourceRectSize.x, sourceRectSize.y };

	DrawTexture(texture, destinationRect, sourceRect);
}


void DrawFood()
{

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

		

			if (((indexColumn % 25) == 0) && (((indexRow % 25) == 0)))
			{
				currentTile->currentType = TileType::Food;
				currentTile->lightTimer = 90;
			}
			

			std::cout << "index:" << indexColumn << '\t' << "coords:" << currentTile->coordinate.x << "," << currentTile->coordinate.y << '\n';
		}

		//debugging purposes to display tiles 
	}
}

void SnakeStart()
{
	g_snake.snakeArray = new Tile[g_snake.length];

	for (int i{0}; i < g_snake.length; i++)
	{
		Tile* currentTile = &g_TileArray[int(g_snake.snakeHeadCoords.x)][int(g_snake.snakeHeadCoords.y - i)];
		currentTile->currentType = TileType::Snake;
		currentTile->lightTimer = (g_snake.length - i);

		g_snake.snakeArray[i] = *currentTile;

		
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
			int newColumn = int(g_snake.snakeHeadCoords.x);
			int newRow = int(g_snake.snakeHeadCoords.y + 1);

			SnakeMove(newColumn, newRow);

				break;
		}
		case Direction::Down:
		{
			int newColumn = int(g_snake.snakeHeadCoords.x);
			int newRow = int(g_snake.snakeHeadCoords.y -1);

			SnakeMove(newColumn, newRow);

				break;
		}
		case Direction::Right:
		{
			int newColumn = int(g_snake.snakeHeadCoords.x +1);
			int newRow = int(g_snake.snakeHeadCoords.y );
			SnakeMove(newColumn, newRow);

				break;
		}
		case Direction::Left:
		{
			int newColumn = int(g_snake.snakeHeadCoords.x -1);
			int newRow = int(g_snake.snakeHeadCoords.y );

			SnakeMove(newColumn, newRow);

			
				break;
		}
	}

	
}

void SnakeMove(int newColumn, int newRow)
{
	if ((IsCoordOutOfBounds(newColumn, newRow)) || (IsCoordSnakeBlock(newColumn, newRow)))
	{
		GameOverTrigger();

	}
	else
	{
		SnakeEat(newColumn, newRow);

		g_snake.snakeHeadCoords = Point2f{ float(newColumn), float(newRow) };

		Tile* currentTile = &g_TileArray[int(g_snake.snakeHeadCoords.x)][int(g_snake.snakeHeadCoords.y)];
		currentTile->currentType = TileType::Snake;
		currentTile->lightTimer = g_snake.length;

		//shifts all segments back in array
		for (int i{ g_snake.length -1 }; i > 0; i--)
		{
			g_snake.snakeArray[i] = g_snake.snakeArray[i - 1];

		}

		g_snake.snakeArray[0] = *currentTile;

	}
}


void SnakeEat(int newColumn, int newRow)
{
	if (g_TileArray[newColumn][newRow].currentType == TileType::Food)
	{
		SnakeIncreaseLength();
	}
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
	g_snake.length += 1;

	Tile* newSnakeArray = new Tile[g_snake.length];

	for (int i{ 0 }; i < (g_snake.length - 1); i++)
	{
		newSnakeArray[i] = g_snake.snakeArray[i];
	}

	delete [] g_snake.snakeArray;
	g_snake.snakeArray = newSnakeArray;


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