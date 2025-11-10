#include "FootballPlayer_Team_TEMPLATE.h"

/////////////////////////////////////////////////
//  AVAILABLE METHODS AND STRUCTURES           //
/////////////////////////////////////////////////

// CalculateDistance(const Coordinates & p1, const Coordinates & p2)) -> double
// returns distance between two points in double

// GetBallCoordinates() ->Coordinates
// returns current ball position

// struct Cooridnates
// 
//              1111111
//    01234567890123456
//  0 ┌───────────────┐
//  1 │x             a│
//  2 │               │
//  3 │               │
//  4 │               │
//  5 │b             y│
//  6 └───────────────┘
// 
// x = {1, 1}     a = {15, 1}
// b = {1, 5}     y = {15, 5}


// GetGoalRange() -> std::pair<double, double>
// returns the size of the goal: the begining and the end
// 
// 0 ┌──────...
// 1 │
// 2 │| <- begining (2)
// 3 │|
// 4 || <- end (4)
// 5 │
// 6 └──────...


// GetMapWidth() -> int
// GetMapHeight() -> int
// returns the size of the pitch
//
//              1111111
//    01234567890123456
//  0 ┌───────────────┐
//  1 │               │
//  2 │               │
//  3 │               │
//  4 │               │
//  5 │               │
//  6 └───────────────┘
// 
//  MapWidth = 16       MapHeight = 6

// GetMyFootballer(N) -> Coordinates -> Coordinates
// returns position of the Nth footballer

// GetOpponentFootballer(N) -> Coordinates
// returns position of the Nth opponent footballer

// GetMyGoals() -> int
// GetOponentGoals() -> int
//
// number of goals

// NoOfFootballers() -> int
// number of footballers in your team

// SetTargetPositionForFootballer(int N, Coordinates) -> void
// destination of the Nth player

// SetTryKick(Coordinates) -> void
// try to kick the ball into the destination


/////////////////////////////////////////////////
//  namespace for your global data and methods //
/////////////////////////////////////////////////
namespace TEMPLATE
{

}

/////////////////////////////////////////////////
//  add your logic here                        //
/////////////////////////////////////////////////
void FootballPlayer_Team_TEMPLATE::CalculateNextMove()
{


}