#include "King.h"

King::King(const unsigned int& x, const unsigned int& y, const bool& color, Piece*** board,
    std::bitset<NUM_OF_PIECES>** myControlledSquares, std::bitset<NUM_OF_PIECES>** enemyControlledSquares, Square** kingLocation)
    : Piece(x, y, color, board, myControlledSquares, enemyControlledSquares, *kingLocation)
{
    this->_moved = new bool;
    *this->_moved = false;
    this->_indexControlledSquaresArr = KING_INDEX;
    this->_square.x = KING_X;
    this->_square.y = y;
    *kingLocation = &this->_square;

    startingUpdateArrs();
}

King::~King()
{
    delete this->_moved;
}

bool King::getMoved() const
{
    return *this->_moved;
}


bool King::checkValidMovement(const Square& target) const
{
    // checking if the target square is controlled by the enemy 
    if ((target.x <= this->_square.x + 1) && (target.x >= this->_square.x - 1)
        && (target.y <= this->_square.y + 1) && (target.y >= this->_square.y - 1)
        && !this->_enemyControlledSquares[target.y][target.x].count())
    {
        return true;
    }
    return false;
}

void King::updateThisPieceSquares(const Square& target) const
{
    // removing old controlled squares
    for (int i = -1; i < 2; i++)
    {
        for (int j = -1; j < 2; j++)
        {
            if (this->_square.x + j > -1 && this->_square.y + i > -1
                && this->_square.y + i < ROWS && this->_square.x + j < ROWS)
            {
                this->_myControlledSquares[this->_square.y + i][this->_square.x + j][this->_indexControlledSquaresArr] = BIT_OFF;
            }
        }
    }

    // adding new controlled squares
    for (int i = -1; i < 2; i++)
    {
        for (int j = -1; j < 2; j++)
        {
            if (target.x + j > -1 && target.y + i > -1
                && target.x + j < ROWS && target.y + i < ROWS)
            {
                this->_myControlledSquares[target.y + i][target.x + j][this->_indexControlledSquaresArr] = BIT_ON;
            }
        }
    }
}

bool King::castling(Square& target, Rook& rook)
{
    // checking if king or rook have moved
    if (*this->_moved == false || rook.getMoved() == false)
    {
        return false;
    }
    // checking if castling is legal
    for (int i = 1; i < abs(int(this->_square.x - target.x)); i++)
    {
        // for short castling
        if (this->_square.x - target.x > 0)
        {
            checkCastling(target, i);
        }
        // for long castling
        else
        {
            checkCastling(target, -i);
        }
    }
    // updating accordingly
    rook.updateThisPieceSquares(target);
    //rook.updateOtherSquares(target);
    this->updateThisPieceSquares(target);
    //this->updateOtherSquares(target);
    return true;
}

bool King::checkCastling(Square& target, int diff)
{
    // checking if in between the rook and the king there are pieces
    if (this->_board[this->_square.y][target.x + diff] == nullptr)
    {
        return false;
    }
    // checking if king is moving through enemy controlled squares
    if (diff != 1 && this->_enemyControlledSquares[this->_square.y][this->_square.x + diff].count() > 0)
    {
        return false;
    }
    return true;
}


void King::startingUpdateArrs() const
{
    // going around the king and turning all the bits around it
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


