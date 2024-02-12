#include "Queen.h"
#include <iostream>
Queen::Queen(const unsigned int& x, const unsigned int& y, const bool& color, Piece*** board,
	std::bitset<NUM_OF_PIECES>** myControlledSquares, std::bitset<NUM_OF_PIECES>** enemyControlledSquares, Square* kingLocation)
	: RangePiece(x, y, color, board, myControlledSquares, enemyControlledSquares, kingLocation)
{
	this->_indexControlledSquaresArr = QUEEN_INDEX;

	startingUpdateArrs();
}


bool Queen::checkValidMovement(const Square& target) const
{
	if (abs(int(target.y - this->_square.y)) != abs(int(target.x - this->_square.x)) && 
		(target.x - this->_square.x) && (target.y - this->_square.y))
	{
		return false;
	}
	
	checkDirection(target);
	return checkClearWay(target);
}

void Queen::plumbDirection(PieceDirection& direction) const
{
	if(direction.x == 0 || direction.y == 0) 
	{
		int temp = direction.x;
		direction.x *= direction.y;
		direction.y *= temp;
	}
	else
	{
		direction.x *= -1;
	}
}

void Queen::updateThisPieceSquares(const Square& target) const
{
	RangePiece::updateThisPieceSquares(target);

	if (this->_lastDirection->x || this->_lastDirection->y)
	{
		// if the queen moved like a bishop than needs to change the squares that it controlls like rook
		PieceDirection direction = PieceDirection(1, 0);
		changeRookSquaresInArr(false, this->_square, direction);
		changeRookSquaresInArr(true, target, direction);
	}
	else
	{
		// if the queen moved like a rook than needs to change the squares that it controlls like bishop
		PieceDirection direction = PieceDirection(1, 1);
		changeRookSquaresInArr(false, this->_square, direction);
		changeRookSquaresInArr(true, target, direction);
	}
}

void Queen::changeRookSquaresInArr(bool onOrOff, const Square& target, PieceDirection initailDirection) const
{
	PieceDirection direction = PieceDirection(1, 0);
	int temp = 0;
	
	// turnning off all of the all of the Bishop or Rook controlled type squares:
	changeMySquaresBits(false, onOrOff, initailDirection, target);
	changeMySquaresBits(true, onOrOff, initailDirection, target);

	// plumb to the direction:
	plumbDirection(initailDirection);

	changeMySquaresBits(false, onOrOff, initailDirection, target);
	changeMySquaresBits(true, onOrOff, initailDirection, target);
}

void Queen::startingUpdateArrs() const
{
	// going around the queen and turning all the bits around it becuase in the starting position it only 
	// controlls the squares around it
	for (int i = -1; i < 2; i++)
	{
		// checking if the y is going outside of the boundries:
		if (!(this->_square.y + i < COLUMNS && this->_square.y + i > -1))
		{
			continue;
		}

		for (int j = -1; j < 2; j++)
		{
			if (i != 0 || j != 0)
			{
				this->_myControlledSquares[this->_square.y + i][this->_square.x + j].set(this->_indexControlledSquaresArr);
			}
		}
	}
}
