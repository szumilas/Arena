#include "TurboBeePlayerTeam1.h"


/*
Available methods:

	GetBagValue();
		returns number of pollen units in your bag

	GetFlowers();
		returns vector of all flowers

	GetMapElement(int x, int y);
		returns map element on position {x, y}, possible values:
			'o' - red flower
			'x' - purple flower
			' ' - grass
			'A'/'B'/'C'/... - player
			'#' - beehouse
		If bee is on flower, only player value is returned

	GetMapHeight();
		returns map height

	GetMapWidth();
		returns map width

	GetMyX();
		returns my X position

	GetMyY();
		returns my Y position

	GetOponentsDetails();
		returns details for all oponents (position, bagValue, beehouseValue)
		
*/

void TurboBeePlayerTeam1::CalculateNextMove()
{
	//--------------------------------------------
	// Add your algorithm here
	//--------------------------------------------


	nextMove = static_cast<NEXTMOVE>(rand() % 5);
}
