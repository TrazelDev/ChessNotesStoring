#include "Pawn.h"

int Pawn::s_pawnNumber = 0;
Pawn::Pawn(const unsigned int& x, const unsigned int& y, const bool& color, Piece*** board, std::bitset<NUM_OF_PIECES>** myControlledSquares, 
	std::bitset<NUM_OF_PIECES>** enemyControlledSquares, Square* kingLocation) : Piece(x, y, color, board, myControlledSquares, enemyControlledSquares, kingLocation)
{
	this->_moved = false;
	this->_indexControlledSquaresArr = PAWN_SATRTING_INDEX + (s_pawnNumber % PAWN_NUMBER);
	s_pawnNumber++;

    startingUpdateArrs();
}


bool Pawn::checkValidMovement(const Square& target) const
{
    // checking if the target square contains an enemy piece
    if (this->_board[target.y][target.x] != nullptr)
    {
        if ((target.x == this->_square.x + 1 || target.x == this->_square.x - 1) && (target.y == this->_square.y + 1 || target.y == this->_square.y - 1))
        {
            return true;
        }
        return false;
    }

    // checking if the current pawn can move forward twice
    else if ((this->_square.y == 6 && this->_board[this->_square.y][this->_square.x]->getColor()) || 
        (this->_square.y == 1 && !this->_board[this->_square.y][this->_square.x]->getColor()))
    {
        if (target.x == this->_square.x && target.y <= this->_square.y + 2)
        {
            return true;
        }
        return false;
    }

    // checking for every "normal" move the pawn can make
    if (target.x == this->_square.x && target.y == this->_square.y + (this->_color * -1) + (!this->_color))
    {
        return true;
    }
    return false;
}

void Pawn::updateThisPieceSquares(const Square& target) const
{
    int yInc = (this->_color * -1) + !this->_color;

    // removing old controlled squares
    if (this->_square.y + yInc < ROWS && this->_square.y > -1)
    {
        if (this->_square.x + 1 < COLUMNS)
        {
            this->_myControlledSquares[this->_square.y + yInc][this->_square.x + 1][this->_indexControlledSquaresArr] = BIT_OFF;
        }
        if (this->_square.x - 1 > -1)
        {
            this->_myControlledSquares[this->_square.y + yInc][this->_square.x - 1][this->_indexControlledSquaresArr] = BIT_OFF;
        }
    }

    // adding new controlled squares
    if (target.y + yInc < ROWS && target.y + yInc > -1)
    {
        if (target.x + 1 < COLUMNS)
        {
            this->_myControlledSquares[target.y + yInc][target.x + 1][this->_indexControlledSquaresArr] = BIT_ON;
        }
        if (target.x - 1 > -1)
        {
            this->_myControlledSquares[target.y + yInc][target.x - 1][this->_indexControlledSquaresArr] = BIT_ON;
        }
    }
}


void Pawn::startingUpdateArrs() const
{
    if (this->_square.x + 1 < COLUMNS)
    {
        this->_myControlledSquares[this->_square.y + (!this->_color + (this->_color * -1))][this->_square.x + 1].set(this->_indexControlledSquaresArr);
    }
    if(this->_square.x - 1 > -1)
    {
        this->_myControlledSquares[this->_square.y + (!this->_color + (this->_color * -1))][this->_square.x - 1].set(this->_indexControlledSquaresArr);
    }
}