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
}

void Draw()
{
	ClearBackground(0.6f,0.6f,1.0f);
	
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
	/*switch (key)
	{
	case SDLK_UP:
	
		break;
	case SDLK_DOWN:
		
		break;
	
	}*/
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
	int arraySize = g_Columns * g_Rows;
	for (int indexColumn{0}; indexColumn <  g_Columns; indexColumn++)
	{
		for (int indexRow{ 0 }; indexRow < g_Rows; indexRow++)
		{
			
			Tile* currentTile = &g_TileArray[indexColumn][indexRow];
			currentTile->coordinate = Point2f(float(indexColumn), float(indexRow));

			if (((indexColumn % 13) == 0) && ((indexRow % 10) == 0 ))
			{
				currentTile->currentType = TileType::Snake;
			}

			std::cout << "index:" << indexColumn << '\t' << "coords:" << currentTile->coordinate.x << "," << currentTile->coordinate.y << '\n';
		}

		//debugging purposes to display tiles 
	}
}

void TileCountDown(Tile& currentTile)
{
	if (currentTile.lightTimer == 0)
	{
		currentTile.currentType = TileType::Inactive;
	}
	else
	{
		currentTile.lightTimer -= 1;
	}
}



	



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