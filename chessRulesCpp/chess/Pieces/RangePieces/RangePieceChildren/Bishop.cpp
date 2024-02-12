#include "Bishop.h"
#include <math.h>
#include <iostream>

Bishop::Bishop(const unsigned int& x, const unsigned int& y, const bool& color, Piece*** board,
	std::bitset<NUM_OF_PIECES>** myControlledSquares, std::bitset<NUM_OF_PIECES>** enemyControlledSquares, Square* kingLocation) 
	: RangePiece(x, y, color, board, myControlledSquares, enemyControlledSquares, kingLocation)
{
	this->_indexControlledSquaresArr = BISHOP_INDEX;

	startingUpdateArrs();
}


bool Bishop::checkValidMovement(const Square& target) const
{
	if(abs(int(target.y - this->_square.y)) != abs(int(target.x - this->_square.x)))
	{
		return false;
	}
	checkDirection(target);
	return checkClearWay(target);
}

void Bishop::updateThisPieceSquares(const Square& target) const
{
	PieceDirection plumbDircection = this->_lastDirection;
	plumbDirection(plumbDircection);
	// turnning on the new squares that the bishop controlls: 
	changeMySquaresBits(false, true, plumbDircection, target);
	changeMySquaresBits(true, true, plumbDircection, target);

	// turnning on the last spot of the bishop:
	this->_myControlledSquares[target.y][target.x].reset(BISHOP_INDEX);

	// turnning off the bits that the old bishop controlled and the new one don't:
	changeMySquaresBits(false, false, plumbDircection, this->_square);
	changeMySquaresBits(true, false, plumbDircection, this->_square);
}

void Bishop::plumbDirection(PieceDirection& direction) const
{
	direction.x *= -1;
}

void Bishop::startingUpdateArrs() const
{
	if (this->_square.y == 0)
	{
		// for black starting position
		this->_myControlledSquares[this->_square.y + 1][this->_square.x - 1].set(this->_indexControlledSquaresArr);
		this->_myControlledSquares[this->_square.y + 1][this->_square.x + 1].set(this->_indexControlledSquaresArr);
	}
	else
	{
		// for white starting position
		this->_myControlledSquares[this->_square.y - 1][this->_square.x - 1].set(this->_indexControlledSquaresArr);
		this->_myControlledSquares[this->_square.y - 1][this->_square.x + 1].set(this->_indexControlledSquaresArr);
	}
}