#include "RangePiece.h"
#include <iostream>

RangePiece::RangePiece(const unsigned int& x, const unsigned int& y, const bool& color, Piece*** board,
	std::bitset<NUM_OF_PIECES>** myControlledSquares, std::bitset<NUM_OF_PIECES>** enemyControlledSquares, Square* kingLocation)
	: Piece(x, y, color, board, myControlledSquares, enemyControlledSquares, kingLocation)
{
	this->_lastDirection = new PieceDirection(0, 0);
}

RangePiece::~RangePiece()
{
	delete this->_lastDirection;
}

void RangePiece::checkDirection(const Square& target) const
{
	// taking the amount of squares that user wants to move in each dimention and checking if it is bigger than 0 and then putting 1
	// if it is smaller than 0 putting -1 and if it is 0 putting 0 and then constructing PieceDirection with the values: 

	bool signBitX = std::signbit((float(target.x) - float(this->_square.x)));
	bool signBitY = std::signbit((float(target.y) - float(this->_square.y)));

	this->_lastDirection->x = (((target.x - this->_square.x) != NO_MOVEMENT) * (((signBitX == true) * -1) + (signBitX == false)));
	this->_lastDirection->y = (((target.y - this->_square.y) != NO_MOVEMENT) * (((signBitY == true) * -1) + (signBitY == false)));
}


bool RangePiece::checkClearWay(const Square& targetSquare) const
{
	int checkedY = this->_square.y + this->_lastDirection->y;
	int checkedX = this->_square.x + this->_lastDirection->x;

	// checking if the path is clear untill the target that the piece wants to go to: 
	for (int i = 0; targetSquare.x != checkedX && targetSquare.y != checkedY;
		checkedX += this->_lastDirection->x, checkedY += this->_lastDirection->y)
	{
		if (checkedY > -1 && checkedY < ROWS && checkedX > -1 && checkedX < COLUMNS)
		{
			if (this->_board[checkedY][checkedX] != nullptr)
			{
				return false;
			}
		}
	}

	
	return true;
}

void RangePiece::changeMySquaresBits(const bool& revrseDirection, const bool& onOrOff,
	PieceDirection& direction, const Square& location) const
{
	Square checkedSquare = location;
	if (revrseDirection)
	{
		direction.reverseDirection();
	}

	// checking if not getting out of the board:
	if (location.x + direction.x >= COLUMNS || location.x + direction.x < 0 || 
		location.y + direction.y >= ROWS || location.y + direction.y < 0)
	{
		if (revrseDirection)
		{
			direction.reverseDirection();
		}
		return;
	}

	// turning off or on the bits in a specific diection  
	if (checkedSquare.y < ROWS && checkedSquare.x < COLUMNS && checkedSquare.y > -1 && checkedSquare.x > -1)
	{
		for (; (this->_board[checkedSquare.y][checkedSquare.x] == nullptr || (location.x == checkedSquare.x && location.y == checkedSquare.y)) ;checkedSquare += direction)
		{
			this->_myControlledSquares[checkedSquare.y][checkedSquare.x][this->_indexControlledSquaresArr] = onOrOff;

			if (checkedSquare.y < ROWS && checkedSquare.x < COLUMNS && checkedSquare.y > -1 && checkedSquare.x > -1)
			{
				break;
			}
		}
	}

	// turning the last bit that enemy piece stand on if this is the reason the for loop stopped
	if (checkedSquare.y < ROWS && checkedSquare.x < COLUMNS && checkedSquare.y > -1 && checkedSquare.x > -1)
	{
		this->_myControlledSquares[checkedSquare.y][checkedSquare.x][this->_indexControlledSquaresArr] = onOrOff;
	}

	if (revrseDirection)
	{
		direction.reverseDirection();
	}
}


void RangePiece::updateThisPieceSquares(const Square& target) const
{
	PieceDirection plumbDircection = this->_lastDirection;
	plumbDirection(plumbDircection);

	// turnning on the last spot of the range piece:
	this->_myControlledSquares[this->_square.y][this->_square.x][this->_indexControlledSquaresArr] = BIT_ON;

	// turnning off the bits that the old range piece controlled and the new one don't:
	changeMySquaresBits(false, false, plumbDircection, this->_square);
	changeMySquaresBits(true, false, plumbDircection, this->_square);

	// turnning on the new squares that the range piece controlls: 
	changeMySquaresBits(false, true, plumbDircection, target);
	changeMySquaresBits(true, true, plumbDircection, target);
}