#include "Knight.h"
#include <iostream>

Knight::Knight(const unsigned int& x, const unsigned int& y, const bool& color, Piece*** board, std::bitset<NUM_OF_PIECES>** myControlledSquares,
    std::bitset<NUM_OF_PIECES>** enemyControlledSquares, Square* kingLocation) : Piece(x, y, color, board, myControlledSquares, enemyControlledSquares, kingLocation)
{
    this->_indexControlledSquaresArr = STARTING_KNIGHT_INDEX + (x == SECOND_KNIGHT_COLUMNS);

    startingUpdateArrs();
}


bool Knight::checkValidMovement(const Square& target) const
{
    // the values of x and y in the arrays match each other:
    int possibleX[NUM_POSSIBILITIES] = { -2, -1, 1, 2, 2, 1, -1, -2 };
    int possibleY[NUM_POSSIBILITIES] = { 1, 2, 2, 1, -1, -2, -2, -1 };

    for (int i = 0; i < NUM_POSSIBILITIES; i++)
    {
        if (target.x == (this->_square.x + possibleX[i]) && target.y == (this->_square.y + possibleY[i]))
        {
            return true;
        }
    }

    return false;
}

void Knight::updateThisPieceSquares(const Square& target) const
{
    int possibleX[NUM_POSSIBILITIES] = { -2, -1, 1, 2, 2, 1, -1, -2 };
    int possibleY[NUM_POSSIBILITIES] = { 1, 2, 2, 1, -1, -2, -2, -1 };

    // removing old control over squares:
    for (int i = 0; i < NUM_POSSIBILITIES; i++)
    {
        if ((this->_square.x + possibleX[i]) > -1 && (this->_square.y + possibleY[i]) > -1 && 
            (this->_square.x + possibleX[i]) < COLUMNS && (this->_square.y + possibleY[i]) < ROWS)
        {
            this->_myControlledSquares[this->_square.y + possibleY[i]][this->_square.x + possibleX[i]][this->_indexControlledSquaresArr] = BIT_OFF;
        }
    }

    // adding new controlled squares:
    for (int i = 0; i < NUM_POSSIBILITIES; i++)
    {
        if ((target.x + possibleX[i]) > -1 && (target.y + possibleY[i]) > -1 && 
            (target.x + possibleX[i]) < COLUMNS && (target.y + possibleY[i]) < ROWS)
        {
            this->_myControlledSquares[target.y + possibleY[i]][target.x + possibleX[i]][this->_indexControlledSquaresArr] = BIT_ON;
        }
    }
}

void Knight::startingUpdateArrs() const
{
    // this var is holding the -1 if the knight is on the final row and it is holding 1 if the knight is on the first row 
    int auxiliaryVar = ((this->_square.y > 0) * -1) + (this->_square.y == 0);

    // 0 | N | 0 | 0
    // 0 | 0 | 0 | 1
    // 1 | 0 | 1 | 0
    // this part is turning on the bits that knight can move int its starting position for every knight it looks similar to 
    // what it is on the pic above
    this->_myControlledSquares[this->_square.y + (2 * auxiliaryVar)][this->_square.x + 1].set(this->_indexControlledSquaresArr);
    this->_myControlledSquares[this->_square.y + (2 * auxiliaryVar)][this->_square.x - 1].set(this->_indexControlledSquaresArr);
    this->_myControlledSquares[this->_square.y + auxiliaryVar][this->_square.x + (2 * (((this->_square.x == COLUMNS - 2) * -1) + (this->_square.x == 1)))].set(this->_indexControlledSquaresArr);

}