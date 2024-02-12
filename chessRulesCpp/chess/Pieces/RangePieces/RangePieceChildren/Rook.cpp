#include "Rook.h"
#include <iostream>

Rook::Rook(const unsigned int& x, const unsigned int& y, const bool& color, Piece*** board, std::bitset<NUM_OF_PIECES>** myControlledSquares, 
	std::bitset<NUM_OF_PIECES>** enemyControlledSquares, Square* kingLocation) : RangePiece(x, y, color, board, myControlledSquares, enemyControlledSquares, kingLocation)
{
    this->_moved = new bool;
    *this->_moved = false;
	// if this is a coustume position than need to use static variable
	this->_indexControlledSquaresArr = (x == COLUMNS - 1);

    startingUpdateArrs();
}

Rook::~Rook()
{
    delete this->_moved;
}

bool Rook::getMoved() const
{
    return *this->_moved;
}

bool Rook::checkValidMovement(const Square& target) const
{
	if ((target.x - this->_square.x) && (target.y - this->_square.y))
	{
		return false;
	}
	checkDirection(target);

    if (checkClearWay(target) == false)
    {
        return false;
    }
    *this->_moved = true;
    return true;
}


void Rook::plumbDirection(PieceDirection& direction) const
{
	int temp = direction.x;
	direction.x *= direction.y;
	direction.y *= temp;
}


void Rook::startingUpdateArrs() const
{
    // checking if the rook is in the first column
    if (this->_square.x == 0)
    {
        this->_myControlledSquares[this->_square.y][1].set(this->_indexControlledSquaresArr);
    }
    else
    {
        this->_myControlledSquares[this->_square.y][COLUMNS - 2].set(this->_indexControlledSquaresArr);
    }

    // checking if the rook is in the first row
    if (this->_square.y == 0)
    {
        this->_myControlledSquares[1][this->_square.x].set(this->_indexControlledSquaresArr);
    }
    else
    {
        this->_myControlledSquares[ROWS - 2][this->_square.x].set(this->_indexControlledSquaresArr);
    }
}